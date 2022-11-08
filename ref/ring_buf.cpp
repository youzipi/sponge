//
// Created by youzipi on 11/8/22.
//
/**
 * ref: https://www.eet-china.com/mp/a49640.html
 */

#include "stdio.h"
#include "stdlib.h"
#define LEN 10

typedef struct ring_buf {
    int array[LEN];
    int W;
    int R;
} * ring;

struct ring_buf *ring_buf_init() {
    auto *_ring = static_cast<ring_buf *>(malloc(sizeof(struct ring_buf)));
    _ring->W = 0;
    _ring->R = 0;
    return _ring;
}

/**
 * 写指针，赶上了 读指针，标志着 ring buffer 满了
 * 实际上，此时，写指针和读指针，指向相同的位置，写指针领先了一轮，套圈了。
 * @param p_ring_buf
 * @return
 */
bool get_ring_buf_full_state(struct ring_buf *p_ring_buf) {
    if (p_ring_buf->W - p_ring_buf->R == LEN) {
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
int get_ring_buf_empty_state(struct ring_buf *p_ring_buf) {
    if (p_ring_buf->W == p_ring_buf->R) {
        return 1;
    } else {
        return 0;
    }
}

int ring_buf_insert(struct ring_buf *p_ring_buf, int data) {
    if (p_ring_buf == nullptr) {
        printf("buf is null\n");
        return -1;
    }
    if (get_ring_buf_full_state(p_ring_buf) == 1) {
        printf("buf is full\n");
        return -2;
    }
    int idx = p_ring_buf->W % LEN;
    p_ring_buf->array[idx] = data;
    p_ring_buf->W += 1;
    printf("[write] data=%d idx=%d, w=%d\n", data, idx, p_ring_buf->W);
    return 0;
}

int ring_buf_get(struct ring_buf *p_ring_buf, int *data) {
    if (p_ring_buf == nullptr) {
        printf("buf is null\n");
        return -1;
    }
    if (get_ring_buf_empty_state(p_ring_buf) == 1) {
        printf("buf is empty\n");
        return -2;
    }
    int idx = p_ring_buf->R % LEN;
    *data = p_ring_buf->array[idx];
    p_ring_buf->R += 1;
    printf("[get] data=%d idx=%d, r=%d\n", *data, idx, p_ring_buf->R);
    return 0;
}

//int main() {
//    auto *ring_buf = ring_buf_init();
//    for (int i = 0; i < 20; i++) {
//        ring_buf_insert(ring_buf, i);
//    }
//    for (int i = 0; i < 20; i++) {
//        int data;
//        ring_buf_get(ring_buf, &data);
//    }
//    return 0;
//}