#include<cstdio>
using namespace std;
int n,m;
int x[100100],y[100100],z[100100];
int getans(int xi,int yi,int zi,int ri)
{
	int ans=0;
	for(int i=0;i<n;i++)
		if(xi<=x[i]&&x[i]<=xi+ri&&yi<=y[i]&&y[i]<=yi+ri&&zi<=z[i]&&z[i]<=zi+ri)	ans++;
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)	scanf("%d%d%d",&x[i],&y[i],&z[i]);
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		char cmd[10];	int xi,yi,zi,ri;	scanf("%s",cmd);
		if(cmd[0]=='A')	scanf("%d%d%d",&xi,&yi,&zi),x[n]=xi,y[n]=yi,z[n]=zi,n++;
		if(cmd[0]=='Q')	scanf("%d%d%d%d",&xi,&yi,&zi,&ri),printf("%d\n",getans(xi,yi,zi,ri));
		if(cmd[0]=='C')	n--;
	}
}
