#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct BiTNode
{
char data;   
    struct BiTNode *lchild, *rchild;    
}BiTNode, *BiTree;
//�������Ľ������������������������������������������������ȣ�
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
//ǰ�����������Ϊ�շ��أ���Ϊ���ȷ��ʸ��ڵ㣬�ٷ������������ٷ����������������ң�
void PreOrderTraverse(BiTree T)
{
    if(!T)
        return;
    cout << T->data;  
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
//�������������Ϊ�շ��أ���Ϊ���ȷ������������ٷ��ʸ��ڵ㣬�ٷ���������������ң�
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
    cout << "ǰ�������";
    PreOrderTraverse(T);   
    cout << endl;
    cout << "���������";
    InOrderTraverse(T);   
    cout << endl;
    return 0;
}

