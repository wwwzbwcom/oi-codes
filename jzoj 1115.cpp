#include<iostream>
#include<cstring>
using namespace std;
int n,m,mod;
class Matrix
{
	public:
		int m[30][30];
		int y,x;
		void init(int yi,int xi)
		{
			y=yi;	x=xi;
			memset(m,0,sizeof m);
		}
		Matrix operator *(const Matrix &in)const
		{
			Matrix ans;	ans.init(y,in.x);
			for(int i=0;i<y;i++)
				for(int j=0;j<in.x;j++)
					for(int k=0;k<x;k++)
						ans.m[i][j]=(ans.m[i][j]+m[i][k]*in.m[k][j])%mod;
			return ans;
		}
		Matrix operator ^(const int &in)const
		{
			if(in==1)	return *this;
			else
			{
				Matrix ans=*this^(in/2);
				ans=ans*ans;
				if(in%2==0)	return ans;
				else	return ans*(*this);
			}
		}
}ma;
class Kmp
{
	public:
		char str[30];
		int nxt[30];
		void getkmp()
		{
			nxt[0]=nxt[1]=0;
			int fix=0;
			for(int i=2;i<=m;i++)
			{
				while(fix&&str[fix+1]!=str[i])	fix=nxt[fix];
				if(str[fix+1]==str[i])	fix++;
				nxt[i]=fix;
			}
		}
}kp;
int qsm(int a,int b)
{
	if(b==0)	return 1;
	else
	{
		int ans=qsm(a,b/2);
		ans=(ans*ans)%mod;
		if(b%2==0)	return ans;
		else	return (ans*a)%mod;
	}
}
int nxt[30][10];
int work()
{
	ma.init(m+1,m+1);
	for(int i=0;i<m;i++)
		for(int j=0;j<=9;j++)
		{
			if(kp.str[i+1]-'0'==j)	nxt[i][j]=i+1;
			else	nxt[i][j]=nxt[kp.nxt[i]][j];
			ma.m[i][nxt[i][j]]++;
		}
	ma.m[m][m]=10;
	ma=ma^n;
	return ma.m[0][m];
}
int main()
{
	cin>>n>>m>>mod;
	for(int i=1;i<=m;i++)	cin>>kp.str[i];
	if(n==0)
	{
		cout<<0<<endl;
		return 0;
	}
	kp.getkmp();
//	cout<<qsm(10,n)<<" "<<work()<<endl; 
	cout<<((qsm(10,n)-work())%mod+mod)%mod<<endl;
}
