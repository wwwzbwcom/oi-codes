#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;

int i,x,n,m,l2,e,anso,anst,j,l1,k;
char s1[2000011],s2[2000011];
int a[2000011],b[2000011],exA[2000011],exB[2000011];
char c;

void Exkmp()
{
	int i,l,k,j,len;
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	len=0;
	k=0;
	for(i=2;i<=l2;i++){
		if(k+a[k]-1<i){
			j=0;
			while(i+j<=l2&&s2[i+j]==s2[1+j])j++;
			a[i]=j;
		}
		else{
			l=k+a[k]-1;
			if(a[i-k+1]<l-i+1)a[i]=a[i-k+1];
			else{
				j=l-i+1;
				while(i+j<=l2&&s2[1+j]==s2[i+j])j++;
				a[i]=j;
			}
		}
		if(i+a[i]-1>len){
			len=i+a[i]-1;
			k=i;
		}
	}
	len=0;
	k=0;
	for(i=1;i<=l1;i++){
		if(k+b[k]-1<i){
			j=0;
			while(1+j<=l2&&i+j<=l1&&s2[1+j]==s1[i+j])j++;
			b[i]=j;
		}
		else{
			l=k+b[k]-1;
			if(a[i-k+1]<l-i+1)b[i]=a[i-k+1];
			else{
				j=l-i+1;
				while(1+j<=l2&&i+j<=l1&&s2[1+j]==s1[i+j])j++;
				b[i]=j;
			}
		}
		if(i+b[i]-1>len){
			len=i+b[i]-1;
			k=i;
		}
	}
}

void Work()
{
	bool p;
	int i,mc;
	for(i=anst;i<anst+l2/2;i++)printf("%c",s2[i]);
	printf("\n");
	for(i=anst;i<anst+l2/2;i++)s2[i-anst+1]=s2[i];
	for(i=1;i<=l2/2;i++)s2[i+l2/2]=s2[i];
	Exkmp();
	for(i=1;i<=l1;i++)exA[i]=b[i];
	for(i=1;i<=l1/2;i++){
		c=s1[i];
		s1[i]=s1[l1-i+1];
		s1[l1-i+1]=c;
	}
	for(i=1;i<=l2/2;i++){
		c=s2[i];
		s2[i]=s2[l2-i+1];
		s2[l2-i+1]=c;
	}
	Exkmp();
	for(i=1;i<=l1;i++)exB[i]=b[i];
	mc=2147483647;
	for(i=1;i<=l1/2;i++){
		
		if(exA[i]+exB[l1-l2/2-i+2]>=l2/2-1){
			if(i-1<mc||l1/2+1-i<mc){
				if(i-1<l1/2+1-i)mc=i-1;
				else mc=l1/2+1-i;
				anso=i;
			}
			if(l1/2+1-i==mc)anso=i;
		}
		cout<<exA[i]<<" "<<exB[l1-l2/2-i+2]<<" "<<mc<<endl;
	}
	for(i=1;i<=l1/2;i++){
		c=s1[i];
		s1[i]=s1[l1-i+1];
		s1[l1-i+1]=c;
	}	
	for(i=anso;i<anso+l1/2;i++)printf("%c",s1[i]);
	printf("\n");
}



int main()
{
	scanf("%d%d",&l1,&l2);
	scanf("%s",&s1);
	for(i=l1;i>=1;i--){
		s1[i]=s1[i-1];
		s1[i+l1]=s1[i];
	}
	l1+=l1;
	scanf("%s",&s2);
	for(i=l2;i>=1;i--){
		s2[i]=s2[i-1];
		s2[i+l2]=s2[i];
	}
	l2+=l2;
	n=l2;
	i=1;
	j=2;
	while(i<=l2/2&&j<=l2/2){
		for(k=0;k<l2/2;k++)if(s2[i+k]!=s2[j+k])break;
		if(k>l2/2)break;
		if(s2[i+k]>s2[j+k])i=i+k+1;
		else j=j+k+1;
		if(i==j)j=i+1;
	}
	if(i<j)anst=i;
	else anst=j;
	Work();
}
