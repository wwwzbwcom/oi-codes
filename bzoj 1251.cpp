#include<algorithm>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int maxn=50100;
struct Splay
{
    struct Node
    {
        int ls,rs;
        int num;
        int mar,add;
        int cnt,mxa;
    }n[maxn];
    int nn;
    int root;
    void download(int u)
    {
        n[n[u].ls].add+=n[u].add;
        n[n[u].rs].add+=n[u].add;
        n[u].num+=n[u].add;
        n[0].add=0;n[0].mxa=-2e9;
        n[u].add=0;
        if(n[u].mar)
        {
            n[n[u].ls].mar^=1;
            n[n[u].rs].mar^=1;
            swap(n[u].ls,n[u].rs);
            n[u].mar=0;
        }
    }
    void upload(int u)
    {
    	if(u==0)	return;
        n[u].cnt=n[n[u].ls].cnt+n[n[u].rs].cnt+1;
        n[u].mxa=max(max(n[n[u].ls].mxa+n[n[u].ls].add,n[n[u].rs].mxa+n[n[u].rs].add),n[u].num);
    }
    void lrotate(int &u)
    {
        int rs=n[u].rs; n[u].rs=n[rs].ls;   n[rs].ls=u; upload(u);  upload(rs); u=rs;
    }
    void rrotate(int &u)
    {
        int ls=n[u].ls; n[u].ls=n[ls].rs;   n[ls].rs=u; upload(u);  upload(ls); u=ls;
    }
    void insert(int &u,int val)
    {
        if(u==0)
        {
            u=++nn;
            n[u].cnt=1;
            n[u].num=n[u].mxa=val;
        }
        else
        {
            download(u);
        //    if(n[u].rs!=0)	lrotate(u);
            insert(n[u].rs,val);
            lrotate(u);
        }
    }
    void findkth(int &u,int pos)
    {
        download(u);
        if(n[n[u].ls].cnt+1==pos)   return;
        else
        {
            if(n[n[u].ls].cnt+1>pos)
			{
				if(n[u].ls!=0&&n[n[ n[u].ls ].ls].cnt+1>pos)	rrotate(u),download(u);
				findkth(n[u].ls,pos);
				rrotate(u);
         	}
		    else	if(n[n[u].ls].cnt+1<pos)
			{
				if(n[u].rs!=0&&n[n[ n[u].rs ].ls].cnt+1 < pos-(n[ u ].cnt+1))	lrotate(u),download(u);
				findkth(n[u].rs,pos-(n[n[u].ls].cnt+1));
				lrotate(u);
        	}
		}
    }
    int query(int le,int re,int mod,int val)
    {
        findkth(root,(le-1)+1);
        findkth(n[root].rs,(re+1)-(n[n[root].ls].cnt+1)+1);
        int u=n[n[root].rs].ls;
        if(mod==1)  n[u].add+=val;
        if(mod==2)  n[u].mar^=1;
        if(mod==3)  return n[u].mxa+n[u].add;
        return 0;
    }
}sp;
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n+1;i++)  sp.insert(sp.root,0);
    for(int i=1;i<=m;i++)
    {
        int mod,le,re,val;
        scanf("%d%d%d",&mod,&le,&re);
        if(mod==1)  scanf("%d",&val),sp.query(le,re,mod,val);
        if(mod==2)  sp.query(le,re,mod,0);
        if(mod==3)  printf("%d\n",sp.query(le,re,mod,0));
    }
}
