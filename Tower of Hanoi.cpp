#include <iostream>
#include <vector>
using namespace std;

#define Columns 3

/*
 Tower of Hanoi using 2d arrays

 1. Create a 2d array of size x size
 2. Fill the first row with the numbers 1 to size
 3. Fill the rest of the array with 0's

*/

/*
In theory the arrays if the given size id 3 should look like this

1 0 0
2 0 0
3 0 0


now we need to move the disks from the first tower to the last tower

1. Move the top disk from the first tower to the second tower
	and it will look like this

	0 0 0
	2 0 0
	3 0 1

2. Move the top disk from the first tower to the last tower
	and it will look like this

	0 0 0
	0 0 0
	3 2 1

3. Now we want to move the bottom disk to the last tower but we can't
	because the top disk is smaller than the bottom disk so we need to move
	the top disk to the middle tower
	and it will look like this

	0 0 0
	0 1 0
	3 2 0

4. Now we can move the bottom disk to the last tower
	and it will look like this

	0 0 0
	0 1 0
	0 2 3

5. Now we can move the top disk from the middle tower to the last tower
	and it will look like this

	0 0 0
	0 0 0
	1 2 3

6. Now we move the second disk to the last tower
	and it will look like this

	0 0 0
	0 0 2
	1 0 3

7. Now we move the top disk from the first tower to the last tower
	and it will look like this

	0 0 1
	0 0 2
	0 0 3
*/

void display(vector<vector<int>> arr, int size) // Displays the 2d array
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

bool checkIfSolved(vector<vector<int>> arr, int size) // Checks if the puzzle is solved
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i][2] != i + 1) // If the last tower is not in order then the puzzle is not solved
		{
			return false;
		}
	}
	return true;
}

// check if the selected disk has another disk ontop of it
bool CheckDisk(vector<vector<int>> arr, int size, int tomove)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			if (arr[i][j] == tomove) // if the selected disk is found in the array
			{
				if (arr[i - 1][j] != 0) // if there is a disk ontop of the selected disk
				{
					return false;
				}
			}
		}
	}

	return true;
}

int findrow(vector<vector<int>> arr, int length, int tomove) // finds the row of the selected disk in the array
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			if (arr[i][j] == tomove) // if the selected disk is found in the array
			{
				return i;
			}
		}
	}
}

int findcol(vector<vector<int>> arr, int length, int tomove) // finds the column of the selected disk in the array
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			if (arr[i][j] == tomove) // if the selected disk is found in the array
			{
				return j;
			}
		}
	}
}

bool MovedToValidTower(vector<vector<int>> arr, int size, int tomove, int to)
{
	// 'to' is the colum number and the 'tomove' is the disk number to be moved
	// to the bottom of that colum if there is no disk already there if there is just place it on top of that disk

	int row = findrow(arr, size, tomove); // finds the row of the selected disk in the array
	int col = findcol(arr, size, tomove); // finds the column of the selected disk in the array

	for (int i = size - 1; i >= 0; i--)
	{
		if (arr[i][to] != 0)
		{
			if (arr[i][to] < tomove) // checking if the disk in the tower is smaller than the disk to be moved
			{
				return false;
			}
		}
		if (arr[i][to] == 0) // if the tower is empty then the disk can be moved there
		{
			return true;
		}
	}

	return false;
}

void MoveToBottom(vector<vector<int>> &arr, int size, int tomove, int to)
{
	// to is the colum number and the tomove is the disk number to be moved to the bottom of that colum if there is no disk already there if there is just place it on top of that disk
	int row = findrow(arr, size, tomove);
	int col = findcol(arr, size, tomove);

	arr[row][col] = 0;

	for (int i = size - 1; i >= 0; i--)
	{
		if (arr[i][to] == 0)
		{
			arr[i][to] = tomove;
			break;
		}
	}
}

int main()
{

	srand(time(NULL));

	int size;
	cout << "Enter the Number of Disks: ";
	cin >> size;

	vector<vector<int>> arr(size);

	for (int i = 0; i < size; i++)
	{
		arr[i].resize(Columns);
		for (int j = 0; j < Columns; j++)
		{
			arr[i][j] = 0;
		}
	}

	for (int i = 0; i < size; i++)
	{
		arr[i][0] = i + 1;
	}

	int moves = 0; // Counts the number of moves it takes to solve the puzzle

	int to; // The tower to move from and the tower to move to

	int indexToMove = 0; // The index of the disk to move

	bool moveMakde = false;

	while (checkIfSolved(arr, size) == 0)
	{
		/*system("cls");
		cout << "Before: " << endl;
		display(arr, size);*/

		to = (rand() % 3);

		indexToMove = (rand() % size) + 1;

		if ((CheckDisk(arr, size, indexToMove) == true) && (MovedToValidTower(arr, size, indexToMove, to)))
		{

			MoveToBottom(arr, size, indexToMove, to);
			moves++;
			moveMakde = true;
		}

		/*cout << endl << "After: " << endl;
		display(arr, size);

		if (moveMakde == true)
		{
			cout << "Moves: " << moves << endl;
			cout << "Moved Disk: " << indexToMove << endl;
			cout << "Moved To Column: " << to << endl;
		}

		moveMakde = false;
		system("pause");*/
	}
	cout << "Moves: " << moves << endl;
	display(arr, size);
}