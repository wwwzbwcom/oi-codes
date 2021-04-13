#include<iostream>
#include<cstring> 
using namespace std;
long long l,r,k;
long long bit[100];
long long dyp[100][1500];		//dp1�б�ʾ��iλ�Ƿ��Ƕ��˲��Ҽ��е���һ����ʱ����Ҫ���ĵ�ֵ��dp2�б�ʾ��iλ���Ƕ���ʱ����ǰ�Ѿ�ʡ��j������ܹ�ʡ���� 
long long num[100][2];			//dp1�б�ʾ��iλ�Ƿ��Ƕ���ʱһ���ж��ٸ��� 
long long getdp1(int pos,int con)
{
	if(pos==0)	
	{
		num[pos][con]=1;
		return 0;
	}
	if(dyp[pos][con]!=-1)	return dyp[pos][con];
	
	int len;	if(con==1)	len=bit[pos];	else	len=k-1;
	dyp[pos][con]=0;	num[pos][con]=0;
	for(int i=0;i<=len;i++)
	{
		int nxt;	if(con==1&&i==len)	nxt=1;	else	nxt=0;
		dyp[pos][con]+=getdp1(pos-1,nxt)+num[pos-1][nxt]*i*(pos-1);
		num[pos][con]+=num[pos-1][nxt];
	}
	return dyp[pos][con];
}
long long getdp2(int pos,long long chg,int mid,int con)
{
	if(pos==0)	return chg;
	if(con==0&&dyp[pos][chg]!=-1)	return dyp[pos][chg];
	int sign;	if(pos>=mid)	sign=1;	else	sign=-1;
	int len;	if(con==1)	len=bit[pos];	else	len=k-1;
	long long ans=0;
	for(int i=0;i<=len;i++)
	{
		long long nxt=chg+sign*i;
		if(nxt<0)	break; 
		ans+=getdp2(pos-1,nxt,mid,con&&(i==len));
	}
	if(con==0)	dyp[pos][chg]=ans;
	return ans;
}
long long work(long long num)
{
	long long tmp=num;
	int len=0;
	while(tmp)	bit[++len]=tmp%k,tmp/=k;
	memset(dyp,-1,sizeof dyp);
	long long ans=getdp1(len,1);
	for(int i=2;i<=len;i++)
	{
		memset(dyp,-1,sizeof dyp);
		ans-=getdp2(len,0,i,1);
	}
	return ans;
}
int main()
{
	cin>>l>>r>>k;
	cout<<work(r)-work(l-1);
}
