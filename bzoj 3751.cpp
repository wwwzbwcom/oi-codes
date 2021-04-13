#include<cstdio>
#include<cstring>
using namespace std;
int mn=5;
int mod[5]={10007,11261,19997,21893,20947};
int n,m;
char str[1001000];
int a[5][110];
int x[5][22000][110];
int res[5][22000];
int ans[1001000],an;
int main()
{
	freopen("equation310.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)
	{
		scanf("%s",str);	int len=strlen(str);
		int sta=0;	if(str[0]=='-')	sta=1;
		for(int j=0;j<mn;j++)
		{
			for(int k=sta;k<len;k++)
			{
				if(sta==1)	a[j][i]=(a[j][i]*10-(str[k]-'0'))%mod[j];
				else		a[j][i]=(a[j][i]*10+(str[k]-'0'))%mod[j];
			}
		}
	}
	for(int i=0;i<mn;i++)
		for(int j=1;j<22000;j++)
		{
			x[i][j][0]=1;
			for(int k=1;k<=n;k++)
			{
				x[i][j][k]=(x[i][j][k-1]*j)%mod[i];
				if(x[i][j][k]==0)	break;
			}
		}
	for(int i=0;i<mn;i++)
		for(int j=1;j<22000;j++)
			for(int k=0;k<=n;k++)
			{
				res[i][j]=(res[i][j]+a[i][k]*x[i][j][k])%mod[i];
				if(x[i][j][k]==0)	break;
			//	if(j==2)	cout<<i<<" "<<k<<" "<<res[i][j]<<endl;
			}
//	cout<<res[0][1]<<"="<<endl;
	for(int i=1;i<=m;i++)
	{
		int flag=0;
		for(int j=0;j<mn;j++)	if(res[j][i%mod[j]]!=0)	{flag=1;	break;}
		if(flag==0)	ans[an++]=i;
	}
	printf("%d\n",an);
	for(int i=0;i<an;i++)	printf("%d\n",ans[i]);
}
