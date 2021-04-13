#include <iostream>
#include <queue>
using namespace std;
int n;
long long bfs()
{
     queue<long long> p;
     while(!p.empty())
     p.pop();
     p.push(1);
     while(1)
     {
             long long sum=p.front();
             if(sum%n==0)
             return sum;
             p.pop();
             p.push(10*sum);
             p.push(10*sum+1);
     }
}
int main()
{
	cout<<111111<<endl;
    while(cin>>n,n)
    {
    	cout<<11111111<<endl;
        cout<<bfs()<<endl;
    }
    return 1;
}

