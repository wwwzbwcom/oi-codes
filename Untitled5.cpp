#include <bits/stdc++.h>
using namespace std;

#define N 100005
#define M 400005

int type, n, m, cnt, in[N], out[N], head[N];
bool con[N],vis[M];
stack<int> s;

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}

struct graph
{
	int next, to, val;
	graph() {}
	graph(int _next, int _to, int _val)
	: next(_next), to(_to), val(_val) {}
} edge[M];

inline void add(int x, int y, int z)
{
	edge[++cnt] = graph(head[x], y, z);
	head[x] = cnt; ++out[x], ++in[y];
}

int cntz=0;
void dfs(int x)
{
	for (int i = head[x]; i; i = head[x])
	{
		while (i && vis[abs(edge[i].val)]) i = edge[i].next,cntz++;
		if (!i) return;
		vis[abs(edge[i].val)] = true;
		head[x] = edge[i].next;//一点优化 
		dfs(edge[i].to); s.push(edge[i].val);
	}
}

int main()
{
	freopen("in.txt","r",stdin);
	cin >> type >> n >> m;
	for (int x, y, i = 1; i <= m; ++i)
	{
		x = read(), y = read(), add(x, y, i);
		if (type == 1) add(y, x, -i);
	}
	for (int i = 1; i <= n; ++i)
		if (in[i] != out[i] || (type == 1 && in[i] % 2))
			{ puts("NO"); return 0; }
	dfs(edge[cnt].to);
	for (int i = 1; i <= m; ++i)
		if (!vis[i]) { puts("NO"); return 0; }
	puts("YES");
	cout<<cntz<<endl;
//	while (!s.empty())
	//	printf("%d ", s.top()), s.pop();
	return 0;
}
