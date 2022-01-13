#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strbuf.h"

//Part 2A
void strbuf_init(struct strbuf *sb, size_t alloc);
//初始化 sb 结构体，容量为 alloc。
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc);
//将字符串填充到 sb 中，长度为 len, 容量为 alloc。
void strbuf_release(struct strbuf *sb);
//释放 sb 结构体的内存。
void strbuf_swap(struct strbuf *a, struct strbuf *b);
//交换两个 strbuf。
char *strbuf_detach(struct strbuf *sb, size_t *sz);
//将 sb 中的原始内存取出，并获得其长度。
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second);
//比较两个 strbuf 的内存是否相同
void strbuf_reset(struct strbuf *sb);
//清空 sb。

//Part 2B
void strbuf_grow(struct strbuf *sb, size_t extra);
//将 sb 的长度扩大 extra。
void strbuf_add(struct strbuf *sb, const void *data, size_t len);
//向 sb 追加长度为 len 的数据 data。
void strbuf_addch(struct strbuf *sb, int c);
//向 sb 追加一个字符 c。
void strbuf_addstr(struct strbuf *sb, const char *s);
//向 sb 追加一个字符串 s。
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2);
//向一个 sb 追加另一个 strbuf的数据。
void strbuf_setlen(struct strbuf *sb, size_t len);
//设置 sb 的长度 len。
size_t strbuf_avail(const struct strbuf *sb);
//计算 sb 目前仍可以向后追加的字符串长度。
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len);
//向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data。


void strbuf_init(struct strbuf *sb, size_t alloc)
{
    sb->len=0;
    sb->alloc=alloc;
    sb->buf = (char *)malloc(alloc*sizeof(char));
	if(sb->buf == NULL)
    {
		printf("malloc memory unsuccessful.");
		exit(1);
	}
}

void strbuf_attach(struct strbuf*sb,void*str,size_t len,size_t alloc)
{
    strbuf_init(sb,alloc);
    while(sb->alloc < len)
    {
        sb->alloc *=2;
        sb->buf = (char *)realloc(sb->buf,2*sb->alloc);
        if(sb->buf == NULL)
        {
            printf("realloc memory unsuccessful.");
            exit(1);
        }
    }
    sb->len = len;
    sb->buf = (char *)str;
}

void strbuf_release(struct strbuf *sb)
{
    if(sb == NULL)
        return;
        free(sb->buf);
    //free(sb);
}

void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
    struct strbuf temp;

    temp.alloc = a->alloc;
    temp.len = a->len;
    temp.buf = a->buf;

    a->alloc = b->alloc;
    a->len = b->len;
    a->buf = b->buf;

    b->alloc = temp.alloc;
    b->len = temp.len;
    b->buf = temp.buf;
}

char *strbuf_detach(struct strbuf *sb, size_t *sz) 
{
    *sz = sb->alloc;
    strbuf_init(sb,0);

    return sb->buf;
}

int strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{
    return &first == &second && &first->len == &second->len && &first->alloc == &second->alloc; 
}//1是，相同；0，否，不相同

void strbuf_reset(struct strbuf *sb)
{
    if(sb == NULL)  
        return;
    int i = 0;
    for(i = 1;i <= sb->len;i++);
    {
        sb->buf[i] = '\0';
    }
    sb->buf = (char *)realloc(sb->buf,32); 
    sb->len = 0; 
    sb->alloc = 32;
}

void strbuf_grow(struct strbuf *sb, size_t extra)
{
    if (sb == NULL || extra == 0) 
        return;
    sb->alloc += extra;
    sb->buf =(char *)realloc(sb->buf,sizeof(char)*(sb->alloc));
    int i = 0;
    for(i = sb->len;i <= sb->len+extra;i++);
    {
        sb->buf[i] = '\0';
    }
}

void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    strbuf_grow(sb,len);
    memcpy(sb->buf+sb->len,data,len);
    sb->len += len; 
}

void strbuf_addch(struct strbuf *sb, int c)
{
    if (sb == NULL) return;
    strbuf_grow(sb,1);
    sb->buf[sb->len] = c;
    sb->len++;
    sb->buf[sb->len] = '\0';
}