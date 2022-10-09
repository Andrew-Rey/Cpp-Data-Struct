#pragma once

#include "defs.h"
#include "PriorityDeque.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <random>
#include <cstdio>
#include <queue>

template<typename T>
class ExternalQS {
private:
    std::deque<T> input_buf;
    std::deque<T> small_buf;
    std::deque<T> large_buf;
public:
    PriorityDeque<T> *qs_queue; // middle

    std::string loc = "./data/target_file.txt";
    std::string temp_loc = "./data/temp_file.txt";

    ExternalQS() {
        qs_queue = new PriorityDeque<T>;
    }

    ~ExternalQS() = default;

    // generate rand number and write to txt
    void generate_rand(std::string &type_name,
                       int bottom, int top, int count);

    // read in data from txt, `p_file` is the tail of file
    void read_to_mid(int file_base, int buf_size, long long &p_file);

    // load data into input buffer
    void read_to_input(int file_base, int buf_size, long long &p_file);

    // write into disk when small or large memo is full
    void write(std::string &loc, std::deque<T> &buffer, int file_base, long long &p_file);

    // write temp_file to result_file
    void write_t2r(std::string &loc_result, std::string &loc_temp,
                   int file_base, int large_count, long long &p_file);

    // insert element into middle memo
    void replace(std::string &loc_result, std::string &loc_temp,
                 int &small_count, int &large_count,
                 long long &p_small, long long &p_large);

    // sort recursively and store the elements into txt
    void sort();

    // show the first elem_num elements of the result
    void show(int offset, int elem_num);
};

template<typename T>
void ExternalQS<T>::read_to_mid(int file_base, int buf_size, long long &p_file) {
    std::fstream read_file{loc, std::ios::in | std::ios::out};
    int read_count = 0;
    assert(read_file.is_open());
    read_file.seekg(file_base, std::ios::beg); // read from 0 + file_base
    for (read_count; read_count < buf_size && !read_file.eof(); ++read_count) {
        T temp;
        read_file >> temp;
        qs_queue->push(temp);
    }
    p_file = read_file.tellg();
    read_file.close();
}

template<typename T>
void ExternalQS<T>::read_to_input(int file_base, int buf_size, long long &p_file) {
    std::fstream read_file{loc, std::ios::in | std::ios::out};
    int read_count = 0;
    assert(read_file.is_open());
    read_file.seekg(file_base, std::ios::beg); // read from 0 + file_base
    for (read_count; read_count < buf_size && !read_file.eof(); ++read_count) {
        T temp;
        read_file >> temp;
        input_buf.push_back(temp);
    }
    p_file = read_file.tellg();
    read_file.close();
}

template<typename T>
void ExternalQS<T>::write(std::string &_loc, std::deque<T> &buffer, int file_base, long long &p_file) {
    if (buffer.empty())
        return;
    std::fstream write_file{_loc, std::ios::in | std::ios::out};
    assert(write_file.is_open() && write_file.good());
    write_file.seekp(file_base, std::ios::beg);
    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
        write_file << *it << "\t";
    }
    p_file = write_file.tellp();
    write_file.close();
    buffer.clear();
}

template<typename T>
void ExternalQS<T>::write_t2r(std::string &loc_result, std::string &loc_temp,
                              int file_base, int large_count, long long &p_file) {
    std::fstream result_file{loc_result, std::ios::in | std::ios::out};
    std::fstream temp_file{loc_temp, std::ios::in | std::ios::out};
    int read_count = 0;
    assert(result_file.is_open() && result_file.good() && temp_file.is_open() && temp_file.good());
    result_file.seekp(file_base, std::ios::beg);
    while (read_count < large_count && !temp_file.eof()) {
        T elem;
        temp_file >> elem;
        result_file << elem << "\t";
        read_count += 1;
    }
    p_file = result_file.tellp();
    result_file.close();
    temp_file.close();
}

template<typename T>
void ExternalQS<T>::replace(std::string &loc_result, std::string &loc_temp,
                            int &small_count, int &large_count,
                            long long &p_small, long long &p_large) {
    // the input two pointers means where to start
    // the return of the two pointers means the size
    if (input_buf.empty()) {
        return;
    }

    std::fstream result_file{loc_result, std::ios::in | std::ios::out};
    std::fstream temp_file{loc_temp, std::ios::in | std::ios::out};

    bool flag = false; // used for change min or max in middle_buf, false--min, true--max

    while (!input_buf.empty()) {
        T mid_max = qs_queue->getMax();
        T mid_min = qs_queue->getMin();

        T input_elem = input_buf.front();
        input_buf.pop_front();

        if (small_buf.size() == SMALL_SIZE) {
            // small_buf write to result file
            small_count += SMALL_SIZE;
            write(loc, small_buf, p_small, p_small);
        }
        if (large_buf.size() == LARGE_SIZE) {
            // large_buf write to temp file, write to result file after middle data is written
            large_count += LARGE_SIZE;
            write(temp_loc, large_buf, p_large, p_large);
        }
        if (input_elem < mid_min) {
            // write back the small part when small_buf is full
            small_buf.push_back(input_elem);
        } else if (input_elem > mid_max) {
            // write back the large part when large_buf is full or all data has been detected
            large_buf.push_back(input_elem);
        } else {
            if (qs_queue->getElemCount() == MIDDLE_SIZE) {
                if (flag) {
                    T pop_min = qs_queue->getMin();
                    small_buf.push_back(qs_queue->getMin());
                    qs_queue->popMin();
                    flag = false;
                } else {
                    T pop_max = qs_queue->getMax();
                    large_buf.push_back(qs_queue->getMax());
                    qs_queue->popMax();
                    flag = true;
                }
                qs_queue->push(input_elem);
            }
        }
    }
    result_file.close();
    temp_file.close();
}

template<typename T>
void ExternalQS<T>::sort() {
    std::deque<int> indices;
    std::deque<long long> file_locs;      // storage the file pointers
    indices.push_front(0);             // storage left flag
    indices.push_back(DATA_SIZE - 1);  // storage right flag
    file_locs.push_front(0);

    while (!indices.empty() && !file_locs.empty()) {
        int left = indices.front();
        int right = indices.back();
        indices.pop_front();
        indices.pop_back();

        int data_size = right - left + 1;

        long long file_base = file_locs.front();  // used for original file
        file_locs.pop_front();

        long long p_file = file_base;
        long long p_small = file_base; // used for write small to file
        long long p_large = 0; // used for write large to file

        int data_count = 0;
        int small_count = 0;
        int large_count = 0;
        int middle_size = std::min(data_size - data_count, MIDDLE_SIZE);
        read_to_mid(file_base, middle_size, p_file);
        data_count += qs_queue->getElemCount();

        while (data_count < data_size) {

            int input_size = std::min(data_size - data_count, INPUT_SIZE);
            read_to_input(p_file, input_size, p_file);
            data_count += input_buf.size();

            replace(loc, temp_loc,
                    small_count, large_count,
                    p_small, p_large);
        }
        small_count += small_buf.size();
        large_count += large_buf.size();
        write(loc, small_buf, p_small, p_small);
        write(temp_loc, large_buf, p_large, p_large);

        // the sequence of file_locs stack should be the same with indices
        p_file = p_small;
        qs_queue->write(loc, p_file, p_file);
        if (file_base < p_small) {
            file_locs.push_front(file_base);
        }
        p_large = p_file;
        write_t2r(loc, temp_loc, p_large, large_count, p_large);
        if (p_file < p_large) {
            file_locs.push_front(p_file);
        }

        // after all data has been detected, partition the small and large part again
        // closed intervals
        // if left part exists
        if (small_count > 0) {
            indices.push_front(left);
            indices.push_back(left + small_count - 1);
        }
        // if right part exists
        if (large_count > 0) {
            indices.push_front(right - large_count);
            indices.push_back(right);
        }
    }
}

template<typename T>
void ExternalQS<T>::show(int offset, int elem_num) {
    std::ifstream show_file{loc};
    assert(show_file.is_open() && show_file.good());
    show_file.seekg(offset, std::ios::beg);
    for (int i = 0; i < elem_num; ++i) {
        T elem;
        show_file >> elem;
        std::cout << elem << "\t";
    }
    std::cout << std::endl;
}

template<typename T>
void ExternalQS<T>::generate_rand(std::string &type_name, int bottom,
                                  int top, int count) {
    std::ofstream write_file{loc};
    assert(write_file.is_open() && write_file.good());
    std::default_random_engine generator(time(nullptr));
    if constexpr (std::is_integral<T>::value) { // confirm the type of data when compiling
        static std::uniform_int_distribution<T> rand_int(bottom, top);
        for (int i = 0; i < count; ++i) {
            T temp = rand_int(generator);
            write_file << temp << "\t";
        }
    } else {
        static_assert(std::is_floating_point<T>::value, "Real Number required.");
        static std::uniform_real_distribution<T> rand_real(bottom, top);
        for (int i = 0; i < count; ++i) {
            T temp = rand_real(generator);
            write_file << temp << "\t";
        }
    }
    write_file.close();
}