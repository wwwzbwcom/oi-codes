#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
map <int,int> boo;
int n,m;
int l,r;
struct YEAR
{
	int times,heigh;
	int lashei,lasemp;
}s[1000000];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)	scanf("%d%d",&s[i].times,&s[i].heigh),boo[s[i].times]=i;
	s[1].lashei=0;
	s[1].lasemp=0;
	for(int i=2;i<=n;i++)
	{
		int las=i-1;
		while(las!=0)
		{
			if(s[las].heigh<s[i].heigh)	las=s[las].lashei;
			else	break;
		}
		s[i].lashei=las;
		
		if(s[i].times-1!=s[i-1].times)	s[i].lasemp=i-1;
		else	s[i].lasemp=s[i-1].lasemp;
	}
	
//	for(int i=1;i<=n;i++)	cout<<s[i].lasbig<<" "<<s[i].lasemp<<endl;

	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&l,&r);
		int pl=boo[l],pr=boo[r];
		if(pr==0||pl==0)	printf("maybe\n");
		else
		{
			if(s[pr].lashei!=pl)	printf("false\n");
			else
			{
				if(s[pr].lasemp>pl)	printf("maybe\n");
				else	printf("true\n");
			}
		}
	}
}
