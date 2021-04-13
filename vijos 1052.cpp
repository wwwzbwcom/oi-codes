#include<iostream>
#include<cmath>
using namespace std;
class Matrix
{
	public:
		double m[200][200];
		double ans[200];
		int y,x;
		void debug()
		{
			for(int i=0;i<y;i++)
			{
				for(int j=0;j<x;j++)	cout<<m[i][j]<<" ";
				cout<<endl;
			}
		}
		void guass()
		{
			int ky=0,kx=0;
			for(int ky=0,kx=0;ky<y&&kx<x-1;ky++,kx++)
			{
				int p=ky;
				for(int i=ky+1;i<y;i++)	if(abs(m[i][kx])>abs(m[p][kx]))	p=i;
				if(p!=ky)	swap(m[p],m[ky]);
				if(m[ky][kx]==0){	ky--;	continue;	}
				
				for(int i=ky+1;i<y;i++)	if(i!=ky)
				{
					double	tmp=m[i][kx]/m[kx][kx];
					for(int j=kx;j<x;j++)	m[i][j]-=tmp*m[kx][j];
				}
			//	debug();
			}
			//debug();
			ans[x-1]=1;
			for(int i=x-2;i>=0;i--)
			{
				for(int j=i+1;j<x;j++)	ans[i]-=ans[j]*m[i][j]; 
				ans[i]/=m[i][i];
			//	cout<<i<<" "<<m[i][i]<<endl; 
			}
			for(int i=0;i<y;i++)	cout<<(int)(ans[i]+0.5)<<" ";
		}
}ma;
int n;
int main()
{
	cin>>n;
	ma.y=n;	ma.x=n+1;
	for(int i=0;i<ma.y;i++)
	{
		for(int j=0;j<ma.x;j++)	cin>>ma.m[i][j];
		ma.m[i][ma.x-1]=-ma.m[i][ma.x-1];
	//	cout<<"="<<endl;
	}
	//ma.debug();
	ma.guass();
}
