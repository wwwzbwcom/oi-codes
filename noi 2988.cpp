#include<iostream>
#include<cstring>
using namespace std;
const int maxn=1500;
int gn;
char ast[maxn],bst[maxn];
int an,bn;
int dyp[maxn][maxn];
int main()
{
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>ast+1>>bst+1;
		an=strlen(ast+1);
		bn=strlen(bst+1);
		for(int i=0;i<maxn;i++)
			for(int j=0;j<maxn;j++)
				dyp[i][j]=1e9; 
		for(int i=0;i<maxn;i++)	dyp[0][i]=dyp[i][0]=i; 
		for(int i=1;i<=an;i++)
			for(int j=1;j<=bn;j++)
			{
				dyp[i][j]=min(dyp[i][j],min(dyp[i-1][j]+1,dyp[i][j-1]+1));
				dyp[i][j]=min(dyp[i][j],dyp[i-1][j-1]+1);
				if(ast[i]==bst[j])	dyp[i][j]=min(dyp[i][j],dyp[i-1][j-1]);
			}
		cout<<dyp[an][bn]<<endl;
	}
}
