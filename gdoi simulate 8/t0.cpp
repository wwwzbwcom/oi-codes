#include<cstdio>
#include<cstring>
#include<map> 
using namespace std;
const int maxn=50010;
int n,d;
char str[maxn][5];
int bu1[1800000];
map <int,int> bu2[1800000];
int mul[50];
int lis[50],ln;
int bit[50];
void init()
{
	mul[0]=1;
	for(int i=1;i<4;i++)	mul[i]=mul[i-1]*36;
	
	for(int i=0;i<20;i++)
	{
		int tmp=i,ans=0;
		while(tmp)
		{
			ans+=tmp%2;
			tmp>>=1;
		}
		bit[i]=ans;
	}
}
int getkey(int p,int con)
{
	int ans=0,cnt=0;
	while(con)
	{
		if(con%2==1)	ans+=str[p][cnt]*mul[cnt];
		cnt++;	con>>=1;
	}
	return	ans;
}
void dfs(int p,int c,int con)
{
	if(c>d)	return;
	if(p==4)
	{
		if(c==d)	lis[ln++]=con;
		return;
	}
	dfs(p+1,c+1,con+(1<<p));	dfs(p+1,c,con);
}
int main()
{
	//freopen("idioms12.in","r",stdin);
	init();
	scanf("%d%d",&n,&d);
	getchar();
	dfs(0,0,0);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<4;j++)
		{
			str[i][j]=getchar();
			if('0'<=str[i][j]&&str[i][j]<='9')	str[i][j]=str[i][j]-'0'+1;	else	str[i][j]=str[i][j]-'a'+11;
		}
		getchar();
	}
	long long ans=0;
	for(register int i=0;i<ln;i++)
	{
		
		for(register int j=0;j<n;j++)
		{
			bu1[getkey(j,15^lis[i])]++;
			for(int k=0;k<16;k++)
			{
				if((k&lis[i])==k&&bit[k]>0)	bu2[getkey(j,15^lis[i])][getkey(j,k)]++;
			}
		}
		for(register int j=0;j<n;j++)
		{
			long long cur=0;	 
			for(int k=0;k<16;k++)
				if((k&lis[i])==k&&bit[k]>0)
				{
					if(bit[k]%2==1)	cur+=(bu2[getkey(j,15^lis[i])][getkey(j,k)]-1);
					if(bit[k]%2==0)	cur-=(bu2[getkey(j,15^lis[i])][getkey(j,k)]-1);
				}
			cur=bu1[getkey(j,15^lis[i])]-1-cur;
			ans+=cur;
			
		}
		memset(bu1,0,sizeof bu1);
		for(int j=0;j<n;j++)	bu2[getkey(j,15^lis[i])].clear();
	}
	printf("%lld\n",ans/2);
}
