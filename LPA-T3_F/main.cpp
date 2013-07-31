#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_BUILDINGS 751


int n;
int m;
int buildings[MAX_BUILDINGS][2];
float connected[MAX_BUILDINGS][MAX_BUILDINGS];
int roots[MAX_BUILDINGS];
float totalCable = 0;
int count;


float calc_distances(int p1,int p2){
	return sqrt(pow((buildings[p2][0]-buildings[p1][0]),2) + pow((buildings[p2][1]-buildings[p1][1]),2));
}




void union_(int i,int j){
    if(j > i)
        roots[j] = i;
    else
        roots[i] = j;
}

int root(int v){
    
    while(roots[v] != v){
        v = roots[v];
    }
    return v;
}
 
int main()
{
	int x,y;
	float extraCable;
	float min;
	int i,j;
	while(scanf("%d\n",&n)!=EOF)
	{
		min = 9999999;
		totalCable =0;
		count =0;
		extraCable = 0;

		memset(connected,0,sizeof(connected));
		for(i=0;i<n;i++)
		{
			scanf("%d %d\n",&buildings[i][0],&buildings[i][1]);	
		}
		
		for(i = 0;i<n;i++)
		{
			roots[i] = i;
			connected[i][i] = 9999999;
		}


		scanf("%d\n",&m);

		for (i = 0; i < m; ++i)
		{
			scanf("%d %d\n",&x,&y);
			--x;
			--y;

			int z = root(x);
			int w = root(y);

			if(z!=w)
			{
				extraCable += calc_distances(x,y);
				
				union_(z,w);	
			}

			connected[x][y] = connected[y][x]= 9999999;
			count++;

		}

		

		for(i = 0;i<n;i++)
		{
			for(j = 0; j<n; j++)
			{
				
				if(connected[i][j]==0)
					connected[i][j] = connected[j][i] = calc_distances(i,j); 
			}
		}

		int v,u;

		while(count<n)
		{
			min = 9999999;

			for(i = 0;i<n;i++)
			{
				for(j = 0;j<n;j++)
				{
					if(connected[i][j]<min)
					{
						min = connected[i][j];
						u = i;
						v = j;
					}
				}
			}

			if(min!=9999999)
			{
				i = root(u);
				j = root(v);	

				if(i!=j)
				{
					totalCable+=min;
					union_(i,j);
				}
				connected[u][v] = connected[v][u]= 9999999;
			}

			++count;
		}


		printf("%.2f\n",totalCable);
	}

	return 0;
}

