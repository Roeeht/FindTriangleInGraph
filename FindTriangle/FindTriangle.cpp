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
		outputFile.close();
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
		outputFile.close();
			break;

	}
		
	case 3:	
	{
		// todo - alon yuster zwick
		AdjacencyList alonYusterAdjacenciesList(verticesNum);
		//AdjacencyMatrix alonYusterGraph(verticesNum);
		while (getline(infile, line))
		{
			istringstream iss(line);
			int u, v;
			if (!(iss >> u >> v)) { break; } // error
			//alonYusterGraph.AddEdge(u, v, 0);
			alonYusterAdjacenciesList.AddEdge(u, v, 0);
		}
		infile.close();
		ofstream outputFile;
		outputFile.open(args[2], ios::out);
		//calc m^1/2
		int mPoweredHalf = pow(alonYusterAdjacenciesList.get_EdgesNum(),0.5);
		//find low degree vertices
		//todo - implement getDegreesArr and mergeSort
		//loop over degrees
		int i;
		int highDegreesAmount=0;
		for (i = 1; i < alonYusterAdjacenciesList.get_length(); i++)
		{
			////if not bigger than mPoweredHalf - "lowDegree"
			if (alonYusterAdjacenciesList.getDegree(i) <= mPoweredHalf)
			{
				int* triangleVertices = alonYusterAdjacenciesList.getTriangle(outputFile, i);
				if (triangleVertices[0] != -1)
				{
					outputFile << triangleVertices[0] << "," << triangleVertices[1] <<
						"," << triangleVertices[2] << endl;
					outputFile.close();
					break;
				}
			}
			else
				highDegreesAmount++;
		}
		//else
			
		AdjacencyMatrix highDegreesMat(verticesNum);
		int j;
		for (i = 1; i < verticesNum; i++)
		{
			if (alonYusterAdjacenciesList.getDegree(i) > mPoweredHalf)
			{
				//loop over highDegree vertex edges and add only to highDegreeMat
				for (j = 1; j < alonYusterAdjacenciesList.getDegree(i); j++)
				{
					if (alonYusterAdjacenciesList.getDegree(j) > mPoweredHalf)
						highDegreesMat.AddEdge(i, j, 0);
				}
				
			}
		}
			//delete vertices from degree 0

			//check with algo 2 triangle in the new graph
		highDegreesMat.getTriangle(outputFile);

			
		//for (int k = 1; k < alonYusterAdjacenciesList.get_EdgesNum(); k++)
		//{
		//	if (alonYusterAdjacenciesList.getDegree(k) == 0)
		//		alonYusterAdjacenciesList.
		//}

		//	//and if it is, check if .... ???
		//for (int i = 0; i < alonYusterGraph.get_EdgesNum(); i++)
		//{
		//	for (int j = 0; j < alonYusterGraph.get_EdgesNum(); j++)
		//	{
		//		if (alonYusterGraph.getDegree(i) < mPoweredHalf)
		//		{
		//			if (alonYusterGraph.IsAdjacent(j, i))
		//				//print triangle
		//				break;
		//		}
		//	}
		//}
		//loop over route of 3 u->v->w when v is low degree, and check if there is w->u edge
		//find triangle of high degree only:
		//build new graph G' with the high degree vertices only and their edges.
		//use algo2 to find triangle.
		

		outputFile.close();
			infile.close();
		break;
	}
		
	case 4:	
	{ //todo run all algorithms and output them all
		//AdjacencyMatrix gm(verticesNum);
		//AdjacencyList gl(verticesNum);
		////todo - create alon yuster zwick
		////read edges
		//while (getline(infile, line))
		//{
		//	istringstream iss(line);
		//	int u, v;
		//	if (!(iss >> u >> v)) { break; } // error
		//	gm.AddEdge(u, v, 0);
		//	gl.AddEdge(u, v, 0);
		//	//todo - add alon yuster edge
		//}
		//float mPowHalf = pow(gm.get_EdgesNum(), 0.5);
		//	
		//infile.close();
		//break;
	}
	
	}

}

