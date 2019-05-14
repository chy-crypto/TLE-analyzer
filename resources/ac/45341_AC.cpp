// _Z3dfsi minLen
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int K, N, R;
struct Road{
	int d, L, t;
};
vector< vector<Road> > G(110);
int minL[110][10010];//minL[i][j]从起点走到i，花费为j的情况下的最短路
int minLen;
int totalLen;
int totalCost;
int visited[110];

void dfs(int s)
{
	if(s == N){
		minLen = min(minLen, totalLen);
		return ;
	}
	minL[s][totalCost] = min(totalLen, minL[s][totalCost]);
	for(int i = 0; i < G[s].size(); ++i){
		Road r = G[s][i];
		if(visited[r.d] ||
		   totalCost + r.t > K ||
		   totalLen + r.L >= minLen ||
		   totalLen + r.L >= minL[r.d][totalCost + r.t])
			continue;
		totalLen += r.L;
		totalCost += r.t;
		visited[r.d] = 1;
		dfs(r.d);
		totalLen -= r.L;
		totalCost -= r.t;
		visited[r.d] = 0;
	}
}

int main()
{
	cin >> K >> N >> R;
	for(int i = 0; i < R; ++i){
		int s;
		Road r;
		cin >> s >> r.d >> r.L >> r.t;
		if(s == r.d)
			continue;
		G[s].push_back(r);
	}
	memset(visited, 0, sizeof(visited));
	for(int i = 0; i < 110; ++i)
		for(int j = 0; j < 10010; ++j)
			minL[i][j] = 1 << 30;
	totalLen = 0;
	minLen = 1 << 30;
	totalCost = 0;
	visited[1] = 1;
	dfs(1);
	if(minLen < (1 << 30))
		cout << minLen << endl;
	else
		cout << "-1" << endl;
	return 0;
}