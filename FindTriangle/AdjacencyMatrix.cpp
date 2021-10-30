#include "AdjacencyMatrix.h"
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
				matrix[i][j] = 0;
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
		matrix = nullptr;
		_length = 0;
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
		else
			matrix[u][v] = 1;
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



}