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
#include <math.h> 
#include <string>
#include <sstream>

using namespace FT;
using namespace std;




int main(int argc, char** args)
{
	string FileName = args[1];
	string line;
	int algoNum;
	int verticesNum;
	int caseFourFlag = 0;
	fstream infile;
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
	verticesNum = stoi(line);
	if (verticesNum < 1) {
		cout << "invalid input";
		exit(1);
	}
	ofstream outputFile;
	outputFile.open(args[2], ios::out);
	switch (algoNum)
	{
	case 4:
		caseFourFlag = 1;
	case 1:
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
		gl_adjacencies.getTriangle(outputFile);
		if (!caseFourFlag)
		{
			outputFile.close();
			infile.close();
			break;
		}
	}

	case 2:
	{
		AdjacencyMatrix gm_adjacencies(verticesNum);
		if (caseFourFlag)
		{
			infile.clear();
			infile.seekg(0, ios::beg);
			getline(infile, line);
			getline(infile, line);

		}
		//read edges

		while (getline(infile, line))
		{
			istringstream iss(line);
			int u, v;
			if (!(iss >> u >> v)) { break; } // error
			gm_adjacencies.AddEdge(u, v, 0);

		}
		gm_adjacencies.getTriangle(outputFile);
		if (!caseFourFlag)
		{
			outputFile.close();
			infile.close();
			break;
		}
	}

	case 3:
	{
		int i;
		int j;
		int highDegreesAmount = 0;
		int* triangleVertices;
		double mPoweredHalf;
			
		if (caseFourFlag)
		{
			infile.clear();
			infile.seekg(0, ios::beg);
			getline(infile, line);
			getline(infile, line);

		}
			
		AdjacencyList alonYusterAdjacenciesList(verticesNum);
		//AdjacencyMatrix alonYusterGraph(verticesNum);
		while (getline(infile, line))
		{
			istringstream iss(line);
			int u, v;
			if (!(iss >> u >> v)) { break; } // error
			alonYusterAdjacenciesList.AddEdge(u, v, 0);
		}
		//calc m^1/2
		mPoweredHalf = sqrt(alonYusterAdjacenciesList.get_EdgesNum());
		//find low degree vertices
		//loop over degrees

		for (i = 1; i <= alonYusterAdjacenciesList.get_length(); i++)
		{
			//if not bigger than mPoweredHalf = "lowDegree"
			if (alonYusterAdjacenciesList.getDegree(i) <= mPoweredHalf)
			{
				triangleVertices = alonYusterAdjacenciesList.getTriangle(outputFile, i);

				if (triangleVertices[2] != -1)
				{
					return 0;
				}
			}
			else
				highDegreesAmount++;
		}

		//didn't find in lowDegrees vertices

		AdjacencyMatrix highDegreesMat(verticesNum);
		for (i = 1; i <= verticesNum; i++)
		{
			if (alonYusterAdjacenciesList.getDegree(i) > mPoweredHalf)
			{
				//loop over highDegree vertex edges and add only to highDegreeMat
				for (j = 1; j <= verticesNum; j++)
				{
					int jDeg = alonYusterAdjacenciesList.getDegree(j);
					if (jDeg > mPoweredHalf && i != j)
						highDegreesMat.AddEdge(i, j, 0);
				}

			}
		}
		//check with algo 2 triangle in the new graph
		highDegreesMat.getTriangle(outputFile);


			outputFile.close();
			infile.close();
			break;
		}

	}
}

