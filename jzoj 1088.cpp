#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int mod=45989;
struct Matrix
{
	int m[121][121];
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
					ans.m[i][j]=(ans.m[i][j]+m[i][k]*in.m[k][j])%mod;
		return ans;
	}
	Matrix operator ^(const int &in)const
	{
	//	cout<<in<<endl;
		if(in==1)	return *this;
		else
		{
			Matrix tmp=(*this)^(in/2);
			if(in%2==0)	return tmp*tmp;
			else	return	tmp*tmp*(*this);
		}
	}
};
int map[30][30][100];
int cnt[30][30];
int n,m,t,s,e;
int main()
{
	//cin>>n>>m>>t>>s>>e;
	scanf("%d%d%d%d%d",&n,&m,&t,&s,&e);
//	cout<<t<<endl;
	for(int i=0;i<m;i++)
	{
		int u,v;	scanf("%d%d",&u,&v);
		map[u][v][cnt[u][v]++]=i*2;
		map[v][u][cnt[v][u]++]=i*2+1;
	}
	Matrix ma(2*m,2*m);
	for(int i=0;i<n;i++)
		for(int k=0;k<n;k++)	if(cnt[i][k]!=0)
			for(int j=0;j<n;j++)	if(cnt[k][j]!=0)
			{
				for(int a=0;a<cnt[i][k];a++)
					for(int b=0;b<cnt[k][j];b++)	if(map[i][k][a]/2!=map[k][j][b]/2)
					//	cout<<map[i][k][a]<<" "<<map[k][j][b]<<endl,
						ma.m[map[i][k][a]][map[k][j][b]]++;
			}
	/*
	cout<<endl;
	for(int i=0;i<2*m;i++)
	{
		for(int j=0;j<2*m;j++)
			cout<<ma.m[i][j]<<" ";
		cout<<endl;
	}
	ma=ma*ma;
	cout<<endl;
	for(int i=0;i<2*m;i++)
	{
		for(int j=0;j<2*m;j++)
			cout<<ma.m[i][j]<<" ";
		cout<<endl;
	}
	*/	
	if(t-1==0)
	{
		printf("%d",cnt[s][e]); 
	}
	else
	{
		ma=ma^(t-1);
		int ans=0; 
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				for(int a=0;a<cnt[s][i];a++)
					for(int b=0;b<cnt[j][e];b++)
					//	cout<<map[s][i][a]<<"="<<map[j][e][b]<<"="<<ma.m[map[s][i][a]][map[j][e][b]]<<endl,
						ans+=ma.m[map[s][i][a]][map[j][e][b]],ans%=mod;
			}
		printf("%d",ans);
	}
}
