#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
#include<map>
using namespace std;
map <long long,string> boo;
int main()
{
	freopen("hashtest127.out","w",stdout);
	srand(time(0));
	int ans=0;
	int lim=127;
	for(int k=0;k<100000;k++)
	{
		for(int i=0;i<100000;i++)
		{
			int len=rand()%1000+10;
			string str;
			long long cur;
			for(int j=0;j<len;j++)
			{
				char c=rand()%2;
				cur=cur*lim+c;
				str+=c;
			}
			if(boo.find(cur)==boo.end())	boo[cur]=str;
			else
				if(boo[cur]!=str)
				{
				//	cout<<boo[cur]<<" "<<str<<endl;
					ans++;
				}
		}
		cout<<k<<" "<<ans<<endl;
	}
}
