#include<cstdio>
#include<cstring>
char str[1001000];
char out[1001000];
void En()
{
	scanf("%s",str);
	for(int i=0;i<6;i++)
	printf("%s",str);
}
void De()
{
	scanf("%s",str);
	int len=strlen(str);
	for(int i=0;i<len;i++)	if(str[i]!='#')	out[i/6]=str[i];
	out[len]='\0';
	printf("%s",out);
}
