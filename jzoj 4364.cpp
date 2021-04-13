#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=100100;
const int mod=10007;
int pos;
char tmp[maxn];
struct bigNum
{
	int sto[maxn];
	int dyp[maxn][2][3][3];
	int vis[maxn][2];
	int len;
	bigNum()
	{
		memset(sto,0,sizeof sto);
		len=0;
	}
	void build()
	{
		scanf("%s",tmp+1);
		len=strlen(tmp+1);
		for(int i=1;i<=len;i++)	sto[i]=tmp[len-i+1]-'0';
	}
	int operator %(const int &in)const
	{
		int ans=0;
		for(int i=len;i>=1;i--)
		{
			ans=(ans*10+sto[i])%3;
		}
		return ans;
	}
	void work(int p,int c)
	{ 
		if(vis[p][c])	return;
		vis[p][c]=1;
		int top;
		if(c==1)	top=sto[p];	else	top=9;
		if(p==1)
		{
			for(int i=0;i<=top;i++)
			{
				if(i!=2&&i!=3&&i!=5&&i!=7)	dyp[p][c][0][i%3]++;
				else	dyp[p][c][1][i%3]++;
			}
			return;
		}
		for(int i=0;i<=top;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(c==1&&i==top)
				{
					work(p-1,1);
					if(i!=2&&i!=3&&i!=5&&i!=7)
					{
						dyp[p][c][0][j]+=dyp[p-1][1][0][((j-i)%3+3)%3];
						if(i!=0)	dyp[p][c][0][j]+=dyp[p-1][1][1][((j-i)%3+3)%3]+dyp[p-1][1][2][((j-i)%3+3)%3];
						else	dyp[p][c][2][j]+=dyp[p-1][1][1][((j-i)%3+3)%3]+dyp[p-1][1][2][((j-i)%3+3)%3];
					}
					else
					{
						dyp[p][c][1][j]+=dyp[p-1][1][1][((j-i)%3+3)%3];
						dyp[p][c][0][j]+=dyp[p-1][1][0][((j-i)%3+3)%3]+dyp[p-1][1][2][((j-i)%3+3)%3];
					}
				}
				else
				{
					work(p-1,0);
					if(i!=2&&i!=3&&i!=5&&i!=7)
					{
						dyp[p][c][0][j]+=dyp[p-1][0][0][((j-i)%3+3)%3];
						if(i!=0)	dyp[p][c][0][j]+=dyp[p-1][0][1][((j-i)%3+3)%3]+dyp[p-1][0][2][((j-i)%3+3)%3];
						else	dyp[p][c][2][j]+=dyp[p-1][0][1][((j-i)%3+3)%3]+dyp[p-1][0][2][((j-i)%3+3)%3];
					}
					else
					{
						dyp[p][c][1][j]+=dyp[p-1][0][1][((j-i)%3+3)%3];
						dyp[p][c][0][j]+=dyp[p-1][0][0][((j-i)%3+3)%3]+dyp[p-1][0][2][((j-i)%3+3)%3];
					}
				}
				dyp[p][c][0][j]%=mod;
				dyp[p][c][1][j]%=mod;
			}
		//	if(p>=2)
		//	cout<<p<<"="<<c<<"="<<i<<"="<<dyp[p][c][0][pos]<<"="<<dyp[p][c][1][pos]<<"="<<dyp[p][c][2][pos]<<endl;
		}
	}
}s,t,num;
int main()
{
	s.build();
	t.build();//	t=t+1;
//	cout<<t.sto[1]<<endl;
	pos=s%3;
	s.work(s.len,1);
	t.work(t.len,1);
	printf("%d",((s.dyp[s.len][1][0][pos]-t.dyp[t.len][1][0][pos])%mod+mod)%mod);
}
