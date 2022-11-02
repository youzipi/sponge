---
## 3.4 Writing webget
- libsponge/util
    - file descriptor.hh
    - socket.hh
    - address.hh

test

```bash
./apps/webget cs144.keithw.org /hello

make check_webget
```


## 4 An in-memory reliable byte stream


> Bytes are written on the “input” side and can be read, in the same sequence, from the “output” side. 
> The byte stream is finite: 
> the writer can end the input, and then no more bytes can be written. 
> When the reader has read to the end of the stream, it will reach “EOF” (end of file) and no more bytes can be read 
>

Your byte stream will also be `flow-controlled` to limit its memory consumption at any given time.

capacity: max number of bytes

> As the reader reads bytes and drains them from the stream, the writer is allowed to write more. 

ring buffer


具体地，要实现以下方法：
libsponge/byte_stream.hh
libsponge/byte_stream.cc


writer:
```cpp
// Write a string of bytes into the stream. Write as many
// as will fit, and return the number of bytes written.
size_t write(const std::string &data);

// Returns the number of additional bytes that the stream has space for
size_t remaining_capacity() const;

// Signal that the byte stream has reached its ending
void end_input();

// Indicate that the stream suffered an error
void set_error();
```


reader:
```cpp
// Peek at next "len" bytes of the stream
std::string peek_output(const size_t len) const;

// Remove ``len'' bytes from the buffer
void pop_output(const size_t len);

// Read (i.e., copy and then pop) the next "len" bytes of the stream
std::string read(const size_t len);

bool input_ended() const; // `true` if the stream input has ended
bool eof() const; // `true` if the output has reached the ending
bool error() const; // `true` if the stream has suffered an error
size_t buffer_size() const; // the maximum amount that can currently be peeked/read
bool buffer_empty() const; // `true` if the buffer is empty

size_t bytes_written() const; // Total number of bytes written
size_t bytes_read() const; // Total number of bytes popped
```


