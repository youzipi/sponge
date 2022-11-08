//
// Created by youzipi on 11/8/22.
//

#ifndef SPONGE_RING_BUF_HH
#define SPONGE_RING_BUF_HH

#include <string>
#include <vector>

using namespace std;

class ring_buf {
  public:
    explicit ring_buf(size_t capacity) : _capacity(capacity), array(vector<char>(capacity)), W(0), R(0) {}
    ~ring_buf() { delete this; }
    bool is_full();
    bool is_empty();
    size_t write(string data);
    size_t try_write(string data);
    void try_remove(size_t n);
    //    int remove();
    char get(size_t index);
    string read(size_t n);
    char peek();
    /**
     * 待读取的部分
     * @return
     */
    size_t size() { return this->W - this->R; }
    size_t capacity() { return this->_capacity; }
    size_t write_total() { return this->W; }
    size_t read_total() { return this->R; }
    int *get_array();

  private:
    size_t _capacity;
    vector<char> array;
    size_t W;
    size_t R;
};

#endif  // SPONGE_RING_BUF_HH
