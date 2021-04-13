#include<iostream>
using namespace std;
int n,m,p,q;
struct CON
{
	int pc[3],qc;
}con[200],cur;
int cn;
void dfs(int pp)
{
	int tmp=0;
	for(int i=0;i<pp;i++)	tmp+=cur.pc[i];
	if(pp==p-1)
	{
		cur.pc[pp]=n-tmp;
		for(int i=0;i<=q;i++)	cur.qc=i,con[cn++]=cur;
	}
	else
	{
		for(int i=0;i<=n-tmp;i++)	cur.pc[pp]=i,dfs(pp+1);
	}
}
struct MATRIX
{
	
}mat;
int main()
{
	cin>>n>>m>>p>>q;
	dfs(0);
	for(int i=0;i<cn;i++)
		for(int j=0;j<cn;j++)
		{
			int flag=0,cnt=0,ans=1;
			CON sto=con[i];
			for(int k=p-1;k>=1;k--)
			{
				int tmp=con[j].pc[k]-con[i].pc[k];
				ans*=C[tmp][con[i].pc[k-1]];
				con[i].pc[k-1]-=tmp;
				cnt+=tmp;
			}
			for(int k=1;k<p;k++)	if(con[i].pc[k]<0)	flag=1;
			if((cnt==n&&con[i].qc+1==con[j].qc)||(cnt<n&&con[i].qc==con[j].qc));
			else	flag=1;
			if(flag==1)	ans=0;
			mat.s[i][j]=ans;
			con[i]=sto;
		}
	mat^=m;
	int ans=0;
	for(int i=0;i<cn;i++)	if(cur.pc[0]==n&&cur.qc==0)	for(int j=0;j<cn;j++)	ans+=mat.s[i][j];
	cout<<ans<<endl;
}
