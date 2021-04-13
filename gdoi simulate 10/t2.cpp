#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
const int maxn=1e5+10;
const int mod=1e8+7;
struct Hash
{
	int mul[maxn];
	int rev[maxn];
	int has[maxn];
	int n;
	map <int,int> boo;
	void init()
	{
		mul[0]=1;	for(int i=1;i<maxn;i++)	mul[i]=(mul[i-1]*130ll)%(long long)mod;
		rev[0]=1;	for(int i=1;i<maxn;i++)	rev[i]=(rev[i-1]*13076924ll)%(long long)mod;
		has[0]=0;	n=0;
	}
	inline int getkey(int p,int l)
	{
		return (((has[p+l-1]-has[p-1])%mod+mod)%mod*(long long)rev[p-1])%mod;
	}
	inline void movefront(char c)
	{
		n++;
		has[n]=((long long)has[n-1]+(long long)mul[n]*c)%(long long)mod;
		for(int i=1;i<=n;i++)	boo[getkey(i,n-i+1)]++;
	}
	inline void moveback()
	{
		for(int i=1;i<=n;i++)
		{
			int key=getkey(i,n-i+1);
			boo[key]--;
			if(boo[key]==0)	boo.erase(key);
		}
		has[n]=0;
		n--;
	}
}h;
char opt[maxn];
int main()
{
	h.init();
	scanf("%s",opt);
	int len=strlen(opt);
	for(int i=0;i<len;i++)
	{
		if(opt[i]=='-')	h.moveback();
		else	h.movefront(opt[i]);
		printf("%d\n",(int)h.boo.size());
	}
}
