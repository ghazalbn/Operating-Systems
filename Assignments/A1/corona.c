// Bakhshande

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Virus 
{
	char name[11]; 
	int INF, MOR, RES, AVG; 
};

void swap (struct Virus *virus, int i, int j)
{
	struct Virus tmp = virus[j];
	virus[j] = virus[i] ; 
	virus[i] = tmp;    
}

void sort(struct Virus *virus, int count, bool (*criterion)(struct Virus*, int, int))
{
	for (int i = 0; i < count - 1 ; i++)
	{
		for (int j = 0; j < count - i - 1 ; j++)
		{
			if ((*criterion)(virus, j, j + 1))
				swap(virus, j, j+1);
		}
	}
}

bool criterion0(struct Virus *virus, int i, int j)
{
  	return virus[i].INF >= virus[j].INF; 
}

bool criterion1(struct Virus *virus, int i, int j)
{
  	return virus[i].AVG >= virus[j].AVG;
}

bool criterion2(struct Virus *virus, int i, int j)
{
  	return virus[i].INF + virus[i].MOR >= virus[j].INF + virus[j].MOR;
}

bool criterion3(struct Virus *virus, int i, int j)
{
  	return virus[i].RES + 3 * virus[i].MOR >= virus[j].RES + 3 * virus[j].MOR;
} 


int main ()
{
	int count, criterion; 
	scanf("%d", &count);
	struct Virus virus[count]; 
	
	for (int i = 0; i < count; i++)
	{
		scanf("%s %d %d %d", &virus[i].name, &virus[i].INF, &virus[i].MOR, &virus[i].RES);
		virus[i].AVG = (virus[i].RES + virus[i].MOR + virus[i].INF) / 3 ; 
	}
	scanf("%d", &criterion);
	
	bool (*criterions[4])(struct Virus*, int, int) = 
	{
		*criterion0, 
		*criterion1, 
		*criterion2, 
		*criterion3
	};
	
	sort(virus, count, criterions[criterion]);
	printf ("           INF MOR RES AVG\n");
	for (int i = count - 1; i >= 0; i--)
	{
		printf(virus[i].name);
		for(int j = 0; j < 11 - strlen(virus[i].name); j++)	
			printf(" ");
		printf("%3d %3d %3d %3d\n", virus[i].INF, virus[i].MOR, virus[i].RES, virus[i].AVG);
	}
 
	return 0; 
}