#include<iostream>
#include<cstring>
using namespace std;
long long m,a,c,x0,n,g;
long long mul(long long a,long long b)
{
	long long ans=a*b-(long long)((long double)(a)*b/m)*m;
	if(ans<0)	ans=ans+m;
	
	return ans;
}
class Matrix
{
	public:
		long long m[2][2];
		int y,x;
		Matrix(int yi,int xi)
		{
			memset(m,0,sizeof m);
			y=yi;	x=xi;
		}
		Matrix operator*(const Matrix &in)const
		{
			Matrix ans(y,in.x);
			for(int i=0;i<y;i++)
				for(int j=0;j<in.x;j++)
					for(int k=0;k<x;k++)
						ans.m[i][j]=(ans.m[i][j]+mul(m[i][k],in.m[k][j]))%(::m);
			return ans;
		}
		Matrix operator^(const long long &in)const
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
}ma(2,2);
int main()
{

	cin>>m>>a>>c>>x0>>n>>g;
	ma.m[0][0]=a%m;	ma.m[0][1]=c%m;
	ma.m[1][0]=0;	ma.m[1][1]=1;
	ma=ma^n;
	cout<<(mul(x0,ma.m[0][0])+ma.m[0][1])%m%g<<endl;
}
