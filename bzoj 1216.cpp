#include<cstdio>
#include<queue>
using namespace std;
struct Node
{
	int nu,rt,ft,we;
	int dt;
	Node(int nui,int rti,int fti,int wei)
	{
		nu=nui;
		rt=rti;
		ft=fti;
		we=wei;
		dt=0;
	}
	bool operator <(const Node &in)const
	{
		if(we==in.we)	return rt>in.rt;
		else	return we<in.we;
	}
};
priority_queue <Node> que;
int main()
{
	int nu,rt,ft,we;
	int ct=0;
	while(~scanf("%d%d%d%d",&nu,&rt,&ft,&we))
	{
		while(ct<rt&&(!que.empty()))
		{
			Node cur=que.top();que.pop();
			int t=min(rt-ct,cur.ft-cur.dt);
			cur.dt+=t;
			ct+=t;
			if(cur.dt==cur.ft) printf("%d %d\n",cur.nu,ct);
			else	que.push(cur);
		}
		ct=rt;
		que.push(Node(nu,rt,ft,we));
	}
	while(!que.empty())
	{
		Node cur=que.top();que.pop();
		int t=cur.ft-cur.dt;
		cur.dt+=t;
		ct+=t;
		if(cur.dt==cur.ft) printf("%d %d\n",cur.nu,ct);
		else	que.push(cur);
	}
}
