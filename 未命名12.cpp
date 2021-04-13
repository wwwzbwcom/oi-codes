#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int n;
int val[10];
int yes,no;
int ans;
int main()
{
	//cout<<0.4*0.4*0.6*3<<endl;
	srand(time(0));
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		val[0]=rand()%10,val[1]=rand()%10,val[2]=rand()%10;
		yes=0;	no=0;
		for(int j=0;j<3;j++)	if(val[j]<4)	yes++;	else	no++;
		if(yes==2&&no==1)	ans++;
	}
	cout<<((double)ans)/n<<endl;
}
