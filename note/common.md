https://tarplkpqsm.feishu.cn/docx/doxcnpBEN4SG3vA9pVyCoANigBh

告警：

```bash
warning: range-based for loop is a C++11 extension [-Wc++11-extensions]
```

A:
`-std=c++11`

```bash
c++ ring_buf.cpp -std=c++11
```



## pass lab0 test
```bash
make check_lab0
[100%] Testing Lab 0...
Test project /home/yzp/projects/0/sponge/build
    Start 26: t_byte_stream_construction
1/9 Test #26: t_byte_stream_construction .......   Passed    0.00 sec
    Start 27: t_byte_stream_one_write
2/9 Test #27: t_byte_stream_one_write ..........   Passed    0.00 sec
    Start 28: t_byte_stream_two_writes
3/9 Test #28: t_byte_stream_two_writes .........   Passed    0.00 sec
    Start 29: t_byte_stream_capacity
4/9 Test #29: t_byte_stream_capacity ...........   Passed    1.04 sec
    Start 30: t_byte_stream_many_writes
5/9 Test #30: t_byte_stream_many_writes ........   Passed    0.06 sec
    Start 31: t_webget
6/9 Test #31: t_webget .........................   Passed    1.02 sec
    Start 53: t_address_dt
7/9 Test #53: t_address_dt .....................   Passed    0.02 sec
    Start 54: t_parser_dt
8/9 Test #54: t_parser_dt ......................   Passed    0.01 sec
    Start 55: t_socket_dt
9/9 Test #55: t_socket_dt ......................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 9

Total Test time (real) =   2.60 sec
[100%] Built target check_lab0
```