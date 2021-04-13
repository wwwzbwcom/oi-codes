#include<iostream>
#include<cstring>
using namespace std;
char str[100100];
int suf[100100];
int tra[100100],tsu[100100];						//给ra1用的数组和给su2用的数组（当然后面会反复调换） 
int buc[100100],tst[100100];						//桶和临时元素（我也不知道该叫什么） 
//su给排名查位置
//ra给位置查排名 
void suffix_array(char *str,int *su1,int n,int m)
{
	int *ra1=tra,*su2=tsu,*tmp;
	for(int i=0;i<m;i++)	buc[i]=0;
	for(int i=0;i<n;i++)	buc[ra1[i]=str[i]]++;	//不要忘了这个 
	for(int i=1;i<m;i++)	buc[i]+=buc[i-1];
	for(int i=n-1;i>=0;i--)	su1[--buc[str[i]]]=i;
	for(int len=1,cnt=1;cnt<n;len*=2,m=cnt)			//len当前排序字符串长度的一半，cnt统计有多少种不同的后缀（当然中间还做了些别的用）。 
	{
		cnt=0;
		for(int i=n-len;i<n;i++)	su2[cnt++]=i;
		for(int i=0;i<n;i++)	if(su1[i]>=len)	su2[cnt++]=su1[i]-len;
		for(int i=0;i<n;i++)	tst[i]=ra1[su2[i]];		//tst[i]存第二关键字排名第i的上次排名第几（保证按第二关键字顺序装入桶中） 
		
		for(int i=0;i<m;i++)	buc[i]=0;
		for(int i=0;i<n;i++)	buc[tst[i]]++;			//因为tst是0-n分别对应第二关键字排名0-n，所以装入桶时，每个桶内都是按照第二关键字从小到大排序的 
		for(int i=1;i<m;i++)	buc[i]+=buc[i-1];
		for(int i=n-1;i>=0;i--)	su1[--buc[tst[i]]]=su2[i];		//计算出新的后缀数组（起始位置要通过su2来查询到） 
		
		tmp=ra1,ra1=su2,su2=tmp;
		ra1[su1[0]]=0;
		cnt=1; 
		for(int i=1;i<n;i++)							//多个后缀可能有同个排名（并列） ，所以通过su1得出ra1的时候，要注意判断和前一位是否一样，一样的话要给相同的rank值，否则才加一 
			if(su2[su1[i-1]]==su2[su1[i]]&&su2[su1[i-1]+len]==su2[su1[i]+len])	ra1[su1[i]]=cnt-1;
			else	ra1[su1[i]]=cnt++;
	}
}
int main()
{
	cin>>str;
	str[strlen(str)]=1;
	str[strlen(str)+1]='\0';						//注意后缀数组后面一定要有一个特殊标识符，不然就会出现错误 
	suffix_array(str,suf,strlen(str),255);
	for(int i=0;i<strlen(str);i++)	cout<<i<<" "<<suf[i]<<endl;
}
