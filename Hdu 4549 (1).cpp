#include<iostream>
#include<cstring>
using namespace std;
const long long mod=1000000007;
struct Matrix
{
	long long s[10][10],x,y;
	
	Matrix(int a,int b):x(a),y(b){memset(s,0,sizeof s);}

	Matrix operator*(Matrix const in)const
	{ 
		Matrix ans(in.x,y);
		for(int i=0;i<y;i++)
			for(int j=0;j<in.x;j++)
				for(int k=0;k<x;k++)
				{
					ans.s[i][j]+=(s[i][k]*in.s[k][j])%(mod-1);
					ans.s[i][j]%=(mod-1);
				}
		return ans;
	}
	Matrix operator^(int in)const
	{
		Matrix ans=*this,temp=*this;
		in--;
		while(in)
		{
			if(in%2) ans=ans*temp;
			temp=temp*temp;
			in/=2;
		}
		return ans;
	}
};
long long mi(long long a,long long in)
{
	a%=mod;
	long long ans=a;
	long long temp=a;
	in--;
	while(in)
	{
		if(in%2) ans=(ans*temp)%mod;	
		temp=(temp*temp)%mod;
		in/=2;
	}
	return ans;
}
long long a,b,n;
int main()
{
//	cout<<mi(2,586268953)<<endl;
	Matrix fib(2,2),ad(1,2),bd(1,2); 
	fib.s[0][0]=1;fib.s[0][1]=1;fib.s[1][0]=1;fib.s[1][1]=0;
	ad.s[0][0]=0;ad.s[1][0]=1;
	bd.s[0][0]=1;bd.s[1][0]=0;
	cout<<(fib*fib*fib*fib*fib).s[0][0]<<endl;
	while(cin>>a>>b>>n)     
	{
		if(n==0) cout<<a<<endl;
		else if(n==1) cout<<b<<endl;
			else
			{
				n--;
				Matrix aa=fib,ba=fib^n;
				aa=fib^n;
				ba=fib^n;
				aa=aa*ad;
				ba=ba*bd;
			//	cout<<aa.s[0][0]<<" "<<ba.s[0][0]<<endl;
				a=mi(a,aa.s[0][0])%mod; b=mi(b,ba.s[0][0])%mod;
			//	cout<<a<<" "<<b<<endl; 
				cout<<(a*b)%mod<<endl;
			}
	}
}
