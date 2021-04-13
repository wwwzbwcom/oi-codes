#include<iostream>
#include<cstring>
using namespace std;
const int maxn=1e6+100;
class Kmp
{	
	private:
		char str[maxn];
		int fai[maxn];
	public:
		void build()
		{
			cin>>str+1;
			int len=strlen(str+1),fix=0;
			fai[1]=0;
			for(int i=2;i<=len;i++)
			{
				while(fix&&str[fix+1]!=str[i])	fix=fai[fix];
				if(str[fix+1]==str[i])	fix++;
				fai[i]=fix;
			}
		}
		int work()
		{
			int mxa=0;
			for(int i=1;i<len;i++)	mxa=max(mxa,fai[i]);
			int tmp=fai[len];
			while(tmp!=0)	if(tmp<=mxa)	return tmp;
			return 0;
		}
}kmp;
int main()
{
	kmp.build();
	cout<<kmp.work();
}
