#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;


char list[301][5001];
int len[301];
char type[301];
char visited[301];
int n,m;



int BFS(int v)
{

	queue<int> Q;

	visited[v] ='1';

	Q.push(v);
	int t,u;
	while(!Q.empty())
	{
		t=Q.front();

		for(int i = 0;i<len[t];i++)
		{	
			u = list[t][i];
			if(visited[u] =='0')
			{
				if(type[t]=='0' && type[u] =='0')
				{
					type[t] = '1';
					type[u] = '2';
				}else if(type[t]!='0' && type[u] =='0')
				{
					if(type[t] == '1')
					{
						type[u] = '2';

					}else{
						type[u] = '1';
					}
				}else if(type[t] == type[u])
				{
					printf("Yes\n");
					return 1;
				}

				Q.push(u);
			}

		}

		visited[t] = '1';
		Q.pop();
	}
	return 0;
}
int main()
{
	int x,y;
	while(scanf("%d %d",&m,&n)!=EOF)
	{
		memset(visited,'0',sizeof(char)*m+1);
		memset(type,'0',sizeof(char)*m+1);
		for(int i = 0;i<=m;i++)
		{
			
			len[i] = 0;
		}

		for(int i = 0;i<n;i++)
		{
			scanf("%d %d",&x,&y);
			list[x][len[x]]=y;
			len[x]++;
			list[y][len[y]]=x;
			len[y]++;
		}

		int flag = 0;
		for(int i = 1;i<=m;i++)
		{
			
			if(BFS(i) == 1)
			{
				flag = 1;
				break;
			}
		}

		if(flag == 0)
			printf("No\n");


	}
	return 0;
}



