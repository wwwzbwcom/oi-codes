#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
char dic[50][20];
char art[1000100];
bool dyp[1000100];
int dle[50];
int ans=0;
int cmp(int i,int j)
{
	int ans=1;
	for(int k=0;k<dle[j];k++)
		if(art[i+k]!=dic[j][k])	ans=0;
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)	scanf("%s",dic[i]),dle[i]=strlen(dic[i]);
	for(int g=0;g<m;g++)
	{
		scanf("%s",art);
		memset(dyp,false,sizeof dyp);
		ans=0;
		dyp[0]=true;
		
		int alen=strlen(art);
		for(int i=0;i<alen;i++)
			if(dyp[i]==true)
			{
				for(int j=0;j<n;j++)
					if(cmp(i,j))
						dyp[i+dle[j]]=true;
			}
		for(int i=0;i<=alen;i++)	if(dyp[i]==true)	ans=i;
			
		printf("%d\n",ans);
	}

}
