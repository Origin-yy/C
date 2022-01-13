#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct strbuf{
    int len;     //当前缓冲区（字符串）长度
    int alloc;   //当前缓冲区（字符串）容量
    char *buf;   //缓冲区（字符串）
};

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
strbuf_reset(struct strbuf *sb);
//清空 sb。

int main(void)
{
    struct strbuf sb;
    strbuf_init(&sb, 10);
    strbuf_attach(&sb, "xiyou", 5, 10);
    assert(strcmp(sb.buf, "xiyou") == 0);
    strbuf_addstr(&sb, "linux");
    assert(strcmp(sb.buf, "xiyoulinux") == 0);
    strbuf_release(&sb);
    return 0;
}

void strbuf_init(struct strbuf *sb, size_t alloc)
{
    sb->len=0;
    sb->alloc=alloc;
    if((sb = (char *)malloc(alloc*sizeof(char)))==NULL)
	{
		printf("malloc memory unsuccessful.");
		exit(1);
	}//（申请空间，若申请失败则异常退出）
}

void strbuf_attach(struct strbuf*sb,void*str,size_t len,size_t alloc)
{
    while(sb->alloc < len)
    {
        sb->alloc *=2;
        if(sb->buf = (char *)realloc(sb->buf,2*sb->alloc) == NULL)
        {
            printf("realloc is unsuccessful.");
            exit(1);
        }
    }
    sb->len = len;
    strcpy(sb->buf,str);
}

void strbuf_release(struct strbuf *sb)
{
    free(sb->buf);
}

void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
    struct strbuf temp;

    temp.alloc = a->alloc;
    temp.len = a->len;
    temp.buf = a->buf;

    a->alloc = b->alloc;
    a->len = b->len;
    a->buf = b->len;

    b->alloc = temp.alloc;
    b->len = temp.len;
    b->buf = temp.len;
}

char *strbuf_detach(struct strbuf *sb, size_t *sz) 
{
    *sz = sb->len;
    return &sb->buf;
}