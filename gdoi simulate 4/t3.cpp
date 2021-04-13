#include<iostream>
#include<cstdio>
using namespace std;
bool row[20][20],col[20][20],blo[20][20];
int map[20][20];
int liy[300],lix[300],ln=0;
int ans=0;
void dfs(int p,int c)
{
	if(c==ln)
	{
		ans=1;
	//	cout<<"============="<<endl;
		for(int y=0;y<16;y++)
		{
			for(int x=0;x<16;x++)
			{
				char c=map[y][x]+'A';
				cout<<c;
			}
			cout<<endl;
		}
		return;
	}
	else
	{
		for(int k=0;k<16;k++)
		{
			int yo=liy[p],xo=lix[p];
			if(row[yo][k]==0&&col[xo][k]==0&&blo[(yo/4)*4+(xo)/4][k]==0)
			{
				map[yo][xo]=k;
				row[yo][k]=1;
				col[xo][k]=1;
				blo[(yo/4)*4+(xo)/4][k]=1;
				int mni=1e9,p=0;
				for(int i=0;i<ln;i++)
				{
					int y=liy[i],x=lix[i],ways=0;
					if(map[y][x]!=20)	continue;
					for(int j=0;j<16;j++)	if(row[y][j]==0&&col[x][j]==0&&blo[(y/4)*4+(x/4)][j]==0)	ways++;
					if(ways<mni)	mni=ways,p=i;
				}
				dfs(p,c+1);
				map[yo][xo]=20;
				row[yo][k]=0;
				col[xo][k]=0;
				blo[(yo/4)*4+(xo)/4][k]=0;
				if(ans==1)	return;
			}
		}
	}
}
int main()
{
	for(int y=0;y<16;y++)
		for(int x=0;x<16;x++)
		{
			char c;	cin>>c;
			if(c=='-')	map[y][x]=20,liy[ln]=y,lix[ln]=x,ln++;
			else
			{
				map[y][x]=c-'A';
				row[y][c-'A']=1;
				col[x][c-'A']=1;
				blo[(y/4)*4+(x/4)][c-'A']=1;
			}
		}
	int mni=1e9,p=0;
	for(int i=0;i<ln;i++)
	{
		int y=liy[i],x=lix[i],ways=0;
		for(int j=0;j<16;j++)	if(row[y][j]==0&&col[x][j]==0&&blo[(y/4)*4+(x/4)][j]==0)	ways++;
		if(ways<mni)	mni=ways,p=i;
	}
	dfs(p,0);
}
