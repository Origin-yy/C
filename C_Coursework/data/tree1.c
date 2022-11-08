#include <stdio.h>
#include <malloc.h>
#include <limits.h>

// ABC##DE#G##F###
#define MAXSIZE 10000
typedef struct TreeNode{
    char data;
    struct TreeNode* LChild;
    struct TreeNode* RChild;

} BiNode,*BiTree;

//栈内元素结构 
typedef struct elem {
    BiNode node;    // 栈中元素的结点信息 
    int flag;       // 标记位，进左子树为0，进右子树为1 
} ElemType;

// 顺序栈结构
typedef struct stack {
    ElemType elem[MAXSIZE];    // 顺序栈数组 
    int top;                   // 栈顶指针 
} SeqStack;

BiTree CreateTree();                 // 扩展先序建立二叉树
void PreOrder(BiTree root);          // 递归先序遍历二叉树 
void InOrder(BiTree root);           // 递归中序遍历二叉树 
void PostOrder(BiTree root);         // 非递归后序遍历二叉树 
SeqStack* InitStack(void);           // 初始化栈  
int Empty(SeqStack* s);              // 判空栈  
int Push(SeqStack* s, ElemType x);   // 入栈  
int Pop(SeqStack* s);                // 出栈  
ElemType* GetTop(SeqStack* s);       // 取栈顶元素  
int NonLeafNode(BiTree root);        // 统计二叉树中非叶子结点的个数  
int BiTreeDeepth(BiTree root);       // 计算二叉树的高度  
void CountLeaf(BiTree root,int *Count);// 统计二叉树中叶子节点的个数

int main(void) {
    int leaf_num = 0;
    printf("请按先序输入二叉树，‘#’表示节点为空： \n");
    BiTree root = NULL;
    root = CreateTree(root);

    printf("先序遍历结果为：");
    PreOrder(root);
    printf("\n");

    printf("中序遍历结果为：");
    InOrder(root);
    printf("\n");

    printf("后序遍历结果为：");
    PostOrder(root);
    printf("\n");

    printf("非叶子结点个数为：%d\n", NonLeafNode(root));

    CountLeaf(root, &leaf_num);
    printf("叶子节点个数为：%d\n", leaf_num);
    printf("高度为：%d\n", BiTreeDeepth(root));
    return 0;
}

// 扩展先序建立二叉树
BiTree CreateTree(BiNode* root){
    char ch;
    ch = getchar();
    // 读入数据，是空就返回
    if(ch == '#'){
        return NULL; 
    } else {
    // 不是空就为这个节点申请空间放数据，并以此为根节点，递归调用创建他的子节点
        root = (BiTree)malloc( sizeof(BiNode) );
        root->data = ch;
        root->LChild = CreateTree(root->LChild);
        root->RChild = CreateTree(root->RChild);
    }
    return root;
}
// 递归先序遍历二叉树
void PreOrder(BiTree root) {
    if (root) {
        printf("%c", root->data);
        PreOrder(root->LChild);
        PreOrder(root->RChild);
    }
}
// 递归中序遍历二叉树
void InOrder(BiTree root) {
    if (root) {
        InOrder(root->LChild);
        printf("%c", root->data);
        InOrder(root->RChild);
    }
}
// 非递归后序遍历二叉树
void PostOrder(BiTree root) {
    SeqStack* s;
    s = (SeqStack*)malloc(sizeof(SeqStack));
    while (root || !Empty(s)) {
        while (root) {
            ElemType temp;
            temp.node = * root;
            temp.flag = 0;
            Push(s, temp);
            root = root->LChild;
        }
        while(!Empty(s) && GetTop(s)->flag == 1) {
            printf("%c", GetTop(s)->node.data);
            Pop(s);
        }
        if (!Empty(s)) {
            root = GetTop(s)->node.RChild;
            GetTop(s)->flag = 1;
        }
    }
}
// 初始化栈
SeqStack* InitStack(void) {
    SeqStack* s;
    s = (SeqStack*)malloc(sizeof(SeqStack));
    s->top = -1;
    return s;
}
// 判空栈
int Empty(SeqStack* s) {
    if (s->top == -1) {
        return 1;
    } else {
        return 0;
    }
}
// 入栈 
int Push(SeqStack* s, ElemType x) {
    if (s->top == MAXSIZE - 1) {
        return 0;    /* 栈满不能入栈 */
    } else {
        s->top++;
        s->elem[s->top] = x;
        return 1;
    }
}
// 出栈 
int Pop(SeqStack* s) {
    if (Empty(s)) {
        return 0;    /* 栈空不能出栈 */
    } else {
        s->top--;
        return 1;
    }
}
// 取栈顶元素
ElemType* GetTop(SeqStack* s) {
    if (Empty(s)) {
        return NULL;    /* 栈空 */
    } else {
        return &(s->elem[s->top]);
    }
}
// 统计二叉树中非叶子结点的个数
int NonLeafNode(BiTree root) {
    if (!root) {
        return 0;
    } else if (!root->LChild && !root->RChild) {
        return 0;
    } else {
        return NonLeafNode(root->LChild) + NonLeafNode(root->RChild) + 1;
    }
}
// 统计二叉树中叶子节点的个数
void CountLeaf(BiTree root,int* Count)
{
    if(root){
        if((root->LChild == NULL) && (root->RChild == NULL)){
            (*Count)++;// 如果左右子树都为空，则为叶子节点，则叶子节点数加一
        } else {   
            CountLeaf(root->LChild, Count);
            CountLeaf(root->RChild, Count);
        }  
    }
}
// 计算二叉树的高度
int BiTreeDeepth(BiTree root) {
    if (!root) {
        return 0;
    } else {
        if (BiTreeDeepth(root->LChild) > BiTreeDeepth(root->RChild)) {
            return 1 + BiTreeDeepth(root->LChild);
        } else {
            return 1 + BiTreeDeepth(root->RChild);
        }
    }
}

