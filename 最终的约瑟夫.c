#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct LNode
{
	int num;
	int password;
	struct LNode *next;
}LNode;

LNode * Creat(int n)
	{
		LNode *L,*T,*p;
		L=(LNode*)malloc(sizeof(LNode));
		T=(LNode*)malloc(sizeof(LNode)); 
		int i, a[n];
		L->next=T;
//		printf("Please input the %d 's password\n", n);
		for (i = 0; i < n; i++)
		{
			scanf("%d", &a[i]);
		}
		L->num=1;
		L->password=a[0];
		T->num=n;
		T->password=a[n-1];
		for (i = n-2; i>0; i--)
		{
			p=(LNode*)malloc(sizeof(LNode));
			p->num = i + 1;
			p->password = a[i];
			p->next=L->next;
			L->next=p;
		}
		T->next=L;
		return L;

	}
LNode * Delete(LNode *p,int *e)
{
	int i;
	LNode *q;
	for(i=1;i<*e;i++)
	{
		q=p;
		p=p->next;
	}
	*e=p->password;
	printf("%-2d",p->num);
	q->next=p->next;
	free(p);
	return q->next;
}

int main()
{
	int i,n, m,*e;
	LNode *p;
//	printf("Please input the count and the maxsize\n");
	scanf("%d %d",&n,&m);
	e=&m;
	p=Creat(n);
	for(i=0;i<n;i++)
	{
		LNode *c;
		if(i==0)
		{
			c=Delete(p,e);
		}
		else
		{
			c=Delete(c,e);
			if(i==n-1)
			printf("\b");
		}
	}
	
	return 0;
}

