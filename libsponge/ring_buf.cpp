//
// Created by youzipi on 11/8/22.
//
/**
 * ref: https://www.eet-china.com/mp/a49640.html
 */

#include "ring_buf.h"

#include "stdio.h"

#include <iostream>
using namespace std;

ring_buf::ring_buf(int capacity) {
    this->_capacity = capacity;
    this->array = new unsigned char[capacity];
    this->W = 0;
    this->R = 0;
}

ring_buf::~ring_buf() { delete this; }

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
bool ring_buf::is_empty() {
    if (this->W == this->R) {
        return 1;
    } else {
        return 0;
    }
}

int ring_buf::insert(string data) {
    int expect = data.length();
    int available = this->capacity() - this->size();
    if (expect > available) {
        cout << "[insert] space is not enough, expect " << expect << " but only " << available << " available." << endl;
        return -2;
    }

    int idx_start = this->W % this->_capacity;
    int idx = idx_start;
    for (char c : data) {
        cout << "inserting " << c << " at " << idx << endl;
        this->array[idx] = c;
        idx = (idx + 1) % this->_capacity;
    }
    int idx_end = idx;
    this->W += expect;
    cout << "[insert] data=" << data << ", idx_start=" << idx_start << ", idx_end=" << idx_end << ", W=" << this->W
         << ", R=" << this->R << endl;
    return 0;
}

char ring_buf::get(int index) {
    if (this->is_empty() == 1) {
        printf("buf is empty\n");
        return -1;
    }
    int idx = (index) % this->_capacity;
    cout << "[get] index=" << index << ", W=" << this->W << ", R=" << this->R << endl;
    return this->array[idx];
}

char ring_buf::peek() {
    if (this->is_empty() == 1) {
        printf("buf is empty\n");
        return -1;
    }
    int idx = (this->R) % this->capacity();
    cout << "[peek] index=" << idx << ", W=" << this->W << ", R=" << this->R << endl;
    this->R += 1;
    return this->array[idx];
}

int main() {
    ring_buf *buf = new ring_buf(10);
    for (int i = 0; i < 20; i++) {
        buf->insert(to_string(i * 10 + i));
    }
    for (int i = 0; i < 20; i++) {
        char data = buf->peek();
        cout << "data=" << data << endl;
    }
    return 0;
}