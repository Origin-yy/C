#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define NONE        "\e[0m"
#define BLACK       "\e[0;30m"
#define L_BLACK     "\e[1;30m"
#define RED         "\e[0;31m"
#define L_RED       "\e[1;31m"
#define GREEN       "\e[0;32m"
#define L_GREEN     "\e[1;32m"
#define YELLOW      "\e[0;33m"
#define L_YELLOW    "\e[1;33m"
#define BLUE        "\e[0;34m"
#define L_BLUE      "\e[1;34m"
#define PURPLE      "\e[0;35m"
#define L_PURPLE    "\e[1;35m"
#define D_GREEN     "\e[0;36m"
#define L_D_GREEN   "\e[1;36m"
#define WHITE       "\e[0;37m"
#define L_WHITE     "\e[1;37m"

#define FILE_PATH   "/home/yuanye/my_code/my_code.c/C_Coursework/C_design/学生信息.c"

typedef struct Node {
  int id;
  char name[50];
  char sex;
  int Chinese;
  int Math;
  int English;
  struct Node *next;
  struct Node *prev;
} Node, *List;

int MAX_NUM = 100;

//展示操作选项
void display_options();

//创建一个空链表
List List_init();

//输入学生信息
void Node_insert(List L);

//删除学生信息
void Node_delete(List L);

//查询学生信息
void Node_find(List L);

//修改学生信息
void Node_change(List L);

//排序学生信息
void List_sort(List L);

//展示学生信息
void List_output(List L);

//读取学生信息
void read_information(List L);

//保存学生信息
void write_information(List L);

//链表销毁
void destroy(List L);

int main(void) {
  printf(L_RED "欢迎使用学生管理系统!\n\n");
  int flag = -1;
  List L = List_init();

  display_options();
  printf("\n");

  while (1) {
    printf(L_BLUE"请输入您想进行的操作的序号: \n"NONE);
    scanf("%d", &flag);
    switch (flag) {
    case 0:
      printf(L_YELLOW"期待您的下次使用，再见!\n"NONE);
      exit(0);
    case 1:
      Node_insert(L);
      break;
    case 2:
      Node_delete(L);
      break;
    case 3:
      Node_find(L);
      break;
    case 4:
      Node_change(L);
      break;
    case 5:
      List_sort(L);
      break;
    case 6:
      List_output(L);
      break;
    case 7:
      read_information(L);
      break;
    case 8:
      write_information(L);
      break;
    case 9:
      display_options();
      break;
    default:
      printf(L_RED "输入有误，请重新输入。\n" NONE);
      continue;
    }
    printf("\n");
  }
  destroy(L);
  return 0;
}

//创建一个空链表
List List_init() {
  List L = (List)malloc(sizeof(Node));
  L->id = 0;
  L->next = NULL;
  L->prev = NULL;
  return L;
}

//输入学生信息
void Node_insert(List L) {
  printf("希望录入的学生信息数量为：\n");
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    Node *T = (Node *)malloc(sizeof(Node));

    Node *p = L;
    while (p->next)
      p = p->next;

    printf("请输入第%d学生的信息:\n", i + 1);

    printf("学号:");
    while (!scanf("%d", &T->id) || T->id > 100000000 || T->id < 1) {
      printf(L_RED "学号范围是1-10000000,请重新输入.\n" NONE);
      printf("学号:");
      continue;
    }

    printf("姓名:");
    while (!scanf("%s", T->name))
      continue;

    printf("性别:");

    while (1) {
      T->sex = getchar();
      if (T->sex == ' ' || T->sex == '\n')
        continue;
      else if (T->sex != 'm' && T->sex != 'w') {
        printf(L_RED "性别为:m(男)/w(女),请重新输入.\n" NONE);
        printf("性别:");
        continue;
      }
      break;
    }

    printf("语文:");
    while (!scanf("%d", &T->Chinese) || T->Chinese > 100 || T->Chinese < 0) {
      printf(L_RED "课程分数范围是0-100,请重新输入成绩.\n" NONE);
      printf("语文:");
      continue;
    }

    printf("数学:");
    while (!scanf("%d", &T->Math) || T->Math > 100 || T->Math < 0) {
      printf(L_RED "课程分数范围是0-100,请重新输入成绩.\n" NONE);
      printf("数学:");
      continue;
    }

    printf("英语:");
    while (!scanf("%d", &T->English) || T->English > 100 || T->English < 0) {
      printf(L_RED "课程分数范围是0-100,请重新输入成绩.\n" NONE);
      printf("英语:");
      continue;
    }
    printf("\n");
    p->next = T;
    T->prev = p;
    T->next = NULL;
    p = T;
  }
  L->id += n;
  printf(L_GREEN"%d名学生信息已录入完毕.\n"NONE,n);
}

//删除学生信息
void Node_delete(List L) {
  if (L->next == NULL) {
    printf("当前还没有学生信息.\n");
    return;
  }
  char name[50];
  int flag = 0;
  printf("请输入您想删除的学生的姓名：");
  scanf("%s", name);
  Node *p = L;
  while (p->next) {
    p = p->next;
    if (strcmp(p->name, name) == 0) {
      p->prev->next = p->next;
      p->next->prev = p->prev;
      free(p);
      p = NULL;
      flag = 1;
      break;
    }
  }
  if (flag == 0)
    printf(L_RED "\n没有该学生,请确认后重试.\n" NONE);
  else {
    printf(L_GREEN "\n%s的学生信息已删除.\n" NONE, name);
    L->id--;
  }
}

//查询学生信息
void Node_find(List L) {
  if (L->next == NULL) {
    printf(L_RED "当前还没有学生信息,请确认后重试.\n" NONE);
    return;
  }
  char name[50];
  int flag = 0;
  int i = 1;

  printf("请输入您想查询的学生姓名：");
  scanf("%s", name);

  Node *p = L;
  while (p->next) {
    p = p->next;
    if (strcmp(p->name, name) == 0) {
      printf("\n学生%s的信息如下: \n", name);
      printf(L_YELLOW "********************************************************"
                      "*****************\n" NONE);
      printf(L_BLUE "*   序号|      学号|    姓名|   性别|   语文|   数学|   "
                    "英语|   均分|   *\n" NONE);
      printf(L_YELLOW "*" NONE);
      printf("%7d|", i);
      printf("%10d|", p->id);
      printf("%8s|", p->name);
      printf("%7c|", p->sex);
      printf("%7d|", p->Chinese);
      printf("%7d|", p->Math);
      printf("%7d|", p->English);
      printf("%7.3lf|", (double)(p->Chinese + p->Math + p->English) / 3);
      printf(L_YELLOW "   *\n" NONE);
      printf(L_YELLOW
             "************************************************************"
             "*************\n" NONE);
      flag = 1;
      break;
    }
  }
  if (flag == 0)
    printf(L_RED "没有该学生，请确认后重试.\n" NONE);
}

//修改学生信息
void Node_change(List L) {
  if (L->next == NULL) {
    printf(L_RED "当前还没有学生信息,请确认后重试.\n" NONE);
    return;
  }

  char name[50];
  int flag = 0;

  printf("请输入您想修改的学生的姓名：");
  scanf("%s", name);

  Node *p = L;
  while (p->next) {
    p = p->next;

    if (strcmp(p->name, name) == 0) {
      flag = 1;

      printf("学号:");
      while (!scanf("%d", &p->id) || p->id > 100000000 || p->id < 1) {
        printf(L_RED "学号范围是1-10000000,请重新输入.\n" NONE);
        printf("学号:");
        continue;
      }

      printf("姓名:");
      while (!scanf("%s", p->name))
        continue;

      printf("性别:");

      while (1) {
        p->sex = getchar();
        if (p->sex == ' ' || p->sex == '\n')
          continue;
        else if (p->sex != 'm' && p->sex != 'w') {
          printf(L_RED "性别为:m(男)/w(女),请重新输入.\n" NONE);
          printf("性别:");
          continue;
        }
        break;
      }

      printf("语文:");
      while (!scanf("%d", &p->Chinese) || p->Chinese > 100 || p->Chinese < 0) {
        printf("课程分数范围是0-100,请重新输入成绩.\n");
        printf("语文:");
        continue;
      }

      printf("数学:");
      while (!scanf("%d", &p->Math) || p->Math > 100 || p->Math < 0) {
        printf(L_RED "课程分数范围是0-100,请重新输入成绩.\n" NONE);
        printf("数学:");
        continue;
      }

      printf("英语:");
      while (!scanf("%d", &p->English) || p->English > 100 || p->English < 0) {
        printf(L_RED "课程分数范围是0-100,请重新输入成绩.\n" NONE);
        printf("英语:");
        continue;
      }
      printf("\n");
    }
  }
  if (flag == 0)
    printf(L_RED "没有该学生，请确认后重试.\n" NONE);
  else
    printf(L_GREEN "%s的学生信息已修改完毕.\n" NONE, name);
}


//排序学生信息
void List_sort(List L) {
  Node *a, *b, temp;
  if (L->next == NULL) {
    printf(L_RED "当前没有学生信息,请确认后重试.\n\n" NONE);
    return;
  }
  if (L->next->next == NULL) {
    printf(L_RED"当前只有一个学生信息,无需排序.\n\n"NONE);
    return;
  }
  a = L->next;
  while (a->next) {
    b = a->next;
    while (b) {
      if ((a->Chinese + a->Math + a->English) <
          (b->Chinese + b->Math + b->English)) {
        temp = *a;
        *a = *b;
        *b = temp;
        temp.next = a->next;
        a->next = b->next;
        b->next = temp.next;
      }
      b = b->next;
    }
    a = a->next;
  }
  printf(L_GREEN "已按照三门课程的平均成绩对学生进行排序\n" NONE);
}

//展示学生信息
void List_output(List L) {
  if(L->id == 0)
  {
    printf(L_RED"当前没有学生信息，请确认后重试.\n"NONE);
    return;
  }
  Node *p = L;
  int i = 1;
  printf("已有的学生信息如下:\n\n");
  printf(L_YELLOW "************************************************************"
                  "*************\n" NONE);
  printf(L_BLUE "*   序号|      学号|    姓名|   性别|   语文|   数学|   英语| "
                "  均分|   *\n" NONE);
  while (p->next) {
    p = p->next;
    printf(L_YELLOW "*" NONE);
    printf("%7d|", i);
    printf("  %08d|", p->id);
    printf("%8s|", p->name);
    printf("%7c|", p->sex);
    printf("%7d|", p->Chinese);
    printf("%7d|", p->Math);
    printf("%7d|", p->English);
    printf("%7.3lf|", (double)(p->Chinese + p->Math + p->English) / 3);
    printf(L_YELLOW "   *\n" NONE);
    i++;
  }
  printf(L_YELLOW "************************************************************"
                  "*************\n" NONE);
  printf(L_GREEN "\n已录入的学生信息展示完毕.\n" NONE);
}

void display_options() {
  printf(
      L_YELLOW
      "************************学生管理系统*************************\n" NONE);
  printf(
      L_GREEN
      "***---------------------------*---------------------------***\n" NONE);
  printf(
      L_BLUE
      "*  1、输入学生信息     2、删除学生信息     3、查询学生信息  *\n" NONE);
  printf(
      L_PURPLE
      "*  4、修改学生信息     5、排序学生信息     6、展示学生信息  *\n" NONE);
  printf(
      L_D_GREEN
      "*  7、读取学生信息     8、保存学生信息     9、显示操作选项  *\n" NONE);
  printf(
      L_RED
      "*  0、退出管理系统                                          *\n" NONE);
  printf(
      L_GREEN
      "***---------------------------*---------------------------***\n" NONE);
  printf(
      L_YELLOW
      "*************************************************************\n" NONE);
}

//读取学生信息
void read_information(List L) {
  char path[256];
  printf("请输入文件的绝对路径(输入0使用默认路径):\n");
  scanf("%s", path);
  FILE *stream;
  int num;
  int a;
  double b;

  if (strncmp(path, "0", 1) == 0)
    strcpy(path,
           "/home/yuanye/my_code/my_code.c/C_Coursework/C_design/学生信息.txt");

  stream = fopen(path, "r");
  if (stream == NULL)
    printf(L_RED "没有找到文件%s.\n" NONE, path);

  fscanf(stream, "%d", &num);
  for (int i = 0; i < num; i++) {
    Node *T = (Node *)malloc(sizeof(Node));

    Node *p = L;
    while (p->next)
      p = p->next;

    fscanf(stream, "%d", &a);
    fgetc(stream);
    fscanf(stream, "%d", &T->id);
    fgetc(stream);
    fscanf(stream, "%s", T->name);
    for (int i = 0; i < 50; i++)
      if (T->name[i] == '|')
        T->name[i] = '\0';
    fgetc(stream);
    fscanf(stream, "%c", &T->sex);
    while (1) {
      if (T->sex != 'm' && T->sex != 'w')
        fscanf(stream, "%c", &T->sex);
      else
        break;
    }
    fgetc(stream);
    fscanf(stream, "%d", &T->Chinese);
    fgetc(stream);
    fscanf(stream, "%d", &T->Math);
    fgetc(stream);
    fscanf(stream, "%d", &T->English);
    fgetc(stream);
    fscanf(stream, "%lf", &b);
    fgetc(stream);

    p->next = T;
    T->prev = p;
    T->next = NULL;
    p = T;
    L->id++;
  }
  fclose(stream);
  printf(L_GREEN "已从%s处读取学生信息.\n" NONE, path);
}
//保存学生信息
void write_information(List L) {
  char path[256];
  int fd;
  printf("请输入文件的绝对路径(输入0使用默认路径):\n");
  scanf("%s", path);
  if (strncmp(path, "0", 1) == 0)
    strcpy(path,
           "/home/yuanye/my_code/my_code.c/C_Coursework/C_design/学生信息.txt");

  fd = open(path, O_RDWR);
  if (fd < 0)
    printf(L_RED "没有找到文件%s.\n\n" NONE, path);
  else
    truncate(path, 0);
  ;

  Node *p = L;
  int i = 1;
  dprintf(fd, "%d\n", L->id);
  while (p->next) {
    p = p->next;
    dprintf(fd, "%7d|", i);
    dprintf(fd, "  %08d|", p->id);
    dprintf(fd, "%8s|", p->name);
    dprintf(fd, "%7c|", p->sex);
    dprintf(fd, "%7d|", p->Chinese);
    dprintf(fd, "%7d|", p->Math);
    dprintf(fd, "%7d|", p->English);
    dprintf(fd, "%7.3lf|", (double)(p->Chinese + p->Math + p->English) / 3);
    dprintf(fd, "\n");
    i++;
  }
  close(fd);
  printf(L_GREEN "学生信息已保存到%s\n" NONE, path);
}
//销毁链表
void destroy(List L) {
  Node *p = L;
  Node *T;
  while (p) {
    T = p->next;
    free(p);
    p = T;
  }
}