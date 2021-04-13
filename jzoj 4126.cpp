#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<map>
using namespace std;
const int mod=100000007;
int mul[5000000];
int rev[5000000];
int ask[5000000],an;
void init()
{
	mul[0]=1;	for(int i=1;i<5000000;i++)	mul[i]=(mul[i-1]*130ll)%(long long)mod;
	rev[0]=1;	for(int i=1;i<5000000;i++)	rev[i]=(rev[i-1]*13076924ll)%(long long)mod;
}
struct Hash
{
	char *str;
	int *has;
	void init(int len)
	{
		str=(char*)(malloc((len+5)*sizeof(char)));
		has=(int*)(malloc((len+5)*sizeof(int)));
		memset(str,0,sizeof str);
		memset(has,0,sizeof has);
	}
	void build(int len)
	{
		has[0]=0;	for(int i=1;i<=len;i++)	has[i]=(has[i-1]+str[i]*(long long)mul[i])%(long long)mod;	
	}
	int getkey(int p,int l)
	{
		return (((has[p+l-1]-has[p-1])%mod+mod)%mod*(long long)rev[p-1])%(long long)mod;
	}
}*t,*s,*a;
int boo[100000010];
int tn,sn,n,m;
int len,ans;
int main()
{
//	freopen("bigyration15.in","r",stdin);
	init();
	scanf("%d%d%d%d",&tn,&sn,&n,&m);
	int flag=0;
	if(n<m)
	{
		swap(n,m);swap(tn,sn);
		flag=1;
	}
	len=n-(n+m)/2;
	t=(Hash*)malloc((tn+5)*sizeof(Hash));
	a=(Hash*)malloc((tn+5)*sizeof(Hash));
	s=(Hash*)malloc((sn+5)*sizeof(Hash));
	for(int i=0;i<tn;i++)	t[i].init(n);
	for(int i=0;i<tn;i++)	a[i].init((n-len)*2);
	for(int i=0;i<sn;i++)	s[i].init(m);
	if(flag==0)
	{
		for(int i=0;i<tn;i++)	scanf("%s",t[i].str+1);
		for(int i=0;i<tn;i++)	memcpy(a[i].str+1,t[i].str+1,n-len),memcpy(a[i].str+1+(n-len),t[i].str+1,m),a[i].str[(n-len)*2+1]='\0';
		for(int i=0;i<sn;i++)	scanf("%s",s[i].str+1);
	}
	else
	{
		for(int i=0;i<sn;i++)	scanf("%s",s[i].str+1);
		for(int i=0;i<tn;i++)	scanf("%s",t[i].str+1);
		for(int i=0;i<tn;i++)	memcpy(a[i].str+1,t[i].str+1,n-len),memcpy(a[i].str+1+(n-len),t[i].str+1,m),a[i].str[(n-len)*2+1]='\0';
	}
	for(int i=0;i<tn;i++)	t[i].build(n);
	for(int i=0;i<tn;i++)	a[i].build((n-len)+m);
	for(int i=0;i<sn;i++)	s[i].build(m);
	for(int i=0;i<sn;i++)	boo[s[i].getkey(1,m)]++;
//	return 0;
	for(int i=0;i<tn;i++)
	{
		int key=t[i].getkey(n-len+1,len); 
		for(int j=1;j<=n-len;j++)
		{
			if(a[i].getkey(j,len)==key)	ans+=boo[a[i].getkey(j+len,m)];
		}
	}
	printf("%d",ans);
}
