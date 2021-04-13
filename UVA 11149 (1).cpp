#include<iostream>
#include<cstring>
using namespace std;
struct Matrix
{
	int s[50][50],x,y;
	Matrix(int a,int b):x(a),y(b){memset(s,0,sizeof s);}
	
	Matrix operator+(const Matrix in)const
	{
	//	cout<<x<<" "<<y<<endl;
		Matrix ans(x,y);
		for(int i=0;i<y;i++)
			for(int j=0;j<x;j++)
				ans.s[i][j]=(s[i][j]+in.s[i][j])%10;
		return ans; 
	}
	Matrix operator*(const Matrix in)const
	{
		Matrix ans(in.x,y);
		for(int i=0;i<y;i++)
			for(int j=0;j<in.x;j++)
				for(int k=0;k<x;k++)
					ans.s[i][j]+=(s[i][k]*in.s[k][j])%10,
					ans.s[i][j]%=10;
		return ans;
	}
	Matrix operator^(int in)const
	{
		Matrix ans=*this,temp=*this;
		in--;
		while(in)
		{
			if(in%2) ans=ans*temp;
			temp=temp*temp;
			in/=2;
		}
		return ans;
	}
	
};
Matrix rec(0,0); 
Matrix sum(int in,Matrix a)
{
	if(in==1) return a;
	Matrix temp=(rec+(a^(in/2)))*sum(in/2,a);
	if(in%2) return temp+(a^in);
	else return temp;
}
int n,k;
int main()
{	
	
	while(cin>>n>>k&&n&&k)
	{
		Matrix d(n,n);
		Matrix ans(n,n);
		rec.x=n,rec.y=n;
		for
		(int i=0;i<n;i++) rec.s[i][i]=1;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				cin>>d.s[i][j],
				d.s[i][j]%=10;
		ans=sum(k,d);
	//	cout<<ans.y<<" "<<ans.x<<endl;      
		for(int i=0;i<ans.y;i++)
		{
			for(int j=0;j<ans.x-1;j++)
				cout<<ans.s[i][j]%10<<" ";
			cout<<ans.s[i][ans.x-1]%10<<endl;
		}
		cout<<endl;
	}
}
