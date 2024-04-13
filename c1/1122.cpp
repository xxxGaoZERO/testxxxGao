#include <iostream>
#include <cstring>//将一些隐藏变量编入命名空间,修正一些C++编译器认为Bug的代码
#include <iomanip>//保留两位小数需要使用
using namespace std;

//图书信息的结构体
typedef struct {
 char no[15]; //15位书号
 char name[40]; //书名
 double price; //价格
}Book;

//定义数据结构——链表，由于图书信息经常需要查找，在顺序表和链表中，链表更适合存储经常需要查找的数据
typedef struct LNode {
 Book data; //数据域
 struct LNode* next; //指针域
}LNode, * LinkList;

LNode* first; //定义链表头结点

//逐个显示图书表中所有图书的相关信息
void BookOut() {
 cout << "管理系统中全部图书信息如下：" << endl;
 LNode* p = first->next;
 while (p) {
  cout << p->data.no << ' 4' << p->data.name << ' ';
  cout << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl;//保留两位小数
     p = p->next;
 }
}

//根据指定的待入库的新图书的位置和信息，将新图书插入到图书表中指定的位置
void BookInsert(int i,Book book) {
 LNode* p = first;
 int j = 0;
 //寻找插入位置的前一个位置
 while (p && j < i - 1) { p = p->next; j++; }
 if (!p) cout << "位置出错" << endl;
 else {
  LNode* s = new LNode();
  s->data = book;
  s->next = p->next;
  p->next = s;
 }
}

//根据指定的待出库的旧图书的位置，将该图书从图书表中删除
void BookDelete(int i) {
 LNode* p = first;
 int j = 0;
 while (p && j < i - 1) { p = p->next; j++; }
 if (!p || !p->next)cout << "位置出错" << endl;
 else {
  LNode* q = p->next;
  Book book = q->data;
  p->next = q->next;
  cout << "删除的图书信息为:" << q->data.no << q->data.name << setiosflags(ios::fixed) << setprecision(2) << q->data.price << endl;
  delete q;
 }
}

//统计表中图书个数
int BookCount() {
 LNode* p = first->next;
 int count = 0;
 while (p) {
  count++;
  p = p->next;
 }
 return count;
}

//图书信息表的图书去重
void BookNosame() {
 LNode* p = first->next, * r = p->next, * l = first;
 while (p) {
  r = p->next;
  while (r) {
   if (strcmp(p->data.no, r->data.no) == 0) {
    l->next = p;
    l->next = p->next;
    break;
   }
   r = r->next;
  }
  p = p->next;
 }
}



//顺序查找喜爱图书
void BookFind(char name[]) {
 LNode* p = first->next;
 Book book[50];
 int i = 0;
 while (p) {
  if (strcmp(p->data.name, name) == 0) {
   book[i] = p->data;
   i++;
  }
  p = p->next;
 }
 if (i == 0) { cout << "抱歉，没有你的最爱！" << endl; }
 else { 
  cout << "查询到的图书数量为：" << i << endl << "图书信息如下：" << endl;
  for (int j = 0; j < i; j++) {
   cout << book[j].no << ' ' << book[j].name << ' ' << book[j].price << endl;
  }
 }
}

//图书信息表按低于均价提升20%，高于均价提升10%进行批量修改
void BookChange() {
 LNode* p = first->next;
 double average = 0;
 while (p) {
  average += p->data.price;
  p = p->next;
 }
 average /= BookCount();
 p = first->next;//重置p指针
 while (p) {
  if (p->data.price < average) {
   p->data.price *= 1.2;
  }
  else { p->data.price *= 1.1; }
  p = p->next;
 }
}

/*利用直接插入排序按照图书价格降序排序
void BookSort() {
 LNode* p = first->next, * r = p->next, * l = p;
 while (r) {
  Book temp = r->data;
  l->next = r;
  while (l && l->data.price < temp.price) {
   l->next->data = l->data;
   l->next = l;
  }
  if (l->next != r) { l->next->data = temp; }
  r = r->next;
 }
}*/
//利用冒泡排序按照图书价格降序排序
void BookSort() {
 LNode* p = first->next, * r = p;
 while (p->next->next != NULL) {
  while (r->next != NULL) {
   if (r->data.price < r->next->data.price) {
    Book temp = r->data;
    r->data = r->next->data;
    r->next->data = temp;
   }
   r = r->next;
  }
  p = p->next;
 }
}

//最贵图书的查找
void BookExpensive() {
 LNode* p = first->next;
 double max = 0;
 while (p) {
  if (p->data.price > max) { max = p->data.price; }
  p = p->next;
 }
 cout << "最贵图书如下：" << endl;
 p = first->next;//重置p指针
 while (p) {
  if (p->data.price == max) { cout << p->data.no << ' ' << p->data.name << ' ' << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl; }
  p = p->next;
 }
}

//用户使用界面菜单
void Menu() {
 cout << "~~欢迎使用图书信息管理系统~~" << endl;
 cout << "~请输入对应序号使用对应功能~" << endl;
 cout << "~~~~~~1.输出所有图书~~~~~~" << endl;
 cout << "~~~~~~2.插入一本图书~~~~~~" << endl;
 cout << "~~~~~~3.删除一本图书~~~~~~" << endl;
 cout << "~~~~~~4.查看图书总数~~~~~~" << endl;
 cout << "~~~~~~5.删除相同图书~~~~~~" << endl;
 cout << "~~~~~~6.寻找喜爱图书~~~~~~" << endl;
 cout << "~~~~~~7.提升图书价格~~~~~~" << endl;
 cout << "~~~~~~8.按照价格排序~~~~~~" << endl;
 cout << "~~~~~~9.查找最贵图书~~~~~~" << endl;
 cout << "~~~~~~~10.退出系统~~~~~~~" << endl;
}

int main() {
 Book book[50];//定义图书存储空间
 int count = 0, n;
 bool tag = true;
 while (tag) {
  cout << "请输入初始书本数量（0~50）：" << endl;
  cin >> n;//初始书本数量
  if (n >= 0 && n <= 50) {
   while (count < n) {
    cout << "请输入书号，书名和价格(中间以空格符隔开)" << endl;
    cin >> book[count].no;
    cin >> book[count].name;
    cin >> book[count].price;
    count++;
   }
   tag = false;
  }
  else { cout << "输入不正确" << endl; }
 }
 //构造后接方式的单链表
 first = new LNode();
 first->next = NULL;
 LNode* r = first, * s;
 for (int i = 0; i < count; i++) { //r为尾指针
  s = new LNode();
  s->data = book[i];
  s->next = NULL;
  r->next = s;
  r = s;
 }
 r->next = NULL;
 int cho = 0;
 while (cho != 10) {
  Menu();
  cin >> cho;
  switch (cho) {
  case 1: {
   BookOut();
   break;
  }
  case 2: {
   cout << "请输入要插入的位置和图书的三个信息（中间用空格隔开）:" << endl;
   int i;//插入位置
   cin >> i >> book[count].no >> book[count].name >> book[count].price;
   BookInsert(i, book[count]);
   break;
  }
  case 3: {
   int i;//删除位置
   cin >> i;
   BookDelete(i);
   break;
  }
  case 4: {
   cout << "图书管理系统中总共有：" << BookCount() << "本书。" << endl;
   break;
  }
  case 5: {
   BookNosame();
   break;
  }
  case 6: {
   char name[40];
   cin >> name;
   BookFind(name);
   break;
  }
  case 7: {
   BookChange();
   break;
  }
  case 8: {
   BookSort();
   break;
  }
  case 9: {
   BookExpensive();
   break;
  }
  }
 }
}


