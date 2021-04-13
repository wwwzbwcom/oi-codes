#include<algorithm>
#include<iostream>
using namespace std;
const int oo=1e7;
int n;
int x[100],y[100];
int dp[100000];
int fee[100000];
/* 
int calc(int a, int b)
{
	if (x[a] != x[b] && y[a] != y[b])
		return abs(x[a] - x[b])*abs(y[a] - y[b]);
	else
		return x[a] == x[b] ? abs(y[a] - y[b]) : abs(x[a] - x[b]);
}

void init()
{
	fee[0] = 0;
	for (int i = 1; i < (1 << n); i++)
	{
		int x1 = oo, x2 = -oo, y1 = oo, y2 = -oo;
		int j,mask = i, cnt = 0;
		for (j = 0; mask; j++)
		{
			if ((1 << j) & mask)
			{
				x1 = min(x1, x[j]), x2 = max(x2, x[j]), y1 = min(y1, y[j]), y2 = max(y2, y[j]);
				mask ^= 1 << j; cnt++;
			}
		}
		fee[i] = (y2 - y1)*(x2 - x1);
		if (fee[i]) continue;
		else if (cnt == 1)
		{
			j--;
			fee[i] = oo;
			for (int k = 0; k < n; k++)
				if(k != j) fee[i] = min(fee[i],calc(j,k));
		}
		else fee[i] = y2==y1 ? (x2-x1) : (y2-y1);
	}
}
*/ 

void pt()
{
	fee[0]=0;
	for(int i=1;i<(1<<n);i++)
	{
		int xma=-oo,xmi=oo,yma=-oo,ymi=oo;
		int cur=i,cnt=0;
		int num=0,last=0;
		while(cur)
		{
			if(cur%2)
			{
				num++;	last=cnt;
				xma=max(xma,x[cnt]);	xmi=min(xmi,x[cnt]);
				yma=max(yma,y[cnt]);	ymi=min(ymi,y[cnt]);
			}
			cur/=2;
			cnt++;
		}
		
		if(num==1)
		{
			fee[i]=oo;
			for(int j=0;j<n;j++)	if(j!=last)	fee[i]=min(fee[i],max(1,abs(xma-x[j]))*max(1,abs(yma-y[j])));
		}
		else	fee[i]=max(1,xma-xmi)*max(1,yma-ymi);
	//	if(i==1)	cout<<last<<"="<<endl;
	}
}

int work()
{
	for(int i=0;i<100000;i++)	dp[i]=oo;
	dp[0]=0;
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=i;j!=0;j=(j-1)&i)
			dp[i]=min(dp[i],dp[i^j]+fee[j]);
	}
	return dp[(1<<n)-1];
}
int main()
{
	while(cin>>n,n)
	{
		for(int i=0;i<n;i++)	cin>>x[i]>>y[i];
		pt();
	//	cout<<"================"<<endl;
	//	cout<<fee[1]<<endl;
		cout<<work()<<endl;
	}
}
