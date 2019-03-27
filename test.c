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
Admin* init_admin();
Account* init_account();
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
void putArray(FILE *fp,int array[MAXSIZE]);
Userlog* init_userlog();
User* init_user();


int main(int argc, char const *argv[])
{
	Account *account;
	Userlog *userlog[20];
	account=init_account();
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
	userlog[chmod]=init_userlog();
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
	if(chmod!=-2)
	{

	}
	if(chmod=-2)
	{
		printf("Sorry ,you don't have permisson to this operate\n");		
	}

}
void Operation(Userlog *userlog[20],int chmod)//-1 for admin ,-2 for none,else for user 
{
	Userlog *front;
	front=init_userlog();
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
	else if(chmod)
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
	int chmod=Check(account,name,pwd);//-1 for admin ,-2 for none,else for user 
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
	account->user[account->usernum]=init_user();
	FILE *fp=fopen("user.txt","a+");
	printf("Please input the username you want to registered\n");
	Assign(account->user[account->usernum]->username);
	fputs("Username:  ",fp);
	putArray(fp,account->user[account->usernum]->username);
	fputs("Password:  ",fp);
	printf("Please input the password you want to registered\n");
	Assign(account->user[account->usernum]->password);
	putArray(fp,account->user[account->usernum]->password);
	fclose(fp);
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
void putArray(FILE *fp,int array[MAXSIZE])
{
	for (int i = 0; i < MAXSIZE; ++i)
	{
		fprintf(fp, "%d",array[i]);
	}
	fprintf(fp,"\n");
}
Admin* init_admin()
{
	Admin *admin;
	admin=(Admin*)malloc(sizeof(Admin));
	int name[MAXSIZE]={1,7,2,8,2,0};
	int pwd[MAXSIZE]={0,0,0,3,2,3};
	FILE *fp=fopen("admin.txt","w+");
	fputs("Username:  ",fp);
	putArray(fp,name);
	fputs("Password:  ",fp);
	putArray(fp,pwd);
	for(int i=0;i<MAXSIZE;i++)
	{
		admin->username[i]=name[i];
		admin->password[i]=pwd[i];
	}
	fclose(fp);
	return admin;
}
User* init_user()
{
	User *user;
	user=(User*)malloc(sizeof(User));
	return user;
}
Account* init_account()
{
	Account *account;
	account=(Account*)malloc(sizeof(Account));
	account->admin=init_admin();
	account->usernum=0;
	return account;
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
	return label;
}
int Check(Account *account,int name[MAXSIZE],int pwd[MAXSIZE])
{
	int chmod=-2;
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
Userlog* init_userlog()
{
	Userlog *userlog;
	userlog=(Userlog*)malloc(sizeof(Userlog));
	return userlog;
}
