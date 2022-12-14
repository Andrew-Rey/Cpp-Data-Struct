#pragma once

#include <deque>
#include <queue>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <iostream>
#include "defs.h"

template<typename T>
struct node {
    T left;
    T right;
    bool lNull;
    bool rNull;
};

template<typename T>
class PriorityDeque {
private:
    int elemCount;
public:
    std::deque<node<T> > Deque;

    PriorityDeque();

    ~PriorityDeque();

    // insert elem in back node
    void push(T elem);

    // delete the max elem and adjust the structure
    void popMax();

    // delete the min elem and adjust the structure
    void popMin();

    // rebuild the construct of interval heap
    void adjust();

    // write the middle part to file/disk
    void write(const std::string &loc, int file_base, long long &p_file);

    // return the max elem
    T getMax();

    // return the min elem
    T getMin();

    // return the elem number
    int getElemCount();
};

template<typename T>
PriorityDeque<T>::PriorityDeque() {
    elemCount = 0;
}

template<typename T>
PriorityDeque<T>::~PriorityDeque() = default;

template<typename T>
void PriorityDeque<T>::adjust() {
    if (elemCount == 0) {
        return;
    } else {
        if (Deque.size() == 1 && !Deque.front().lNull && !Deque.front().rNull &&
            Deque.front().left > Deque.front().right) {
            std::swap(Deque.front().left, Deque.front().right);
            return;
        }
        int child;
        int parent;
        for (child = Deque.size() - 1, parent = (Deque.size() - 2) / 2;
             child > parent && parent >= 0;
             child = parent, parent = (parent - 1) / 2) {

            if (Deque.at(child).left > Deque.at(child).right &&
                !Deque.at(child).lNull &&
                !Deque.at(child).rNull) {
                // both right and left isn't null, left > right
                std::swap(Deque.at(child).left, Deque.at(child).right);
            }

            if (Deque.at(child).right > Deque.at(parent).right &&
                !Deque.at(child).rNull) {
                // compare right value when:
                // child.right is not null
                std::swap(Deque.at(child).right, Deque.at(parent).right);
            } else if (Deque.at(child).left < Deque.at(parent).left &&
                       !Deque.at(child).lNull) {
                // compare left value when:
                // child.left is not null
                std::swap(Deque.at(child).left, Deque.at(parent).left);
            } else {
                break;
            }
        }
    }
}

template<typename T>
void PriorityDeque<T>::push(T elem) {
    int init = 0;
    if (elemCount == 0) {
        node<T> newNode;
        Deque.push_back(newNode);
        Deque.back().left = elem;
        Deque.back().right = *(T *) &init;
        Deque.back().rNull = true;
        Deque.back().lNull = false;
        elemCount += 1;
        return;
    } else if (elemCount % 2 == 0) {
        node<T> newNode;
        Deque.push_back(newNode);
        int parent = (Deque.size() - 2) / 2;
        if (elem > Deque.at(parent).right) {
            Deque.back().right = elem;
            Deque.back().rNull = false;
            Deque.back().left = *(T *) &init;
            Deque.back().lNull = true;
        } else {
            // default, insert in left
            Deque.back().left = elem;
            Deque.back().lNull = false;
            Deque.back().right = *(T *) &init;
            Deque.back().rNull = true;
        }
        elemCount += 1;
    } else {
        // elemCount % 2 == 1
        if (Deque.back().lNull) {
            Deque.back().left = elem;
            Deque.back().lNull = false;
        } else {
            Deque.back().right = elem;
            Deque.back().rNull = false;
        }
        elemCount += 1;
    }
    adjust();
}

template<typename T>
void PriorityDeque<T>::popMax() {
    if (Deque.empty()) {
        throw std::runtime_error("empty Deque can't popMax");
    }
    if (Deque.size() == 1 && elemCount == 1) {
        Deque.pop_front();
        elemCount -= 1;
        return;
    } else if (Deque.size() == 1 && elemCount == 2) {
        int init = 0;
        Deque.front().right = *(T *) &init;
        Deque.front().rNull = true;
        elemCount -= 1;
        return;
    } else {
        if (elemCount % 2 == 0) {
            int init = 0;
            Deque.front().right = Deque.back().right;
            Deque.back().right = *(T *) &init;
            Deque.back().rNull = true;
            elemCount -= 1;
        } else {
            if (!Deque.back().rNull) {
                Deque.front().right = Deque.back().right;
                Deque.pop_back();
                elemCount -= 1;
            } else {
                Deque.front().right = Deque.at(Deque.size() - 2).right;
                Deque.at(Deque.size() - 2).right = Deque.back().left;
                Deque.pop_back();
                elemCount -= 1;
                adjust();
            }
        }
        // rebuild from top to bottom
        int parent = 0;
        int lchild = parent * 2 + 1;
        int rchild = parent * 2 + 2;
        int next = parent;
        while (lchild < Deque.size()) {
            if (Deque.at(lchild).right > Deque.at(parent).right && !Deque.at(lchild).rNull) {
                next = lchild;
            }
            if (rchild < Deque.size() &&
                Deque.at(rchild).right > Deque.at(parent).right &&
                Deque.at(lchild).right < Deque.at(rchild).right &&
                !Deque.at(rchild).rNull) {
                next = rchild;
            }
            if (parent != next) {
                std::swap(Deque.at(parent).right, Deque.at(next).right);
                if (Deque.at(next).left > Deque.at(next).right) {
                    std::swap(Deque.at(next).left, Deque.at(next).right);
                }
            } else {
                break;
            }
            parent = next;
            lchild = parent * 2 + 1;
            rchild = parent * 2 + 2;
        }
        return;
    }
}

template<typename T>
void PriorityDeque<T>::popMin() {
    if (Deque.empty()) {
        throw std::runtime_error("empty Deque can't popMax");
    }
    if (Deque.size() == 1 && elemCount == 1) {
        Deque.pop_front();
        elemCount -= 1;
        return;
    } else if (Deque.size() == 1 && elemCount == 2) {
        int init = 0;
        Deque.front().left = Deque.front().right;
        Deque.front().right = *(T *) &init;
        Deque.front().rNull = true;
        elemCount -= 1;
        return;
    } else {
        if (elemCount % 2 == 0) {
            int init = 0;
            Deque.front().left = Deque.back().left;
            Deque.back().left = *(T *) &init;
            Deque.back().lNull = true;
            elemCount -= 1;
        } else {
            if (!Deque.back().lNull) {
                Deque.front().left = Deque.back().left;
                Deque.pop_back();
                elemCount -= 1;
            } else {
                // back node has no left, has only right part
                Deque.front().left = Deque.at(Deque.size() - 2).left;
                Deque.at(Deque.size() - 2).left = Deque.back().right;
                Deque.pop_back();
                elemCount -= 1;
                adjust();
            }
        }
        // rebuild from top to bottom
        int parent = 0;
        int lchild = parent * 2 + 1;
        int rchild = parent * 2 + 2;
        int next = parent;
        while (lchild < Deque.size()) {
            if (Deque.at(lchild).left < Deque.at(parent).left && !Deque.at(lchild).lNull) {
                next = lchild;
            }
            if (rchild < Deque.size() &&
                Deque.at(rchild).left < Deque.at(parent).left &&
                Deque.at(rchild).left < Deque.at(lchild).left &&
                !Deque.at(rchild).lNull) {
                next = rchild;
            }
            if (next != parent) {
                std::swap(Deque.at(parent).left, Deque.at(next).left);
                if (Deque.at(next).left > Deque.at(next).right) {
                    std::swap(Deque.at(next).left, Deque.at(next).right);
                }
            } else {
                break;
            }
            parent = next;
            lchild = parent * 2 + 1;
            rchild = parent * 2 + 2;
        }
        return;
    }
}

template<typename T>
T PriorityDeque<T>::getMax() {
    if (Deque.empty()) {
        throw std::runtime_error("empty Deque can't getMax!");
    }
    return Deque.front().right;
}

template<typename T>
T PriorityDeque<T>::getMin() {
    if (Deque.empty()) {
        throw std::runtime_error("empty Deque can't getMin");
    }
    return Deque.front().left;
}

template<typename T>
int PriorityDeque<T>::getElemCount() {
    return elemCount;
}

template<typename T>
void PriorityDeque<T>::write(const std::string &loc, int file_base, long long &p_file) {
    if (Deque.empty()) {
        return;
    }
    std::fstream write_file{loc, std::ios::in | std::ios::out};
    assert(write_file.is_open() && write_file.good());
    write_file.seekp(file_base, std::ios::beg);
    while (!Deque.empty()) {
        T value = getMin();
        popMin();
        write_file << value << "\t";
    }
    p_file = write_file.tellp();
    write_file.close();
    Deque.clear();
}