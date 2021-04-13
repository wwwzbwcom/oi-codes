#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
const int maxn=50100;
const long long mod=1000000009;
char ast[maxn];
char bst[maxn];
char tst[maxn];
struct AC
{
	struct Node
	{
		int nxt[27];
		int end,fail;
	}n[1000010];
	int nn,root;
	void insert(char str[])
	{
		int len=strlen(str+1);
		int u=root;
		for(int i=1;i<=len;i++)
		{
			if(n[u].nxt[str[i]-'A']==0)	n[u].nxt[str[i]-'A']=++nn;
			u=n[u].nxt[str[i]-'A'];
		}
		n[u].end++;
	}
	void build()
	{
		queue <int> que;
		for(int i=0;i<26;i++)
		{
			if(n[root].nxt[i]==0)	n[root].nxt[i]=root;
			else	n[n[root].nxt[i]].fail=root,que.push(n[root].nxt[i]);
		}
		while(!que.empty())
		{
			int u=que.front();	que.pop();
			for(int i=0;i<26;i++)
			{
				if(n[u].nxt[i]==0)	n[u].nxt[i]=n[n[u].fail].nxt[i];
				else	n[n[u].nxt[i]].fail=n[n[u].fail].nxt[i],que.push(n[u].nxt[i]);
			}
		}
	}
	int match(char str[])
	{
		int u=root;
		int len=strlen(str);
		int ans=0;
		for(int i=0;i<len;i++)
		{
			u=n[u].nxt[str[i]-'A'];
			int tmp=u;
			while(tmp)
			{
				ans+=n[tmp].end;
				tmp=n[tmp].fail;
			}
		}
		return ans;
	}
}ac;
struct HW
{
	int fst[maxn*2];
	int bst[maxn*2];
	long long mul[maxn*2];
	long long rev[maxn*2];
	long long fha[maxn*2];
	long long bha[maxn*2];
	int len;
	void build(char str[])
	{
		len=strlen(str);
		int cnt=1;
		fst[cnt++]='#';
		for(int i=0;i<len;i++)
		{
			fst[cnt++]=str[i];
			fst[cnt++]='#';
		}
		cnt=1;
		bst[cnt++]='#';
		for(int i=0;i<len;i++)
		{
			bst[cnt++]=str[len-i-1];
			bst[cnt++]='#';
		}
		len=cnt-1;
		mul[0]=1;	for(int i=1;i<maxn*2;i++)	mul[i]=(mul[i-1]*130)%mod;
		rev[0]=1;	for(int i=1;i<maxn*2;i++)	rev[i]=(rev[i-1]*161538463)%mod;
		for(int i=1;i<=len;i++)	fha[i]=(fha[i-1]+fst[i]*mul[i])%mod;
		for(int i=1;i<=len;i++)	bha[i]=(bha[i-1]+bst[i]*mul[i])%mod;
	}
	long long fkey(int l,int r)
	{
		return (((fha[r]-fha[l-1])%mod+mod)%mod*rev[l-1])%mod;
	}
	long long bkey(int l,int r)
	{
		return (((bha[r]-bha[l-1])%mod+mod)%mod*rev[l-1])%mod;
	}
	int huiwen(int p)
	{
		int l=1,r=min(p,len-p+1),ans=0;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(p-mid+1<=0||p+mid-1>len)	break;
			if(fkey(p,p+mid-1)==bkey((len-p+1),(len-p+1)+mid-1))	ans=mid,l=mid+1;
			else	r=mid-1;
		}
		return ans-1;
	}
}hw;
int main()
{
	scanf("%s",ast);
	scanf("%s",bst);
	hw.build(ast);
	int len=strlen(ast);
	for(int i=1;i<=2*len+1;i++)
	{
		int tmp=hw.huiwen(i),p=i/2;
		for(int j=0;j<=tmp/2;j++)
		{
			int cnt=1;
			if(i%2==1)
			{
				if(j!=0)	for(int k=(p)-j+1;k<=(p+1)+j-1;k++)	tst[cnt++]=ast[k-1];
			}
			else
			{
				for(int k=p-j;k<=p+j;k++)	tst[cnt++]=ast[k-1];
			}
			tst[cnt]='\0';
			if(cnt!=1)	ac.insert(tst);
		}
	}
	ac.build();
	printf("%d",ac.match(bst)); 
}
