#include<iostream>
#include<cstring>
using namespace std;
class Matrix
{
	public:
		int m[60][60];
		int y,x;
		void init(int yi,int xi)
		{
			memset(m,0,sizeof m);
			y=yi;	x=xi;
		}
		Matrix operator *(const Matrix &in)const
		{
			Matrix ans;	ans.init(y,in.x);
			for(int i=0;i<y;i++)
				for(int j=0;j<in.x;j++)
					for(int  k=0;k<x;k++)
					{
						ans.m[i][j]=(ans.m[i][j]+m[i][k]*in.m[k][j])%10000;
					}
			return ans;
		}
		Matrix operator ^(const int &in)const
		{
			if(in==1)	return *this;
			else
			{
				Matrix ans=(*this)^(in/2);
				ans=ans*ans;
				if(in%2==0)	return ans;
				else	return ans*(*this);
			}
		}
		void debug()
		{
			for(int i=0;i<y;i++)
			{
				for(int j=0;j<x;j++)	cout<<m[i][j]<<"";
				cout<<endl;
			}
			cout<<"=================="<<endl;
		}
}ba,ma[15],ans;
int n,m,sta,end,k;
int nf;
int ron[30];
int ros[30][5];
int main()
{
	cin>>n>>m>>sta>>end>>k;
	ba.init(n,n);
	for(int i=0;i<m;i++)
	{
		int x,y;	cin>>x>>y;
		ba.m[x][y]=ba.m[y][x]=1;
	}
	cin>>nf;
	for(int i=0;i<nf;i++)
	{
		cin>>ron[i];
		for(int j=0;j<ron[i];j++)	cin>>ros[i][j];
	}
	for(int i=0;i<12;i++)
	{
		ma[i]=ba;
		for(int j=0;j<nf;j++)	memset(ma[i].m[ ros[j][ i%ron[j] ] ],0,sizeof ma[i].m[ ros[j][ i%ron[j] ] ]);
	}
	//for(int i=0;i<12;i++)	ma[i].debug();
	
	if(k/12>0)
	{
		ans=ma[0];
		for(int i=1;i<12;i++)	ans=ans*ma[i];
		ans=ans^k/12;
		for(int i=0;i<k%12;i++)	ans=ans*ma[i];
	}
	else
	{
		ans=ma[0];
		for(int i=1;i<k;i++)	ans=ans*ma[i];
	}
	cout<<ans.m[sta][end];
}
