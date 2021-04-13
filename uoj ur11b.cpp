#include<iostream>
using namespace std;
struct BCJ
{
	private: 
		int fat[50];
	public:
		void init()
		{
			for(int i=0;i<50;i++)	fat[i]=i;
		}
		int find(int u)
		{
			if(fat[u]==u)	return u;
			else	return fat[u]=find(fat[u]);
		}
		bool merge(int u,int v)
		{
			if(find(u)==find(v))	return 0;
			fat[find(u)]=find(v);
			return 1;
		}
}a,b;
int n,m;
int u[30],v[30];
int main()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)	cin>>u[i]>>v[i];
	int ans=0;
	for(int i=0;i<(1<<m);i++)
	{
		a.init();	b.init();
		int flag=0;
		for(int j=0;j<m;j++)
		{
			if((i&(1<<j))==(1<<j))
			{
				if(a.merge(u[j],v[j])==0)
				{
					flag=1;
					break;
				}
			}
			else
			{
				if(b.merge(u[j],v[j])==0)
				{
					flag=1;
					break;
				}
			}
		}
		if(flag==0)
		{
			ans=1;
			break;
		}
	}
	if(ans)	cout<<"Yes"<<endl;
	else	cout<<"No"<<endl;
}
