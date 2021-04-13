#include<iostream>
#include<cstring>
using namespace std;
const int maxn=1000100;
char *str[2][maxn];
char tmp[maxn];
int cnt[2];
int main()
{
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>n;
		memset(tmp,0,sizeof tmp);
		for(int i=1;i<=n;i++)
		{
			
			int len=strlen(tmp),flag=0;
			for(i=0;i<len;i++)	if(tmp[i]=='*')	flag=1;
			for(int)
			str[0][cnt[0]++]=(char*)malloc(len*sizeof(char));
		}
	}
}
