//summary:
//

//gets: 
//		
//		
//		

//returns: 

#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"

#include <string>
#include <sstream>

using namespace FT;
using namespace std;




int main(int argc, char** args)
{
	ifstream infile(args[1]);
	string line;
	//read chosen algorithm number
	getline(infile, line);
	int algoNum = stoi(line);
	if (algoNum < 1 || algoNum > 4) {
		cout << "invalid input";
		exit(1);
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
	case 1: {
		AdjacencyList gl_adjacencies = AdjacencyList(verticesNum);
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
		
	case 2: { //todo - fix getTriangle
		AdjacencyMatrix gm_adjacencies = AdjacencyMatrix(verticesNum);
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
		
	case 3:	{
		// todo - alon yuster zwick
		infile.close();
		break;
	}
		
	case 4:	{
		AdjacencyMatrix gm = AdjacencyMatrix(verticesNum);
		AdjacencyList gl = AdjacencyList(verticesNum);
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
		infile.close();
		break;
	}

	}

}

