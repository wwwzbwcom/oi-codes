#include<algorithm>
#include<iostream>
#include<string>
using namespace std;
long long s[1000000];
int cnt=0;
int main()
{
	for(long long two=1;two<=2e9;two*=2)
		for(long long thr=1;thr<=2e9;thr*=3)
			for(long long fiv=1;fiv<=2e9;fiv*=5)
				for(long long sev=1;sev<=2e9;sev*=7)
					if((double)two*(double)thr*(double)fiv*(double)sev<=3e9)	s[cnt++]=two*thr*fiv*sev;
	sort(s,s+cnt);
	int n;
	while(cin>>n,n)
	{
		string str;
		if((n%100)/10==1)	str="th";
		else
		{
			if(n%10==1)	str="st";
			else	if(n%10==2)	str="nd";
			else	if(n%10==3)	str="rd";
			else	str="th";
		}
		cout<<"The "<<n<<str<<" humble number is "<<s[n-1]<<"."<<endl;
	}
}
