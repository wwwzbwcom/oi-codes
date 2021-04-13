#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
const int maxn=10000100;
char tmp[maxn];
char *str[2][maxn];
int cnt[2];
int len[2][maxn];
int head,las[maxn],nxt[maxn];
bool judge0()
{
	if(cnt[0]>=2)
	{
		int p;
		p=0;
		head=0;
		for(int i=0;i<=cnt[0];i++)	nxt[i]=i+1;
		for(int i=0;i<=cnt[0];i++)	las[i]=i-1;
		while(1)
		{
			while(nxt[head]<cnt[0]&&str[0][head][p]=='*')	head=nxt[head];	
			char stnd=str[0][head][p];
			for(int i=nxt[head];i<cnt[0];i=nxt[i])
			{
				if(str[0][i][p]=='*')
				{
					nxt[las[i]]=nxt[i];
					las[nxt[i]]=las[i];
				}
				else	if(str[0][i][p]!=stnd)	return 0;
			}
			p++;
		//	cout<<p<<endl;
			if(nxt[head]>=cnt[0])	break;
		}
		//cout<<"===================="<<endl;
		p=0;
		head=0;
		for(int i=0;i<=cnt[0];i++)	nxt[i]=i+1;
		for(int i=0;i<=cnt[0];i++)	las[i]=i-1;
		while(1)
		{
			while(nxt[head]<cnt[0]&&str[0][head][len[0][head]-p-1]=='*')	head=nxt[head];
			char stnd=str[0][head][len[0][head]-p-1]; 
			for(int i=nxt[head];i<cnt[0];i=nxt[i])
			{
				if(str[0][i][len[0][i]-p-1]=='*')
				{
					nxt[las[i]]=nxt[i];
					las[nxt[i]]=las[i];
				}
				else	if(str[0][i][len[0][i]-p-1]!=stnd)	return 0;
			}
			p++;
			if(nxt[head]>=cnt[0])	break;
		}
	}
	return 1;
}
int sta[maxn],end[maxn],bc;
int *fai;
int poi[maxn];
int judge1()
{
	fai=poi+10;
	if(cnt[1]>=2)
	{
		int stnd=len[1][0];
		for(int i=0;i<cnt[1];i++)	if(len[1][i]!=stnd)	return 0;
		for(int i=0;i<len[1][0];i++)
		{
			char stnd=str[1][0][i];
			for(int j=0;j<cnt[1];j++)	if(str[1][j][i]!=stnd)	return 0;
		}
	}
	if(cnt[0]>=1&&cnt[1]>=1)
	{
		for(int i=0;i<cnt[0];i++)
		{	 
			int con=1;	bc=0;
			str[0][i][len[0][i]]='*';
			for(int j=0;j<=len[0][i];j++)
			{
				if(str[0][i][j]=='*')
				{
					if(con==0)	end[bc-1]=j-1,con=1;
				}
				else	if(con==1)	sta[bc]=j,bc++,con=0;
				//cout<<i<<" "<<bc<<" "<<str[0][0][i]<<endl;
			}
			str[0][i][len[0][i]]='\0';
		//	for(int j=0;j<bc;j++)	cout<<sta[j]<<"="<<end[j]<<endl;
			for(int j=0;j<bc;j++)
			{
				int fix=sta[j]-1;
				fai[sta[j]-1]=sta[j]-1;
				fai[sta[j]]=sta[j]-1;
				for(int k=sta[j]+1;k<=end[j];k++)
				{
				//	cout<<fix+1<<"~"<<j<<" "<<str[0][fix+1]<<" "<<str[j]<<endl;
					while(fix!=sta[j]-1&&str[0][i][fix+1]!=str[0][i][k])	fix=fai[fix];
					if(str[0][i][fix+1]==str[0][i][k])	fix++;
					fai[k]=fix;
				}
			//	for(int k=sta[j];k<=end[j];k++)	cout<<k<<"="<<fai[k]<<" ";
			//	cout<<endl; 
			}
	
			int p=0;
			//	cout<<i<<endl;
			for(int j=0;j<bc;j++)
			{
			//	cout<<i<<" "<<j<<endl;
				int fix=sta[j]-1;
			
				if(sta[j]!=0&&end[j]==len[0][i]-1)
				{
					if(p>len[1][0]-(end[j]-sta[j]+1))	return 0;
					else	p=len[1][0]-(end[j]-sta[j]+1);
				}
			
				while(fix<end[j]&&p<len[1][0])
				{
					while(fix!=sta[j]-1&&str[0][i][fix+1]!=str[1][0][p])	fix=fai[fix];
					if(str[0][i][fix+1]==str[1][0][p])	fix++;
					p++;
				}
				//	cout<<p<<" "<<len[1][i]<<" "<<end[j]<<endl;
			//	cout<<p<<" "<<fix<<" "<<j<<" "<<sta[j]<<" "<<end[j]<<" "<<len[1][0]<<endl;
				if(p==len[1][0]&&(fix!=end[j]||j!=bc-1))	return 0;
			//	cout<<1<<"="<<endl;
				if(sta[j]==0&&p-(end[j]-sta[j]+1)+1-1!=0)	return 0;
			//	cout<<2<<"="<<endl;
				if(end[j]==len[0][i]-1&&p!=len[1][0])	return 0;
			//	cout<<3<<"="<<endl;
			}
		}
	}	
	return 1;
}
void clear()
{
	for(int i=0;i<2;i++)
			for(int j=0;j<cnt[i];j++)
				delete str[i][j]; 
	cnt[0]=cnt[1]=0;
	bc=0;
}
int main()
{	
	freopen("hs.in","r",stdin);
	freopen("hs.out","w",stdout);
//	cout<<sizeof(char)<<" "<<sizeof(int)<<endl;
	int gn;	scanf("%d",&gn);
	for(int g=1;g<=gn;g++)
	{
		int n;	scanf("%d",&n);
		int mxa=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%s",tmp);	int lt=strlen(tmp);
			mxa=max(mxa,lt);
			int p=1;
			for(int j=0;j<lt;j++)	if(tmp[j]=='*')	p=0;
			len[p][cnt[p]]=lt;
			str[p][cnt[p]]=(char*)malloc((lt+5)*(sizeof lt));
			memcpy(str[p][cnt[p]],tmp,lt+10);
			cnt[p]++; 
		}
		//cout<<mxa<<endl;
		//cout<<cnt[0]<<" "<<cnt[1]<<endl;
		
		if(judge0())
		{
		//	cout<<"="<<endl;
			if(judge1())	printf("Y\n");
			else	printf("N\n");
		}
		else	printf("N\n");
		
		clear();
	}
}
