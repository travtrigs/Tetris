#include <iostream>
#include <Carbon/Carbon.h>
#include <term.h>
#include <time.h>
#include <thread>
#include <chrono>
using namespace std;

int board[25][12];
int x = 5, y = 3;

class block {
	public :
	block() : type(), rotation() {}
	int type;
	int rotation;
} piece;

//checks if game is over
bool gameOver() {
	if (board[4][5] == 2) {
		cout << "Game over!";
		return true;
	}
	return false;
}
//checks if block is at bottom
bool isBottom() {
	for (int row = 24; row >= 0; row--) {
		for (int column = 1; column <= 10; column++) {
			if (board[row][column] == 1 && board[row+1][column] == 2) {
				return true;
			}
		}
	}
	return false;
}

void moveDown() {
	if (!isBottom()) {
		for (int row = 24; row >= 0; row--) {
			for (int column = 1; column <= 10; column++) {
				if (board[row][column] == 1) {
					board[row][column] = 0;
					board[row+1][column] = 1;
				}
			}
		}
		y++;
	}
	if (isBottom()) {
		for (int row = 0; row < 25; row++) {
			for (int column = 1; column <= 10; column++) {
				if (board[row][column] == 1) {
					board[row][column] = 2;
				}
			}
		}
		y = 3;
	}
	return;
}
//moves piece left
void moveLeft() {
	//checks if can move left
	bool canMove = true;
	for (int row = 24; row >= 0; row--) {
		for (int column = 1; column <= 10; column++) {
			if (board[row][column] == 1 && board[row][column-1] == 2) {
				canMove = false;
			}
		}
	}
	//moves left if possible
	if (canMove == true) {
		x--;
		for (int row = 24; row >= 0; row--) {
			for (int column = 1; column <= 10; column++) {
				if (board[row][column] == 1) {
					board[row][column] = 0;
					board[row][column-1] = 1;
				}
			}
		}
	}
	return;
}
//moves piece right
void moveRight() {
	//checks if can move right
	bool canMove = true;
	for (int row = 24; row >= 0; row--) {
		for (int column = 10; column >= 1; column--) {
			if (board[row][column] == 1 && board[row][column+1] == 2) {
				canMove = false;
			}
		}
	}
	//moves right if possible
	if (canMove == true) {
		x++;
		for (int row = 24; row >= 0; row--) {
			for (int column = 10; column >= 1; column--) {
				if (board[row][column] == 1) {
					board[row][column] = 0;
					board[row][column+1] = 1;
				}
			}
		}
	}
	return;
}

void addPiece() {
	switch (piece.type) {
		//O block
		case 1:
			switch (piece.rotation) {
				case 1:
					board[y][x] = 1;
					board[y][x+1] = 1;
					board[y-1][x] = 1;
					board[y-1][x+1] = 1;
					break;
				case 2:
					board[y][x] = 1;
					board[y][x+1] = 1;
					board[y-1][x] = 1;
					board[y-1][x+1] = 1;
					break;
				case 3:
					board[y][x] = 1;
					board[y][x+1] = 1;
					board[y-1][x] = 1;
					board[y-1][x+1] = 1;
					break;
				case 4:
					board[y][x] = 1;
					board[y][x+1] = 1;
					board[y-1][x] = 1;
					board[y-1][x+1] = 1;
					break;
			}
			break;
		//I block
		case 2:
			switch (piece.rotation) {
				case 1:
					board[y+2][x] = 1;
					board[y+1][x] = 1;
					board[y][x] = 1;
					board[y-1][x] = 1;
					break;
				case 2:
					board[y][x-1] = 1;
					board[y][x] = 1;
					board[y][x+1] = 1;
					board[y][x+2] = 1;
					break;
				case 3:
					board[y+1][x] = 1;
					board[y][x] = 1;
					board[y-1][x] = 1;
					board[y-2][x] = 1;
					break;
				case 4:
					board[y][x-2] = 1;
					board[y][x-1] = 1;
					board[y][x] = 1;
					board[y][x+1] = 1;
					break;
			}
			break;
		//T block
		case 3:
			switch (piece.rotation) {
				case 1:
					board[y-1][x-1] = 3;
					board[y-1][x] = 1;
					board[y-1][x+1] = 3;
					board[y][x-1] = 1;
					board[y][x] = 1;
					board[y][x+1] = 1;
					break;
				case 2:
					board[y-1][x] = 1;
					board[y-1][x+1] = 3;
					board[y][x] = 1;
					board[y][x+1] = 1;
					board[y+1][x] = 1;
					board[y+1][x+1] = 3;
					break;
				case 3:
					board[y+1][x-1] = 3;
					board[y+1][x] = 1;
					board[y+1][x+1] = 3;
					board[y][x-1] = 1;
					board[y][x] = 1;
					board[y][x+1] = 1;
					break;
				case 4:
					board[y-1][x] = 1;
					board[y-1][x-1] = 3;
					board[y][x] = 1;
					board[y][x-1] = 1;
					board[y+1][x] = 1;
					board[y+1][x-1] = 3;
					break;
			}
			break;
		//Z block
		case 4:
			switch (piece.rotation) {
				case 1:
					board[y-1][x-1] = 1;
					board[y-1][x] = 1;
					board[y-1][x+1] = 3;
					board[y][x-1] = 3;
					board[y][x] = 1;
					board[y][x+1] = 1;
					break;
				case 2:
					board[y-1][x] = 3;
					board[y-1][x+1] = 1;
					board[y][x] = 1;
					board[y][x+1] = 1;
					board[y+1][x] = 1;
					board[y+1][x+1] = 3;
					break;
				case 3:
					board[y-1][x-1] = 1;
					board[y-1][x] = 1;
					board[y-1][x+1] = 3;
					board[y][x-1] = 3;
					board[y][x] = 1;
					board[y][x+1] = 1;
					break;
				case 4:
					board[y-1][x] = 3;
					board[y-1][x+1] = 1;
					board[y][x] = 1;
					board[y][x+1] = 1;
					board[y+1][x] = 1;
					board[y+1][x+1] = 3;
					break;
			}
			break;
		//S block
		case 5:
			switch (piece.rotation) {
				case 1:
					board[y-1][x-1] = 3;
					board[y-1][x] = 1;
					board[y-1][x+1] = 1;
					board[y][x-1] = 1;
					board[y][x] = 1;
					board[y][x+1] = 3;
					break;
				case 2:
					board[y-1][x-1] = 1;
					board[y-1][x] = 3;
					board[y][x-1] = 1;
					board[y][x] = 1;
					board[y+1][x-1] = 3;
					board[y+1][x] = 1;
					break;
				case 3:
					board[y-1][x-1] = 3;
					board[y-1][x] = 1;
					board[y-1][x+1] = 1;
					board[y][x-1] = 1;
					board[y][x] = 1;
					board[y][x+1] = 3;
					break;
				case 4:
					board[y-1][x-1] = 1;
					board[y-1][x] = 3;
					board[y][x-1] = 1;
					board[y][x] = 1;
					board[y+1][x-1] = 3;
					board[y+1][x] = 1;
					break;
			}
			break;
		//J block
		case 6:
			switch (piece.rotation) {
				case 1:
					board[y-1][x-1] = 1;
					board[y-1][x] = 1;
					board[y-1][x+1] = 1;
					board[y][x+1] = 1;
					board[y][x-1] = 2;
					board[y][x] = 2;
					break;
				case 2:
					board[y-2][x] = 1;
					board[y-2][x+1] = 2;
					board[y-1][x] = 1;
					board[y-1][x+1] = 2;
					board[y][x] = 1;
					board[y][x-1] = 1;
					break;
				case 3:
					board[y][x-1] = 1;
					board[y][x] = 1;
					board[y][x+1] = 1;
					board[y-1][x-1] = 1;
					board[y-1][x] = 2;
					board[y-1][x+1] = 2;
					break;
				case 4:
					board[y-2][x] = 1;
					board[y-2][x+1] = 1;
					board[y-1][x] = 1;
					board[y][x] = 1;
					break;
			}
			break;
		//L block
		case 7:
			switch (piece.rotation) {
				case 1:
					board[y-1][x-1] = 1;
					board[y-1][x] = 1;
					board[y-1][x+1] = 1;
					board[y][x-1] = 1;
					break;
				case 2:
					board[y-2][x] = 1;
					board[y-1][x] = 1;
					board[y][x] = 1;
					board[y][x-1] = 1;
					break;
				case 3:
					board[y-1][x-1] = 1;
					board[y-1][x] = 1;
					board[y-1][x+1] = 1;
					board[y][x+1] = 1;
					break;
				case 4:
					board[y-2][x] = 1;
					board[y-1][x] = 1;
					board[y][x] = 1;
					board[y][x+1] = 1;
					break;
			}
			break;
	}
}
void drawBoard() {
	string icon[4] = { "  ", "o", "o", " " };
	
	cout << "+--------------------------+" << endl;
	for (int row = 4; row < 24; row++) {
		cout << "|\t";
		for (int column = 1; column <= 10; column++) {
			cout << icon[board[row][column]] << "\t";
		}
		cout << "|" << endl;
	}
	cout << "+--------------------------+"<< endl << endl;
	return;
}

void rotate() {
	for (int row = 24; row >= 0; row--) {
		for (int column = 0; column < 10; column++) {
			if (board[row][column] == 1) {
				board[row][column] = 0;
			}
		}
	}
	if (piece.rotation == 4) piece.rotation = 0;
	piece.rotation++;
	addPiece();
}
bool isPressed( unsigned short inKeyCode ) {
	unsigned char keyMap[16];
	GetKeys((BigEndianUInt32*) &keyMap);
	return (0 != ((keyMap[ inKeyCode >> 3] >> (inKeyCode & 7)) & 1));
}
void clearscreen() {
	if (!cur_term)
	{
		void *a;
		int result;
		setupterm( NULL, STDOUT_FILENO, &result );
		a = malloc(sizeof(int) *result);
		free (a);
		if (result <= 0) free (a); return;
	}
	putp( tigetstr( "clear" ) );
}

bool isClearable(int y) {
	for (int i = 0; i < 10; i++) {
		if (board[y][i] == 0) {
			return false;
		}
	}
	return true;
}
void clearLine() {
	for (int y = 4; y < 24; y++) {
		if (isClearable(y)) {
			for (int i = y; i >= 3; i--) {
				for (int j = 0; j < 10; j++) {
					board[i][j] = board[i-1][j];
				}
			}
		}
	}
}

int main() {
	for (int row = 0; row < 25; row++) {
		for (int column = 0; column <= 10; column++) {
			board[row][column] = 0;
			if (row == 24 || column == 0 || column == 11) {
				board[row][column] = 2;
			}
		}
	}
	srand(time(NULL));
	while (!gameOver()) {
		piece.type =  rand() % 6 + 1;
		piece.rotation = 1;
		srand(time(NULL));
		while (!isBottom()) {
	
			clearLine();
			clearscreen();
			addPiece();
			if (isPressed(0) && x > 0) {
				moveLeft();
			}
			if (isPressed(2) && x < 10) {
				moveRight();
			}
			if (isPressed(1)) {
				rotate();
			}

			this_thread::sleep_for (chrono::milliseconds(200));
			drawBoard();
			moveDown();
		}
	}
	return 0;
}





