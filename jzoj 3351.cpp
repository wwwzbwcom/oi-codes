//#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int mod=100000007;
int mul[2000100];
int rev[2000100];
void init()
{
	mul[0]=1;	for(int i=1;i<2000100;i++)	mul[i]=(mul[i-1]*130ll)%(long long)mod;
	rev[0]=1;	for(int i=1;i<2000100;i++)	rev[i]=(rev[i-1]*13076924ll)%(long long)mod;
}
struct Hash
{
	char *str;
	int *has;
	inline void init(int len)
	{
		str=(char*)malloc((len+5)*sizeof(char)),memset(str,0,sizeof str);
		has=(int*)malloc((len+5)*sizeof(int)),memset(has,0,sizeof has);
	}
	inline void build()
	{
		int len=strlen(str+1); 
		has[0]=0; for(int i=1;i<=len;i++)	has[i]=(has[i-1]+str[i]*(long long)mul[i])%(long long)mod;
	}
	inline int getkey(int p,int l)
	{
		return (((has[p+l-1]-has[p-1])*(long long)rev[p-1])%(long long)mod+mod)%mod;
	}
}l[2100],s1,s2;
char tmp[2000100];
int len[2100];
int n,m;
int ans;
int main()
{
//	freopen("godcow28.in","r",stdin);
//	freopen("out.txt","w",stdout);
	init();
	//cout<<rev[1]<<"="<<endl;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%s",tmp);	len[i]=strlen(tmp);
		l[i].init(len[i]);
		memcpy(l[i].str+1,tmp,len[i]+1);
		l[i].build();
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%s",&tmp);	int len1=strlen(tmp);
		for(int j=0;j<len1;j++)	tmp[j]='a'+(tmp[j]-'a'+ans)%26;
		s1.init(len1);
		memcpy(s1.str+1,tmp,len1+1);
		s1.build();
		
		scanf("%s",&tmp);	int len2=strlen(tmp);
		for(int j=0;j<len2;j++)	tmp[j]='a'+(tmp[j]-'a'+ans)%26;
		s2.init(len2);
		memcpy(s2.str+1,tmp,len2+1);
		s2.build();
		
		ans=0;
		
	//	return 0;
	
		register int key1=s1.has[len1],key2=s2.has[len2];
		for(int j=0;j<n;j++)
		{
		//	printf("%d %d\n",l[j].has[len1],s1.has[len1]);
			if(l[j].has[len1]==key1&&l[j].getkey(len[j]-len2+1,len2)==key2)	ans++; 
		}
		
		
		printf("%d\n",ans);
	}
}
