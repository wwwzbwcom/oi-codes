#include<iostream>
#include<algorithm>
using namespace std;
struct S1
{
	int l,r;
	bool operator<(const S1 in)const
	{
		if(in.r==r) return in.l<l;
		return r<in.r;
	}
}s1[1000000];
struct S2
{
	int l,r;
	int back,next;
	bool operator<(const S2 in)const
	{
		if(in.l==l) return in.r<r;
		return l<in.l;
	}
}s2[1000000];
int n;
int ans1,ans2;
int main()
{
	freopen("block.in","r",stdin);
	freopen("block.out","w",stdout);
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>s1[i].l>>s1[i].r;
		s2[i].l=s1[i].l;
		s2[i].r=s1[i].r;
	}
	
	sort(s1,s1+n);
	sort(s2,s2+n);
	int start=0;
	for(int i=0;i<n;i++) s2[i].back=i-1,s2[i].next=i+1;
	s2[n-1].next=-1;
	
	int end=-999999999;
//	cout<<"================"<<endl;
	for(int i=0;i<n;i++)	if(end<=s1[i].l) ans1++,end=s1[i].r;
	
	
//	cout<<"================"<<endl;
	int flag=1;
	while(flag==1)
	{
		int end=-999999999;
		flag=0;
		for(int i=start;i!=-1;i=s2[i].next)
		{
			flag=1;
			if(end<=s2[i].l)
			{
				cout<<s2[i].l<<" "<<s2[i].r<<endl;
				end=s2[i].r;
				if(i==start) start=s2[i].next;
				else s2[s2[i].back].next=s2[i].next;
				s2[s2[i].next].back=s2[i].back;
			}
		}
		//cout<<"=============="<<endl;
		if(flag==0) break;
		ans2++; 
	}
	cout<<ans1<<" "<<ans2<<endl;
}
