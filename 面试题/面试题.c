#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strbuf.h"
#include<ctype.h>


//Paret 2A

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
    /*
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
    */
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
    if(sb->alloc == 0 || sb == NULL)
        return;
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
    a->buf = b->buf;

    b->alloc = temp.alloc;
    b->len = temp.len;
    b->buf = temp.buf;
}

char *strbuf_detach(struct strbuf *sb, size_t *sz) 
{
    *sz = sb->alloc;
    return sb->buf;
}

int strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{
    //return first->len-second->len;
    return first != second && first->len != second->len;
}

void strbuf_reset(struct strbuf *sb)
{
    if (sb == NULL) return;
    strbuf_init(sb,sb->alloc);
}

//Part 2B

void strbuf_grow(struct strbuf *sb, size_t extra)
{
    if(extra == 0) return;
    sb->buf = (char*)realloc(sb->buf,(sb->alloc+extra)*sizeof(char));
    sb->alloc += extra;
}

void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    if(sb->len + len > sb->alloc)
        strbuf_grow(sb,len);
    memmove(sb->buf + sb->len,data,len);
    sb->len += len;
    sb->buf[sb->len] = '\0';
}

void strbuf_addch(struct strbuf *sb, int c)
{
    if (sb == NULL) return;
    if(sb->len + 2>sb->alloc)
        strbuf_grow(sb,2);
    memmove(sb->buf + sb->len,&c,2);
    sb->len++;
    sb->buf[sb->len] = '\0';
}

void strbuf_addstr(struct strbuf *sb, const char *s)
{
    int len = strlen(s);
    if(sb->len + len +1 > sb->alloc)
        strbuf_grow(sb,len + 1);
    memmove(sb->buf + sb->len,s,len);
    sb->len += len;
    sb->buf[sb->len] = '\0';
}

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
    strbuf_addstr(sb,sb2->buf);
}

void strbuf_setlen(struct strbuf *sb, size_t len)
{
    int stop = '\0';
    memmove(sb->buf + len,&stop,1);
    sb->len = len;
}

size_t strbuf_avail(const struct strbuf *sb)
{
    return sb->alloc-sb->len-1;
}

void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len)
{
    sb->len += len;
    int last_len = sb->len - pos - len;
    char *temp = (char *)malloc(sizeof(char)*last_len + 1);
    memmove(temp,sb->buf + pos,last_len + 1);
    memmove(sb->buf + pos,data,len + 1);
    memmove(sb->buf + pos + len,temp,last_len + 1);
}

//Part 2C

void strbuf_ltrim(struct strbuf *sb)
{
    int i = 0; 
    while(sb->buf[i] == ' ' || sb->buf[i] == '\t')
        i++;
    char *temp = (char *)malloc(sb->len + 1 - i);
    memmove(temp,sb->buf + i,sb->len + 1 - i);
    memmove(sb->buf,temp,sb->len + 1 - i);
    sb->len -=i;
}

void strbuf_rtrim(struct strbuf *sb)
{
    int i = sb->len; 
    while(sb->buf[i-1] == ' ' || sb->buf[i] == '\t')
       i--;
    char *temp = (char *)malloc(i + 1);
    memmove(temp,sb->buf,i + 1);  
    memmove(sb->buf,sb->buf, i + 1);
    sb->len= i - 1;
}

void strbuf_remove(struct strbuf *sb, size_t pos, size_t len)
{
    sb->len -= len;
    int last_len = sb->len - pos;
    char *temp = (char *)malloc(sizeof(char)*last_len);
    memmove(temp,sb->buf + pos + len,last_len);
    memmove(sb->buf + pos,temp,last_len);
    sb->buf[sb->len + 1] = '\0';
}

//Part 2D
ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
    FILE *fp = fdopen(fd, "r");//文件标识符转为文件指针。
    char ch;
    while ((ch = fgetc(fp)) != EOF )//逐字符拷贝到结尾。
    {
        while(sb->alloc <= sb->len+1)//是否扩容。
        {
            sb->buf = (char *)realloc(sb->buf,sb->len+(hint ? hint : 8192) );
            sb->alloc += (hint ? hint : 8192);
        }
        strbuf_addch(sb, ch);
    }
    
    return 1;
}

int strbuf_getline(struct strbuf *sb, FILE *fp)
{
    char ch = '\0';
    while ((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n')
            break;
        strbuf_addch(sb,ch);
    }
    return 1;
}


//CHALLENGE

struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max)
{
    int i,count=0;

    char q[2]; 
    q[0]=(char)terminator;
    q[1]='\0';
    struct strbuf **ptr2=NULL;
    struct strbuf *ptr;
    char s[len+1];
    memcpy(s,str,len+1);

    for(i=0;i<len;i++){
        if(s[i]=='\0'){
            s[i]='#';
        }
    }
    char*r=strtok(s,q);


    while(r!=NULL&&count<max)
    {   
        int rlen=strlen(r);
        for(i=0;i<rlen;i++){
            if(r[i]=='#'){
                r[i]='\0';
            }
        }
        ptr=(struct strbuf*)malloc(sizeof(struct strbuf));
        {
            strbuf_init(ptr,rlen+1); 
            strbuf_add(ptr,r,rlen);
        }
        ptr2=(struct strbuf**)realloc(ptr2,sizeof(struct strbuf*)*(count+2));
        ptr2[count]=ptr;
        count++;

        r=strtok(NULL,q);

    }

    ptr2=(struct strbuf**)realloc(ptr2,sizeof(struct strbuf*)*(count+1));


    ptr2[count]= NULL;
    return ptr2;

}

bool strbuf_begin_judge(char *target_str, const char *str, int len) 
{
    if(str == NULL) 
        return true;
    if(target_str == NULL) 
        return false;
    return strncmp(target_str,str,strlen(str)) == 0;
}

char *strbuf_get_mid_buf(char *target_buf, int begin, int end, int len) 
{
    if(target_buf == NULL)
        return NULL;
    char *str = (char *) malloc(sizeof(char) * (end - begin + 2));
    int n = 0;
    for (int i = begin; i < end; i++)
    {
        str[n++] = target_buf[i];
    }
    str[n] = '\0';

    return str;
}