// Chess Game in C++
// Course: CL1004 - Object Oriented Programming
// National University of Computer & Emerging Sciences
// Faisalabad-Chiniot Campus | Spring 2026

#include <iostream>
#include <string>
using namespace std;

// Color Enum
enum Color { WHITE, BLACK };

// Piece Class
class Piece {
protected:
	Color  color;
	char   symbol;
	string name;
	bool   hasMoved;

public:
	Piece(Color c, char sym, string n) {
		color = c;
		symbol = sym;
		name = n;
		hasMoved = false;
	}

	virtual ~Piece() {}

	Color  getColor() { return color; }
	char   getSymbol() { return symbol; }
	string getName() { return name; }
	void   markMoved() { hasMoved = true; }

	// Pure virtual move validation
	virtual bool isValidMove(int fr, int fc,
		int tr, int tc,
		Piece* grid[8][8]) = 0;
};

// Pawn Class
class Pawn : public Piece {
public:
	Pawn(Color c) : Piece(c, (c == WHITE ? 'P' : 'p'), "Pawn") {}

	bool isValidMove(int fr, int fc, int tr, int tc, Piece* grid[8][8]) {
		int dir = (color == WHITE) ? -1 : 1;
		int startRow = (color == WHITE) ? 6 : 1;
		int dr = tr - fr;
		int dc = tc - fc;

		if (dc == 0 && dr == dir && grid[tr][tc] == NULL)
			return true;

		if (dc == 0 && dr == 2 * dir && fr == startRow
			&& grid[fr + dir][fc] == NULL && grid[tr][tc] == NULL)
			return true;

		if ((dc == 1 || dc == -1) && dr == dir
			&& grid[tr][tc] != NULL && grid[tr][tc]->getColor() != color)
			return true;

		return false;
	}
};

// Rook Class
class Rook : public Piece {
public:
	Rook(Color c) : Piece(c, (c == WHITE ? 'R' : 'r'), "Rook") {}

	bool isValidMove(int fr, int fc, int tr, int tc, Piece* grid[8][8]) {
		if (fr != tr && fc != tc) return false;

		if (grid[tr][tc] != NULL && grid[tr][tc]->getColor() == color)
			return false;

		int dr = (tr == fr) ? 0 : (tr > fr ? 1 : -1);
		int dc = (tc == fc) ? 0 : (tc > fc ? 1 : -1);
		int r = fr + dr, c = fc + dc;
		while (r != tr || c != tc) {
			if (grid[r][c] != NULL) return false;
			r += dr; c += dc;
		}
		return true;
	}
};

// Knight Class
class Knight : public Piece {
public:
	Knight(Color c) : Piece(c, (c == WHITE ? 'N' : 'n'), "Knight") {}

	bool isValidMove(int fr, int fc, int tr, int tc, Piece* grid[8][8]) {
		int dr = tr - fr; if (dr < 0) dr = -dr;
		int dc = tc - fc; if (dc < 0) dc = -dc;

		if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2)))
			return false;

		if (grid[tr][tc] != NULL && grid[tr][tc]->getColor() == color)
			return false;

		return true;
	}
};

// Bishop Class
class Bishop : public Piece {
public:
	Bishop(Color c) : Piece(c, (c == WHITE ? 'B' : 'b'), "Bishop") {}

	bool isValidMove(int fr, int fc, int tr, int tc, Piece* grid[8][8]) {
		int dr = tr - fr; if (dr < 0) dr = -dr;
		int dc = tc - fc; if (dc < 0) dc = -dc;

		if (dr != dc || dr == 0) return false;

		if (grid[tr][tc] != NULL && grid[tr][tc]->getColor() == color)
			return false;

		int stepR = (tr > fr) ? 1 : -1;
		int stepC = (tc > fc) ? 1 : -1;
		int r = fr + stepR, c = fc + stepC;
		while (r != tr || c != tc) {
			if (grid[r][c] != NULL) return false;
			r += stepR; c += stepC;
		}
		return true;
	}
};

// Queen Class
class Queen : public Piece {
public:
	Queen(Color c) : Piece(c, (c == WHITE ? 'Q' : 'q'), "Queen") {}

	bool isValidMove(int fr, int fc, int tr, int tc, Piece* grid[8][8]) {
		int dr = tr - fr; int adr = dr < 0 ? -dr : dr;
		int dc = tc - fc; int adc = dc < 0 ? -dc : dc;

		bool straight = (fr == tr || fc == tc);
		bool diagonal = (adr == adc && adr != 0);

		if (!straight && !diagonal) return false;

		if (grid[tr][tc] != NULL && grid[tr][tc]->getColor() == color)
			return false;

		int stepR = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
		int stepC = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);
		int r = fr + stepR, c = fc + stepC;
		while (r != tr || c != tc) {
			if (grid[r][c] != NULL) return false;
			r += stepR; c += stepC;
		}
		return true;
	}
};

// King Class
class King : public Piece {
public:
	King(Color c) : Piece(c, (c == WHITE ? 'K' : 'k'), "King") {}

	bool isValidMove(int fr, int fc, int tr, int tc, Piece* grid[8][8]) {
		int dr = tr - fr; if (dr < 0) dr = -dr;
		int dc = tc - fc; if (dc < 0) dc = -dc;

		if (dr > 1 || dc > 1) return false;

		if (grid[tr][tc] != NULL && grid[tr][tc]->getColor() == color)
			return false;

		return true;
	}
};

// Board Class
class Board {
private:
	Piece* grid[8][8];

public:
	Board() {
		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++)
				grid[r][c] = NULL;

		// Black pieces
		grid[0][0] = new Rook(BLACK);
		grid[0][1] = new Knight(BLACK);
		grid[0][2] = new Bishop(BLACK);
		grid[0][3] = new Queen(BLACK);
		grid[0][4] = new King(BLACK);
		grid[0][5] = new Bishop(BLACK);
		grid[0][6] = new Knight(BLACK);
		grid[0][7] = new Rook(BLACK);
		for (int c = 0; c < 8; c++) grid[1][c] = new Pawn(BLACK);

		// White pieces
		grid[7][0] = new Rook(WHITE);
		grid[7][1] = new Knight(WHITE);
		grid[7][2] = new Bishop(WHITE);
		grid[7][3] = new Queen(WHITE);
		grid[7][4] = new King(WHITE);
		grid[7][5] = new Bishop(WHITE);
		grid[7][6] = new Knight(WHITE);
		grid[7][7] = new Rook(WHITE);
		for (int c = 0; c < 8; c++) grid[6][c] = new Pawn(WHITE);
	}

	~Board() {
		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++) {
				delete grid[r][c];
				grid[r][c] = NULL;
			}
	}

	// Get piece at a square
	Piece* get(int r, int c) {
		if (r < 0 || r > 7 || c < 0 || c > 7) return NULL;
		return grid[r][c];
	}

	// Set piece at a square
	void set(int r, int c, Piece* p) {
		grid[r][c] = p;
	}

	// Get raw grid pointer
	Piece** getGrid() {
		return &grid[0][0];
	}

	// Display board
	void display() {
		cout << "\n     a   b   c   d   e   f   g   h\n";
		cout << "   +---+---+---+---+---+---+---+---+\n";
		for (int r = 0; r < 8; r++) {
			cout << " " << (8 - r) << " |";
			for (int c = 0; c < 8; c++) {
				if (grid[r][c] != NULL)
					cout << " " << grid[r][c]->getSymbol() << " |";
				else
					cout << " . |";
			}
			cout << " " << (8 - r) << "\n";
			cout << "   +---+---+---+---+---+---+---+---+\n";
		}
		cout << "     a   b   c   d   e   f   g   h\n\n";
	}

	// Validate move using piece rules
	bool isMoveValid(int fr, int fc, int tr, int tc) {
		return grid[fr][fc]->isValidMove(fr, fc, tr, tc, grid);
	}

	// Temporarily apply a move for simulation
	Piece* tempMove(int fr, int fc, int tr, int tc) {
		Piece* captured = grid[tr][tc];
		grid[tr][tc] = grid[fr][fc];
		grid[fr][fc] = NULL;
		return captured;
	}

	// Undo a temporary move
	void undoTemp(int fr, int fc, int tr, int tc, Piece* captured) {
		grid[fr][fc] = grid[tr][tc];
		grid[tr][tc] = captured;
	}

	// Find king position by colour
	bool findKing(Color col, int& kr, int& kc) {
		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++)
				if (grid[r][c] != NULL
					&& grid[r][c]->getColor() == col
					&& grid[r][c]->getName() == "King") {
					kr = r; kc = c;
					return true;
				}
		return false;
	}

	// Check if colour is in check
	bool isInCheck(Color col) {
		int kr, kc;
		if (!findKing(col, kr, kc)) return false;

		Color opp = (col == WHITE) ? BLACK : WHITE;
		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++)
				if (grid[r][c] != NULL && grid[r][c]->getColor() == opp)
					if (grid[r][c]->isValidMove(r, c, kr, kc, grid))
						return true;
		return false;
	}

	// Check if colour has no legal moves
	bool hasNoLegalMoves(Color col) {
		for (int fr = 0; fr < 8; fr++)
			for (int fc = 0; fc < 8; fc++) {
				Piece* p = grid[fr][fc];
				if (p == NULL || p->getColor() != col) continue;

				for (int tr = 0; tr < 8; tr++)
					for (int tc = 0; tc < 8; tc++) {
						if (fr == tr && fc == tc) continue;
						if (!p->isValidMove(fr, fc, tr, tc, grid)) continue;

						Piece* cap = tempMove(fr, fc, tr, tc);
						bool   inDanger = isInCheck(col);
						undoTemp(fr, fc, tr, tc, cap);

						if (!inDanger) return false;
					}
			}
		return true;
	}
};

int main() {

	Board board;

	Color turn = WHITE;

	// Player names
	string whitePlayer;
	string blackPlayer;

	cout << "\n=============================================\n";
	cout << "           CHESS GAME MAIN MENU\n";
	cout << "=============================================\n";

	cout << "Enter White Player Name: ";
	getline(cin, whitePlayer);

	cout << "Enter Black Player Name: ";
	getline(cin, blackPlayer);

	cout << "\n=============================================\n"
		<< "         CHESS GAME IN C++ - OOP\n"
		<< "  NUCES Faisalabad-Chiniot | Spring 2026\n"
		<< "=============================================\n"
		<< "  White Player : " << whitePlayer << "\n"
		<< "  Black Player : " << blackPlayer << "\n"
		<< "=============================================\n"
		<< "  Enter moves like: e2 e4\n"
		<< "  Type 'quit' to resign.\n"
		<< "---------------------------------------------\n"
		<< "  Piece key (UPPER=White, lower=Black):\n"
		<< "  K/k=King  Q/q=Queen  R/r=Rook\n"
		<< "  B/b=Bishop  N/n=Knight  P/p=Pawn\n"
		<< "=============================================\n";

	while (true) {

		string who;

		if (turn == WHITE)
			who = whitePlayer + " (White)";
		else
			who = blackPlayer + " (Black)";

		Color opp = (turn == WHITE) ? BLACK : WHITE;

		// Check for checkmate or stalemate
		bool inCheck = board.isInCheck(turn);
		bool noMoves = board.hasNoLegalMoves(turn);

		if (noMoves) {

			if (inCheck) {

				if (turn == WHITE)
					cout << "  CHECKMATE! "
					<< blackPlayer << " (Black) wins!\n";

				else
					cout << "  CHECKMATE! "
					<< whitePlayer << " (White) wins!\n";
			}

			else {

				cout << "  STALEMATE! The game is a draw.\n";
			}

			break;
		}

		if (inCheck)
			cout << "  *** CHECK! "
			<< who << " is in check. ***\n";

		// Display board and read input
		board.display();

		cout << who << "'s move (e.g. e2 e4): ";

		string from, to;

		cin >> from;

		if (from == "quit" || from == "exit") {

			cout << "  " << who
				<< " resigned the game.\n";

			break;
		}

		cin >> to;

		// Parse algebraic notation
		if (from.size() < 2 || to.size() < 2) {

			cout << "  [!] Use format: e2 e4\n";
			continue;
		}

		char fileFrom = from[0];
		char rankFrom = from[1];

		char fileTo = to[0];
		char rankTo = to[1];

		if (fileFrom < 'a' || fileFrom > 'h' ||
			rankFrom < '1' || rankFrom > '8' ||
			fileTo < 'a' || fileTo > 'h' ||
			rankTo < '1' || rankTo > '8') {

			cout << "  [!] Invalid square. "
				<< "Use files a-h and ranks 1-8.\n";

			continue;
		}

		int fc = fileFrom - 'a';
		int fr = 8 - (rankFrom - '0');

		int tc = fileTo - 'a';
		int tr = 8 - (rankTo - '0');

		// Validate piece selection
		Piece* piece = board.get(fr, fc);

		if (piece == NULL) {

			cout << "  [!] No piece on "
				<< from << ".\n";

			continue;
		}

		if (piece->getColor() != turn) {

			cout << "  [!] That is not your piece.\n";
			continue;
		}

		if (!board.isMoveValid(fr, fc, tr, tc)) {

			cout << "  [!] Illegal move for "
				<< piece->getName() << ".\n";

			continue;
		}

		// Simulate move to check for self-check
		Piece* cap = board.tempMove(fr, fc, tr, tc);

		bool selfCheck = board.isInCheck(turn);

		board.undoTemp(fr, fc, tr, tc, cap);

		if (selfCheck) {

			cout << "  [!] That move leaves "
				<< "your King in check!\n";

			continue;
		}

		// Commit move
		Piece* captured = board.get(tr, tc);

		delete captured;

		board.set(tr, tc, piece);

		board.set(fr, fc, NULL);

		piece->markMoved();

		cout << "  --> " << who << ": "
			<< piece->getName()
			<< " " << from
			<< " -> " << to << "\n";

		// Pawn promotion
		if (piece->getName() == "Pawn") {

			if ((turn == WHITE && tr == 0) ||
				(turn == BLACK && tr == 7)) {

				cout << "  Pawn promotion! "
					<< "Choose Q / R / B / N: ";

				char ch;
				cin >> ch;

				Piece* promoted = NULL;

				if (ch == 'r' || ch == 'R')
					promoted = new Rook(turn);

				else if (ch == 'b' || ch == 'B')
					promoted = new Bishop(turn);

				else if (ch == 'n' || ch == 'N')
					promoted = new Knight(turn);

				else
					promoted = new Queen(turn);

				board.set(tr, tc, promoted);

				delete piece;

				cout << "  Promoted to "
					<< promoted->getName()
					<< "!\n";
			}
		}

		// Switch turn
		turn = opp;
	}

	cout << "\nGame over. Thanks for playing!\n";

	system("pause");

	return 0;
}
