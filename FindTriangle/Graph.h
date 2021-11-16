//graph class
#pragma once
#include "List.h"
#include "Pair.h"

namespace FT {


	class Graph {
	protected:

		int _length; //=V amount
		int _edgesNum; //=E amount
		int* degrees;

		/// <summary>
		/// check if num is in bounds of vertices
		/// and return result as bool
		/// </summary>
		/// <param name="num">name of vertex</param>
		/// <returns>true for inbound, flase for out of bounds</returns>
		bool check_bounds(int num) const;

	public:

		Graph(int size = 0);
		Graph(const Graph& other) = default;
		virtual ~Graph() {  }

		Graph& operator=(const Graph& other) = default;
		/// <summary>
		/// returns graph amount of vertices 
		/// </summary>
		/// <returns> aomunt </returns>
		int get_length() const { return _length; }
		int get_EdgesNum() const { return _edgesNum; }

		virtual bool IsAdjacent(int u, int v) const = 0;

		List<Pair<int, float>> GetAdjList(int u);

		const List<Pair<int, float>> GetAdjList(int u) const;
		virtual void AddEdge(int u, int v, float c) = 0;
		virtual void RemoveEdge(int u, int v) = 0;
		virtual void makeEmpty() = 0;
	};
}