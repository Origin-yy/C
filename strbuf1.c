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
    return 0;
}

void strbuf_init(struct strbuf *sb, size_t alloc)
{
    char *buf ;
    if((buf = (char *)realloc(5,sizeof(char)))==NULL)
	{
		printf("malloc memory unsuccessful");
		exit(1);
	}//（申请空间，若申请失败则异常退出）
}