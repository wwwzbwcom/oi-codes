#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
struct Matrix
{
	int m[210][210];
	int y,x;
	Matrix(int yi,int xi)
	{
		for(int i=0;i<210;i++)	for(int j=0;j<210;j++)	m[i][j]=1e9;
		y=yi;	x=xi;
	} 
	Matrix operator *(const Matrix &in)const
	{
		Matrix ans(y,in.x);
		for(int i=0;i<y;i++)
			for(int j=0;j<in.x;j++)
				for(int k=0;k<x;k++)
					ans.m[i][j]=min(ans.m[i][j],m[i][k]+in.m[k][j]);
		return ans;
	}
	Matrix operator ^(const int &in)const
	{
		if(in==1)	return *this;
		else
		{
			Matrix tmp=(*this)^(in/2);
			if(in%2==0)	return tmp*tmp;
			else	return	tmp*tmp*(*this);
		}
	}
};
int n,t,s,e;
int c[300],u[300],v[300];
int sto[600],sn;
int main()
{
	cin>>n>>t>>s>>e;
	sto[sn++]=s;
	sto[sn++]=e;
	for(int i=1;i<=t;i++)
	{
		cin>>c[i]>>u[i]>>v[i];
		sto[sn++]=u[i];	sto[sn++]=v[i];
	}
	sort(sto,sto+sn);
	sn=unique(sto,sto+sn)-sto;
	s=lower_bound(sto,sto+sn,s)-sto;
	e=lower_bound(sto,sto+sn,e)-sto;
	Matrix m(sn,sn);
	for(int i=1;i<=t;i++)
	{
		u[i]=lower_bound(sto,sto+sn,u[i])-sto;
		v[i]=lower_bound(sto,sto+sn,v[i])-sto;
		m.m[u[i]][v[i]]=m.m[v[i]][u[i]]=c[i];
	}
	m=m^n;
	cout<<m.m[s][e]<<endl;
}
