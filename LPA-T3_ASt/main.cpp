#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stack>
#define MAX_VALUE 10001
using namespace std;


int marked[MAX_VALUE];
int matrix[MAX_VALUE][101];
int len[MAX_VALUE];
int n;
int distNodes[MAX_VALUE];
int ligacoes[MAX_VALUE];


int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void imprime_resultados(){
	int i;
	printf("Shortest:");
	for(i=0;i<=n;i++){
		if(ligacoes[i]==1){
			printf(" %d",i);
		}
	}
	
}



void cut(){
	int i,z;
	int no;
	int passed[MAX_VALUE]={0};



	for(i=0;i<n;i++){
		if(ligacoes[i]==1 && passed[i]==0){
			ligacoes[i]=0;
			passed[i]=1;
			/*atualizar os nos*/
			for(z=0;z<len[i];z++){
				no = matrix[i][z];
				if(ligacoes[no] > 0){
					--ligacoes[no];
				}
				passed[no]=1;
			}
		}
	}
}

bool checkCon()
{
	for(int i = 1; i<=n;i++)
	{
		if(len[i]>1)
			return true;
	}

	return false;
}



void removeFromQueue(int que[MAX_VALUE],int tam)
{
	int w; 
	int pos;
		for(int i = 0;i<tam;i++)
		{
			pos = que[i];

			for(int j = 0;j<len[pos];j++)
			{
				w = matrix[pos][j];

				for(int k = 0;k<len[w];k++)
				{
					if(matrix[w][k]==pos)
					{
						for(int l = k; l<len[w]-1;l++)
						{
							matrix[w][l]= matrix[w][l+1];
						}	
						len[w]--;
						break;
					}
				}
			}
			
			memset(matrix[que[i]],0,sizeof(int)*n+1);
			len[que[i]]=0;

		}
}
int maisLonge[2][101];
int lenMaisLonge = 0;
void dfs(int v, int dist)
{

	if(len[v] == 1)
	{
		if(dist>maisLonge[0][0])
		{
			maisLonge[0][0] = dist;
			maisLonge[1][0] = v;
			lenMaisLonge=1;
		}else if(dist == maisLonge[0][0])
		{
			maisLonge[1][lenMaisLonge++] = v;
		}
	}

	marked[v] = 1;
	int t;
	for(int i = 0;i<len[v];i++)
	{
		t = matrix[v][i];
		if(marked[t] ==0)
		{
			dfs(t,dist+1);
		}
	}
	marked[v] =0;
}

int main()
{
	int x,y;
	while(scanf("%d\n",&n)!=EOF)
	{
		memset(distNodes,0,sizeof(distNodes));
		memset(marked,0,sizeof(marked));
		memset(len,0,sizeof(len));
		

		for(int i = 0;i<n-1;i++)
		{
			scanf("%d %d\n",&x,&y);

			matrix[x][len[x]]=y;
			len[x]++;

			matrix[y][len[y]]=x;
			len[y]++;

			++ligacoes[x];
			++ligacoes[y];
		}

		dfs(1,1);
		int tallest[101];
		int lenTallest = 0;

		for(int i = 0;i<lenMaisLonge;i++)
		{
			tallest[lenTallest] = maisLonge[1][i];
			lenTallest++;
		}


		memset(marked,0,sizeof(marked));
		maisLonge[0][0] = 0;
		lenMaisLonge = 0;

		dfs(tallest[0],1);

		int flag =0;
		for(int i = 0;i<lenMaisLonge;i++)
		{	
			flag = 0;

			for(int j = 0;j<lenTallest;j++)
			{
				if(tallest[j]==maisLonge[1][i])
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
				tallest[lenTallest++] = maisLonge[1][i];
		}


		qsort (tallest, lenTallest, sizeof(int), compare);


		
		int Q[MAX_VALUE];
		int lenQ = 0;
		while(checkCon())
		{	
			
			for(int i = 0;i<=n;i++)
			{
				if(len[i] == 1)
				{
					
					Q[lenQ] = i;
					lenQ++;
				}
			}
			
			

			removeFromQueue(Q,lenQ);
			lenQ = 0;

			memset(Q,0,sizeof(Q));
		}

		for(int i = 0;i<=n;i++)
			{
				if(len[i] == 1)
				{

					Q[lenQ] = i;
					lenQ++;
				}
			}
			


		qsort (Q, lenQ, sizeof(int), compare);

		printf("Shortest:");
		for(int i = 0;i<lenQ;i++)
		{
			printf(" %d",Q[i]);
		}
		printf("\nTallest:");
		for(int i = 0;i<lenTallest;++i)
		{
			printf(" %d",tallest[i]);
		}
		printf("\n");


	}

}




