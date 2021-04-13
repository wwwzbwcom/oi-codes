#include<cstring>
#include<cstdio>
using namespace std;
const int maxn=10100;
int gn;
char str[maxn];
int main()
{
	scanf("%d",&gn);
	while(gn--)
	{
		scanf("%s",str);
		int len=strlen(str),cnt=0,cur=0,ans=0,con=0;
		str[len]='0';
		for(int i=0;i<=len;i++)
		{
			if(str[i]=='0')
			{
				if(con==0)	cnt++;
				else
				{
				//	cout<<cnt<<" "<<cur<<endl;
					if(cnt%2)	ans^=(cur%3);
					else	ans^=0;
					cnt++;
					con=0;
				}
			}
			else
			{
				if(con==0)	cur=1,con=1;
				else	cur++;
			}
		}
		if(ans)	printf("first\n");
		else	printf("second\n");
	}
}
