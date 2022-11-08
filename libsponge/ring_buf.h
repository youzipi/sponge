//
// Created by youzipi on 11/8/22.
//

#ifndef SPONGE_RING_BUF_H
#define SPONGE_RING_BUF_H

#include <string>

using namespace std;

class ring_buf {
  public:
    ring_buf(int capacity);
    ~ring_buf();
    bool is_full();
    bool is_empty();
    int insert(string data);
    //    int remove();
    char get(int index);
    char peek();
    /**
     * 待读取的部分
     * @return
     */
    int size() { return this->W - this->R; }
    int capacity() { return this->_capacity; }
    int *get_array();

  private:
    int _capacity;
    unsigned char *array;
    int W;
    int R;
};

#endif  // SPONGE_RING_BUF_H
