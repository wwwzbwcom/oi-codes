#include<iostream>
#include<algorithm>
using namespace std;
const int mod=998244353;
const int maxn=6000;
int gn;
struct QUERY
{
	QUERY(){x=y=d=0;}
	QUERY(int xi,int yi,int di){x=xi;y=yi;d=di;} 
	int x,y,d;
	bool operator <(const QUERY &in)const
	{
		return x<in.x;
	}
}s[maxn],q[maxn];
int n,m;
int sn,qn;
int len;
int ansl,ansr,ansb;
int C[maxn][maxn];
int work()
{
	int ret=0;
	//cout<<"==============="<<endl;
//	for(int i=1;i<=qn;i++)	cout<<q[i].x<<" "<<q[i].y<<" "<<q[i].d<<endl;
	
	for(int i=1;i<=n;i++)
	{
		int cur=0,lp=0,tmp=1;
		for(int j=1;j<=qn;j++)
		{
			int x=q[j].x,y=q[j].y,d=q[j].d;
			if(d==0)	y=(i-y)-cur;	else	y=y-cur;
			if(x-lp<0||y<0)	tmp=0;
			else	tmp=((long long)tmp*C[x-lp][y])%mod;
		//	cout<<i<<":=  "<<x-lp<<" "<<y<<" "<<C[x-lp][y]<<endl; 
			cur+=y;
			lp=x;
		}
	//	cout<<cur<<"~~~"<<endl; 
		if(cur<=i&&i-cur<=n-lp)
		{
			if(n-lp<0||i-cur<0)	tmp=0;
			else	tmp=((long long)tmp*C[n-lp][i-cur])%mod;
		//	cout<<i<<":=  "<<n-lp<<" "<<i-cur<<" "<<C[n-lp][i-cur]<<endl;
		//	cout<<tmp<<endl;
			ret=(ret+tmp)%mod;
		}
	}
//	cout<<"=============================="<<endl;
	return ret;
}
void init()
{
	C[0][0]=1;
	for(int i=1;i<maxn;i++)
	{
		C[i][0]=C[i-1][0];
		for(int j=1;j<maxn;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
}
int main()
{
//	freopen("ex_A2.in","r",stdin);
	init();
	cin>>gn;
	for(int g=1;g<=gn;g++)
	{
		cin>>n>>m;
		len=0;	sn=0;
		for(int i=1;i<=m;i++)
		{
			int x,y;	cin>>x>>y;
			if(x==y)	len=max(len,x);
			else
			{
				if(x>y)	s[++sn]=QUERY(x,y,1);
				else			s[++sn]=QUERY(n-y,x,0);
			}
		}
		
		qn=sn;
		for(int i=1;i<=sn;i++)	q[i]=s[i];
		q[++qn]=QUERY(len,len,1);
		sort(q+1,q+qn+1);
		ansl=work();
		
		qn=sn;
		for(int i=1;i<=sn;i++)	q[i]=s[i];
		q[++qn]=QUERY(n-len,len,0);
		sort(q+1,q+qn+1);
		ansr=work();
		
		qn=sn;
		for(int i=1;i<=sn;i++)	q[i]=s[i];
		q[++qn]=QUERY(len,len,1);
		q[++qn]=QUERY(n-len,len,0);
		sort(q+1,q+qn+1);
		ansb=work();
		
		if(len>0)	cout<<((ansl+ansr-ansb)%mod+mod)%mod<<endl;
		else		cout<<ansl<<endl;
	}
}
