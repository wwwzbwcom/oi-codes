#include<map>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=50010;
class Type
{
	private:	
		class Block
		{
			public:
				long long add,cnt,sum;
				map <int,int> mxa,mni;
		}b[maxn];
		int bn;
	public:
		int lef;
		Type(){bn=0;}
		long long optA(int i)
		{
			return b[i].cnt;
		}
		long long optB(int i)
		{
			return b[i].sum+b[i].cnt*b[i].add;
		}
		int optC(int i)
		{
			if(b[i].mxa.size()==0)	return 0;
			map <int,int>::iterator it=b[i].mxa.end();
			it--;
			return (*it).first+b[i].add;
		}
		int optD(int i)
		{
			return (*b[i].mni.begin()).first+b[i].add;
		}
		//=========================================================
		void optE(int i,int x,int mod)
		{
		//	
		//	cout<<i<<" "<<x<<" "<<b[i].add<<endl;
			x-=b[i].add;
			if(mod==1)
			{
				
				b[i].sum+=x;
				b[i].cnt++;
			}
		//	else cout<<i<<"="<<x<<endl;
			
			if(b[i].mni.size()<lef)	b[i].mni[x]++;
			else
			{
			//	cout<<"1="<<endl;
				map <int,int>::iterator it=b[i].mni.end();
				it--;	int p=(*it).first;
				if(p>x)
				{
					b[i].mni[x]++;
					b[i].mni[p]--;
					if(b[i].mni[p]==0)	b[i].mni.erase(it);
				}
			}
			if(b[i].mxa.size()<lef)	b[i].mxa[x]++;
			else
			{
			//	cout<<"2="<<endl;
				map <int,int>::iterator it=b[i].mxa.begin();
				int p=(*it).first;
				if(p<x)
				{
					b[i].mxa[x]++;
					b[i].mxa[p]--;
					if(b[i].mxa[p]==0)	b[i].mxa.erase(it);
				}
			}
		}
		void optF(int i,int x)
		{
			cout<<i<<" "<<x<<endl;
			b[i].add+=x;
		}
		void optG(int i,int x)
		{
			map <int,int>::iterator it=b[i].mxa.end();
			it--;	int p=(*it).first;
			b[i].add+=x;
			b[i].cnt--;
			b[i].sum-=p;
			b[i].mxa[p]--;
			if(b[i].mxa[p]==0)	b[i].mxa.erase(p);
			if(b[i].mni.find(p)!=b[i].mni.end())
			{
				b[i].mni[p]--;
				if(b[i].mni[p]==0)	b[i].mni.erase(p);
			}
		///	cout<<i<<" "<<p<<" "<<x<<endl;
			optE(i,p+b[i].add-x,1);
		}
		void optH(int i,int j)
		{
			map <int,int>::iterator it=b[i].mxa.end();
			it--;	int p=(*it).first;
			b[i].cnt--;
			b[i].sum-=p;
			b[i].mxa[p]--;
			if(b[i].mxa[p]==0)	b[i].mxa.erase(p);
			if(b[i].mni.find(p)!=b[i].mni.end())
			{
				b[i].mni[p]--;
				if(b[i].mni[p]==0)	b[i].mni.erase(p);
			}
			optE(j,p+b[i].add,1);
		}
	//========================================================
		void optI(int i,int j,int x)
		{
		//	cout<<optD(i)<<"=============="<<endl;
			int cnt;
			map <int,int>::iterator it;
			if(b[i].mxa.size()>0)
			{
				cnt=0;
				it=b[i].mni.begin();
				for(;it!=b[i].mni.end()&&cnt<=lef;it++)	optE(j,(*it).first+b[i].add-x,0),cnt++;
				cnt=0;
				it=b[i].mxa.end();	it--;
			}
			if(b[i].mni.size()>0)
			{
				for(;cnt<=lef;it--)
				{
					optE(j,(*it).first+b[i].add-x,0),cnt++;
					if(it==b[i].mxa.begin())	break;
				}
			}
			b[j].cnt+=b[i].cnt;
			b[j].sum+=b[i].sum+b[i].cnt*(b[i].add-x-b[j].add);
		}
		void optJ(int i,int j,int t,int x)
		{
			cout<<i<<" "<<j<<endl; 
			int cnt;
			if(b[i].mni.size()>0)
			{
				for(int k=t;k>=1;k--)
				{
					cnt=0;
					map <int,int>::iterator it=b[i].mni.begin();
					for(;it!=b[i].mni.end()&&cnt<=lef;it++)	optE(j,(*it).first+b[i].add-x*k,0),cnt++;
				}
			}
			cout<<"="<<endl;
			if(b[i].mxa.size()>0)
			{
				for(int k=1;k<=t;k++)
				{	
					cnt=0;
					map <int,int>::iterator it=b[i].mxa.end();	it--;
					for(;cnt<=lef;it--)
					{
						optE(j,(*it).first+b[i].add-x*k,0),cnt++;
						if(it==b[i].mxa.begin())	break; 
					}
				}
			}
			b[j].cnt+=b[i].cnt*t;
			b[j].sum+=b[i].sum*t+b[i].cnt*(b[i].add*t-(((1ll+t)*(long long)t)/2)*x-b[j].add*t);
		}
}ty;
int n;
char cmd[maxn];
int i[maxn],j[maxn],t[maxn],x[maxn];
int sto[maxn*2],sn;
int main()
{
	cin>>n;
	ty.lef=n;
	for(int k=1;k<=n;k++)
	{
		cin>>cmd[k];
		if(cmd[k]=='A')	cin>>i[k],sto[sn++]=i[k];
		if(cmd[k]=='B')	cin>>i[k],sto[sn++]=i[k];
		if(cmd[k]=='C') cin>>i[k],sto[sn++]=i[k];
		if(cmd[k]=='D') cin>>i[k],sto[sn++]=i[k];
		if(cmd[k]=='E') cin>>i[k]>>x[k],sto[sn++]=i[k];
		if(cmd[k]=='F') cin>>i[k]>>x[k],sto[sn++]=i[k];
		if(cmd[k]=='G') cin>>i[k]>>x[k],sto[sn++]=i[k];
		if(cmd[k]=='H') cin>>i[k]>>j[k],sto[sn++]=i[k],sto[sn++]=j[k];
		if(cmd[k]=='I')	cin>>i[k]>>j[k]>>x[k],sto[sn++]=i[k],sto[sn++]=j[k];
		if(cmd[k]=='J')	cin>>i[k]>>j[k]>>t[k]>>x[k],sto[sn++]=i[k],sto[sn++]=j[k];
	}
	sort(sto,sto+sn);
	sn=unique(sto,sto+sn)-sto;
	for(int k=1;k<=n;k++)
	{
		cout<<k<<endl;
		if(cmd[k]=='A')	i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,				cout<<ty.optA(i[k])<<endl;
		if(cmd[k]=='B')	i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,				cout<<ty.optB(i[k])<<endl;
		if(cmd[k]=='C') i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,				cout<<ty.optC(i[k])<<endl;
		if(cmd[k]=='D') i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,				cout<<ty.optD(i[k])<<endl;
		if(cmd[k]=='E') i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,			ty.optE(i[k],x[k],1);
		if(cmd[k]=='F') i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,			ty.optF(i[k],x[k]);
		if(cmd[k]=='G') i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,			ty.optG(i[k],x[k]);
		if(cmd[k]=='H') i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,	j[k]=lower_bound(sto,sto+sn,j[k])-sto+1,			ty.optH(i[k],j[k]);
		if(cmd[k]=='I')	i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,	j[k]=lower_bound(sto,sto+sn,j[k])-sto+1,		ty.optI(i[k],j[k],x[k]);
		if(cmd[k]=='J')	i[k]=lower_bound(sto,sto+sn,i[k])-sto+1,	j[k]=lower_bound(sto,sto+sn,j[k])-sto+1,	ty.optJ(i[k],j[k],t[k],x[k]);
		ty.lef--;
	//	cout<<k<<" "<<ty.optB(1)<<"="<<"="<<ty.optB(2)<<endl;
	}
}
 
