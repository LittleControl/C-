数据结构快结课了，今天又把之前的线性表部分看了一下，并更新了一下最终的约瑟夫环问题（捂脸）
调试工具 VS2019社区版
//3 1 7 2 4 8 4
//6 1 4 7 2 3 5
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define MAXSIZE 100
typedef struct linklist
{
	int num;
	int password;
	struct linklist *next;
}LinkList;
LinkList* init()
{
	LinkList *L;
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = L;
	return L;
}
void Add(LinkList *L,int m,int n)
{
	printf("Please input the %d's password\n", n);
	L->num = 1;
	printf("The 1's password:");
	scanf_s("%d", &L->password);
	for (int i = 2; i < m+1; i++)
	{
		LinkList *p;
		p = (LinkList*)malloc(sizeof(LinkList));
		p->num = i;
		printf("The %d's password:", i);
		scanf_s("%d", &p->password);
		p ->next= L->next;
		L->next = p;
		L = L->next;
	}
}
void Test(LinkList *L, int m)
{
	for (int i = 0; i < m; i++)
	{
		printf("%d\t", L->num);
		printf("%d\n", L->password);
		L = L->next;
	}
}
void App(LinkList *L, int m, int n)
{
	int *e;
	e = &n;
	LinkList *p;
	p = (LinkList*)malloc(sizeof(LinkList));
	for (int i = 0; i < m; i++)
	{
		for (int j= 0; j< *e-1; j++)
		{
			p = L;
			L = L->next;
		}
		printf("----%d----", L->num);
	//	printf("----%d----\n", L->password);
		e = &(L->password);
		printf("*e=%d\n", *e);
		p->next = L->next;
		L = p->next;
	}
}
int main()
{
	LinkList *L;
	L= init();
	int m, n;
	printf("Please input the amount:");
	scanf_s("%d", &m);
	printf("Please input the limitation:");
	scanf_s("%d", &n);
	Add(L, m, n);
	Test(L, m);
	App(L, m, n);
	system("pause");
	return 0;
}
