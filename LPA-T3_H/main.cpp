#include <cstdio>
#include <queue>
#include <vector>
#include <functional>
#include <cstring>
#include <algorithm>
#define INF 1e9

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int n, k, T[5], ant;
vector<vii> AdjList;
priority_queue<ii, vector<ii>, greater<ii> > pq;
vi dist, sources;
vector<vi> same;
char line[1000], *num;

int dijkstra() {
  while (!pq.empty()) {
    ii front = pq.top(); pq.pop();
    int d, u;
    d = front.first; u = front.second;
    if (dist[u] == d) {
      for (int i=0 ; (unsigned)i<AdjList[u].size() ; i++) {
        ii v = AdjList[u][i];
        if (dist[u] + v.second < dist[v.first]) {
          dist[v.first] = dist[u] + v.second;
          pq.push(ii(dist[v.first], v.first));
        }
      }
    }
  }
  int mn=(int)1e9;
  for (int i=k ; i<500 ; i+=100) {
    mn = min(mn, dist[i]);
  }
  return mn;
}

int main() {
  int next;
  while (scanf("%d %d\n", &n, &k) == 2) {
    same.assign(100, vi());
    AdjList.assign(500, vii());
    sources.clear();
    for (int i=0 ; i<n ; i++)
      scanf("%d ", &T[i]);
    scanf("\n");
    for (int i=0 ; i<n ; i++) {
      fgets(line,sizeof(line),stdin);
      num = strtok(line, " ");
      sscanf(num, "%d", &ant);
      for (int s=0 ; (unsigned)s<same[ant].size() ; s++) {
        AdjList[ant + (i * 100)].push_back(ii(same[ant][s], 60)); // Bi-directional
        AdjList[same[ant][s]].push_back(ii(ant + (i * 100), 60)); // Bi-directional
      }
      same[ant].push_back(ant + (100 * i));
      if(ant == 0) sources.push_back(ant + (100 * i));
      while ((num = strtok(NULL, " ")) != NULL) {
        sscanf(num, "%d", &next);
        AdjList[ant + (i * 100)].push_back(ii(next + (i*100), (next-ant) * T[i])); // Bi-directional
        AdjList[next + (i*100)].push_back(ii(ant + (i * 100), (next-ant) * T[i]));
        for (int s=0 ; (unsigned)s<same[next].size() ; s++) {
          AdjList[next + (i * 100)].push_back(ii(same[next][s], 60)); // Bi-directional
          AdjList[same[next][s]].push_back(ii(next + (i * 100), 60)); // Bi-directional
        }
        ant = next;
        same[next].push_back(next + (100 * i));
      }
    }
    dist.assign(500, (int)INF);
    for (int i=0 ; (unsigned)i<sources.size() ; i++) 
    {
      pq.push(ii(0, sources[i]));
      dist[sources[i]] = 0;
    }
    int mn = dijkstra();
    if (mn == INF)
      printf("IMPOSSIBLE\n");
    else    
      printf("%d\n", mn);
  }
}

