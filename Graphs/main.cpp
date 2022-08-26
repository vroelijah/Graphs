#include <iostream>
using namespace std;
#include <cstdlib> // for rand(), srand()
#include <ctime> // for time()
#include <assert.h>
#include <math.h> // for sqrt()
#include "List.h"
#include "Edge.h"
#include <fstream>
int vec;

void traverse(int v, vector<bool>& vis, const vector<List<Edge>>& g) {
	vis[v] = true;
	//cout << "Visited vertex : " << v << endl;
	cout << " " << v;
	for (auto& w : g[v]) {
		if (!vis[w.tv])
			traverse(w.tv, vis, g);
	}
}

int set_distancesopt(int source, vector<bool>& vis, vector<List<Edge>>& g) {
	cout << " this is the opt code " << endl;
	int* parent = new int[vec];
	double* distance = new double[vec];
	vector<bool> visite(vec, false);
	vis = visite;
	int* A = new int[vec];
	int h;
	for (int i = 0; i < vec; i++)
	{
		A[i] = i;
	}
	int start = 0;

	int w, v = source;
	for (int i = 0; i < vec; i++)
	{
		parent[i] = source;
	}

	double min = 999;

	if (g[source].empty())
	{
		cout << "for vertex " << source << " there is no edge leading to other vertices" << endl << endl;
		return 1;
	}

	//cout << "d: ";
	for (v = 0; v < vec; v++)
	{
		distance[v] = g[source].adjacency2(v);
		//	cout << distance[v] << " ";
	}
	//cout << endl;


	visite[source] = true;
	A[start] = source;
	A[source] = start;
	start++;

	distance[source] = 0;
	for (int j = 0; j < 10; j++)
	{
		min = 999;
		for (int m = start; m < vec; m++)
		{
			w = A[m];
			if (distance[w] < min)
			{
				v = w;
				min = distance[w];

			}
		}
		if (visite[v] != true)
		{
			visite[v] = true;
			A[start] = v;
			A[v] = start;
			start++;
		}
		for (int m = start; m < vec; m++)
		{
			w = A[m];
			if (min + g[v].adjacency2(w) < distance[w])
			{
				distance[w] = min + g[v].adjacency2(w);
				parent[w] = v;
			}
		}
	}

	//cout << "parent: ";
	//for (int i = 0; i < vec; i++)
	//{
	//	cout << parent[i] << " ";
	//}
	//cout << endl;
	for (int i = 0; i < vec; i++)
	{
		cout << "vertex " << source << " to vertex " << i << ":" << endl;
		cout << "distance v is: ";
		cout << distance[i] << endl;
		cout << i << " ";
		v = i;
		while (v != source)
		{
			if (distance[i] == 999)
			{
				cout << "there is no path that leads to this vertices";
				break;
			}
			else
			{
				cout << parent[v] << " ";
			}
			v = parent[v];
		}
		cout << endl;
		cout << endl;
	}
	return 1;
}


int set_distances(int source, vector<bool>& vis, vector<List<Edge>>& g) {
	int* parent = new int[vec];
	double* distance = new double[vec];
	vector<bool> visited(vec, false);
	vis = visited;
	int w, v = source;;
	for (int i = 0; i < vec; i++)
	{
		parent[i] = source;
	}

	double min = 999;

	if (g[source].empty())
	{
		cout << "for vertex " << source << " there is no edge leading to other vertices" << endl << endl;
		return 1;
	}

	//cout << "d: ";
	for (v = 0; v < vec; v++)
	{
		distance[v] = g[source].adjacency2(v);
		//	cout << distance[v] << " ";
	}
	//cout << endl;

	vis[source] = true;
	distance[source] = 0;
	for (int j = 0; j < 10; j++)
	{
		min = 999;
		for (w = 0; w < vec; w++)if (!vis[w])
			if (distance[w] < min)
			{
				v = w;
				min = distance[w];

			}
		vis[v] = true;
		for (w = 0; w < vec; w++)
		{
			if (!vis[w])
			{
				if (min + g[v].adjacency2(w) < distance[w])
				{
					distance[w] = min + g[v].adjacency2(w);
					parent[w] = v;
				}
			}
		}
	}

	//cout << "parent: ";
	//for (int i = 0; i < vec; i++)
	//{
	//	cout << parent[i] << " ";
	//}
	//cout << endl;

	for (int i = 0; i < vec; i++)
	{
		cout << "vertex " << source << " to vertex " << i << ":" << endl;
		cout << "distance v is: ";
		cout << distance[i] << endl;
		cout << i << " ";
		v = i;
		while (v != source)
		{
			if (distance[i] == 999)
			{
				cout << "there is no path that leads to this vertices";
				break;
			}
			else
			{
				cout << parent[v] << " ";
			}
			v = parent[v];
		}
		cout << endl;
		cout << endl;
	}
	return 1;
}
int main() {

	int nv = 0; // number of vertices
	int ne = 0; // number of edges
	ifstream fin("input1.txt");


	if (fin.fail())
	{
		cerr << "Error opening input file!" << endl;
		exit(1);
	}
	fin >> nv >> ne;
	cout << "number of verticies: " << nv << " number of edges: " << ne << endl;
	vec = nv;
	if ((nv < 0) || (nv > 10000) || (ne < 0) || (ne > 10000)) {
		cerr << "Input values out of range." << endl;
		exit(1);
	}

	vector<List<Edge>> g2(nv); //graph
	int cv1 = 0, cv2 = 0; // Edge from current vertex cv1 to cv2
	double wt = 0.0; // weight

	for (int ne1 = 0; ne1 < ne; ne1++)
	{
		fin >> cv1 >> cv2 >> wt; // input; assume no error in input.
		if ((cv1 < 0) || (cv1 > nv) || (cv2 < 0) || (cv2 > nv) || (wt < 0) || (wt > 10000.0)) {
			cerr << "Input values out of range." << endl;
			exit(1);
		}
		Edge nsq(cv1, cv2, wt);
		g2[cv1].push_back(nsq);
	}
	cout << endl << " Graph " << endl;
	for (int i = 0; i < nv; i++) {
		cout << i << " : ";
		g2[i].printList();
		cout << endl;
	}
	vector<bool> visited(nv, false);
	//cout << "Depth First traversal " << endl << "Visited vertex : ";
	/*for (int v = 0; v < nv; v++) {
		if (!visited[v])
			traverse(v, visited, g2);
	}*/
	cout << endl;
	//for (int v = 0; v < nv; v++)
	//{
	//	if (!visited[v])
	//	{
	//set_distances(0, visited, g2);
	for (int i = 0; i < nv; i++) {
		set_distances(i, visited, g2);
	}

	//	}
	//}


	for (int i = 0; i < nv; i++) {
		// cout << i << " : Cleared ";
		g2[i].clear();
		cout << endl;
	}
	return 0;
}