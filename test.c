#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MAXSIZE 6
typedef struct admin
{
	int username[MAXSIZE];
	int password[MAXSIZE];
}Admin;
typedef struct user
{
	int username[MAXSIZE];
	int password[MAXSIZE];
}User;
typedef struct account
{
	int usernum;
	Admin *admin;
	User *user[20];
}Account;
typedef struct userlog
{
	int expenses;
	int revenue;
	int date[8];
	struct userlog *next;
}Userlog;
void init_admin(Admin *admin);
void init_account(Account *account);
void Assign(int array[MAXSIZE]);
void Assign_date(int array[8]);
int diff(int username[MAXSIZE],int name[MAXSIZE]);
int diff_date(int date1[8],int date2[8]);
int Check(Account *account,int name[MAXSIZE],int pwd[MAXSIZE]);
void printDate(int date[8]);
void Inquire(Userlog *userlog[20],int date[8],int chmod,Userlog *front);
void Add(Userlog *userlog[20],int chmod);
void Delete(Userlog *userlog[20],int chmod,Userlog *front);
void Modify(Userlog *userlog[20],int chmod, Userlog *front);
void Operation(Userlog *userlog[20],int chmod);
void Login(Account *account,Userlog *userlog[20]);
void Registered(Account *account);
int Choose();
void init_userlog(Userlog *userlog[20])
{
	for (int i = 0; i < 20; ++i)
	{
		userlog[i]=(Userlog*)malloc(sizeof(Userlog));
		userlog[i]=NULL;
	}
}

int main(int argc, char const *argv[])
{
	Account *account;
	Userlog *userlog[20];
	init_account(account);
	init_userlog(userlog);
	printf("Welcome\n");
	printf("Login(0) or Registered(1)?\n");
	int tag=Choose();
	if(tag==0)
	{
		Login(account,userlog);
	}
	else
	{
		Registered(account);
		Login(account,userlog);
	}
	return 0;
}
void Inquire(Userlog *userlog[20],int date[8],int chmod,Userlog *front)
{
	int result=0;
	while(userlog[chmod]!=NULL)
	{
		front=userlog[chmod];
		result=diff_date(userlog[chmod]->date,date);
		if(result==1)
		{
			printf("expenses : %d\n",userlog[chmod]->expenses);
			printf("revenue :  %d\n",userlog[chmod]->revenue );
			printDate(date);
			break;
		}
		userlog[chmod]=userlog[chmod]->next;
	}
	if(result==0)
	{
		printf("Sorry,nothing can be founded!\n");
		Operation(userlog,chmod);
	}
}
void Add(Userlog *userlog[20],int chmod)
{
	printf("Please input the expenses\n");
	scanf("%d",&userlog[chmod]->expenses);
	printf("Please input the revenue\n");
	scanf("%d",&userlog[chmod]->revenue);
	printf("Please input the date\n");
	Assign_date(userlog[chmod]->date);
	userlog[chmod]=userlog[chmod]->next;
	printf("Add Successfully!\n");
}
void Delete(Userlog *userlog[20],int chmod,Userlog *front)
{
	if(chmod==-1)
	{
		front->next=front->next->next;
		printf("Delete Successfully!\n");
	}
	else
	{
		printf("Sorry ,you don't have permisson to this operate\n");
	}
}
void Modify(Userlog *userlog[20],int chmod, Userlog *front)
{
	if(chmod==-1)
	{
		printf("Please input the expenses you want to modify \n");
		scanf("%d",&front->next->expenses);
		printf("Please input the revenue you want to modify\n");
		scanf("%d",&front->next->revenue);
		printf("Please input the date you want to modify\n");
		Assign_date(front->next->date);
		printf("Modify Successfully!\n");
	}
	else
	{
		printf("Sorry ,you don't have permisson to this operate\n");		
	}

}
void Operation(Userlog *userlog[20],int chmod)
{
	Userlog *front;
	front=(Userlog*)malloc(sizeof(Userlog));
	if(chmod==-1)
	{
		int choice=0;
		int date[8];
		printf("Dear backstage administrator,Welcome you\n");
		printf("1.add\t2.delete\t3.modify\t4.inquire\n");
		scanf("%d",&choice);
		printf("Please input date you want to operation\n");
		Assign_date(date);
		Inquire(userlog,date,chmod,front);
	}
	else
	{
		printf("Welcome to you \n");
	}	
}
void Login(Account *account,Userlog *userlog[20])
{
	int name[6];
	int pwd[6];
	printf("Please input your username\n");
	Assign(name);
	printf("Please input your password\n");
	Assign(pwd);
	int chmod=Check(account,name,pwd);//2 for admin ,1 for user ,0 for none 
	Operation(userlog,chmod);
}
void printDate(int date[8])
{
	for (int i = 0; i < 8; ++i)
	{
		printf("%d\n",date[i]);
	}
}
void Registered(Account *account)
{
	printf("Please input the username you want to registered\n");
	Assign(account->user[account->usernum]->username);
	printf("Please input the password you want to registered\n");
	Assign(account->user[account->usernum]->password);
	account->usernum++;
	printf("Registered Successfully!\n");
	printf("Transferring to the login screen...\n");
}
int Choose()
{
	int tag=0;
	scanf("%d",&tag);
	if(tag!=1&&tag!=0)
	{
		tag=Choose();
	}
	return tag;
}
void init_admin(Admin *admin)
{
	int name[MAXSIZE]={1,7,2,8,2,0};
	int pwd[MAXSIZE]={0,0,0,3,2,3};
	for(int i=0;i<MAXSIZE;i++)
	{
		admin->username[i]=name[i];
		admin->password[i]=pwd[i];
	}
}
void init_account(Account *account)
{
	account=(Account*)malloc(sizeof(Account));
	account->admin=(Admin*)malloc(sizeof(Admin));
	init_admin(account->admin);
	account->usernum=0;
}
void Assign(int array[MAXSIZE])
{
	for(int i=0;i<MAXSIZE;i++)
	{
		scanf("%d",&array[i]);
	}
}
void Assign_date(int array[8])
{
	for(int i=0;i<8;i++)
	{
		scanf("%d",&array[i]);
	}
}
int diff(int username[MAXSIZE],int name[MAXSIZE])
{
	int label=1;
	for(int i=0;i<MAXSIZE;i++)
	{
		if(username[i]!=name[i])
		{
			label=-1;
			break;
		}
	}
	return label;
}
int diff_date(int date1[8],int date2[8])
{
	int label=1;
	for(int i=0;i<8;i++)
	{
		if(date1[i]!=date2[i])
		{
			label=0;
			break;
		}
	}
}
int Check(Account *account,int name[MAXSIZE],int pwd[MAXSIZE])
{
	int chmod=0;
	int isadmin=diff(account->admin->username,name)+diff(account->admin->password,pwd);
	if(isadmin==2)
	{
		chmod=-1;
	}
	if(isadmin!=2)
	{
		for(int i=0;i<20;i++)
		{
			chmod=diff(account->user[i]->username,name)+diff(account->user[i]->password,pwd);
			if(chmod==2)
			{
				chmod=i;
				break;
			}
		}
	}
	return chmod;
}
