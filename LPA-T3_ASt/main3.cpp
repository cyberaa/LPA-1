#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#define max(a,b) a>b?a:b


int adj[10001][101];
int len[10001];
int n;
int dfs[10001];
int t =0;
int Q[10001];
int Qfilled[10001];
int lenQ;

int maxDFS[2];

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}


void fdfs(int v)
{
	dfs[v] = t=t+1;
	int w;
	for(int i = 0;i<len[v]; i++)
	{
		w = adj[v][i];
		if(dfs[w]==-1)
		{
			fdfs(w);
		}
	}
	if(dfs[v]>maxDFS[0])
	{
		maxDFS[0] = dfs[v];
		maxDFS[1] = v;
	}
}

bool checkCon()
{
	for(int i = 0; i<n;i++)
	{
		if(len[i]>1)
			return true;
	}

	return false;
}


void getLeafs()
{

	for(int i = 1;i<=n;i++)
	{
		fdfs(i);

		if(Qfilled[maxDFS[1]]<=0)
		{

			Q[lenQ]=maxDFS[1];
			Qfilled[maxDFS[1]] = 1;
			lenQ++;

		}
		t = 0;
		maxDFS[0] = 0;
		maxDFS[1] = 0;


		memset(dfs,-1,sizeof(dfs));
	}

}

void removeFromQueue(int que[10001],int tam)
{
	int w; 
	int pos;
		for(int i = 0;i<tam;i++)
		{
			pos = que[i];

			for(int j = 0;j<len[pos];j++)
			{
				w = adj[pos][j];

				for(int k = 0;k<len[w];k++)
				{
					if(adj[w][k]==pos)
					{
						for(int l = k; l<len[w]-1;l++)
						{
							adj[w][l]= adj[w][l+1];
						}	
						len[w]--;
						break;
					}
				}
			}
			
			memset(adj[que[i]],0,sizeof(int)*n+1);
			len[que[i]]=0;

		}
}
int main()
{
	int x,y;
	scanf("%d\n",&n);
	
	memset(dfs,-1,sizeof(dfs));

	for(int i = 0;i<n-1;i++)
	{
		scanf("%d %d\n",&x,&y);

		adj[x][len[x]]=y;
		len[x]++;

		adj[y][len[y]]=x;
		len[y]++;
		
	}


	getLeafs();

	int maxQ[10001];

	memcpy(maxQ,Q,sizeof(int)*lenQ+1);
	
	int maxLenQ = lenQ;
	
	while(checkCon())
	{

		removeFromQueue(Q,lenQ);
		memset(Q,0,sizeof(Q));
		lenQ = 0;
		for(int i = 1;i<=n;i++)
		{
			if(len[i] == 1)
			{
				Q[lenQ] = i;
				lenQ++;
			}
		}
	}


		qsort (Q, lenQ, sizeof(int), compare);
		printf("Shortest:");
		for(int i = 0;i<lenQ;i++)
		{
			printf(" %d",Q[i]);
		}
		printf("\nTallest:");
		qsort (maxQ, maxLenQ, sizeof(int), compare);

		for(int i = 0;i<maxLenQ;i++)
		{
			printf(" %d",maxQ[i]);
		}
		printf("\n");
		

	
}



