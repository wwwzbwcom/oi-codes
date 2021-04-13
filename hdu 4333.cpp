#include<iostream>
#include<cstring>
using namespace std;
const int maxn=200100;
struct Externdkmp
{
	char str[maxn];
	int nxt[maxn];
	getnxt()
	{
		int len=strlen(str),s=1;
		nxt[0]=len;	nxt[1]=0;
		while(str[nxt[1]]==str[nxt[1]+1])	nxt[1]++;
		for(int i=2;i<len;i++)
		{
			int e=s+nxt[s]-1;
			if(i+nxt[i-s]-1<e)	nxt[i]=nxt[i-s];
			else
			{
				if(e-i+1>0)	nxt[i]=e-i+1;	else	nxt[i]=0;
				while(i+nxt[i]<len&&str[nxt[i]]==str[i+nxt[i]])	nxt[i]++;
				s=i;
			}
		}
	}
}ek;
struct Kmp
{
	char str[maxn];
	int nxt[maxn];
	getnxt()
	{
		int len=strlen(str+1),fix=0;
		nxt[1]=0;
		for(int i=2;i<=len;i++)
		{
			while(fix!=0&&str[fix+1]!=str[i])	fix=nxt[fix];
			if(str[fix+1]==str[i])	fix++;
			nxt[i]=fix;
		}
	}
}km;
int gn;
int les,equ,mor;
int main()
{
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>ek.str;	
		int len=strlen(ek.str);
		memcpy(km.str+1,ek.str,len);
		for(int i=len;i<2*len;i++)	ek.str[i]=ek.str[i-len];
		ek.str[2*len]='\0';
		ek.getnxt();
	//	for(int i=0;i<len;i++)	cout<<i<<" "<<ek.nxt[i]<<endl;
		les=equ=mor=0;
		for(int i=0;i<len;i++)
		{
			if(ek.nxt[i]>=len)	equ++;
			else
			{
				if(ek.str[ek.nxt[i]]>ek.str[i+ek.nxt[i]])	les++;
				else	mor++;
			}
		}
		km.getnxt();
		int mod=len-km.nxt[len],div=1;
	//	cout<<mod<<endl; 
		if(len%mod==0)	div=len/mod;
		cout<<"Case "<<g<<": "<<les/div<<" "<<equ/div<<" "<<mor/div<<endl;
	}
}
