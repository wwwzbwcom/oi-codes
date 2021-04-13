#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1100;
const int mod=123456789;
int n,m,kk;
int q;
char str[maxn];
int xro[maxn],adn[maxn];
int dyp[maxn][maxn];
int main()
{
	scanf("%d%d%d",&n,&m,&kk);
	for(int i=1;i<=n;i++)
	{
		int a,b;	scanf("%d%d",&a,&b);
		for(int j=1;j<=b;j++)
		{
			int l,r;	scanf("%d%d",&l,&r);
			for(int k=l;k<=r;k++)
			{
				if(a==0)	adn[k]+=(1<<(i-1));
				else		xro[k]+=(1<<(i-1));
			}
		}
	}
	for(int i=1;i<=m;i++)	cout<<i<<"=="<<xro[i]<<" "<<adn[i]<<" "<<((0^xro[i])&adn[i])<<endl;
	dyp[0][0]=1;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=kk;j++)
			for(int k=0;k<(1<<n);k++)
				if(j+1<=kk)	dyp[j+1][((k^xro[i])|adn[i])]=(dyp[j+1][((k^xro[i])|adn[i])]+dyp[j][k])%mod;
	for(int i=0;i<(1<<n);i++)	cout<<i<<"="<<dyp[kk][i]<<endl;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%s",str);
		int len=strlen(str),con=0;
		for(int j=0;j<len;j++)	con+=(1<<(str[j]-'A'));
		printf("%d\n",dyp[kk][con]);
	}
}
