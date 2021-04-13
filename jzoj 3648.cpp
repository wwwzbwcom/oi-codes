#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2000100;
class Externkmp
{
	private:
		char str[2][maxn];
		int nxt[2][maxn];	
	public:
		int len[2];
		int ext[2][maxn];
		void input()
		{
			scanf("%d",&len[0]);
			len[1]=len[0];
			scanf("%s%s",str[0],str[1]);
		}
		void getnxt()
		{
			for(int k=0;k<2;k++)
			{
				nxt[k][0]=len[k];
				while(nxt[k][1]+1<len[k]&&str[k][nxt[k][1]+1]==str[k][nxt[k][1]])	nxt[k][1]++;
				int p=1;
				for(int i=2;i<len[k];i++)
				{
					if(i+nxt[k][i-p]<p+nxt[k][p])	nxt[k][i]=nxt[k][i-p];
					else
					{
						if(p+nxt[k][p]-1-i+1>0)	nxt[k][i]=p+nxt[k][p]-1-i+1;	else	nxt[k][i]=0;
						while(nxt[k][i]+i<len[k]&&str[k][nxt[k][i]]==str[k][nxt[k][i]+i])	nxt[k][i]++;
						p=i;
					}
				}
			}
		//	for(int i=0;i<len[0];i++)	cout<<nxt[0][i]<<" "<<nxt[1][i]<<endl;
		}
		void getext()
		{
			for(int k=0;k<2;k++)
			{
				while(ext[k][0]<len[k^1]&&ext[k][0]<len[k]&&str[k^1][ext[k][0]]==str[k][ext[k][0]])	ext[k][0]++;
				int p=0;
				for(int i=1;i<len[k];i++)
				{
					if(i+nxt[k^1][i-p]<p+ext[k][p])	ext[k][i]=nxt[k^1][i-p];
					else
					{
						if(p+ext[k][p]-1-i+1>0)	ext[k][i]=p+ext[k][p]-1-i+1;	else	ext[k][i]=0;
						while(ext[k][i]<len[k^1]&&ext[k][i]+i<len[k]&&str[k^1][ext[k][i]]==str[k][ext[k][i]+i])	ext[k][i]++;
						p=i;
					}
				}
			}
		}
}ek;
int fat[maxn];
int ans=0;
int getfat(int p,int lim)
{
//	cout<<p<<" "<<ek.ext[0][p]<<" "<<fat[p]<<endl;
	if(ek.ext[0][p]>=lim)	return p;
	else
	{
		if(fat[p]==-1)	return -1;
		else	return fat[p]=getfat(fat[p],lim);
	}
}
int main()
{
	freopen("beyond3.in","r",stdin);
	ek.input();
	ek.getnxt();
	ek.getext();
//	for(int i=0;i<ek.len[0];i++)	cout<<ek.ext[0][i]<<" "<<ek.ext[1][i]<<endl;
	for(int i=0;i<ek.len[0];i++)	fat[i]=i-1;
	for(int i=0;i<ek.len[1];i++)
	{
	//	cout<<i<<"=="<<ek.ext[1][i]<<endl;
		int tmp=getfat(ek.ext[1][i],i);
	//	cout<<i<<"=="<<tmp<<endl;
		if(tmp>0)	ans=max(ans,tmp+i);
	}
	printf("%d",ans);
}
