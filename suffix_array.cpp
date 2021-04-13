#include<iostream>
#include<cstring>
using namespace std;
char str[100100];
int suf[100100];
int tra[100100],tsu[100100];						//��ra1�õ�����͸�su2�õ����飨��Ȼ����ᷴ�������� 
int buc[100100],tst[100100];						//Ͱ����ʱԪ�أ���Ҳ��֪���ý�ʲô�� 
//su��������λ��
//ra��λ�ò����� 
void suffix_array(char *str,int *su1,int n,int m)
{
	int *ra1=tra,*su2=tsu,*tmp;
	for(int i=0;i<m;i++)	buc[i]=0;
	for(int i=0;i<n;i++)	buc[ra1[i]=str[i]]++;	//��Ҫ������� 
	for(int i=1;i<m;i++)	buc[i]+=buc[i-1];
	for(int i=n-1;i>=0;i--)	su1[--buc[str[i]]]=i;
	for(int len=1,cnt=1;cnt<n;len*=2,m=cnt)			//len��ǰ�����ַ������ȵ�һ�룬cntͳ���ж����ֲ�ͬ�ĺ�׺����Ȼ�м仹����Щ����ã��� 
	{
		cnt=0;
		for(int i=n-len;i<n;i++)	su2[cnt++]=i;
		for(int i=0;i<n;i++)	if(su1[i]>=len)	su2[cnt++]=su1[i]-len;
		for(int i=0;i<n;i++)	tst[i]=ra1[su2[i]];		//tst[i]��ڶ��ؼ���������i���ϴ������ڼ�����֤���ڶ��ؼ���˳��װ��Ͱ�У� 
		
		for(int i=0;i<m;i++)	buc[i]=0;
		for(int i=0;i<n;i++)	buc[tst[i]]++;			//��Ϊtst��0-n�ֱ��Ӧ�ڶ��ؼ�������0-n������װ��Ͱʱ��ÿ��Ͱ�ڶ��ǰ��յڶ��ؼ��ִ�С��������� 
		for(int i=1;i<m;i++)	buc[i]+=buc[i-1];
		for(int i=n-1;i>=0;i--)	su1[--buc[tst[i]]]=su2[i];		//������µĺ�׺���飨��ʼλ��Ҫͨ��su2����ѯ���� 
		
		tmp=ra1,ra1=su2,su2=tmp;
		ra1[su1[0]]=0;
		cnt=1; 
		for(int i=1;i<n;i++)							//�����׺������ͬ�����������У� ������ͨ��su1�ó�ra1��ʱ��Ҫע���жϺ�ǰһλ�Ƿ�һ����һ���Ļ�Ҫ����ͬ��rankֵ������ż�һ 
			if(su2[su1[i-1]]==su2[su1[i]]&&su2[su1[i-1]+len]==su2[su1[i]+len])	ra1[su1[i]]=cnt-1;
			else	ra1[su1[i]]=cnt++;
	}
}
int main()
{
	cin>>str;
	str[strlen(str)]=1;
	str[strlen(str)+1]='\0';						//ע���׺�������һ��Ҫ��һ�������ʶ������Ȼ�ͻ���ִ��� 
	suffix_array(str,suf,strlen(str),255);
	for(int i=0;i<strlen(str);i++)	cout<<i<<" "<<suf[i]<<endl;
}
