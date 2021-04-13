#include<iostream>
#include<cstring>
using namespace std;
int A,B1,B2;
int num,cur;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(~scanf("%d%d%d",&A,&B1,&B2))
	{
		if(A==0&&B1==0&&B2==0) break;
		cur=0;
		if(A%B1==0)
		{ 
			num=(A/B1)*B2;
			int i;
			for(i=1;i*i<num;i++)
				if(num%i==0) cur+=i,cur+=num/i;
			if(i*i==num) cur+=i;
		} 
		//cout<<cur<<endl;
		if(cur==A) cout<<1<<" "<<num<<endl;
		else cout<<0<<endl;
	} 
}
