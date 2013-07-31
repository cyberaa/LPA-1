#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int n,m;
char names[5001][256];
int list[5001][5001];
int len[5001];
char visited[5001];

int union_find(int v)
{

	if(visited[v]=='1')
		return 0;

	visited[v] = '1';
	int w = 1;

	for(int i = 0;i<len[v];i++)
	{

		w += union_find(list[v][i]);
		
	}

	return w;

}
int main()
{
	int a,b;
	char p1[256],p2[256];
	while(scanf("%d %d\n",&n,&m)!=EOF)
	{
		for(int i = 0;i<n;i++)
		{
			scanf("%s\n",names[i]);

			
		}

		for(int i = 0;i<m;i++)
		{
			scanf("%s %s\n",p1,p2);

			for(int j = 0; j<n; j++)
			{
				if(strcmp(names[j],p1)==0)
				{
					a = j;
					break;
				}
			}

			for(int j = 0; j<n; j++)
			{
				if(strcmp(names[j],p2)==0)
				{
					b= j;
					break;
				}
			}


			list[a][len[a]]=b;
			len[a]++;
			list[b][len[b]]=a;
			len[b]++;

		}
		int max = -1;
		for(int i = 0; i<n;i++)
		{
			int v = union_find(i);
			if(v>max)
				max = v;
		}

		printf("%d\n",max);
	}

	return 0;
}


