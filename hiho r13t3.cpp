#include<iostream>
using namespace std;
int sto[2][3];
int tim;
int main()
{
	cin>>sto[0][0]>>sto[0][1]>>sto[0][2];
	while(1)
	{
		int flag=0;
		for(int i=0;i<3;i++)	if(sto[0][i]||sto[1][i])	flag=1;
		if(flag==0)	break;

		tim++;
		if(sto[1][0]+sto[1][1]+sto[1][2]<35||tim%2==0)
		{
			int val=(35-(sto[1][0]+sto[1][1]+sto[1][2]));
			if(tim%2==0)	val=20;
			
			int p1=-1,p2=-1;
			for(int i=0;i<3;i++)	if(p1==-1||sto[0][i]>=sto[0][p1])			p1=i;
			for(int i=0;i<3;i++)	if(i!=p1&&(p2==-1||sto[0][i]>=sto[0][p2]))	p2=i;
			
			if(sto[0][p2]<10)	val=min(val,min(15,sto[0][p1]));
			
			int t;
			t=min(val,sto[0][p1]);	sto[1][p1]+=t;	sto[0][p1]-=t;	val-=t;
			t=val;					sto[1][p2]+=t;	sto[0][p2]-=t;	val-=t;
		}
		if(tim%2==0)
		{
			int p1=-1,p2=-1;
			for(int i=0;i<3;i++)	if(p1==-1||sto[1][i]>=sto[1][p1])			p1=i;
			for(int i=0;i<3;i++)	if(i!=p1&&(p2==-1||sto[1][i]>=sto[1][p2]))	p2=i;
			cout<<p1<<" "<<p2<<endl;
			cout<<sto[1][0]<<" "<<sto[1][1]<<" "<<sto[1][2]<<endl;
			int val;
			if(sto[1][p2]<10)	val=min(15,sto[1][p1]);
			else				val=20;
			
			int t;
			t=min(val,sto[1][p1]);	sto[1][p1]-=t;	val-=t;
			t=val;					sto[1][p2]-=t;	val-=t;
		}
	}
	cout<<tim*3<<endl;
}
