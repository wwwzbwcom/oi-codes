#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
const int oo=2e9+100;
int n;
int x[1000100],y[1000100],w[1000100];
int ans=oo;
string out;
void work(int xmi,int xma,int ymi,int yma)
{
    int tmp=0;
    string otmp="";
    for(int i=1;i<=n;i++)
    { 
    
		if((xmi<=x[i]&&x[i]<=xma)&&(ymi<=y[i]&&y[i]<=yma)) 	otmp+='0';
    	else
    	{
    		if((xmi<=y[i]&&y[i]<=xma)&&(ymi<=x[i]&&x[i]<=yma))	tmp+=w[i],otmp+='1';
    		else	return;
		}
	
	//	if((!(xmi<=x[i]&&x[i]<=xma))||(!(ymi<=y[i]&&y[i]<=yma)))    tmp+=w[i],otmp+='1';    else    otmp+='0';
	} 
//  cout<<tmp<<endl;
    if(tmp<ans)  ans=tmp,out=otmp;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)    scanf("%d%d%d",&x[i],&y[i],&w[i]);
    int xmi=oo,xma=-oo;
    int ymi=oo,yma=-oo;
    for(int i=1;i<=n;i++)
    {
        xmi=min(xmi,min(x[i],y[i]));
        xma=max(xma,min(x[i],y[i]));
        ymi=min(ymi,max(x[i],y[i]));
        yma=max(yma,max(x[i],y[i]));
    }
    work(xmi,xma,ymi,yma);
    work(ymi,xma,xmi,yma);
    work(xmi,yma,ymi,xma);
    work(ymi,yma,xmi,xma);
    long long len=(long long)2*(long long)((xma-xmi)+(yma-ymi));
    printf("%lld %d\n",len,ans);
    cout<<out;
}
