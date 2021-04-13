#include<iostream>
#include<queue>
using namespace std;
int n,k;
class CON
{
	public: 
		long long val,dep;
		CON(long long vali,long long depi)
		{
			val=vali;
			dep=depi;
		}
		bool operator <(const CON &in)const
		{
			if(val==in.val)	return dep>in.dep;
			return val>in.val;
		}
};
priority_queue <CON> que;
long long ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		long long val;	scanf("%d",&val);
		que.push(CON(val,0));
	}
//	cout<<((k-1)-(n-1)%(k-1))%(k-1)<<"="<<endl;
	for(int i=1;i<=((k-1)-(n-1)%(k-1))%(k-1);i++)	que.push(CON(0,0));
	while(que.size()!=1)
	{
		long long val=0,dep=0;
		for(int i=1;i<=k;i++)	val+=que.top().val,dep=max(dep,que.top().dep+1),que.pop();
		ans+=val;	que.push(CON(val,dep)); 
	}
	printf("%lld\n%lld\n",ans,que.top().dep);
}
