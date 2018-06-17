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
			return board[row*COLS + col];
		}

		PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player) {
			board[row*COLS + col] = std::make_unique(std::make_pair(player, piece));
		}
		
		class iterator {
			PieceInfo<GAME_PIECE>* square;
			int pos;
			iterator(PieceInfo<GAME_PIECE>* curSquare, int newPos = 0) : square(curSquare), pos(newPos) {}
			iterator operator++() {
				this.square++;
				pos++;
				return *this;
			}
			tuple<int, int, GAME_PIECE, int> operator*() {
				int curRow = pos / ROWS;
				int curCol = pos % COLS;
				pair<int, GAME_PIECE> curGameInfo = *(this->square);
				return make_tuple(curRow, curCol, curGameInfo.second, curGameInfo.first);
			}

			bool operator!=(iterator other) {
				return square != other.square;
			}
		};

		const iterator begin() {
			return board;
		}

		const iterator end() {
			return board + COLS * ROWS;
		}
};


