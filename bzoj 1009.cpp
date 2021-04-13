#include<iostream>
using namespace std;
int n,m,mod;
char tmp[50];
int str[50];
int fai[50];
struct Matrix
{
	int sto[50][50];
	int yn,xn;
	Matrix operator *(const Matrix &in)const
	{
		Matrix ans;	ans.yn=yn;	ans.xn=in.xn;
		for(int i=1;i<=yn;i++)
			for(int j=1;j<=in.xn;j++)
				for(int k=1;k<=xn;k++)
				//	cout<<i<<" "<<j<<" "<<ans.sto[i][j]<<endl,
					ans.sto[i][j]+=sto[i][k]*in.sto[k][j],
				//	cout<<i<<" "<<j<<" "<<sto[i][k]*in.sto[k][j]<<" "<<ans.sto[i][j]<<endl,
					ans.sto[i][j]%=mod;
		return ans;
	}
	Matrix operator ^(const int &in)const
	{
		if(in==1)	return (*this);
		else
		{
			Matrix ans=(*this)^(in/2);
			ans=ans*ans;
			if(in%2)	return ans* *this;
			else		return ans;
		}
	}
	void output()
	{
		for(int i=1;i<=yn;i++)
		{
			for(int j=1;j<=xn;j++)
				cout<<sto[i][j]<<" ";
			cout<<endl;
		}
	}
};
void kmp()
{
	fai[1]=0;
	for(int i=2;i<=m;i++)
	{
		int f=i-1;
		do
		{
			f=fai[f];
			if(str[f+1]==str[i])
			{
				fai[i]=f+1;
				break;
			}
		}
		while(f!=0);
	//	cout<<i<<" "<<fai[i]<<endl;
	}
}
Matrix buildMatrix()
{
	Matrix ans;
	ans.yn=m+1;	ans.xn=m+1;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<=9;j++)
		{
			int f=i,flag=0;
		//	cout<<i<<"==================="<<j<<endl;
			while(1)
			{
			//	cout<<f<<endl;
				if(str[f+1]==j)
				{
					ans.sto[i+1][f+2]++;
					ans.sto[i+1][f+2]%=mod;
					flag=1;
				//	cout<<"========="<<endl;
					break; 
				}
				if(f==0)	break;
				f=fai[f];	
			}
			if(flag==0)	ans.sto[i+1][1]++;
		}
	}
	return ans;
}
int main()
{
	cin>>n>>m>>mod;
	cin>>tmp;
	for(int i=1;i<=m;i++)	str[i]=tmp[i-1]-'0';
	kmp();
//	for(int i=1;i<=m;i++)	cout<<fai[i]<<" ";
	Matrix ans=buildMatrix();
//	ans.output();
//	ans=ans*ans*ans;
//	
	ans=ans^n;
	int output=0;
//	ans.output();
	for(int i=1;i<=m;i++)	output+=ans.sto[1][i],output%=mod;
	cout<<output;
}
