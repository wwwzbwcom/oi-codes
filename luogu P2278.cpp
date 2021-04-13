#include<iostream>
#include<queue>
using namespace std;
struct Point
{
	int num,ret,dot,lev;
	bool operator<(const Point &in)const
	{
		if(lev!=in.lev)	return lev<in.lev;
		else	return ret>in.ret;
	}
}p[1000000];
priority_queue <Point> q;
int tim=0;
int main()
{
	Point in;
	while(1)
	{
		if(~scanf("%d%d%d%d",&in.num,&in.ret,&in.dot,&in.lev))
		{
			while(1)
			{
				if(q.empty())
				{
					tim=in.ret;	q.push(in);
					break;
				}
				else
				{
					Point cur=q.top();q.pop();
					if(tim+cur.dot<=in.ret)
					{
						tim+=cur.dot;cur.dot=0;
						printf("%d %d\n",cur.num,tim);
					}
					else
					{
						cur.dot-=(in.ret-tim);
						tim+=(in.ret-tim);
						q.push(in);
						q.push(cur);
						break;
					}
				}
			}
		}
		else
		{
			while(!q.empty())
			{
				Point cur=q.top();q.pop();
				tim+=cur.dot;
				printf("%d %d\n",cur.num,tim);
			}
			break;
		}
	}
}
