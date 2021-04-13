#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct bigNum
{
	int s[20100];
	int len;
	bigNum(int in)
	{
		memset(s,0,sizeof s);
		if(in==0)	len=0;
		else
		{
			while(in)
			{
				s[len]=in%10;
				in/=10;
				len++;
			}
		}
	}
	void read()
	{
		memset(s,0,sizeof s);
		char t[20100];	scanf("%s",t);
		len=strlen(t);
		for(int i=0;i<len;i++)	s[i]=t[len-i-1]-'0';	
	}
	bool operator <=(const bigNum &in)const
	{
		if(len<in.len)	return 1;
		else
		{
			if(len>in.len)	return 0;
			else
			{
				for(int i=len-1;i>=0;i--)
				{
					if(s[i]<in.s[i])	return 1;
					else	if(s[i]>in.s[i])	return 0;
				}
			}
		}
		return 1;
	}
	bigNum operator+(const bigNum &in)const
	{
		bigNum ans(0);
		ans.len=max(len,in.len);
		int carry=0;
		for(int i=0;i<ans.len;i++)
		{
			ans.s[i]=s[i]+in.s[i]+carry;
			carry=ans.s[i]/10,ans.s[i]%=10;
		}
		while(carry)
		{
			ans.s[ans.len++]=carry%10;
			carry/=10;	
		}
		return ans;
	}
	bigNum operator-(const int &in)const
	{
		bigNum ans=*this;
		int carry=0;
		int inc=in;
		for(int i=0;i<ans.len;i++)
		{
			ans.s[i]=s[i]-inc%10+carry;
			inc/=10;
			if(ans.s[i]<0)	carry=-1,ans.s[i]+=10; 
			else	carry=0;
		}
		while(ans.len>0&&ans.s[ans.len-1]==0)	ans.len--;
		return ans;
	}
	bigNum operator*(const int &in)const
	{
		bigNum ans(0);
		ans.len=len;
		int carry=0;
		for(int i=0;i<ans.len;i++)
		{
			ans.s[i]=s[i]*in+carry;
			carry=ans.s[i]/10;	ans.s[i]%=10;
		}
		while(carry)
		{
			ans.s[ans.len++]=carry%10;
			carry/=10;	
		}
		return ans;
	}
	bigNum operator*(const bigNum &in)const
	{
		bigNum ans(0);
		
		for(int i=0;i<len;i++)
		{
			bigNum a(0),b(0);
			a=in*s[i];
			b.len=a.len+i;
			for(int j=0;j<a.len;j++)	b.s[j+i]=a.s[j];
		//	ans.out();	b.out();
		//	cout<<"============="<<endl;
			ans=ans+b;
		}
		
		return ans;
	}
	bigNum operator/(const int &in)const
	{
		bigNum ans=*this;
		int carry=0;
		for(int i=len-1;i>=0;i--)
		{
			ans.s[i]=(s[i]+carry*10)/in;
			carry=s[i]%in;
		}
		while(ans.len>0&&ans.s[ans.len-1]==0)	ans.len--;
		return ans;
	}
	bigNum qsm(const int &in,const bigNum &mxa)
	{
		bigNum o(1);
		if(in==1)	return *this;
		else
		{
			bigNum t=(*this).qsm(in/2,mxa);
			if(mxa<=(t-1))	t=mxa+o;	
			t=t*t;
			if(mxa<=(t-1))	t=mxa+o;
			if(in%2==1)	return t* *this;
			else	return t;
		}
	}
	bigNum sqrt(int k)
	{
		bigNum l(1),r=*this;
		bigNum o(1);
		bigNum ans(0);
		while(l<=r)
		{
			bigNum m=(l+r)/2;
		//	l.out();	r.out();
		//	m.out();
		//	(m^k).out();
		//	(*this).out();
			if(m.qsm(k,*this)<=(*this))	ans=m,l=m+o;
			else	r=m-1;
			cout<<"================="<<endl;
		//	getchar();
		}
		return ans;
	}
	void out()
	{
		for(int i=len-1;i>=0;i--)	printf("%d",s[i]);
		printf("\n");
	}
};
void test()
{
	bigNum a(76);
	(a*a*a).out();
}
bigNum n(0);
bigNum ans(0);
int main()
{
//	test();
	int k;scanf("%d",&k);
	n.read();
	ans=n.sqrt(k);
	if(ans.len==0)	printf("0");
	else	ans.out();
}
