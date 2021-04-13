#include<cstdio>
#include<queue>
#include<list>
using namespace std;
struct LIS
{
	LIS(int numi,int sizi){num=numi;	siz=sizi;}
	int num,siz;
};
struct QUE
{
	QUE(int numi,int sizi,int timi){num=numi;	siz=sizi;	tim=timi;}
	int num,siz,tim;
};
struct PQU
{
	PQU(int numi,int timi){num=numi;	tim=timi;}
	int num,tim;
	bool operator <(const PQU &in)const{	return tim>in.tim;	}
};
int n,ct;
list <LIS>	lis;
queue <QUE>	que;
priority_queue <PQU>	pqu;
int ans1,ans2;
bool insert(QUE in)
{
	int flag=0;
	for(list <LIS>::iterator it=lis.begin();it!=lis.end();it++)	if((*it).num==0&&(*it).siz>=in.siz)
	{
		int siz=(*it).siz;
		lis.insert(it,LIS(in.num,in.siz));
		if(siz-in.siz>0)	lis.insert(it,LIS(0,siz-in.siz));
		lis.erase(it);
		pqu.push(PQU(in.num,ct+in.tim-1));
		flag=1;
		break;
	}
	return flag;
}
void erase(PQU in)
{
//	printf("%d~~%d\n",in.num,in.tim);
	for(list <LIS>::iterator it=lis.begin();it!=lis.end();it++)	if((*it).num==in.num)
	{
		list <LIS>::iterator pre,nxt;	int siz=0;
		it--;	pre=it;	it++;	it++;	nxt=it;	it--;
		
		if(it !=lis.begin()&&(*pre).num==0)	siz+=(*pre).siz;
		if(nxt!=lis.end()  &&(*nxt).num==0)	siz+=(*nxt).siz;	
		siz+=(*it).siz;
		
		if(it!=lis.begin()&&(*pre).num==0)	lis.erase(pre);
		if(nxt!=lis.end() &&(*nxt).num==0)	lis.erase(nxt);
		lis.insert(it,LIS(0,siz));
		lis.erase(it);
		break;
	}
	ans1=max(ans1,in.tim);
	ct=in.tim+1;
}
void output()
{
	for(list <LIS>::iterator it=lis.begin();it!=lis.end();it++)	printf("%d=%d	",(*it).num,(*it).siz);
	printf("\n");
}
int main()
{
	scanf("%d",&n);
	lis.push_back(LIS(0,n));
	int i=0;
	while(1)
	{
		int T,M,P;	scanf("%d%d%d",&T,&M,&P);	i++;
		if(T==0&&M==0&&P==0)	break;
		
		while(!pqu.empty()&&pqu.top().tim<T)
		{
			int t=pqu.top().tim;
			while(!pqu.empty()&&pqu.top().tim==t)
			{
				erase(pqu.top());
				pqu.pop();
			}
			while(!que.empty()&&insert(que.front()))	que.pop();
		}
	//	printf("%d=============(\n",ct);
	//	output();
		
		
		ct=T;
		if(insert(QUE(i,M,P))==0)	que.push(QUE(i,M,P)),ans2++;
		
	//	printf("%d=============)\n",ct);
	//	output();
	}
	while(!pqu.empty())
	{
		int t=pqu.top().tim;
		while(!pqu.empty()&&pqu.top().tim==t)
		{
			erase(pqu.top());
			pqu.pop();
		}
		while(!que.empty()&&insert(que.front()))	que.pop();
	} 
	printf("%d\n%d\n",ans1+1,ans2);
}
