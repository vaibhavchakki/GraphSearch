#include <iostream>
#include <queue>
#include <list>
#include <assert.h>

using namespace std;

class Graph {
public:

	Graph(int N) {
		N_ = N;
		adj_ = new list<int>[N];
	}

	void addNode(int s, int d) {
		assert((s < N_) && (d < N_));

		adj_[s].push_back(d);
		adj_[d].push_back(s);
	}

	void BFS(int start, int* distance);
	void DFS_(int s, bool* visited)
	{
		if (!visited[s]) {
			for (auto it = adj_[s].begin(); it != adj_[s].end(); it++) {
				if (!visited[*it]) {
					visited[*it] = true;
					DFS_(*it, visited);
				}
			}
		}
	}

	void DFS(int start) {

		assert(start < N_);

		bool *visited = new bool[N_];
		for (int i = 0; i < N_; i++) {
			visited[i] = false;
		}

		visited[start] = true;
		DFS_(start, visited);

		delete[] visited;
	}


private:
	int N_;
	list<int> *adj_;
};

void Graph::BFS(int start, int* distance) {
	assert(start < N_);
	assert(distance);

	queue<int> Q;

	bool *visited = new bool[N_];

	for (int i = 0; i < N_; i++) {
		visited[i] = false;
		distance[i] = -1;
	}

	visited[start] = true;
	Q.push(start);
	distance[start] = 0;

	while (!Q.empty()) {
		int el = Q.front();
		Q.pop();

		for (auto it = adj_[el].begin(); it != adj_[el].end(); it++) {
			if (!visited[*it]) {
				distance[*it] = distance[el] + 1;
				Q.push(*it);
				visited[*it] = true;
			}
		}
	}

	delete[] visited;
}


// main function

int main(int argc, char** argv) {

	Graph* g = new Graph(6);
	g->addNode(0, 1); g->addNode(0, 2);
	g->addNode(1, 3); g->addNode(2, 3);
	g->addNode(2, 4); g->addNode(3, 4);
	g->addNode(3, 5); g->addNode(4, 5);

	int* distance = new int[6];
	g->BFS(0, distance);

	for (int i = 0; i < 6; i++) {
		cout << distance[i] << endl;
	}

	delete g;

	return 0;
}