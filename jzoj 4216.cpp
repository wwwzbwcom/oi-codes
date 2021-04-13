#include<iostream>
#include<cstring>
#include<cstdlib>
#include<map>
using namespace std;
const long long mod=1000000007;
long long mul[5000000];
long long rev[5000000];
void init()
{
	mul[0]=1;	for(int i=1;i<5000000;i++)	mul[i]=(mul[i-1]*130)%mod;
	rev[0]=1;	for(int i=1;i<5000000;i++)	rev[i]=(rev[i-1]*515384619)%mod;
}
struct Hash
{
	char *str;
	long long *has;
	void init(int len)
	{
		str=(char*)(malloc((len+10)*sizeof(char)));
		has=(long long*)(malloc((len+10)*sizeof(long long)));
		memset(str,0,sizeof str);
		memset(has,0,sizeof has);
	}
	void build()
	{
		int len=strlen(str+1);
	//	if(len!=100)	cout<<len<<"~"<<endl;
		has[0]=0;	for(int i=1;i<=len;i++)	has[i]=(has[i-1]+str[i]*mul[i])%mod;	
	}
	long long getkey(int p,int l)
	{
		return (((has[p+l-1]-has[p-1])%mod+mod)%mod*rev[p-1])%mod;
	}
}*t,*s,*a;
map <long long,long long> boo;
int tn,sn,n,m;
int len,ans;
int main()
{
	freopen("bigyration3.in","r",stdin);
	init();
	cin>>tn>>sn>>n>>m;
	int flag=0;
	if(n<m)
	{
		swap(n,m);swap(tn,sn);
		flag=1;
	}
	len=n-(n+m)/2;
	t=(Hash*)malloc((tn+10)*sizeof(Hash));
	a=(Hash*)malloc((tn+10)*sizeof(Hash));
	s=(Hash*)malloc((sn+10)*sizeof(Hash));
	for(int i=0;i<tn;i++)	t[i].init(n);
	for(int i=0;i<tn;i++)	a[i].init(n*2);
	for(int i=0;i<sn;i++)	s[i].init(m);
	if(flag==0)
	{
		for(int i=0;i<tn;i++)	cin>>t[i].str+1;
		for(int i=0;i<tn;i++)	memcpy(a[i].str+1,t[i].str+1,n-len),memcpy(a[i].str+1+(n-len),t[i].str+1,n-len),a[i].str[(n-len)*2+1]='\0';
		for(int i=0;i<sn;i++)	cin>>s[i].str+1;
	}
	else
	{
		for(int i=0;i<sn;i++)	cin>>s[i].str+1;
		for(int i=0;i<tn;i++)	cin>>t[i].str+1;
		for(int i=0;i<tn;i++)	memcpy(a[i].str+1,t[i].str+1,n-len),memcpy(a[i].str+1+(n-len),t[i].str+1,n-len),a[i].str[(n-len)*2+1]='\0';
	}
//	for(int i=0;i<tn;i++)	if(strlen(t[i].str+1)!=100)	cout<<i<<" "<<strlen(t[i].str+1)<<endl<<t[i].str+1<<endl;
	for(int i=0;i<tn;i++)	t[i].build();
	for(int i=0;i<tn;i++)	a[i].build();
	for(int i=0;i<sn;i++)	s[i].build();
	for(int i=0;i<sn;i++)	boo[s[i].getkey(1,m)]++;
	for(int i=0;i<tn;i++)
	{
		for(int j=1;j<=n-len;j++)
		{
		//	cout<<a[i].getkey(j,len)<<"="<<t[i].getkey(n-len+1,len)<<" "<<a[i].getkey(j+len,m)<<" "<<boo[a[i].getkey(j+len,m)]<<endl;
			if(a[i].getkey(j,len)==t[i].getkey(n-len+1,len))	ans+=boo[a[i].getkey(j+len,m)];
		}
		//cout<<"========================="<<endl;
	}
	cout<<ans<<endl;
}
