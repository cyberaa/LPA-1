#include <stdio.h>
#define MAX_FUNCS 101

int adj[MAX_FUNCS][MAX_FUNCS];
int n;

void FW()
{

	int i;
	int j;
	int k;

	for(k = 0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j = 0;j<n;j++)
			{
				if(adj[i][k] == 1 and adj[k][j] == 1)
					adj[i][j] = 1;
			}
		}
	}

}


int main ()
{
	scanf("%d",&n);
	int i,j;
	int nCon = 0;
	int con =0;
	for(i = 0; i<n; i++)
	{
		scanf("%d",&nCon);
		for(j= 0;j<nCon;j++)
		{
			scanf("%d",&con);
			adj[i][con] = 1;
						
		}
	}

	FW();

	for(i=0;i<n;i++)
	{
		if(adj[i][i]==1)
		{
			printf("%d\n",i);
		}
	}

	return 0;
}

