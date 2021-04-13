#include<iostream>
#include<cstring>
using namespace std;
bool tmp[2][1000];
int a[10];
bool *f=&tmp[0][500];
bool *g=&tmp[1][500];
int gn=0;
int main()
{
	while(cin>>a[1]>>a[2]>>a[3]>>a[4]>>a[5]>>a[6])
	{
		if(a[1]==0&&a[2]==0&&a[3]==0&&a[4]==0&&a[5]==0&&a[6]==0)	break;
		memset(tmp,0,sizeof tmp);
		g[0]=1;
		while(a[1]||a[2]||a[3]||a[4]||a[5]||a[6])
		{
			for(int i=1;i<=6;i++)
				if(a[i])
				{
					a[i]--;
				//	cout<<"========================"<<endl;
					for(int j=-400;j<=400;j++)	if(g[j]==1)	f[j+i]=1,f[j-i]=1;//cout<<j+i<<" "<<j-i<<endl;
					for(int j=-400;j<=400;j++)	g[j]=f[j],f[j]=0;
				}
		}
		cout<<"Collection #"<<++gn<<":"<<endl;
		if(g[0])	cout<<"Can be divided."<<endl;
		else	cout<<"Can't be divided."<<endl;
		cout<<endl;
	}
}
