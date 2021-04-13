#include<iostream>
#include<queue>
#include<list>
using namespace std;
const int maxn=10010;
struct BLOCK
{
	int con,siz;
	BLOCK(int coni,int sizi)
	{
		con=coni,siz=sizi;
	}
};
struct NODE
{
	int tim,siz,num;
	NODE(int timi,int sizi,int numi)
	{
		tim=timi;	siz=sizi;	num=numi;
	}
};
int n;
list <BLOCK>	lis;
queue <NODE>	que;
int til[maxn],pos[maxn],tp,tn,ct;
int ans1,ans2;
int main()
{
	cin>>n;
	lis.insert(lis.end(),BLOCK(0,n));
	lis.insert(lis.end(),BLOCK(-1,0));
	int t,m,p;
	int i=1;
	while(1)
	{
		cin>>t>>m>>p;
		if(t==0&&m==0&&p==0)	break;
		que.push(NODE(p,m,i));
		while(1)
		{
			ct=max(ct,t);
			int flag=0;
			for(list <BLOCK>::iterator it=lis.begin();it!=lis.end();it++)	if((*it).con==0&&(*it).siz>=que.front().siz)
			{
				list <BLOCK>::iterator pre;	it--;	pre=it;	it++;
				int siz=(*it).siz;	lis.erase(it);
				
				lis.insert(pre,BLOCK(que.front().num,que.front().siz));
				cout<<siz<<endl;
				siz-=que.front().siz;	pre++;
				
				if(siz>0)	lis.insert(pre,BLOCK(0,siz));
				til[tn]=ct+que.front().tim-1;	pos[tn]=i;	tn++;
				flag=1;
				que.pop();
				break;
			}
			if(flag==1)	break;
			
			for(list <BLOCK>::iterator it=lis.begin();it!=lis.end();it++)
			{
			//	cout<<(*it).con<<"="<<pos[j]<<endl;
				if((*it).con==pos[j])
				{
					list <BLOCK>::iterator ppr,pre,nxt;	int siz;
					it--;	it--;	ppr=it;	it++;	pre=it;	it++;	it++;	nxt=it;	it--;
					siz=(*it).siz,lis.erase(it);
					
					if(pre!=lis.begin()&&(*pre).con==0)	siz+=(*pre).siz,lis.erase(pre);
					if(nxt!=lis.end()  &&(*pre).con==0)	siz+=(*pre).siz,lis.erase(nxt);	
					
					lis.insert(ppr,BLOCK(0,siz));
					ct=max(ct,til[j]);
					break;
						
				}
			}
			
			//cout<<"==="<<endl;
		}
		i++;
	}
	for(int i=0;i<tn;i++)	ans1=max(ans1,til[i]),cout<<i<<"="<<til[i]<<"="<<pos[i]<<endl;
	cout<<ans1<<endl<<ans2;
}

