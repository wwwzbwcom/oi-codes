#include<cstdio>
#include<algorithm> 
using namespace std;
int main()
{
	int gn;	scanf("%d",&gn);
	while(gn--)
	{
		int x,y,d;	scanf("%d%d%d",&x,&y,&d);
		if(x==1&&y==1)
		{
			printf("lose again\n");
			continue; 
		}
		if(x==1||y==1)
		{
			printf("finally win\n");
			continue;
		}
		if(abs(x-y)<d)
		{
			printf("finally win\n");
			continue;
		}
		if(abs(x-y)<d+1)
		{
			printf("lose again\n");
			continue;
		}
		else
		{
			printf("finally win\n");
			continue;
		}
	}
}
