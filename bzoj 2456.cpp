#include<iostream>
using namespace std;
int n,num,cnt,cur;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num);
		if(num==cur)	cnt++;	else	cnt--;
		if(cnt<=0)	cur=num,cnt=0;
	}
	printf("%d",cur);
}
