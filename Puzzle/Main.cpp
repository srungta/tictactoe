#include "allheaders.hpp"
#define EMPTY 0
#define HUMANOCCUPIED 3
#define COMPOCCUPIED 9
#define HUMANTURN 'h'
#define COMPTURN 'c'
#define COMPWINS 1
#define HUMANWINS -1
#define DRAW 0
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

//Checks if the game is over or who wins
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

//called once in the beginning
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

int setMove(Board &b, int n,int playerMove){
	if(n <1 || n > 9){
		return INVALIDMOVE;
	}
	int rownumber = (n- 1)/3;
	int columnnumber = (n-1)%3;
	if(b.mat[rownumber][columnnumber] == EMPTY){
		b.mat[rownumber][columnnumber] = playerMove;
		return VALIDMOVE;
	}
	else{
		return INVALIDMOVE;
	}
}

int getNextMove(Board &b, char playerTurn){
	switch (checkWin(b))
	{
		case HUMANWINS:
			return HUMANWINS;
		case COMPWINS:
			return COMPWINS;
		case DRAW:
			return DRAW;
	}
	int k;
	switch (playerTurn){
	case COMPTURN:
		k = -99;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (b.mat[i][j] == EMPTY)
				{
					b.mat[i][j] = COMPOCCUPIED;
					int temp = getNextMove(b, HUMANTURN);
					if (temp > k)
					{
						k = temp;
					}
					b.mat[i][j] = EMPTY;
				}
			}
		}
		return k;

	case HUMANTURN:
		k = 99;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (b.mat[i][j] == EMPTY)
				{
					b.mat[i][j] = HUMANOCCUPIED;
					int temp = getNextMove(b, COMPTURN);
					if (temp < k)
					{
						k = temp;
					}
					b.mat[i][j] = EMPTY;
				}
			}
		}
		return k;
	}
}
int main(){
	Board b;
	bool GAMEOVER = false;
	displayBoardPositions();
	displayBoard(b);
	int temp =0,currentmove = 0;
	while(true){
		std::cout<<"Enter your move : ";
		std::cin>>currentmove;
		if(setMove(b,currentmove,HUMANOCCUPIED) == INVALIDMOVE){
			std::cout<<"Invalid move.\n";
			continue;
		}
		switch (checkWin(b))
		{
			case HUMANWINS: 
				std::cout << "HUMANS rule.\n";
				GAMEOVER = true;
				break;
			case COMPWINS:
				std::cout << "STUPID Human!!\n";
				GAMEOVER = true;
				break;
			case DRAW:
				std::cout << "ITS not over yet";
				GAMEOVER = true;
				break;
			case NOTOVERYET:
			{
				int k = -99;
				Board change;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (b.mat[i][j] == EMPTY)
						{
							b.mat[i][j] = COMPOCCUPIED;
							int temp = getNextMove(b, HUMANTURN);
							if (temp > k)
							{
								k = temp;
								change = b;
							}
							b.mat[i][j] = EMPTY;
						}
					}
				}
				b = change;

				switch (checkWin(b))
				{
				case HUMANWINS:
					std::cout << "HUMANS rule.\n";
					GAMEOVER = true;
					break;
				case COMPWINS:
					std::cout << "STUPID Human!!\n";
					GAMEOVER = true;
					break;
				case DRAW:
					std::cout << "ITS not over yet";
					GAMEOVER = true;
					break;
				}
				break;
			}
			default:
				std::cout << "Well this is embarrasing.";
				std::cout << "Something unexpected happened.\n Exiting now";
				exit(1);
				break;
		}
		displayBoard(b);
		if (GAMEOVER)
		{
			break;
		}
	}
}
