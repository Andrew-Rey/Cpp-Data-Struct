#pragma once

#include "Buffer.hpp"
#include "LoserTree.hpp"

namespace sortFunction {


    template<typename T>
    void restWrite_n(std::string &out_file_loc, std::string &in_file_loc,
                     long long &start_bytes, long long &write_bytes) {
        std::fstream source_file{out_file_loc, std::ios::in | std::ios::out | std::ios::binary};
        std::fstream target_file{in_file_loc, std::ios::in | std::ios::out | std::ios::binary};
        assert(target_file.is_open() && source_file.is_open());
        std::vector<T> temp(write_bytes / sizeof(T));
        source_file.seekp(start_bytes, std::ios::beg);
        target_file.seekg(start_bytes, std::ios::beg);
        source_file.read(reinterpret_cast<char *>(temp.data()), write_bytes);
        target_file.write(reinterpret_cast<const char *>(temp.data()), write_bytes);
        start_bytes += write_bytes;
        source_file.close();
        target_file.close();
    }


    // 2-way merge
    template<typename T>
    int defaultCompare(int buf_loc, Buffer<T> &cmp_buf, std::vector<T> values) {
        assert(!cmp_buf.empty() && !values.empty());
        int min_ind = 0;
        for (int ind = 0; ind < values.size(); ++ind) {
            if (values.at(min_ind) > values.at(ind)) {
                min_ind = ind;
            }
        }
        cmp_buf[buf_loc] = values.at(min_ind);
        return min_ind; // which input buffer
    }


    // 2-way merge
    template<typename T>
    void defaultCompareWrapper(std::string &file_A, std::string &file_B,
                               std::vector<Buffer<T> > &input_buf_,
                               Buffer<T> &output_buf_,
                               std::vector<long long> &seq_start_p_,
                               std::vector<long long> &seq_end_p_,
                               int &sequence_num_) {

        long long input_buf_size_ = input_buf_[0].size();
        long long compare_buf_size_ = output_buf_.size();
        std::vector<long long> reading_p = seq_start_p_;

        int buf_head = 0;
        int buf_tail = 0;
        int buf_limit = sequence_num_;

        std::vector<long long> next_start_p;
        std::vector<long long> next_end_p;
        next_end_p.push_back(std::ios::beg);

        // merge 的整数倍进行归并
        for (buf_tail = 1; buf_tail < buf_limit; buf_tail += 2) {
            buf_head = buf_tail - 1;
            for (int buf = buf_head; buf <= buf_tail; ++buf) {
                long long read_bytes = input_buf_size_ * sizeof(T);
                input_buf_[buf - buf_head].read_n(file_A, reading_p[buf], read_bytes);
            }

            std::vector<T> front_values;
            std::vector<T> front_indices(2, 0);

            for (int i = 0; i < 2; ++i) {
                int index = front_indices[i];
                front_values.push_back(input_buf_[i][index]);
            }
            int empty_seq = 0;
            int cmp_loc = 0;
            // 记录每一次归并结束后的写指针
            long long write_p = next_end_p.back();
            // 遍历范围内每一个seq, 直到全部归并完
            while (empty_seq != 2) {
                // 下一个被填充数的buffer
                int next_ind = defaultCompare(cmp_loc, output_buf_, front_values);
                cmp_loc += 1;
                // 若compare_buffer已满, 则写入, 并更新下一次指针
                if (cmp_loc == compare_buf_size_) {
                    long long write_bytes = std::min((long long) (compare_buf_size_ * sizeof(T)),
                                                     seq_end_p_.back() - write_p);
                    std::cout << output_buf_;
                    output_buf_.write_n(file_B, write_p, write_bytes);
                    // 更新compare buffer 的下标
                    cmp_loc = 0;
                }
                int in_buf_ind = front_indices[next_ind];
                // 当前buffer到达底部
                if (in_buf_ind == input_buf_[next_ind].size() - 1) {
                    // 当前input buffer对应的归并段有剩余, 继续读取归并段
                    if (reading_p[buf_head + next_ind] < seq_end_p_[buf_head + next_ind + 1]) {
                        // 计算合法区
                        long long read_bytes = std::min((long long) (input_buf_size_ * sizeof(T)),
                                                        seq_end_p_[buf_head + next_ind + 1] -
                                                        reading_p[buf_head + next_ind]);
                        input_buf_[next_ind].read_n(file_A, reading_p[buf_head + next_ind], read_bytes);
                        // 将非法读入的值为空
                        input_buf_[next_ind].tagEmpty(read_bytes / sizeof(T));
                        // 且将当前buffer下标修改为0
                        front_indices[next_ind] = 0;
                        in_buf_ind = 0;
                    } else {
                        // 无剩余则设为最大, 标志已空
                        input_buf_[next_ind].tagEmpty(0);
                        empty_seq += 1;
                        // 若归并段结束, 则更新下一次的写指针, 和归并段的数目
                        if (empty_seq == 2) {
                            next_end_p.push_back(write_p);
                            sequence_num_ = sequence_num_ - 1;
                        }
                    }
                } else {
                    // 未到达底部则相应的buffer中的下标+1
                    front_indices[next_ind] += 1;
                    in_buf_ind += 1;
                }
                // 更新front vector
                front_values[next_ind] = input_buf_[next_ind][in_buf_ind];
            }

        }

        // 已读的数据大于实际写入的数据, 说明缓存中还有未写入的数据
        if (reading_p.back() > next_end_p.back()) {
            long long write_bytes = reading_p.back() - next_end_p.back();
            output_buf_.write_n(file_B, next_end_p.back(), write_bytes);
        }

        // 剩余元素直接写入, 等待下一次归并, 更新下一次的指针
        if (next_end_p.back() < seq_end_p_.back()) {
            long long write_bytes = seq_end_p_.back() - next_end_p.back();
            long long start_bytes = next_end_p.back();
            // file_A > file_B
            restWrite_n<T>(file_A, file_B, start_bytes, write_bytes);
            next_end_p.push_back(start_bytes);
        }

        // 更新指针
        next_start_p = next_end_p;
        next_start_p.pop_back();

        seq_start_p_ = next_start_p;
        seq_end_p_ = next_end_p;

    }


    /*
     * typedef void(*sortFunc)(std::string &file_A, std::string &file_B,
                            std::vector<Buffer<T> > &input_buf_,
                            Buffer<T> &output_buf_,
                            std::vector<long long> &seq_start_p_,
                            std::vector<long long> &seq_end_p_,
                            int &sequence_num_);
     */

    // loser tree k-way merge
    template<typename T>
    void loserTreeCompare(std::string &file_A, std::string &file_B,
                          std::vector<Buffer<T> > &input_pipe,
                          Buffer<T> &output_buf,
                          std::vector<long long> &seq_start_p,
                          std::vector<long long> &seq_end_p,
                          int &sequence_num) {
        std::vector<long long> reading_p = seq_start_p;
        int input_num = input_pipe.size();
        int input_size = input_pipe[0].size();
        int output_size = output_buf.size();
        long long read_bytes = input_size * sizeof(T);
        long long write_bytes = input_pipe.size() * sizeof(T);
        long long file_size = seq_end_p.back();

        long long write_p = std::ios::beg;

        // initialize loser tree, the length of leaf is equal to sequence number
        LoserTree<T> lt(sequence_num);

        // record which input buffer needs to read new value or fill max value
        // 0: need to read, 1: normal, -1: fill with empty
        std::vector<int> input_state(input_num, 0);

        // record pointers in input buffers
        std::vector<int> input_idx(input_num, 0);

        auto update_input = [&]() {
            for (int i = 0; i < input_num; ++i) {
                if (input_state[i] == 0) {
                    read_bytes = std::min(seq_end_p[i + 1] - reading_p[i], (long long) (input_size * sizeof(T)));
                    input_pipe[i].read_n(file_A, reading_p[i], read_bytes);
                    std::cout << "input buf " << i << "read: " << std::endl << input_pipe[i] << std::endl;
                    input_state[i] = 0;
                } else if (input_state[i] == -1) {
                    input_pipe[i].tagEmpty(0);
                    input_state[i] = 0;
                } else {
                    return;
                }
            }
        };

        auto init_lt = [&]() {
            Buffer<T> temp(sequence_num);
            temp.read_n(file_A, read)
        };

        auto update_lt = [&](T &pop_value, int &pop_idx) {
            // get pop value and input buffer index
            pop_idx = lt.getMin();
            pop_value = lt[pop_idx];
            std::cout << "lt pop: " << pop_value << std::endl;
            if (input_idx[pop_idx] == input_size) {
                input_state[pop_idx] = -1;
                if (reading_p[pop_idx] < seq_end_p[pop_idx + 1]) {
                    input_state[pop_idx] = 0;
                }
            }
            // update loser tree
            input_idx[pop_idx] += 1;
            int in_input_idx = input_idx[pop_idx];
            lt[pop_idx] = input_pipe[pop_idx][in_input_idx];
            lt.adjust(pop_idx);
        };

        auto update_out = [&](int output_idx, T value) {
            output_buf[output_idx] = value;
            if (output_idx == output_size - 1) {
                write_bytes = output_size * sizeof(T);
                std::cout << "write buf " << output_buf << std::endl;
                output_buf.write_n(file_B, write_p, write_bytes);
            } else if (write_p == file_size) {
                write_bytes = file_size - write_p;
                output_buf.write_n(file_B, write_p, write_bytes);
                std::cout << "write buf " << output_buf << std::endl;
            }
        };

        int output_idx = 0;
        // loop when there are values haven't been written
        while (write_p < file_size) {
            // write just one value for every loop
            // check every input buffer's state
            update_input();

            // update loser tree
            T pop_value = 0;
            int pop_idx = 0;
            update_lt(pop_value, pop_idx);

            // write to output buffer and write to file if needed
            update_out(output_idx, pop_value);
            output_idx += 1;
        }

        sequence_num = 1;
    }

}