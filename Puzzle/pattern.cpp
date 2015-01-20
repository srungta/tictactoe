#include<iostream>
#include<conio.h>
int *counter;

int addOneAtLocation(int i, int &n, int &m) {
	if (i == m) {
		return -1;
	}
	counter[i]++;
	if (counter[i] == n) {
		counter[i] = 0;
		return addOneAtLocation(i + 1, n, m);
	}
	return 0;
}


int tempmain() {
	int n, m;
	std::cout << "Enter m and n";
	std::cin >> m >> n;
	int i = 0, j = 0;
	std::cout << "Enter the matrix \n";
	int **matrix = new int*[m];
	for (int i = 0; i < m; ++i)
		matrix[i] = new int[n];

	for (size_t i = 0; i < m; i++) {
		for (size_t j = 0; j < n; j++) {
			std::cin >> matrix[i][j];
		}
	}
	counter = new int[m];
	for (int i = 0; i < m; i++) {
		counter[i] = 0;
	}
	counter[0] = -1;
	while (addOneAtLocation(0, n, m) == 0) {
		for (int i = 0; i < m; i++) {
			std::cout << matrix[i][counter[i]] << " ";
			//getch();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	getch();
}
