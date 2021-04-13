#include<iostream>
#include<cstring>
#include<string>
using namespace std;
string as,bs,ts;
string ah,at,bh,bt;
int an,bn;
int bd[2];
int n,m,mod;
long long ans;
struct Matrix
{
	Matrix(int yi,int xi)
	{
		y=yi;	x=xi;
		memset(m,0,sizeof m);
	}
	
	int m[10][10];
	int y,x;
	Matrix operator *(const Matrix &in)const
	{
		Matrix ans(y,in.x);
		for(int i=0;i<y;i++)
			for(int j=0;j<x;j++)
				for(int k=0;k<in.x;k++)
					ans.m[i][k]=(ans.m[i][k]+m[i][j]*(long long)in.m[j][k])%(long long)mod;
		return ans;
	}
	Matrix operator ^(const int &in)const
	{
		if(in==1)	return *this;
		else
		{
			Matrix tmp=(*this)^(in/2);
			tmp=tmp*tmp;
			if(in%2==0)	return tmp;
			else	return tmp * *this;
			
		}
	}
};
int main()
{
	as="0";	bs="1";
	cin>>n>>m>>mod;
	cin>>ts;
	int p;
	for(p=1;p<=n;p++)
	{
		if(as.size()<2*m)
		{
			swap(as,bs);
			bs+=as;
		}
		if(as.size()>=2*m)	break;
	}
	for(int i=0;i<=as.size()-m;i++)	if(as.substr(i,m)==ts)	an++;
	for(int i=0;i<=bs.size()-m;i++)	if(bs.substr(i,m)==ts)	bn++;
	an%=mod;	bn%=mod;
	if(p>=n)
	{
		cout<<an<<endl;
		return 0;
	}
	if(m>1)
	{
		p++;
		ah=as.substr(0,m-1);	at=as.substr(as.size()-m+1,m-1);
		bh=bs.substr(0,m-1);	bt=bs.substr(bs.size()-m+1,m-1);
		string	tmp;
		swap(an,bn);	bn+=an; 
		tmp=at+bh;
		for(int i=0;i<=tmp.size()-m;i++)	if(tmp.substr(i,m)==ts)	if(i<at.size())	bn++;
		bn%=mod;
		if(p>=n)
		{
			cout<<an<<endl;
			return 0;
		}
		
		tmp=bt+ah;
		for(int i=0;i<=tmp.size()-m;i++)	if(tmp.substr(i,m)==ts)	bd[0]++;
		bd[0]%=mod;
		tmp=bt+bh;
		for(int i=0;i<=tmp.size()-m;i++)	if(tmp.substr(i,m)==ts)	bd[1]++;
		bd[1]%=mod;
		p++;
	}
	Matrix mat(4,4);
	mat.m[0][0]=0;	mat.m[0][1]=1;	mat.m[0][2]=0;	mat.m[0][3]=0;
	mat.m[1][0]=1;	mat.m[1][1]=1;	mat.m[1][2]=1;	mat.m[1][3]=0;
	mat.m[2][0]=0;	mat.m[2][1]=0;	mat.m[2][2]=0;	mat.m[2][3]=1;
	mat.m[3][0]=0;	mat.m[3][1]=0;	mat.m[3][2]=1;	mat.m[3][3]=0;
	if(n-p+1!=0)	mat=mat^(n-p+1);
	ans+=mat.m[0][0]*(long long)an;	ans%=(long long)mod;
	ans+=mat.m[0][1]*(long long)bn;	ans%=(long long)mod;
	ans+=mat.m[0][2]*(long long)bd[0];	ans%=(long long)mod;
	ans+=mat.m[0][3]*(long long)bd[1];	ans%=(long long)mod;
	cout<<ans<<endl;
}
