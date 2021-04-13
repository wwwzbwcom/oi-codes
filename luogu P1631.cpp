#include<iostream>
#include<queue>
using namespace std;
struct Point
{
	int ac,bc;
	long long num;
	bool operator<(const Point &in)const
	{
		return num>in.num;
	}
};
int n;
long long a[100010],b[100010];
Point makePoint(int ac,int bc,long long num)
{
	Point ans;
	ans.ac=ac;
	ans.bc=bc;
	ans.num=num;
	return ans;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)	cin>>a[i];
	for(int i=0;i<n;i++)	cin>>b[i];
	priority_queue <Point> q;
	for(int i=0;i<n;i++)	q.push(makePoint(i,0,a[i]+b[0]));
	for(int i=0;i<n;i++)
	{
		Point cur=q.top();q.pop();
		cout<<cur.num<<" ";
		if(cur.bc+1<n)	q.push(makePoint(cur.ac,cur.bc+1,a[cur.ac]+b[cur.bc+1]));
	}
}
