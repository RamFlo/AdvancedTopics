#include <memory>
#include <tuple>
#include <utility>
using namespace std;
template<typename GAME_PIECE>


using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;
template<int ROWS, int COLS, typename GAME_PIECE, int PLAYERS = 2>

class GameBoard {
	PieceInfo<GAME_PIECE> board[ROWS*COLS];

	public :
		GameBoard() {};
		PieceInfo<GAME_PIECE> getPiece(int row, int col) {
			if (board[row*COLS + col] == nullptr)
				return nullptr;
			return make_unique<const std::pair<int, GAME_PIECE>>(*(board[row*COLS + col]));
		}

		PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player) {
			PieceInfo<GAME_PIECE> previousPiece = this->getPiece(row, col);
			board[row*COLS + col] = std::make_unique<const std::pair<int, GAME_PIECE>>(std::make_pair(player, piece));
			return previousPiece;
		}
		
		class iterator {
			PieceInfo<GAME_PIECE>* square;
			int pos;
		public:
			iterator(PieceInfo<GAME_PIECE>* curSquare, int newPos = 0) : square(curSquare), pos(newPos) {}
			iterator operator++() { //to fix: should only go through existing pieces
				this->square++;
				pos++;
				return *this;
			}
			tuple<int, int, GAME_PIECE, int> operator*() {
				int curRow = pos / ROWS;
				int curCol = pos % COLS;
				pair<int, GAME_PIECE> curGameInfo = **(this->square);
				return make_tuple(curRow, curCol, curGameInfo.second, curGameInfo.first);
			}
			bool operator!=(iterator other) {
				return square != other.square;
			}
		};

		const iterator begin() {
			return board; //to fix: should only go through existing pieces
		}

		const iterator end() {
			return board + COLS * ROWS; //to fix: should only go through existing pieces
		}
};


