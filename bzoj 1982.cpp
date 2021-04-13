#include<algorithm>
#include<cstdio>
using namespace std;
int n;
int sto[100100];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)	scanf("%d",&sto[i]);
	sort(sto,sto+n);
	int flag=0,las=0,ans=0;
	for(int i=0;i<n;i++)
	{
		if(flag==0)	las=sto[i],flag=1;
		else
		{
			flag=0;
			if(las!=sto[i])	ans=1;
		}
	}
	if(ans==0)	printf("second player");
	else	printf("first player");
}
