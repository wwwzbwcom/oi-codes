#include<iostream>
using namespace std;
long long cm[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
long long rm[]={0,31,29,31,30,31,30,31,31,30,31,30,31};
long long gn;
long long aim,ye,mo,da,ho,mi,se;
int main()
{
	cin>>gn;
	while(gn--)
	{
		cin>>aim>>ye>>mo>>da>>ho>>mi>>se;
		aim=(((long long)1)<<(aim-1))-1;
		long long cur=0;
		while(1)
		{
			if(cur+24*3600<=aim)	da++,cur+=24*3600;
			else	break;
			
			if( (ye%100&&ye%4==0) || (ye%100==0&&ye%400==0))
			{	if(da==rm[mo]+1)	mo++,da=1;}
			else
			{	if(da==cm[mo]+1)	mo++,da=1;}
			
			if(mo==13)	ye++,mo=1;
		}
		
		while(1)
		{
			if(cur+1<=aim)	se++,cur++;
			else	break;
			
			if(se==60)	mi++,se=0;
			if(mi==60)	ho++,mi=0;
			if(ho==24)	da++,ho=0;
		}
		
		if( (ye%100&&ye%4==0) || (ye%100==0&&ye%400==0))
		{	if(da==rm[mo]+1)	mo++,da=1;}
		else
		{	if(da==cm[mo]+1)	mo++,da=1;}
			
		if(mo==13)	ye++,mo=1;
		
		cout<<ye<<" "<<mo<<" "<<da<<" "<<ho<<" "<<mi<<" "<<se<<endl;
	}
}
