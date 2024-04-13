#include <iostream>
#include <cstring>//��һЩ���ر������������ռ�,����һЩC++��������ΪBug�Ĵ���
#include <iomanip>//������λС����Ҫʹ��
using namespace std;

//ͼ����Ϣ�Ľṹ��
typedef struct {
 char no[15]; //15λ���
 char name[40]; //����
 double price; //�۸�
}Book;

//�������ݽṹ������������ͼ����Ϣ������Ҫ���ң���˳���������У�������ʺϴ洢������Ҫ���ҵ�����
typedef struct LNode {
 Book data; //������
 struct LNode* next; //ָ����
}LNode, * LinkList;

LNode* first; //��������ͷ���

//�����ʾͼ���������ͼ��������Ϣ
void BookOut() {
 cout << "����ϵͳ��ȫ��ͼ����Ϣ���£�" << endl;
 LNode* p = first->next;
 while (p) {
  cout << p->data.no << ' 4' << p->data.name << ' ';
  cout << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl;//������λС��
     p = p->next;
 }
}

//����ָ���Ĵ�������ͼ���λ�ú���Ϣ������ͼ����뵽ͼ�����ָ����λ��
void BookInsert(int i,Book book) {
 LNode* p = first;
 int j = 0;
 //Ѱ�Ҳ���λ�õ�ǰһ��λ��
 while (p && j < i - 1) { p = p->next; j++; }
 if (!p) cout << "λ�ó���" << endl;
 else {
  LNode* s = new LNode();
  s->data = book;
  s->next = p->next;
  p->next = s;
 }
}

//����ָ���Ĵ�����ľ�ͼ���λ�ã�����ͼ���ͼ�����ɾ��
void BookDelete(int i) {
 LNode* p = first;
 int j = 0;
 while (p && j < i - 1) { p = p->next; j++; }
 if (!p || !p->next)cout << "λ�ó���" << endl;
 else {
  LNode* q = p->next;
  Book book = q->data;
  p->next = q->next;
  cout << "ɾ����ͼ����ϢΪ:" << q->data.no << q->data.name << setiosflags(ios::fixed) << setprecision(2) << q->data.price << endl;
  delete q;
 }
}

//ͳ�Ʊ���ͼ�����
int BookCount() {
 LNode* p = first->next;
 int count = 0;
 while (p) {
  count++;
  p = p->next;
 }
 return count;
}

//ͼ����Ϣ���ͼ��ȥ��
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



//˳�����ϲ��ͼ��
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
 if (i == 0) { cout << "��Ǹ��û��������" << endl; }
 else { 
  cout << "��ѯ����ͼ������Ϊ��" << i << endl << "ͼ����Ϣ���£�" << endl;
  for (int j = 0; j < i; j++) {
   cout << book[j].no << ' ' << book[j].name << ' ' << book[j].price << endl;
  }
 }
}

//ͼ����Ϣ�����ھ�������20%�����ھ�������10%���������޸�
void BookChange() {
 LNode* p = first->next;
 double average = 0;
 while (p) {
  average += p->data.price;
  p = p->next;
 }
 average /= BookCount();
 p = first->next;//����pָ��
 while (p) {
  if (p->data.price < average) {
   p->data.price *= 1.2;
  }
  else { p->data.price *= 1.1; }
  p = p->next;
 }
}

/*����ֱ�Ӳ���������ͼ��۸�������
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
//����ð��������ͼ��۸�������
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

//���ͼ��Ĳ���
void BookExpensive() {
 LNode* p = first->next;
 double max = 0;
 while (p) {
  if (p->data.price > max) { max = p->data.price; }
  p = p->next;
 }
 cout << "���ͼ�����£�" << endl;
 p = first->next;//����pָ��
 while (p) {
  if (p->data.price == max) { cout << p->data.no << ' ' << p->data.name << ' ' << setiosflags(ios::fixed) << setprecision(2) << p->data.price << endl; }
  p = p->next;
 }
}

//�û�ʹ�ý���˵�
void Menu() {
 cout << "~~��ӭʹ��ͼ����Ϣ����ϵͳ~~" << endl;
 cout << "~�������Ӧ���ʹ�ö�Ӧ����~" << endl;
 cout << "~~~~~~1.�������ͼ��~~~~~~" << endl;
 cout << "~~~~~~2.����һ��ͼ��~~~~~~" << endl;
 cout << "~~~~~~3.ɾ��һ��ͼ��~~~~~~" << endl;
 cout << "~~~~~~4.�鿴ͼ������~~~~~~" << endl;
 cout << "~~~~~~5.ɾ����ͬͼ��~~~~~~" << endl;
 cout << "~~~~~~6.Ѱ��ϲ��ͼ��~~~~~~" << endl;
 cout << "~~~~~~7.����ͼ��۸�~~~~~~" << endl;
 cout << "~~~~~~8.���ռ۸�����~~~~~~" << endl;
 cout << "~~~~~~9.�������ͼ��~~~~~~" << endl;
 cout << "~~~~~~~10.�˳�ϵͳ~~~~~~~" << endl;
}

int main() {
 Book book[50];//����ͼ��洢�ռ�
 int count = 0, n;
 bool tag = true;
 while (tag) {
  cout << "�������ʼ�鱾������0~50����" << endl;
  cin >> n;//��ʼ�鱾����
  if (n >= 0 && n <= 50) {
   while (count < n) {
    cout << "��������ţ������ͼ۸�(�м��Կո������)" << endl;
    cin >> book[count].no;
    cin >> book[count].name;
    cin >> book[count].price;
    count++;
   }
   tag = false;
  }
  else { cout << "���벻��ȷ" << endl; }
 }
 //�����ӷ�ʽ�ĵ�����
 first = new LNode();
 first->next = NULL;
 LNode* r = first, * s;
 for (int i = 0; i < count; i++) { //rΪβָ��
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
   cout << "������Ҫ�����λ�ú�ͼ���������Ϣ���м��ÿո������:" << endl;
   int i;//����λ��
   cin >> i >> book[count].no >> book[count].name >> book[count].price;
   BookInsert(i, book[count]);
   break;
  }
  case 3: {
   int i;//ɾ��λ��
   cin >> i;
   BookDelete(i);
   break;
  }
  case 4: {
   cout << "ͼ�����ϵͳ���ܹ��У�" << BookCount() << "���顣" << endl;
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


