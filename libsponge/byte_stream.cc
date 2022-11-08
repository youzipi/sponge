#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : _buf(new ring_buf(capacity)) {}

size_t ByteStream::write(const string &data) {
    size_t written_cnt = this->_buf->try_write(data);
    return written_cnt;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    string s = this->_buf->peek(len);
    return s;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { this->_buf->pop(len); }

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    if (!eof()) {
        const string &str = peek_output(len);
        pop_output(len);
        return str;
    } else {
        return {};
    }
}

void ByteStream::end_input() { this->_input_ended = true; }

bool ByteStream::input_ended() const { return this->_input_ended; }

size_t ByteStream::buffer_size() const { return this->_buf->size(); }

bool ByteStream::buffer_empty() const { return this->_buf->is_empty(); }

bool ByteStream::eof() const { return this->input_ended() && this->buffer_empty(); }

size_t ByteStream::bytes_written() const { return this->_buf->write_total(); }

size_t ByteStream::bytes_read() const { return this->_buf->read_total(); }

size_t ByteStream::remaining_capacity() const { return this->_buf->capacity() - this->_buf->size(); }
