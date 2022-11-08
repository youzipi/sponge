//
// Created by youzipi on 11/8/22.
//
/**
 * ref: https://www.eet-china.com/mp/a49640.html
 */

#include "ring_buf.hh"

#include "stdio.h"

#include <iostream>
using namespace std;

/**
 * 写指针，赶上了 读指针，标志着 ring buffer 满了
 * 实际上，此时，写指针和读指针，指向相同的位置，写指针领先了一轮，套圈了。
 * @param p_ring_buf
 * @return
 */
bool ring_buf::is_full() {
    if (this->W - this->R == this->_capacity) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 读指针，赶上了 写指针，标志着 ring_buf 为空
 * @param p_ring_buf
 * @return
 */
bool ring_buf::is_empty() { return this->size() == 0; }

size_t ring_buf::try_write(string data) {
    int w_before = this->W;
    for (char c : data) {
        if (this->W - this->R == this->_capacity) {
            break;
        } else {
            // 可以写
            cout << "inserting " << c << " at " << this->W << endl;
            int w = this->W + 1;
            int idx = w % this->_capacity;
            this->array[idx] = c;
            this->W += w;
        }
    }
    int w_after = this->W;
    int written_cnt = w_after - w_before;
    cout << "[insert] data=" << data.substr(0, written_cnt) << ", W=" << this->W << ", R=" << this->R << endl;
    return written_cnt;
}

void ring_buf::try_remove(size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (this->R == this->W) {
            break;
        } else {
            int r = this->R + 1;
            cout << "removing idx=" << this->R << endl;
            this->R += r;
        }
    }
}

size_t ring_buf::write(string data) {
    size_t expect = data.length();
    size_t available = this->capacity() - this->size();
    if (expect > available) {
        cout << "[insert] space is not enough, expect " << expect << " but only " << available << " available." << endl;
        return -2;
    }

    size_t idx_start = this->W % this->_capacity;
    size_t idx = idx_start;
    for (char c : data) {
        cout << "inserting " << c << " at " << idx << endl;
        this->array[idx] = c;
        idx = (idx + 1) % this->_capacity;
    }
    size_t idx_end = idx;
    this->W += expect;
    cout << "[insert] data=" << data << ", idx_start=" << idx_start << ", idx_end=" << idx_end << ", W=" << this->W
         << ", R=" << this->R << endl;
    return 0;
}

char ring_buf::get(size_t index) {
    if (this->is_empty() == 1) {
        printf("buf is empty\n");
        return -1;
    }
    size_t idx = (index) % this->_capacity;
    cout << "[get] index=" << index << ", W=" << this->W << ", R=" << this->R << endl;
    return this->array[idx];
}

string ring_buf::read(size_t n) {
    int to_read = n;
    string s = string();
    while ((to_read > 0) && (this->R < this->W)) {
        int idx = this->R % this->capacity();
        s.push_back(this->array[idx]);
        this->R += 1;
        to_read -= 1;
    }
    return s;
}

char ring_buf::peek() {
    if (this->is_empty() == 1) {
        printf("buf is empty\n");
        return '#';
    }
    size_t idx = (this->R) % this->capacity();
    cout << "[peek] index=" << idx << ", W=" << this->W << ", R=" << this->R << endl;
    this->R += 1;
    return this->array[idx];
}

//int main() {
//    ring_buf *buf = new ring_buf(10);
//    for (size_t i = 0; i < 20; i++) {
//        buf->write(to_string(i * 10 + i));
//    }
//    for (size_t i = 0; i < 20; i++) {
//        char data = buf->peek();
//        cout << "data=" << data << endl;
//    }
//    return 0;
//}