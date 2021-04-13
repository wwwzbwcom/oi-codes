#include<iostream>
#include<cstring>
using namespace std;
char a[300],b[300];
int alen,blen;
int dyp[300][300];
int main()
{
	while(cin>>a+1>>b+1)
	{
		alen=strlen(a+1);
		blen=strlen(b+1);
		memset(dyp,0,sizeof dyp); 
		for(int i=1;i<=alen;i++)
			for(int j=1;j<=blen;j++)
			{
				dyp[i][j]=max(dyp[i-1][j],dyp[i][j-1]);
				if(a[i]==b[j])	dyp[i][j]=max(dyp[i][j],dyp[i-1][j-1]+1);
			}
		cout<<dyp[alen][blen]<<endl; 
	}
}
