#include<stdio.h>

char changes(int n)
{
	switch(n)
	{
		case 0:	printf("ling");break;
		case 1:	printf("yi");break;
		case 2:printf("er");break;
		case 3:printf("san");break;
		case 4:printf("si");break;
		case 5:printf("wu");break;
		case 6:printf("liu");break;
		case 7:printf("qi");break;
		case 8:printf("ba");break;
		case 9:printf("jiu");break;
	}	
}

int main()
{
	int n,remark=0;
	scanf("%d",&n);
	if(n<0)
	{
		n=-n;
		remark=1;
	}
	int	t=n;
	int mask=1;
	while(t>9)
	{
		t/=10;
		mask*=10;
	}
	int d;
	if(remark==1)
	{
		printf("fu ");
	}
	do
	{
		d=n/mask;
		changes(d);
		if(mask>9)
		{
			printf(" ");
		}
		n%=mask;
		mask/=10;
	}while(mask>0);

	return 0;
}
