#include<iostream>
#include<cstring>
using namespace std;
long long l,r;
int boo[20];
int ans;
int main()
{
	cin>>l>>r;
	for(long long i=l;i<=r;i++)
	{
		long long tmp=i;
		memset(boo,0,sizeof boo);	int com=0,las=0,flag=0,first=0;
		while(tmp)
		{
			boo[tmp%10]=1;
			 
			if(tmp%10==las)	com++;	else	com=1,las=tmp%10;
			//cout<<tmp<<" "<<tmp%10<<" "<<las<<" "<<com<<endl;
			if(com==3)	flag=1;
			tmp/=10;
		}
		//cout<<las<<" "<<boo[4]<<" "<<boo[8]<<endl; 
		if(las==0||(boo[4]&&boo[8]))	flag=0;
		ans+=flag;
	}
	cout<<ans<<endl;
}
