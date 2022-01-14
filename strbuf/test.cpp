#include "strbuf.h"
#include <cstring>
#include <gtest/gtest.h>


// 获取由 malloc 类函数分配的 buf 的大小
// 本函数依赖 ptmalloc 实现
size_t getChunkSize(const void *pr) {
    size_t size = *(const size_t *) ((char *) pr - sizeof(size_t));
    return size & (~3);
}

// 本函数依赖 ptmalloc 实现
size_t getChunkFd(const void *pr) { return *(const size_t *) pr; }


// 不要在意这些常量
#define SIZE_SZ (sizeof(size_t))
#define MALLOC_ALIGNMENT (2 * SIZE_SZ < __alignof__(long double) \
                                  ? __alignof__(long double)     \
                                  : 2 * SIZE_SZ)
#define MIN_CHUNK_SIZE (4 * SIZE_SZ)

#define MALLOC_ALIGN_MASK (MALLOC_ALIGNMENT - 1)
#define MINSIZE \
    (unsigned long) (((MIN_CHUNK_SIZE + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK))

#define request2size(req) \
    (((req) + SIZE_SZ + MALLOC_ALIGN_MASK < MINSIZE) ? MINSIZE : ((req) + SIZE_SZ + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK)

//若一个由 malloc/realloc/calloc 申请的 buf 的大小一定不为 size 则返回 false，否则返回 true
// char * pr= malloc(0x20);
// AssertBufSize(pr , 0x20) 返回 true
// AssertBufSize(pr , 0x30) 返回 false
// 本函数依赖 ptmalloc 实现
#define AssertBufSize(pr, size) ASSERT_EQ(getChunkSize(pr), request2size(size))

// 2A
TEST(strbufA, init1) {
    strbuf t;
    strbuf_init(&t, 0x10);
    ASSERT_EQ(t.alloc, 0x10);
    ASSERT_EQ(t.len, 0);
    AssertBufSize(t.buf, 0x10);
}

TEST(strbufA, init2) {
    strbuf t;
    strbuf_init(&t, 0x20);
    ASSERT_EQ(t.alloc, 0x20);
    ASSERT_EQ(t.len, 0);
    AssertBufSize(t.buf, 0x20);
}

TEST(strbufA, init3) {
    strbuf t;
    strbuf_init(&t, 0x5);
    ASSERT_EQ(t.alloc, 0x5);
    ASSERT_EQ(t.len, 0);
    AssertBufSize(t.buf, 0x5);
}

TEST(strbufA, init4) {
    strbuf t;
    strbuf_init(&t, 0x0);
    ASSERT_EQ(t.alloc, 0x0);
    ASSERT_EQ(t.len, 0);
    AssertBufSize(t.buf, 0x0);
}
TEST(strbufA, attach1) {

    strbuf t;
    char *a = (char *) malloc(0x10);
    strcpy(a, "1234");
    strbuf_attach(&t, a, 4, 0x10);
    ASSERT_EQ(t.len, 4);
    ASSERT_EQ(t.alloc, 0x10);
    ASSERT_EQ(t.buf, a);
    ASSERT_STREQ(t.buf, "1234");
}

TEST(strbufA, attach2) {
    strbuf t;
    char *a = (char *) malloc(0x18);
    strcpy(a, "123456789abcdef12234567");
    strbuf_attach(&t, a, 0x17, 0x20);
    ASSERT_EQ(t.alloc, 0x20);
    ASSERT_EQ(t.buf, a);
    ASSERT_EQ(t.len, 0x17);
    ASSERT_STREQ(t.buf, "123456789abcdef12234567");
}

TEST(strbufA, attach3) {
    strbuf t;
    char *a = (char *) malloc(0x18);
    char str[] = "123456789abcdef12234567";
    str[6] = '\0';
    memcpy(a, str, 0x17);
    strbuf_attach(&t, a, 0x17, 0x20);
    ASSERT_EQ(t.alloc, 0x20);
    ASSERT_EQ(t.buf, a);
    ASSERT_EQ(t.len, 0x17);
    int ret = memcmp(t.buf, str, 0x17);
    ASSERT_EQ(ret, 0);
}
TEST(strbufA, release1) {
    strbuf t;
    char *a = (char *) malloc(0x18);
    strcpy(a, "123456789abcdef12234567");
    strbuf_attach(&t, a, 0x17, 0x20);
    //测试内存是否被释放
    size_t backUp = getChunkFd(t.buf);
    strbuf_release(&t);
    if (t.buf != nullptr) {
        size_t fd = getChunkFd(t.buf);
        ASSERT_NE(backUp, fd);
    }
    strbuf_init(&t, 0x20);
    ASSERT_EQ(t.alloc, 0x20);
    ASSERT_EQ(t.len, 0);
}

TEST(strbufA, swap1) {
    char *buf[2];
    buf[0] = (char *) malloc(0x20);
    buf[1] = (char *) malloc(0x30);
    strcpy(buf[0], "123456");
    strcpy(buf[1], "abcdefg");
    strbuf t[2];
    strbuf_attach(&t[0], buf[0], 6, 0x20);
    strbuf_attach(&t[1], buf[1], 7, 0x30);

    strbuf_swap(t, t + 1);

    ASSERT_EQ(t[0].alloc, 0x30);
    ASSERT_EQ(t[0].len, 7);
    ASSERT_EQ(t[0].buf, buf[1]);
    ASSERT_STREQ(t[0].buf, "abcdefg");
    AssertBufSize(t[0].buf, 0x30);

    ASSERT_EQ(t[1].alloc, 0x20);
    ASSERT_EQ(t[1].len, 6);
    ASSERT_EQ(t[1].buf, buf[0]);
    ASSERT_STREQ(t[1].buf, "123456");
    AssertBufSize(t[1].buf, 0x20);
}

TEST(strbufA, detach1) {
    strbuf t;
    char *a = (char *) malloc(0x10);
    strcpy(a, "1234");
    strbuf_attach(&t, a, 4, 0x10);
    size_t size;
    char *ret = strbuf_detach(&t, &size);
    ASSERT_EQ(0x10, size);
    ASSERT_EQ(ret, a);
    ASSERT_STREQ(ret, "1234");
}

TEST(strbufA, cmp1) {
    char *buf[2];
    buf[0] = (char *) malloc(0x20);
    buf[1] = (char *) malloc(0x30);
    strcpy(buf[0], "123456");
    strcpy(buf[1], "abcdefg");
    strbuf t[2];
    strbuf_attach(&t[0], buf[0], 6, 0x20);
    strbuf_attach(&t[1], buf[1], 7, 0x30);

    ASSERT_TRUE(strbuf_cmp(&t[0], &t[1]) != 0);

    ASSERT_EQ(t[0].alloc, 0x20);
    ASSERT_EQ(t[0].len, 6);
    ASSERT_EQ(t[0].buf, buf[0]);
    ASSERT_STREQ(t[0].buf, "123456");
    AssertBufSize(t[0].buf, 0x20);

    ASSERT_EQ(t[1].alloc, 0x30);
    ASSERT_EQ(t[1].len, 7);
    ASSERT_EQ(t[1].buf, buf[1]);
    ASSERT_STREQ(t[1].buf, "abcdefg");
    AssertBufSize(t[1].buf, 0x30);
}

TEST(strbufA, cmp2) {

    char *buf[2];
    buf[0] = (char *) malloc(0x20);
    buf[1] = (char *) malloc(0x30);
    strcpy(buf[0], "123456");
    strcpy(buf[1], "123456");
    strbuf t[2];
    strbuf_attach(&t[0], buf[0], 6, 0x20);
    strbuf_attach(&t[1], buf[1], 6, 0x30);

    ASSERT_TRUE(strbuf_cmp(&t[0], &t[1]) == 0);

    ASSERT_EQ(t[0].alloc, 0x20);
    ASSERT_EQ(t[0].len, 6);
    ASSERT_EQ(t[0].buf, buf[0]);
    ASSERT_STREQ(t[0].buf, "123456");
    AssertBufSize(t[0].buf, 0x20);

    ASSERT_EQ(t[1].alloc, 0x30);
    ASSERT_EQ(t[1].len, 6);
    ASSERT_EQ(t[1].buf, buf[1]);
    ASSERT_STREQ(t[1].buf, "123456");
    AssertBufSize(t[1].buf, 0x30);
}

TEST(strbufA, cmp3) {

    char *buf[2];
    buf[0] = (char *) malloc(0x20);
    buf[1] = (char *) malloc(0x20);
    strcpy(buf[0], "123456");
    strcpy(buf[1], "123");
    strbuf t[2];
    strbuf_attach(&t[0], buf[0], 6, 0x20);
    strbuf_attach(&t[1], buf[1], 3, 0x20);

    ASSERT_TRUE(strbuf_cmp(&t[0], &t[1]) != 0);

    ASSERT_EQ(t[0].alloc, 0x20);
    ASSERT_EQ(t[0].len, 6);
    ASSERT_EQ(t[0].buf, buf[0]);
    ASSERT_STREQ(t[0].buf, "123456");
    AssertBufSize(t[0].buf, 0x20);

    ASSERT_EQ(t[1].alloc, 0x20);
    ASSERT_EQ(t[1].len, 3);
    ASSERT_EQ(t[1].buf, buf[1]);
    ASSERT_STREQ(t[1].buf, "123");
    AssertBufSize(t[1].buf, 0x20);
}
TEST(strbufA, reset1) {
    strbuf t;
    char *a = (char *) malloc(0x10);
    strcpy(a, "1234");
    strbuf_attach(&t, a, 4, 0x10);
    strbuf_reset(&t);
    ASSERT_EQ(t.len, 0);
    ASSERT_EQ(t.alloc, 0x10);
    AssertBufSize(t.buf, 0x10);
}

TEST(strbufA, reset2) {
    strbuf t;
    char *a = (char *) malloc(0x10);
    strcpy(a, "1234");
    strbuf_attach(&t, a, 4, 0x10);
    strbuf_reset(&t);
    ASSERT_EQ(t.len, 0);
    ASSERT_EQ(t.alloc, 0x10);
    AssertBufSize(t.buf, 0x10);
}
// 2B测试代码

// strbuf_grow，将sb的长度扩大到extra
TEST(StrBufTest2B, grow) {
    strbuf sb;
    strbuf_init(&sb, 0);// init的第二个参数可以是0
    ASSERT_EQ(sb.alloc, 0);
    AssertBufSize(sb.buf, 0);
    strbuf_grow(&sb, 10);
    AssertBufSize(sb.buf, 10);
    ASSERT_EQ(sb.alloc, 10);
    strbuf_grow(&sb, 20);
    ASSERT_EQ(sb.alloc, 20);
    AssertBufSize(sb.buf, 20);
    strbuf_release(&sb);
}

// strbuf_add，向sb追加长度为len的数据data。
TEST(StrBufTest2B, add) {
    strbuf sb;
    strbuf_init(&sb, 20);
    strbuf_add(&sb, "hello", 5);
    int res = 0;
    res = memcmp((void *) "hello", (void *) sb.buf, 5);
    ASSERT_EQ(res, 0);
    ASSERT_EQ(sb.len, 5);
    AssertBufSize(sb.buf, sb.alloc);
    strbuf_add(&sb, "world", 5);
    res = memcmp((void *) "helloworld", (void *) sb.buf, 10);
    ASSERT_EQ(res, 0);
    ASSERT_EQ(sb.len, 10);
    AssertBufSize(sb.buf, sb.alloc);
    strbuf_add(&sb, NULL, 0);
    res = memcmp((void *) "helloworld", (void *) sb.buf, 10);
    ASSERT_EQ(res, 0);
    strbuf_release(&sb);
}

// strbuf_addch，向sb追加一个字符c。
TEST(StrBufTest2B, addch) {
    strbuf sb;
    strbuf_init(&sb, 20);
    strbuf_addch(&sb, 'h');
    strbuf_addch(&sb, 'e');
    strbuf_addch(&sb, 'l');
    strbuf_addch(&sb, 'l');
    strbuf_addch(&sb, 'o');
    strbuf_addch(&sb, 'w');
    strbuf_addch(&sb, 'o');
    strbuf_addch(&sb, 'r');
    strbuf_addch(&sb, 'l');
    strbuf_addch(&sb, 'd');
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 10);
    int res = memcmp((void *) "helloworld", (void *) sb.buf, 10);
    ASSERT_EQ(res, 0);
    strbuf_release(&sb);
}

// strbuf_addstr，向sb追加一个字符串s。
TEST(StrBufTest2B, addstr) {
    strbuf sb;
    strbuf_init(&sb, 20);
    strbuf_addstr(&sb, "hello");
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 5);
    ASSERT_STREQ(sb.buf, "hello");
    strbuf_addstr(&sb, "world");
    ASSERT_EQ(sb.alloc, 20);
    ASSERT_EQ(sb.len, 10);
    ASSERT_STREQ(sb.buf, "helloworld");
    strbuf_release(&sb);
}
