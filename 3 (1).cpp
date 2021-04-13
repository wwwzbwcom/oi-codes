#include <iostream>

#include <cstdlib>

using namespace std;

struct MAP 

{

int c[5][5],setp,clor;

MAP ()

{

setp=0;

}

} que[100000];

const int dx[4]={-1,1,0,0},

  dy[4]={0,0,-1,1};

int head=0,tail=2;

char ch[4];

bool done(int i=tail)

{

MAP &p=que[i];

if(p.c[0][0]==p.c[0][1] and p.c[0][0]==p.c[0][2] and p.c[0][0]==p.c[0][3])

return true;

if(p.c[1][0]==p.c[1][1] and p.c[1][0]==p.c[1][2] and p.c[1][0]==p.c[1][3])

return true;

if(p.c[2][0]==p.c[2][1] and p.c[2][0]==p.c[2][2] and p.c[2][0]==p.c[2][3])

return true;

if(p.c[3][0]==p.c[3][1] and p.c[3][0]==p.c[3][2] and p.c[3][0]==p.c[3][3])

return true;

if(p.c[0][0]==p.c[1][0] and p.c[0][0]==p.c[2][0] and p.c[0][0]==p.c[3][0])

return true;

if(p.c[0][1]==p.c[1][1] and p.c[0][1]==p.c[2][1] and p.c[0][1]==p.c[3][1])

return true;

if(p.c[0][2]==p.c[1][2] and p.c[0][2]==p.c[2][2] and p.c[0][2]==p.c[3][2])

return true;

if(p.c[0][3]==p.c[1][3] and p.c[0][3]==p.c[2][3] and p.c[0][3]==p.c[3][3])

return true;

if(p.c[0][0]==p.c[1][1] and p.c[0][0]==p.c[2][2] and p.c[0][0]==p.c[3][3])

return true;

if(p.c[0][3]==p.c[1][2] and p.c[0][3]==p.c[2][1] and p.c[0][3]==p.c[3][0])

return true;

return false;

}

int change(int x,int y,int clor,MAP &h=que[head])

{

for(int i=0;i<4;i++)

{

if(0<=x+dx[i] and x+dx[i]<4 and 0<=y+dy[i] and y+dy[i]<4 and h.c[x+dx[i]][y+dy[i]]==clor)

{

que[++tail]=h;

swap(que[tail].c[x][y],que[tail].c[x+dx[i]][y+dy[i]]);

que[tail].setp=h.setp+1;

que[tail].clor*=-1;

}

if(done())

{

cout<<que[tail].setp;

exit(0);

}

}

}

int main()

{

for(int i=0;i<4 and cin>>ch;i++)

for(int j=0;j<4;j++)

que[1].c[i][j]=que[2].c[i][j]=ch[j]=='B'?-1:ch[j]=='W'?1:0;

que[1].clor=1;

que[2].clor=-1;

while(++head<=tail)

{

for(int i=0,clor=que[head].clor;i<4;i++)

for(int j=0;j<4;j++)

if(que[head].c[i][j]==0)

change(i,j,clor);

}

return 0;

}

