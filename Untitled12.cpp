#include<algorithm>
using namespace std;
struct Node
{
	int l,r,p;
}n[1000];
bool cmp1(const Node a,const Node b)
{
	return a.l<b.l;
}
void test()
{
	sort(n+1,n+3,cmp1);
}
int main()
{
	
}
