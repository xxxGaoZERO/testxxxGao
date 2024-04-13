#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct BiTNode
{
char data;   
    struct BiTNode *lchild, *rchild;    
}BiTNode, *BiTree;
//二叉树的建立：先输入根，再输入左子树，再输入右子树（左边优先）
void CreatBiTree(BiTree &T)
{
    char ch;
    cin >> ch;
    if(ch == '#')
        T = NULL;
    else
    {
        T = new BiTNode;    
        if(!T)
            exit(1);
        T->data = ch;
        CreatBiTree(T->lchild); 
        CreatBiTree(T->rchild); 
    }
}
//前序遍历：若树为空返回，不为空先访问根节点，再访问左子树，再访问右子树（根左右）
void PreOrderTraverse(BiTree T)
{
    if(!T)
        return;
    cout << T->data;  
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
//中序遍历：若树为空返回，不为空先访问左子树，再访问根节点，再访问右子树（左根右）
void InOrderTraverse(BiTree T)
{
    if(!T)
        return;
    InOrderTraverse(T->lchild);
    cout << T->data;    
    InOrderTraverse(T->rchild);
}
int main()
{
    BiTree T;
    CreatBiTree(T);
    cout << "前序遍历：";
    PreOrderTraverse(T);   
    cout << endl;
    cout << "中序遍历：";
    InOrderTraverse(T);   
    cout << endl;
    return 0;
}

