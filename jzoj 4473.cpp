#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
const int maxn=1100;
int n;
int str[maxn];
set <long long> boo;
class Hash
{
	private:
		long long mul[maxn];
		long long has[maxn];
		int len;
	public:
		void init()
		{
			mul[0]=1;	for(int i=1;i<maxn;i++)	mul[i]=mul[i-1]*(int)(1e9+7); 
		}
		inline void insert(int val)
		{
			len++;
			has[len]=has[len-1]*(int)(1e9+7)+val;
		}
		inline long long getkey(int p,int l)
		{
			p++;
			return has[p+l-1]-has[p-1]*mul[l];
		}	
}hs;
int main()
{
	freopen("incantation.in","r",stdin);
	freopen("incantation.out","w",stdout);
	cin>>n;
	hs.init();
	for(int i=0;i<n;i++)	cin>>str[i];
	int ans=0;
	for(int i=0;i<n;i++)
	{
		hs.insert(str[i]);	
		for(int j=1;j<=i+1;j++)
		{
			long long key=hs.getkey(i-j+1,j);
			if(boo.find(key)==boo.end())
			{
				boo.insert(key);
				ans++;
			}
		}
		cout<<ans<<endl;
	}
}
