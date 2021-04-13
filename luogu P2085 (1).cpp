#include<iostream>
#include<queue>
using namespace std;
struct Point
{
	int num;
	int cur;
	int dir;
	int val;
	bool operator<(const Point &in)const
	{
		return val>in.val;
	}
};
int n,m;
int a[10100],b[10100],c[10100];
Point makePoint(int n,int c,int d,int v)
{
	Point	ans;
	ans.num=n;
	ans.cur=c;
	ans.dir=d;
	ans.val=v;
	return ans;
}
int getval(int num,int x)
{
	return a[num]*x*x+b[num]*x+c[num];
}
int main()
{
	cin>>n>>m;
	priority_queue <Point> q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i]>>c[i];
		double Xmin=-(b[i])/(2*a[i]);
		if(Xmin>=1)
		{
			q.push(makePoint(i,(int)(Xmin),-1,getval(i,(int)(Xmin))));
			q.push(makePoint(i,(int)(Xmin+1),1,getval(i,(int)(Xmin+1))));
		}
		else	q.push(makePoint(i,1,1,getval(i,1)));
	}
	for(int i=1;i<=m;i++)
	{
		Point cur=q.top();q.pop();
		cout<<cur.val<<" ";
		if(cur.cur+cur.dir>=1)	q.push(makePoint(cur.num,cur.cur+cur.dir,cur.dir,getval(cur.num,cur.cur+cur.dir)));
	}
}
