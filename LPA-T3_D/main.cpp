#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define min(a,b) ((a) < (b) ? a : b) 
int nNodes;
int list[1001][1001];
int len[1001];
int low[1001];
int dfs[1001];
int time = 0;
int nArts = 0;

int checkArt[1001];


void Art(int v)
{
	low[v]=dfs[v]=time=time+1;

	int i = 0;
	int w;
	for(i=0;i<len[v];i++)
	{
		w = list[v][i];

		if(dfs[w]==-1)
		{
			Art(w);
			low[v] = min(low[v],low[w]);

			if(dfs[v]==1 and dfs[w]!=2)
			{
				
				if(checkArt[v]==0)
				{
					checkArt[v]=1;
					nArts++;
				}
				
			}else if(dfs[v]!=1 and low[w]>=dfs[v])
			{
				if(checkArt[v]==0)
				{
					checkArt[v]=1;
					nArts++;
				}
			}
		}else{
			low[v] = min(low[v],dfs[w]);
		}
	}
}
int main()
{
	
	
	char  c[256];
	
	char *aux;
	int flag = 0;
	int i = 0;
	int toAdd;
	int aNum; 

	while(scanf("%d\n",&nNodes)!=EOF)
	{
		memset(len,0,sizeof(len));
		memset(low,0,sizeof(low));
		memset(dfs,-1,sizeof(dfs));
		memset(list,0,sizeof(list));
		memset(checkArt,0,sizeof(checkArt));
		time = 0;
		nArts = 0;
		if(nNodes==0)
			break;

		do{
			flag = 0;
			i=0;
			while((c[i]=getchar())!='\n')
			{
				i++;
			}

			c[i] = '\0';
			i=0;
			aux = strtok(c," ");

			while(aux!=NULL)
			{
				aNum = atoi(aux);

				if(aNum==0)
				{
					flag = 1;
					break;
				}

				if(i == 0)
				{

					toAdd = aNum;
					i++;
				}else
				{
					list[toAdd][len[toAdd]] = aNum;
					len[toAdd]++;
					list[aNum][len[aNum]] = toAdd;
					len[aNum]++;
				}

				aux = strtok(NULL," ");
			}

			
			if(flag == 1)
				break;

		}while(1);

		for(i=1;i<=nNodes;i++)
		{
			if(dfs[i]==-1)
				Art(i);
		}

		printf("%d\n",nArts);

	}

	return 0;
}


