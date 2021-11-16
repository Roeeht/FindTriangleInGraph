#include "AdjacencyMatrix.h"
#include <fstream>
using namespace std;

namespace FT
{

	void AdjacencyMatrix::init_matrix(int size)
	{
		_length = size;

		//already built in exception if new fails so no need to try
		matrix = new int* [size + 1];

		for (int i = 0; i < size + 1; i++)
			matrix[i] = new int[size + 1];
	}

	void AdjacencyMatrix::make_empty_graph() {
		for (int i = 0; i <= _length; i++)
		{
			for (int j = 0; j <= _length; j++)
			{
				this->matrix[i][j] = 0;
			}
		}
	}

	void AdjacencyMatrix::copy_matrix(const AdjacencyMatrix& other)
	{
		for (int i = 0; i <= _length; i++)
			for (int j = 0; j <= _length; j++)
				matrix[i][j] = other.matrix[i][j];
	}

	void AdjacencyMatrix::destroy()
	{
		if (matrix != nullptr)
		{
			for (int i = 0; i <= _length; i++)
				delete[] matrix[i];
			delete[] matrix;
		}
		delete[] degrees;
		matrix = nullptr;
		_length = 0;
	}

	AdjacencyMatrix::AdjacencyMatrix(AdjacencyList& source)
	{
		int len = source.get_length();
		AdjacencyMatrix res(len);
		for (int i = 1; i <= len; i++)
		{
			for (auto j = source.get_adjacent_by_ref(i).begin(); j != source.get_adjacent_by_ref(i).end(); ++j)
			{
				matrix[i][j->get_first()] = 1;
			}
		}
	}


	AdjacencyMatrix::AdjacencyMatrix(int size) : Graph(size), matrix(nullptr)
	{
		if (size > 0)
		{
			init_matrix(size);
			make_empty_graph();
		}
	}

	AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& other)
	{
		copy_matrix(other);

	}


	AdjacencyMatrix::~AdjacencyMatrix()
	{
		destroy();
	}

	AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& other)
	{
		if (this != &other)
		{
			destroy();

			init_matrix(other._length);

			copy_matrix(other);
		}

		return *this;
	}


	AdjacencyMatrix AdjacencyMatrix::MakeEmptyGraph(int n)
	{
		return AdjacencyMatrix(n);
	}

	bool AdjacencyMatrix::IsAdjacent(int u, int v) const
	{
		bool found = false;
		if (!check_bounds(u) || !check_bounds(v))
			throw std::logic_error("out of bounds - MatrixGraph");
		else
			return matrix[u][v] != 0;

	}


	void AdjacencyMatrix::AddEdge(int u, int v, float weight)
	{
		if (!check_bounds(u) || !check_bounds(v))
			throw std::logic_error("out of bounds - MatrixGraph");

		matrix[u][v] = 1;
		degrees[u]++;
		_edgesNum++;
	}

	void AdjacencyMatrix::RemoveEdge(int u, int v)
	{
		if (!check_bounds(u) || !check_bounds(v))
			throw std::logic_error("out of bounds - MatrixGraph");
		else
			matrix[u][v] = 0;
	}

	void AdjacencyMatrix::makeEmpty()
	{
		for (int i = 0; i <= _length; i++)
			for (int j = 0; j <= _length; j++)
				matrix[i][j] = 0;
	}


	void AdjacencyMatrix::ReadGraph()
	{
		int v, u;
		int weight = 0;
		while (!cin.eof())
		{
			cin >> u;
			if (check_bounds(u))
			{
				cin >> v;
				if (check_bounds(v))
					this->AddEdge(u, v, weight);
				else
				{
					cout << "invalid input";
					exit(1);
				}
			}
			else
			{
				cout << "invalid input";
				exit(1);
			}
		}
	}

	//void PrintGraph() const;

	int** mulMat(int** mat1, int** mat2, int size1, int size2) {
		int** rslt = new int* [size1];
		for (int i = 0; i < size1 + 1; i++)
			rslt[i] = new int[size2 + 1];

		for (int i = 0; i < size1; i++)
		{
			for (int j = 0; j < size2; j++)
			{
				rslt[i][j] = 0;

				for (int k = 0; k < size2; k++)
				{
					rslt[i][j] += mat1[i][k] * mat2[k][j];
				}

			}
		}
		return rslt;

	}

	void AdjacencyMatrix::getTriangle(ofstream& outputFile) //using multiply matrices algo
	{
		AdjacencyList thisInList(this->get_length());
		//todo - create multiply matrixes func
		int** PoweredTwo = mulMat(matrix, matrix, this->get_length(), this->get_length());
		int** PoweredThree = mulMat(matrix, PoweredTwo, this->get_length(), this->get_length());
		for (int i = 0; i < this->get_length(); i++)
		{
			if (PoweredThree[i][i] > 0) //true if found a triangle
			{
				for (int j = 0; j < this->get_length(); j++)
				{
					if (PoweredTwo[i][j] > 0)
					{
						for (int k = 0; k < this->get_length(); k++)
						{
							if (PoweredTwo[j][k] > 0 && matrix[i][k] > 0)
							{
								outputFile << i << "," << j << "," << k << endl;
								outputFile.close();
								return;
							}
						}

					}
				}

			}
		}
		cout << "NO";
	}
	//for (int i = 0; i < this->get_length(); i++)
	//{
	//	for (int j = 0; j < this->get_length(); j++)
	//	{
	//		if (PoweredTwo[i][j] > 0 && matrix[i][j] > 0) //true if found a triangle
	//		{
	//			for (int k = 0; k < this->get_length(); k++) //find the third edge in the triangle
	//			{
	//				if (thisInList.IsAdjacent(i,k) && thisInList.IsAdjacent(k, j))
	//				{
	//					outputFile << i << "," << j << "," << k << endl;
	//					outputFile.close();
	//					return;
	//				}
	//			}
	//		
	//		}

	//	}

	//}


	//		 check after func if [i,j] [j,k] [k,i] are 1
	/*for (int i = 0; i <= _length; i++)
	{
		for (int j = 0; j <= _length; j++)
		{
			if (matrix[i][j] == 1)
			{
				for (int k = 0; k <= _length; k++)
				{
					if (matrix[j][k] == 1)
					{
						if (matrix[k][i] == 1 && k!= i)
						{
							outputFile << i << "," << j << "," << k << endl;
							outputFile.close();
							return;
						}

					}
				}
			}
		}
	}
	cout << "NO";*/

}