#include<iostream>
#include<cstring> 
using namespace std;
const int maxn=100000;
struct ex_kmp
{
	char st1[maxn];
	char st2[maxn];
	int nxt[maxn];
	int ext[maxn];
	void getnxt()
	{
		int len=strlen(st2); 
		int p=2;
		nxt[0]=len;
		nxt[1]=0;
		while(st2[nxt[1]]==st2[nxt[1]+1])	nxt[1]++;
		for(int i=2;i<len;i++)
		{
			int s=p,e=p+nxt[p]-1;
			if(i+nxt[i-s]-1<e)	nxt[i]=nxt[i-s];
			else
			{
				int j;
				if(e-i+1>0)	j=e-i+1;	else	j=0;
			//	cout<<i<<"="<<j<<endl;
				while(j<len&&st2[j]==st2[i+j])	j++;
				nxt[i]=j;
				p=i;
			}
		}
	}
	void getext()
	{
		int le1=strlen(st1),le2=strlen(st2);
		int p=0;
		while(nxt[p]<le1&&nxt[p]<le2&&st1[nxt[p]]==st2[nxt[p]])	nxt[p]++;
		for(int i=1;i<le1;i++)
		{
			int s=p,e=p+nxt[p]-1;
			if(i+nxt[i-s]-1<p+ext[p]-1)	ext[i]=nxt[i-s];
			else
			{
				int j;
				if(e-i+1>0)	j=e-i+1;	else	j=0;
				while(j<le1&&j&&le2&&st2[j]==st1[i+j])	j++;
				ext[i]=j;
				p=i;
			}
		}
	}
}ek;
int main()
{
	cin>>ek.st2;
//	cin>>ek.st2;
	ek.getnxt();
	for(int i=0;i<10;i++)	cout<<i<<" "<<ek.nxt[i]<<endl;
}
