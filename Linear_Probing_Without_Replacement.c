#include <stdio.h>

int tableSize = 10;
int collisions = 0;

void hashingWithoutReplacement(int arr[], int table[][2])
{
	for (int i = 0; i < 8; i++)
	{
		int index = arr[i] % tableSize;
		if (table[index][0] == -1)
		{
			table[index][0] = arr[i];
		}
		else
		{
			collisions++;
			int pos = index;
			int chain = -1;
			while (table[pos][0] != -1)
			{
				if (table[pos][0] % tableSize == index)
				{
					chain = pos;
				}
				pos = (pos + 1) % tableSize;
			}
			table[pos][0] = arr[i];
			if (chain != -1)
			{
				table[chain][1] = pos;
			}
		}
	}
}

void display(int table[][2])
{
	printf("Index\tValue\tChain\n");
	for (int i = 0; i < tableSize; i++)
	{
		printf("%d\t%d\t%d\n", i, table[i][0], table[i][1]);
	}
	printf("Number of collisions = %d\n", collisions);
}

int main()
{
	int arr[8] = {11, 101, 88, 18, 48, 3, 70, 19};	
	int table[tableSize][2];

	for (int i = 0; i < tableSize; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			table[i][j] = -1;
		}
	}

	hashingWithoutReplacement(arr, table);
	display(table);

	return 0;
}