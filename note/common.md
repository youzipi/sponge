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