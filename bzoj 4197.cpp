#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int boo[1000];
int pri[1000],pn;
void init()
{
	boo[1]=1;
	for(int i=2;i<1000;i++)
	{
		if(boo[i]==0)	pri[++pn]=i;
		for(int j=1;j<=pn;j++)
		{
			if(i*pri[j]>=1000)	break;
			boo[i*pri[j]]=1;
			if(i%pri[j]==0)	break;
		}
	}
}
class CON
{
	public:
		int big,con;
		CON()
		{
			big=con=0;
		}
		CON(int in)
		{
			big=con=0;
			for(int i=1;i<=8;i++)	while(in%pri[i]==0)	con|=(1<<(i-1)),in/=pri[i];
			big=in;
		}
		bool operator <(CON const &in)const
		{
			return big<in.big;
		}
}c[1000];
int n,mod;
int dpf[300][300];
int dpg[2][300][300];
int ans;
int main()
{
	init();
	scanf("%d%d",&n,&mod);
	for(int i=1;i<=n-1;i++)	c[i]=CON(i+1);
	sort(c,c+n);
	dpf[0][0]=1;
	int l=1,r=1;
	while(l<n)
	{
		while(c[r+1].big==c[l].big)	r++;
		
		memcpy(dpg[0],dpf,sizeof dpf);
		memcpy(dpg[1],dpf,sizeof dpf);
		for(int j=l;j<=r;j++)	
			for(int q=0;q<300;q++)
				for(int p=300-1;p>=0;p--)
					dpg[0][p|c[j].con][q]+=dpg[0][p][q],dpg[0][p|c[j].con][q]%=mod;
		int t=1;
		if(c[l].big==1)	t=0;
		for(int j=l;j<=r;j++)
			for(int p=0;p<300;p++)
				for(int q=300-1;q>=0;q--)
					dpg[t][p][q|c[j].con]+=dpg[t][p][q],dpg[t][p][q|c[j].con]%=mod;
		for(int p=0;p<300;p++)
			for(int q=0;q<300;q++)
				dpf[p][q]=((dpg[0][p][q]+dpg[1][p][q]-dpf[p][q])%mod+mod)%mod;
		l=r+1;
	//	cout<<dpf[1][0]<<"="<<dpg[0][1][0]<<"="<<dpg[1][1][0]<<endl;
	}
//	cout<<"====="<<endl;
	for(int p=0;p<300;p++)
		for(int q=0;q<300;q++)
			if((p|q)==(p^q))
			{
			//	if(p<=3&&q<=3)	cout<<p<<" "<<q<<" "<<dpf[p][q]<<endl;
				ans=(ans+dpf[p][q])%mod;
			}
	printf("%d",ans);
}
