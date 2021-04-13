#include<stdio.h>


int main()
{
   int n; scanf("%d",&n);
   int ans = 0;
   for(int i = 1; i <= n; )
   {
   	    int val = n/i, up = n/val;
   	    ans += (up - i + 1) * val;
   	    
   }
   printf("%d\n",ans);
   return 0;	
} 
