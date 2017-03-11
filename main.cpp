#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX 11

void writeMatrix(int[MAX][MAX],int,int);

struct matrix
{
	int num1;
	int num2;
};

int main()
{
	//Declaring Variables
	ifstream myFile;
	int number;
	int DiagonalTable[MAX][MAX];
	int DiagonalTable2[MAX][MAX];
	matrix matrices[MAX];
	int m[MAX];
	int increment = 0;
	bool nextmatrix = false;
	int cur_size = 0;
	bool first = true;
	string expr;


	//Open the file
	myFile.open("matrices.txt");

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			DiagonalTable[i][j] = -1;

		}

	}

	//Go through the file until it is empty to get information
	while (myFile >> number)
	{
		if (nextmatrix)
		{
			matrices[increment].num2 = number;
			increment++;
			nextmatrix = false;
		}
		else
		{
			matrices[increment].num1 = number;
			nextmatrix = true;
		}


	}

	cur_size = increment;

	//collect value's to use for calculation
	for (int n = 0; n < cur_size; n++)
	{
		m[n] = matrices[n].num1;

		if (n == cur_size - 1)
		{
			m[n + 1] = matrices[n].num2;
		}


	}

	cur_size += 1;

	//set the diagonal to zero to start the algorithm
	for (int m = 1; m < cur_size; m++)
	{
		DiagonalTable[m][m] = 0;
	}

	int j;

    //calculate values for the diagonal table
	for (int d = 1; d < cur_size-1; d++)
	{
		for (int i = 1; i < cur_size-d;i++)
		{
			j = i + d;

			number = 0;
			first = true;

			for (int k = i; k < j; k++)
			{

				number = DiagonalTable[i][k] + DiagonalTable[k + 1][j] + (m[i-1] * m[k] * m[j]);

				if (first)
				{
					DiagonalTable[i][j] = number;
					DiagonalTable2[i][j] = k;
					first = false;
				}
				else
				{
					if (DiagonalTable[i][j] > number)
					{
						DiagonalTable[i][j] = number;
						DiagonalTable2[i][j] = k;
					}

				}
			}

		}

	}

    //the minimize value is always the top right value in the table
	cout << "Minimized Work: " << DiagonalTable[1][cur_size-1] << "\n\n";

	//write the order of the matrices
	writeMatrix(DiagonalTable2,1,cur_size-1);

	cout << endl;


	cout << "\nDiagonal Table" << endl;

	//print the table
	for (int i = 1; i < cur_size; i++)
	{
		for (int j = 1; j < cur_size; j++)
		{
			if (DiagonalTable[i][j] == -1)
			{
				cout << "X      ";
			}
			else
			{
				cout << DiagonalTable[i][j] << "    ";
			}

		}
		cout << endl;
	}

	myFile.close();

	return 0;

}

void writeMatrix(int Table[MAX][MAX],int i,int j)
{

	if (i == j)
	{
		cout << "A";
		cout << i;
	}
	else
	{
		cout << "(";
		int k = Table[i][j];
		writeMatrix(Table, i, k);
		writeMatrix(Table,k+1,j);
		cout << ")";
	}



}

