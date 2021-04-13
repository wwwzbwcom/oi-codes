#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1001000;
char str[maxn];
class Hash
{
	public:
		char str[maxn];
		long long has[maxn],mul[maxn];
		int len;
		void build()
		{
			mul[0]=1;	for(int i=1;i<=len;i++)	mul[i]=mul[i-1]*129;
			has[0]=0;	for(int i=1;i<=len;i++)	has[i]=has[i-1]*129+str[i];
		}
		long long getkey(int p,int l)
		{
			p++;
			return has[p+l-1]-has[p-1]*mul[l];
		}
}f,b;
class XDS
{
	private: 
		class Node
		{
			public:
				int le,re;
				int ls,rs;
				int lmx,rmx;
		}n[maxn*3];
		int nn;
	public:
		int r;
		int build(int le,int re)
		{
			int u=++nn; 
			n[u].le=le;	n[u].re=re;
			int  mid=(le+re)/2;
			n[u].lmx=n[u].rmx=0;
			if(le==re)	n[u].ls=n[u].rs=0;
			else
			{
				n[u].ls=build(le,mid);
				n[u].rs=build(mid+1,re);
			}
			return u;
		}
		void optlef(int u,int lc,int rc,int val)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
		//	getchar(); 
			if(le==lc&&re==rc)
			{
				n[u].lmx=max(n[u].lmx,val);
			}
			else
			{
				if(rc<=mid)	optlef(n[u].ls,lc,rc,val);
				else
				{
					if(lc>=mid+1)	optlef(n[u].rs,lc,rc,val);
					else	optlef(n[u].ls,lc,mid,val-2*(re-(mid+1)+1)),optlef(n[u].rs,mid+1,rc,val);
				}
			}
		}
		void optrig(int u,int lc,int rc,int val)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
		//	cout<<le<<"="<<re<<" "<<lc<<"="<<rc<<endl;
		//	getchar();
			if(le==lc&&re==rc)
			{
				//cout<<le<<" "<<re<<" "<<val<<endl; 
				n[u].rmx=max(n[u].rmx,val);
			} 
			else
			{
				if(rc<=mid)	optrig(n[u].ls,lc,rc,val);
				else
				{
					if(lc>=mid+1)	optrig(n[u].rs,lc,rc,val);
					else	optrig(n[u].ls,lc,mid,val),optrig(n[u].rs,mid+1,rc,val-2*(mid-le+1));
				}
			}
		}
		int qrylef(int u,int p)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
			if(le==re)
			{
				return n[u].lmx;
			} 
			else
			{
				if(p<=mid)	return max(qrylef(n[u].ls,p),n[u].lmx-2*(re-p));
				else	return max(qrylef(n[u].rs,p),n[u].lmx-2*(re-p));
			}
		}
		int qryrig(int u,int p)
		{
			int le=n[u].le,re=n[u].re;
			int mid=(le+re)/2;
		//	cout<<le<<"="<<re<<"="<<p<<" "<<n[u].rmx-2*(p-le)<<endl; 
			if(le==re)	return n[u].rmx;
			else
			{
				if(p<=mid)	return max(qryrig(n[u].ls,p),n[u].rmx-2*(p-le));
				else	return max(qryrig(n[u].rs,p),n[u].rmx-2*(p-le));
			}
		}
}xds;
int rng[maxn];
void work()
{
	int len=strlen(str);
	f.str[++f.len]='#';
	for(int i=0;i<len;i++)
	{
		f.str[++f.len]=str[i];
		f.str[++f.len]='#';
	}
	b=f;
	reverse(b.str+1,b.str+b.len+1);
	f.build();	b.build();
	//cout<<f.len<<" "<<b.len<<endl;
	for(int i=1;i<f.len-1;i++)
	{
	//	cout<<i<<endl;
		int l=0,r=min(i+1,f.len-i),ans=0;
		while(l<=r)
		{
			int mid=(l+r)/2;
		//	cout<<mid<<"="<<f.getkey(i,mid)<<" "<<b.getkey(b.len-i-1,mid)<<endl;
			if(f.getkey(i,mid)==b.getkey(b.len-i-1,mid))	ans=mid,l=mid+1;
			else	r=mid-1;
		}
		//if(ans>47)	cout<<ans<<" "<<endl;
		if(ans==1)	continue;
		if(f.str[i+1]=='#')
		{
			xds.optlef(xds.r,i/2,i/2+ans/2-1,ans-1);
			xds.optrig(xds.r,(i-1)/2-ans/2+1,(i-1)/2,ans-1);
		}
		else
		{
			xds.optlef(xds.r,i/2,i/2+ans/2-1,ans-1);
			xds.optrig(xds.r,i/2-ans/2+1,i/2,ans-1);
		}
	}
//	cout<<"="<<endl;
}
int getans()
{
	int len=strlen(str);
	int ans=0;
	for(int i=0;i<len-1;i++)
	{
	//	cout<<xds.qrylef(xds.r,i)<<"=========="<<xds.qryrig(xds.r,i+1)<<endl;
		ans=max(ans,xds.qrylef(xds.r,i)+xds.qryrig(xds.r,i+1));
	} 
	return ans;
}
int main()
{
	//freopen("dpal5.in","r",stdin);
	scanf("%s",str);
	int len=strlen(str);
	xds.r=xds.build(0,len-1);
	
	work();
	cout<<getans()<<endl;
}
 
