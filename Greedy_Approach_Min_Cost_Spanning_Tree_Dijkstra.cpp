#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<math.h>
#include<fstream>
#include <cassert>

using namespace std;


//定义空间方式
void malloc2D_2(int**& a, int xDim, int yDim)
{
	a = (int**)malloc(xDim * sizeof(int*));
	a[0] = (int*)malloc(xDim * yDim * sizeof(int));
	for (int i = 1; i < xDim; i++)
	{
		a[i] = a[i - 1] + yDim;
	}
	assert(a != NULL);
}

//释放空间方式
void free2D_2(int** a)
{
	free(a[0]);
	free(a);
}

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

void Kru(int** a, int node, int link)
{
	int *repeat = (int*)malloc(sizeof(int) * link);
	memset(repeat, 0, sizeof(int) * link);
	/*for (int i = 0; i < link; i++)
	{
		printf("%d", repeat[i]);
	}*/
	int* num = (int*)malloc(sizeof(int) * link);
	int* step = (int*)malloc(sizeof(int) * link * 2);
	memset(step, -1, sizeof(int) * link * 2);
	for (int i = 0; i < link; i++)
	{
		num[i] = a[i][2];
	}
	qsort(num, link, sizeof(num[0]), cmp);
	int number = 1;
	int total = 0;
	int stp = 0;
	for (int i = 0; i < link; i++)
	{
		for (int j = 0; j < link; j++)
		{
			if (num[i] == a[j][2])
			{
				if (repeat[a[j][0]] == 0 && repeat[a[j][1]] == 0)
				{
					repeat[a[j][0]] = number;
					repeat[a[j][1]] = number;
					step[stp] = a[j][0];
					step[stp + 1] = a[j][1];
					stp = stp + 2;
					number++;
				}
				else if (repeat[a[j][0]] == 0 && repeat[a[j][1]] != 0)
				{
					repeat[a[j][0]] = repeat[a[j][1]];
					step[stp] = a[j][0];
					step[stp + 1] = a[j][1];
					stp = stp + 2;
				}
				else if (repeat[a[j][0]] != 0 && repeat[a[j][1]] == 0)
				{
					repeat[a[j][1]] = repeat[a[j][0]];
					step[stp] = a[j][0];
					step[stp + 1] = a[j][1];
					stp = stp + 2;
				}
				else if (repeat[a[j][0]] != 0 && repeat[a[j][1]] != 0)
				{
					if (repeat[a[j][0]] != repeat[a[j][1]])
					{
						step[stp] = a[j][0];
						step[stp + 1] = a[j][1];
						stp = stp + 2;
						int mid = repeat[a[j][1]];
						for (int x = 1; x <= node; x++)
						{
							if (repeat[x] == mid)
								repeat[x] = repeat[a[j][0]];
						}
						for (int y = 0; y < node; y++)
						{
							if (repeat[y + 1] == repeat[1])
								total++;
						}
						if (total == node)
						{
							printf("Found!The steps are:\n");
							for (int k = 0; step[k] != -1; k = k + 2)
							{
								printf("%d %d ->", step[k], step[k+1]);
							}
							break;
						}
					}
				}
			}
		}
		if (total == node)
		{
			printf("end");
			break;
		}
	}
	/*for (int i = 0; i < link; i++)
	{
		printf("%d", num[i]);
	}*/

}
	

int main()
{
	int node, link;
	cout << "Please input the number of the nodes and the links:";
	cin >> node >> link;
	int** arr = NULL;
	malloc2D_2(arr, link, 3);
	cout << "Please input the start node,the end node and the weight of the link:" << '\n';
	for (int i = 0; i < link; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			scanf_s("%d", &arr[i][j]);
		}
	}
	/*for (int i = 0; i < link; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d", arr[i][j]);
		}
	}*/
	Kru(arr, node, link);
	free2D_2(arr);
	return 0;
}





/*{
	
	cout << "Please input the start node,the end node and the weight of the link:";

	for (int i = 0; i < link; i++)
	{
		scanf_s("%s", number->array->start);
		scanf_s("%s", number->array->end);
		scanf_s("%d", number->array->weight);
		number++;
	}
	//cin >> address->start >> address->end >> address->weight;
	Kru(address);

}*/


