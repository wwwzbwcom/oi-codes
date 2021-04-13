#include<iostream>
using namespace std;
int dyp[500][20];
int chg[20][20],chn[20];
void getsit(int p,int in,int out)
{
	if(p==4)
	{
		chg[in][chn[in]++]=out;
		return;
	}
	getsit(p+1,in+(1<<p),out);
	getsit(p+1,in,out+(1<<p));
	if(p+2<=4)	getsit(p+2,in,out); 
}
void init()
{
	getsit(0,0,0);
	dyp[0][0]=1;
	for(int i=0;i<=200;i++)
		for(int j=0;j<16;j++)
			for(int k=0;k<chn[j];k++)
				dyp[i+1][chg[j][k]]+=dyp[i][j];
}
int gn;
int main()
{
	cin>>gn;
	init();
	for(int g=1;g<=gn;g++)
	{
		int p;	cin>>p;
		cout<<g<<" "<<dyp[p][0]<<endl;
	}
}
