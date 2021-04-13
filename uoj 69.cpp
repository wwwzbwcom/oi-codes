#include<cstdio>
using namespace std;
int main()
{
//	freopen("prog.txt","w",stdout);
	printf("input n\n");
	printf("input m\n");
	printf("a = 0\n");
	printf("b = 1\n");
	printf("if n goto 14\n");
	printf("u = a + b\n");
	printf("v = a + b\n");
	printf("u = u %% m\n");
	printf("v = v %% m\n");
	printf("w = u - v\n");
	printf("if w goto 6\n");
	printf("a = b\n");
	printf("b = u\n");
	printf("u = n - 1\n");
	printf("v = n - 1\n");
	printf("w = u - v\n");
	printf("if w goto 14\n");
	printf("n = u\n");
	printf("if n goto 6\n");
	printf("output b\n");
}
