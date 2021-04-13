#include<algorithm>
#include<iostream>
#include<map>
using namespace std;
const int maxn=1000100;
int n,m,t;
map <int,map<int,map<int,int> > > boo;
int ast[maxn],an;
int bst[maxn],bn;
int cst[maxn],cn;
int main()
{
	cin>>n>>m>>t;
	for(int i=1;i<=m;i++)
	{
		int a,b,c;	cin>>a>>b>>c;
		boo[a][b][c]++;
		ast[an++]=a;
		bst[bn++]=b;
		cst[cn++]=c;
	}
	sort(ast,ast+an);
	sort(bst,bst+bn);
	sort(cst,cst+cn);
	for(int i=1;i<=t;i++)
	{
		int a,b,c;	cin>>a>>b>>c;	
		int cnt=0,tie=0;
		cnt+=(lower_bound(ast,ast+an,a)-ast)-(an-(upper_bound(ast,ast+an,a)-ast));
		cnt+=(lower_bound(bst,bst+bn,b)-bst)-(bn-(upper_bound(bst,bst+bn,b)-bst));
		cnt+=(lower_bound(cst,cst+cn,c)-cst)-(cn-(upper_bound(cst,cst+cn,c)-cst));
		
		tie+=(upper_bound(ast,ast+an,a)-ast)-(lower_bound(ast,ast+an,a)-ast);
		tie+=(upper_bound(bst,bst+bn,b)-bst)-(lower_bound(bst,bst+bn,b)-bst);
		tie+=(upper_bound(cst,cst+cn,c)-cst)-(lower_bound(cst,cst+cn,c)-cst);
		tie-=boo[a][b][c]*2;
		
		//cout<<cnt<<endl;
		cout<<(m+cnt-tie)/2<<endl;
	}
}
