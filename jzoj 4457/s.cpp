#include<iostream>
using namespace std;
class DigitDP
{
	private:
		int dig[20];
		int len;
		long long dyp[20][5][5][10][2];
		bool	vis[20][5][5][10][2];
		long long dfs(int p,int c1,int c2,int ld,int fla)
		{
			if(vis[p][c1][c2][ld][fla])	return dyp[p][c1][c2][ld][fla];
			vis[p][c1][c2][ld][fla]=1;
			
			if(p==0)
			{
				if(c2==3)	return dyp[p][c1][c2][ld][fla]=1;
				else	return dyp[p][c1][c2][ld][fla]=0;
			}
			int lim;
			if(fla)	lim=dig[p];	else	lim=9;	
			for(int i=0;i<=lim;i++)
			{
				if(i!=0||p!=len)
				{
					int vp=p-1,vc1=c1,vc2=c2,vld=i,vfla;
					if(i==4)	vc1|=(1<<0);
					if(i==8)	vc1|=(1<<1);
					if(i==ld||p==len)	vc2++;	else	vc2=1;
					vc2=min(vc2,3); 
					if(c2==3)	vc2=3;
					if(fla&&i==lim)	vfla=1;	else	vfla=0;
					if(vc1!=3)	dyp[p][c1][c2][ld][fla]+=dfs(vp,vc1,vc2,vld,vfla);
				}
			}
			//cout<<p<<" "<<c1<<" "<<c2<<" "<<ld<<" "<<dyp[p][c1][c2][ld]<<endl; 
			return dyp[p][c1][c2][ld][fla];
		}
	public:
		void build(long long val)
		{
			len=1;
			while(val)
			{
			//	cout<<val<<" "<<val%10<<endl;
				dig[len]=val%10;
				val/=10;
				len++;
			}
			len--;
		}
		long long work()
		{
		//	for(int i=1;i<=len;i++)	cout<<dig[i]<<" ";
		//	cout<<endl;
			return dfs(len,0,0,0,1);
		}
}l,r;
int main()
{
	long long a,b;	cin>>a>>b;
	if(a==1e10)	l.build(a);	else	l.build(a-1);
	r.build(b);
	long long ans=r.work()-l.work();
	if(a==1e10)	ans++;
	cout<<ans<<endl;
}
