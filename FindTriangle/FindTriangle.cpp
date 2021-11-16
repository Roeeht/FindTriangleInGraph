//summary: todo
//

//gets: todo
//		
//		
//		

//returns: todo
#include <iomanip>
#include <iostream>
#include <fstream>
#include "AdjacencyMatrix.h"
#include <cmath> 
#include <string>
#include <sstream>

using namespace FT;
using namespace std;




int main(int argc, char** args)
{
	fstream infile;
	string FileName = args[1];
	string line;
	int algoNum;
	infile.open(args[1], ios::in);
	if (infile.good()) {
		//read chosen algorithm number
		getline(infile, line);
		algoNum = stoi(line);
		if (algoNum < 1 || algoNum > 4) {
			cout << "invalid input";
			exit(1);
		}
	}
	//read vertices amount
	getline(infile, line);
	int verticesNum = stoi(line);
	if (verticesNum < 1) {
		cout << "invalid input";
		exit(1);
	}

	switch (algoNum)
	{
	case 1: //todo - check
	{
		AdjacencyList gl_adjacencies(verticesNum);
		//read edges
		while (getline(infile, line))
		{
			istringstream iss(line);
			int u, v;
			if (!(iss >> u >> v)) { break; } // error
			gl_adjacencies.AddEdge(u, v, 0);

		}
		infile.close();
		ofstream outputFile;
		outputFile.open(args[2], ios::out);
		gl_adjacencies.getTriangle(outputFile);

		break;


	}
		
	case 2: { //todo - check
		AdjacencyMatrix gm_adjacencies(verticesNum);
		//read edges
		while (getline(infile, line))
		{
			istringstream iss(line);
			int u, v;
			if (!(iss >> u >> v)) { break; } // error
			gm_adjacencies.AddEdge(u, v, 0);

		}
		infile.close();
		ofstream outputFile;
		outputFile.open(args[2], ios::out);
		gm_adjacencies.getTriangle(outputFile);
		break;

	}
		
	case 3:	
	{
		// todo - alon yuster zwick

		AdjacencyMatrix alonYusterGraph(verticesNum);
		while (getline(infile, line))
		{
			istringstream iss(line);
			int u, v;
			if (!(iss >> u >> v)) { break; } // error
			alonYusterGraph.AddEdge(u, v, 0);

		}
		infile.close();
		ofstream outputFile;
		outputFile.open(args[2], ios::out);
		//calc m^1/2
		int mPoweredHalf = pow(alonYusterGraph.get_EdgesNum(),0.5);
		//find low degree vertices
		for (int i = 0; i < alonYusterGraph.get_EdgesNum(); i++)
		{
			for (int j = 0; j < alonYusterGraph.get_EdgesNum(); j++)
			{
				if (alonYusterGraph.getDegree(i) < mPoweredHalf)
				{
					if (alonYusterGraph.IsAdjacent(j, i))
						//print triangle
						break;
				}
			}
		}
		//loop over route of 3 u->v->w when v is low degree, and check if there is w->u edge
		//find triangle of high degree only:
		//build new graph G' with the high degree vertices only and their edges.
		//use algo2 to find triangle.
		


			infile.close();
		break;
	}
		
	case 4:	{
		AdjacencyMatrix gm(verticesNum);
		AdjacencyList gl(verticesNum);
		//todo - create alon yuster zwick
		//read edges
		while (getline(infile, line))
		{
			istringstream iss(line);
			int u, v;
			if (!(iss >> u >> v)) { break; } // error
			gm.AddEdge(u, v, 0);
			gl.AddEdge(u, v, 0);
			//todo - add alon yuster edge
		}
		float mPowHalf = pow(gm.get_EdgesNum(), 0.5);
			
		infile.close();
		break;
	}

	}

}

