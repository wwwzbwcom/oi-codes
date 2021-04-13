#include<iostream>
#include<algorithm>
using namespace std;
const int oo=999999999;
struct Node
{
	int l,r;
	int n;
	int degree;
	bool operator<(const Node in)const
	{
		return degree<in.degree;
	}
}b[1010000];
int s[1010];
int book[1010000];
int map[1010][1010];
int n,cnt=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if(s[i]==s[j])
			{
				b[cnt].l=i;
				b[cnt].r=j;
				b[cnt].n=cnt;
				b[cnt].degree=0;
				cnt++;
			}
		}
	for(int i=0;i<cnt;i++)
		for(int j=i+1;j<cnt;j++)
		{
			if((b[i].l<=b[j].l&&b[j].l<=b[i].r)&&b[j].r>=b[i].r) map[i][j]=map[j][i]=1,b[i].degree++,b[j].degree++;
			else if((b[i].l<=b[j].r&&b[j].r<=b[i].r)&&b[j].l<=b[i].l) map[i][j]=map[j][i]=1,b[i].degree++,b[j].degree++;
		//	cout<<b[i].l<<"="<<b[i].r<<" "<<b[j].l<<"="<<b[j].r<<" "<<map[i][j]<<endl;
		}
	int ans=0;
	for(int i=0;i<cnt;i++)
	{
		int min0=oo,u;
		for(int j=0;j<cnt;j++)
			if(b[j].degree<min0&&book[j]==0) min0=b[j].degree,u=j;
		//cout<<b[i].l<<"=	"<<b[i].r<<"=	"<<b[i].degree<<"	"<<u<<"	"<<book[u]<<endl;
		if(min0==oo) break;
		book[u]=1;
		for(int v=0;v<cnt;v++)
			if(map[u][v])
			{
				book[v]=1;
				for(int j=0;j<cnt;j++)
					if(map[v][j]) b[j].degree--;
			}
		ans+=2;
	}    
	cout<<n-ans<<endl;
}
