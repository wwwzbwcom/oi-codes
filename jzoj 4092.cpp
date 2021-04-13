#include<iostream>
#include<cstring>
using namespace std;
const int mod=1e9+7;
class Matrix
{
	public:
		int m[40][40];
		int y,x;
		Matrix(int yi,int xi)
		{
			memset(m,0,sizeof m);
			y=yi;	x=xi;
		}
		Matrix operator *(const Matrix &in)const
		{
			Matrix ans(y,in.x);
			for(int i=0;i<y;i++)
				for(int j=0;j<in.x;j++)
					for(int k=0;k<x;k++)
						ans.m[i][j]=(ans.m[i][j]+m[i][k]*(long long)in.m[k][j])%(long long)mod;
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
		Matrix debug()
		{
			for(int i=0;i<y;i++)
			{
				cout<<i<<" ";
				for(int j=0;j<x;j++)
					cout<<m[i][j]<<" ";
				cout<<endl;
			}
			cout<<"===================";
		 } 
}ma(32,32);
bool judge(int a,int b)
{
	if((a&1)==0&&a+1==b)	return 1;
	if((a&2)==0&&a+2==b)	return 1;
	if((a&4)==0&&a+4==b)	return 1;
	if((a&8)==0&&a+8==b)	return 1;
	if((a&16)==0&&a+16==b)	return 1;
	return 0;
}
void init()
{
	for(int i=16;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			if((i<<1)-32<16)
			{
				if((i<<1)-32+16==j)	ma.m[i][j]++; 
			}
			else
			{
				if(judge((i<<1)-32,j))	ma.m[i][j]++;
			}
		//	cout<<ma.m[i][j]<<" ";
		}
		//cout<<endl;
	}
}
int main()
{
	init();
	ma.debug();
	long long n;	cin>>n;
	ma=ma^n;
	ma.debug();
	//for(int i=0;i<32;i++)	cout<<i<<' '<<ma.m[28][i]<<endl;
	cout<<ma.m[28][28]<<endl;
}
