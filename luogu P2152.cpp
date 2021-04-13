#include<iostream>
#include<cstring>
using namespace std;

struct bigNum
{
	int s[2500];
	int len;
	bool operator<(const bigNum &in)  const
	{
		if(len<in.len)	return 1;
		if(len>in.len)	return 0;
		for(int i=len-1;i>=0;i--)
		{
			if(s[i]<in.s[i])	return 1;
			if(s[i]>in.s[i])	return 0;
		}
	}
	bool operator==(const bigNum &in)  const
	{
		if(len!=in.len)	return 0;
		for(int i=0;i<len;i++)
			if(s[i]!=in.s[i])	return 0;
		return 1;
	}
	void output()
	{
		for(int i=len-1;i>=0;i--)	cout<<s[i];
	}
};
char as[10010],bs[10010],temp[10010];
bigNum zero,one;
bigNum c2b(char const *a)
{
	bigNum ans;
	ans.len=strlen(a);
	int cnt=1;
	for(int i=0;i<ans.len;i++)	ans.s[i]=a[ans.len-i-1]-'0';
	return ans;
}
bigNum decrease(bigNum const &a,bigNum const &b)
{
	bigNum ans;	ans.len=max(a.len,b.len);
	int carry=0;
	for(int i=0;i<ans.len;i++)
	{
		ans.s[i]=a.s[i]-b.s[i]+carry;
		if(ans.s[i]<0)	ans.s[i]+=10,carry=-1;
		else	carry=0;
	}
	while(ans.s[ans.len-1]==0&&ans.len>1)	ans.len--;
	return ans;
}
bigNum divide2(bigNum const &a)
{
	bigNum ans; ans.len=a.len;
	int carry=0;
	for(int i=ans.len-1;i>=0;i--)
	{
		ans.s[i]=(a.s[i]+carry)/2;
		if(a.s[i]%2)	carry=10;
		else	carry=0;
	}
	while(ans.s[ans.len-1]==0&&ans.len>1)	ans.len--;
	return ans;
}
bigNum multi(bigNum const &a,int const &b)
{
	bigNum ans;	ans.len=a.len;
	int carry=0;
	for(int i=0;i<ans.len;i++)
	{
		ans.s[i]=a.s[i]*b+carry;
		carry=ans.s[i]/10;
		ans.s[i]%=10;
	}
	while(carry)
	{
		ans.s[ans.len++]=carry%10;
		carry/=10;
	}
	return ans;
}
bigNum t;
bigNum a,b,c;
int cnt=0;
void gcd()
{
	if(b<a)	t=a,a=b,b=t;
	while(1)
	{
		if(b<a)	t=a,a=b,b=t;
		if(a==one){c=one;break;}
		if(a==zero){c=b;break;}
		
		if(a.s[0]%2==0&&b.s[0]%2==0){	a=divide2(a);	b=divide2(b);	cnt++;}
		else
		{
			if(a.s[0]%2==0){a=divide2(a);}
			else
			{
				if(b.s[0]%2==0){b=divide2(b);}
				else
				{
					t=a;
					a=decrease(b,a);
					b=t;
				}
			}
		}
	}
	int cur=1;
	for(int i=0;i<cnt;i++)
	{
		cur*=2;
		if(cur>1e7)	c=multi(c,cur),cur=1;
	}
	c=multi(c,cur);
}
int main()
{
	cin>>as>>bs;
	temp[0]='0';	temp[1]='\0';	zero=c2b(temp);
	temp[0]='1';	temp[1]='\0';	one=c2b(temp);
	
	a=c2b(as);	b=c2b(bs);
	gcd();
	c.output();
}
