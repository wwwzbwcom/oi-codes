#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
bool book[1000];
unsigned long long s[1000000];
int cnt=0;
void pt()
{
	for(int i=2;i<100;i++)
		for(int j=2;j*i<100;j++)
			book[i*j]=1;
}
int main()
{
	pt();
	printf("1\n");
	for(int i=2;i<=100000;i++)
	{
		unsigned long long t=i;
		for(int j=2;j<=64&&t==(t*i)/i;j++)
		{
			t*=i;
			if(book[j]==1) s[cnt++]=t;
		}
	}
	sort(s,s+cnt);
	cnt=unique(s,s+cnt)-s;
	for(int i=0;i<cnt;i++)
	cout<<s[i]<<endl;
}
