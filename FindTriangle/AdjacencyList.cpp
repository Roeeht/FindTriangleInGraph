#include <fstream>
#include "AdjacencyMatrix.h"

using namespace std;
namespace FT {


	void AdjacencyList::destroy()
	{
		delete[] _vertices;
		delete[] degrees;

		_vertices = nullptr;
		_length = 0;
	}


	AdjacencyList::AdjacencyList(int size) : Graph(size), _vertices(nullptr)
	{
		if (size > 0)
		{
			_vertices = new Pair<int, List<Pair<int, float>>>[size+1];

			for (int i = 0; i < size+1; i++)
			{
				_vertices[i].get_first() = i + 1;
			}
		}
	}

	AdjacencyList::AdjacencyList(const AdjacencyList& other) : AdjacencyList(0)
	{
		*this = other;
	}

	AdjacencyList& AdjacencyList::operator=(const AdjacencyList& other)
	{
		if (this != &other)
		{
			destroy();

			if (other._length > 0)
			{
				_length = other._length;

				//already built in exception if new fails so no need to try
				_vertices = new Pair<int, List<Pair<int, float>>>[other._length];

				for (int i = 0; i < other._length; i++)
				{
					_vertices[i] = other._vertices[i];
				}
			}
		}

		return *this;
	}

	AdjacencyList AdjacencyList::MakeEmptyGraph(int n)
	{
		return AdjacencyList(n);
	}


	bool AdjacencyList::IsAdjacent(int u, int v) const
	{
		bool found = false;
		auto& adjacents = GetAdjList(u);

		for (auto itr = adjacents.begin(); itr != adjacents.end() && !found; ++itr)
			if (itr->get_first() == v)
				found = true;

		return found;
	}


	List<Pair<int, float>> AdjacencyList::GetAdjList(int u)
	{
		return get_adjacent_by_ref(u);
	}


	const List<Pair<int, float>> AdjacencyList::GetAdjList(int u) const
	{
		if (!check_bounds(u))
			throw std::logic_error("out of bounds - ListGraph");
		else
			return _vertices[u - 1].get_second();
	}


	List<Pair<int, float>>& AdjacencyList::get_adjacent_by_ref(int u)
	{
		if (!check_bounds(u))
			throw std::logic_error("out of bounds - ListGraph");
		else
			return _vertices[u - 1].get_second();
	}


	void AdjacencyList::AddEdge(int u, int v, float weight)
	{
		if (!IsAdjacent(u, v)) 
		{
			get_adjacent_by_ref(u).insert_to_tail(Pair<int, float>(v, weight));
			_edgesNum++;
			degrees[u]++;
			degrees[v]++;
		}
	}


	void AdjacencyList::RemoveEdge(int u, int v)
	{
		auto& adjacents = get_adjacent_by_ref(u);

		for (auto itr = adjacents.begin(); itr != adjacents.end(); ++itr)
		{
			if (itr->get_first() == v)
			{
				itr.itr_delete();
				break;
			}
		}
	}


	void AdjacencyList::makeEmpty()
	{
		for (int i = 0; i < _length; i++)
			_vertices[i].get_second().make_empty();
	}


	void AdjacencyList::PrintGraph() const
	{
		for (int i = 0; i < _length; ++i)
			if (!_vertices[i].get_second().is_empty())
			{
				std::cout << _vertices[i].get_first() << ": " << _vertices[i].get_second() << std::endl;
			}
	}


	void AdjacencyList::transpose(AdjacencyList* transposedGraph)
	{
		for (int i = 1; i <= this->get_length(); i++)
			for (auto j = this->get_adjacent_by_ref(i).begin(); j != this->get_adjacent_by_ref(i).end(); ++j)
			{
				transposedGraph->AddEdge(j->get_first(), i, 0);
			}
	}



	int* AdjacencyList::BFS(int s)
	{
		int V = this->get_length();
		int* p = new int[V];
		int* d = new int[V]; //distances arr

		// Mark all the vertices as not visited
		for (int i = 0; i < V; i++)
		{
			d[i] = -1; //-1 used to initiate
			p[i] = -1;
		}
		// Create a queue for BFS
		List<int> queue;
		int j = 0; //distance from s

		// Mark the current node as visited and enqueue it
		d[s - 1] = j;
		queue.insert_to_tail(s);

		// 'i' will be used to get all adjacent
		// vertices of a vertex
		List<int>::iterator i();

		while (!queue.is_empty())
		{
			// Dequeue a vertex from queue 
			int u = queue.get_head()->_item;

			queue.delete_head();
			auto adjacents = this->GetAdjList(u);
			// Get all adjacent vertices of the dequeued
			// vertex s. If a adjacent has not been visited,
			// then mark it visited and enqueue it
			for (auto v = adjacents.begin(); v != adjacents.end(); ++v)
			{
				if (d[v->get_first() - 1] == -1)
				{
					d[v->get_first() - 1] = d[u - 1] + 1;
					p[v->get_first() - 1] = u;
					queue.insert_to_tail(v->get_first());
				}
			}
			j++;
		}
		return d;
	}

	void AdjacencyList::ReadGraph()
	{
		int v, u;
		int weight = 0;

		while (!cin.eof())
		{
			cin >> v;
			if (check_bounds(v))
			{
				cin >> u;
				if (check_bounds(u))
					this->AddEdge(v, u, weight);
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

	int* AdjacencyList::getTriangle(ofstream& outputFile, int algo3HighDegVertex)
	{
		int triangleVertices[3];
		AdjacencyMatrix AdjacencyListInMat(*this);
		if (algo3HighDegVertex != 0)
		{
			int i = algo3HighDegVertex;
			for (auto j = this->get_adjacent_by_ref(i).begin();
				j != this->get_adjacent_by_ref(i).end(); ++j)
			{
				for (auto k = this->get_adjacent_by_ref(j->get_first()).begin();
					k != this->get_adjacent_by_ref(j->get_first()).end(); ++k)
				{
					if (AdjacencyListInMat.IsAdjacent(k->get_first(), i))
					{

						outputFile << i << "," << j->get_first() << "," << k->get_first() << endl;
						triangleVertices[0] = i;
						triangleVertices[1] = j->get_first();
						triangleVertices[2] = k->get_first();

						return triangleVertices;


					}
				}
			}
		}
		else 
		{
			for (int i = 1; i <= this->get_length(); i++)
			{
				for (auto j = this->get_adjacent_by_ref(i).begin();
					j != this->get_adjacent_by_ref(i).end(); ++j)
				{
					for (auto k = this->get_adjacent_by_ref(j->get_first()).begin();
						k != this->get_adjacent_by_ref(j->get_first()).end(); ++k)
					{
						if (AdjacencyListInMat.IsAdjacent(k->get_first(), i))
						{

							outputFile << i << "," << j->get_first() << "," << k->get_first() << endl;
							triangleVertices[0] = i;
							triangleVertices[1] = j->get_first();
							triangleVertices[2] = k->get_first();

							return triangleVertices;


						}
					}
				}
			}
		}
		triangleVertices[2] = -1; //flag for triangle wasn't found
		if (algo3HighDegVertex == 0)
			cout << "NO";
		return triangleVertices;

	}

	
}