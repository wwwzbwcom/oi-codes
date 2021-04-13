#include<iostream>
using namespace std;
int n,p,q,x,y;
char sto[100100];
int cur,lack,m,fee,mxa;
int main()
{
	cin>>n>>p>>q>>x>>y;
	cur=p;
	for(int i=1;i<=n;i++)
	{
		cin>>sto[i];
		if(sto[i]=='+')	cur++;
		if(sto[i]=='-')	cur--;
	}
	lack=q-cur;
	cur=0;
	cout<<lack<<endl;
	if(lack>=0)
	{
		for(int i=1;i<=n-m;i++)
		{
			if(sto[i]=='+')	cur++;
			if(sto[i]=='-')
			{
				if(lack)	lack-=2,cur++,fee+=x;
				else	cur--;
			}
			if(cur<0)
			{
				while(cur<0)
				{
					if(sto[n-m]=='+')	cur++;
					if(sto[n-m]=='-')	cur--;
					m++;
					fee+=y;
				}
			}
		}
	}
	else
	{
		lack=-lack;
		cout<<y<<" "<<lack<<endl;
		for(int i=1;i<=n-m;i++)
		{
			if(sto[i]=='+')	cur++;
			if(sto[i]=='-')	cur--;
			if(cur<0)
			{
				while(cur<0)
				{
					if(sto[n-m]=='+')	cur++;
					if(sto[n-m]=='-')
				}
			}
			mxa=max(mxa,cur);
		}
		if(mxa>=lack)	fee=x*lack/2;
		else
		{
			cur=0;
			fee=x*lack/2;
			while(mxa+cur<lack*2)
			{
				if(sto[n-m]=='+')	cur++;
				if(sto[n-m]=='-')	cur--;
				fee+=x;
				m++;
			}
		}
	}
	cout<<fee<<endl;
}
