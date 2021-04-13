#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cmath>
using namespace std;
int n,l;
int x[100],y[100],k[100];
int sum;
int ans[100]; 
int main()
{
	srand(time(NULL));
	cin>>n>>l;
	for(int i=1;i<=n;i++)	cin>>x[i]>>y[i]>>k[i];
	for(int i=1;i<=1e7;i++)
	{
	//	cout<<i<<endl;
	//	cout<<rand()*1e4<<endl;
	//	cout<<i<<endl;
		double p=(double)((int)(rand()*1e4+rand())%((int)(l*1e6)))/1e6;
		int cnt=0;
		for(int j=1;j<=n;j++)
		{
			double r=(double)(rand()%(int)1e4)/1e4;
			if(r<=(1.0-abs((double)y[j]-p)/(double)k[j]))
			cnt++;
		}
		sum+=cnt;
		ans[cnt]++;
	}
	printf("%.10lf\n",sum/1e7);
	for(int i=0;i<=n;i++)	printf(".10%lf\n",ans[i]/1e7);
}

