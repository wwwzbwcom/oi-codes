#include<iostream>
#include<cstring>
using namespace std;
long long m,a,c,x0,n,g;
long long mul(long long const &a,long long const &b,long long const &m)
{
	if(b==0)	return 0;
	else
	{
		long long ans=mul(a,b/2,m);
		ans=(ans+ans)%m;
		if(b%2==0)	return ans;
		else	return (ans+a)%m;
	}
}
class Matrix
{
	public:
		long long s[5][5];
		long long y,x;
		Matrix(long long yi,long long xi)
		{
			y=yi;	x=xi;
			memset(s,0,sizeof s);
		}
		Matrix operator *(const Matrix &in)const
		{
			Matrix ans(y,in.x);
			for(long long i=0;i<y;i++)
				for(long long j=0;j<in.x;j++)
					for(long long k=0;k<x;k++)
					{
					//	cout<<i<<" "<<j<<" "<<k<<" "<<mul(s[i][k],in.s[k][j],m)<<endl;
						ans.s[i][j]+=mul(s[i][k],in.s[k][j],m),ans.s[i][j]%m;
					}
			return ans;
		}
		Matrix operator ^(const long long &in)const
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
};
Matrix ma(2,2);
int main()
{
	cin>>m>>a>>c>>x0>>n>>g;
	if(n==0)	cout<<x0%g<<endl;
	else
	{
		ma.s[0][0]=a;	ma.s[0][1]=c;
		ma.s[1][0]=0;	ma.s[1][1]=1;
		ma=ma^n;
		cout<<(mul(ma.s[0][0],x0,m)+ma.s[0][1])%m%g<<endl;
	}
}
