#include "Graph.h"
#include "List.h"


namespace FT {

	class AdjacencyMatrix : public Graph
	{
	private:
		int** matrix;
		void init_matrix(int size);
		void make_empty_graph();
		void copy_matrix(const AdjacencyMatrix& other);

		void destroy();


	public:

		AdjacencyMatrix(int size = 0);
		AdjacencyMatrix(const AdjacencyMatrix& other);
		virtual ~AdjacencyMatrix();

		AdjacencyMatrix& operator=(const AdjacencyMatrix& other);


		static AdjacencyMatrix MakeEmptyGraph(int n);
		bool IsAdjacent(int u, int v) const override;



		void AddEdge(int u, int v, float weight) override;
		void RemoveEdge(int u, int v) override;
		void makeEmpty() override;

		void ReadGraph();

		//void PrintGraph() const;


	};
}
