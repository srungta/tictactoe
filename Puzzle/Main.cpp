#include "allheaders.hpp"
#define EMPTY 0
#define HUMANOCCUPIED 3
#define COMPOCCUPIED 9
#define HUMANTURN 'h'
#define COMPTURN 'c'
#define COMPWINS -1
#define HUMANWINS 1
#define DRAW 1
#define NOTOVERYET -2
struct Board{
	int mat[3][3];
	int placesOccupied;
	Board(){
		placesOccupied = 0;
		for(int i = 0;i<3;i++)
			for(int j = 0;j<3;j++)
				mat[i][j] = EMPTY; // denotes an empty state
	}
};

void displayBoard(Board m){
	for(int i = 0;i<3;i++){
		for(int j = 0;j<3;j++){
			if(m.mat[i][j] == EMPTY){ // denotes an empty state
				std::cout<<"_ ";
			}
			else if(m.mat[i][j] == HUMANOCCUPIED){
				std::cout<<"X ";
			}
			else if(m.mat[i][j] == COMPOCCUPIED){
				std::cout<<"O ";
			}
		}
		std::cout<<std::endl;
	}
}

int checkWin(Board m){
	if(m.placesOccupied < 9){
		return NOTOVERYET;
	}
	//check rows
	int sum = 0;
	for(int i = 0;i<3;i++){
		sum = 0;
		for(int j = 0;j<3;j++){
			sum+=m.mat[i][j];
		}
		if(sum == 3*HUMANOCCUPIED)
			return HUMANWINS;
		if(sum == 3*COMPOCCUPIED)
			return COMPWINS;
	}
	sum = 0;
	for(int i = 0;i<3;i++){
		sum = 0;
		for(int j = 0;j<3;j++){
			sum+=m.mat[j][i];
		}
		if(sum == 3*HUMANOCCUPIED)
			return HUMANWINS;
		if(sum == 3*COMPOCCUPIED)
			return COMPWINS;
	}
	sum = 0;
	for(int j = 0;j<3;j++){
		sum+=m.mat[j][j];
	}
	if(sum == 3*HUMANOCCUPIED)
		return HUMANWINS;
	if(sum == 3*COMPOCCUPIED)
		return COMPWINS;

	sum = 0;
	for(int j = 0;j<3;j++){
		sum+=m.mat[j][2-j];
	}
	if(sum == 3*HUMANOCCUPIED)
		return HUMANWINS;
	if(sum == 3*COMPOCCUPIED)
		return COMPWINS;
	return DRAW;
}
void displayBoardPositions(){
	std::cout<<"Enter in this format :\n";
	for(int i = 0,k=1;i<3;i++){
		for(int j = 0;j<3;j++,k++)
			std::cout<<k<<" ";
		std::cout<<std::endl;
	}
}

#define INVALIDMOVE -1
#define VALIDMOVE 1

int setMove(Board &b, int n){
	if(n <1 || n > 9){
		return INVALIDMOVE;
	}
	int rownumber = (n- 1)/3;
	int columnnumber = (n-1)%3;
	if(b.mat[rownumber][columnnumber] == EMPTY){
		b.mat[rownumber][columnnumber] = HUMANOCCUPIED;
		return VALIDMOVE;
	}
	else{
		return INVALIDMOVE;
	}
}

int main(){
	Board b;
	displayBoardPositions();
	displayBoard(b);
	int temp =0,currentmove = 0;
	while(true){
		std::cout<<"Enter your move : ";
		std::cin>>currentmove;
		if(setMove(b,currentmove) == INVALIDMOVE){
			std::cout<<"Invalid move.\n";
			continue;
		}
		displayBoard(b);
	}
}