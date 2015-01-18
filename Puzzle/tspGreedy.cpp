#include "allheaders.hpp"

const

int main(){
	int N;
	
	scanf("Number of nodes : %d", &N);
	std::set<int> visited;
	std::vector< std::vector< std::pair<int, int> > > graph(N,std::vector<std::pair<int,int> >());
	std::vector< std::pair<int, int> >::iterator It;
	while (true) {
		int src = 0, dest = -1, path = 0;
		std::cin >> src;
		if (src == -1) {
			break;
		} 
		std::cin>> dest >> path;
		graph[src].push_back(std::make_pair(dest, path));
	}
	
	for (size_t i = 0; i < N; i++) {
		std::sort(graph[i].begin(), graph[i].end());
		//std::reverse(graph[i].begin(), graph[i].end());
		/*for (It = graph[i].begin(); It != graph[i].end(); ++It) {
			std::cout << (*It).first;
		}*/
	}

	visited.clear();


	int source = 0, cost = 0;
	scanf("Source node : %d", &source);

	std::stack<int> visiting;
	visiting.push(source);
	while (!visiting.empty()) {
		int current = visiting.top();
		if (visited.find(current) != visited.end()) {
			visiting.pop();
			continue;
		}
		for (It = graph[current].begin(); It != graph[current].end(); ++It) {
			if (visited.find((*It).first) == visited.end()) {
				visiting.pop();
				visiting.push((*It).first);
				cost += (*It).second;
				break;
			}			
		}
		visited.insert(current);
	}

	return 0;
}