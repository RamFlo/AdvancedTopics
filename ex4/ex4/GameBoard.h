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
		GameBoard() {}
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
		
		/*class iterator {
			PieceInfo<GAME_PIECE>* square;
			int pos;
		public:
			iterator(PieceInfo<GAME_PIECE>* curSquare) : square(curSquare), pos(0) {}
			iterator operator++() {
				this->square++;
				pos++;
				while (!(*this->square)) {
					this->square++;
					pos++;
				}
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
		};*/

		class iterator {
			PieceInfo<GAME_PIECE>* square;
			int pos, playerFilter;
			GAME_PIECE pieceFilter;
			bool filterByPlayer, filterByPiece;
		public:
			iterator(PieceInfo<GAME_PIECE>* curSquare) : filterByPlayer(false), filterByPiece(false), square(curSquare), pos(0) {}

			iterator(PieceInfo<GAME_PIECE>* curSquare, int player) : filterByPlayer(true), playerFilter(player), filterByPiece(false), square(curSquare), pos(0) {}

			iterator(PieceInfo<GAME_PIECE>* curSquare, GAME_PIECE piece) : filterByPlayer(false), filterByPiece(true), pieceFilter(piece), square(curSquare), pos(0) {}
			
			iterator(PieceInfo<GAME_PIECE>* curSquare, GAME_PIECE piece, int player) : filterByPlayer(true), playerFilter(player), filterByPiece(true), pieceFilter(piece), square(curSquare), pos(0) {}


			iterator operator++() {
				this->square++;
				pos++;
				while (!(*this->square) && (!filterByPlayer || (pair<int, GAME_PIECE>(**(this->square))).first != playerFilter) && (!filterByPiece || (pair<int, GAME_PIECE>(**(this->square))).second != pieceFilter)) {
					this->square++;
					pos++;
				}
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
			int curPosition = 0;
			while (!board[curPosition] && curPosition < COLS * ROWS)
				curPosition++;
			return board + curPosition;
		}
		const iterator end() {
			return board + COLS * ROWS;
		}
		const iterator allPiecesOfPlayer(int playerNum) {
			int curPosition = 0;
			while ((!board[curPosition] || ((pair<int, GAME_PIECE>)*board[curPosition]).first != playerNum) && curPosition < COLS * ROWS)
				curPosition++;
			return iterator(board + curPosition, playerNum);
		}
		const iterator allOccureneceOfPiece(GAME_PIECE piece) {
			int curPosition = 0;
			while ((!board[curPosition] || ((pair<int, GAME_PIECE>)*board[curPosition]).second != piece) && curPosition < COLS * ROWS)
				curPosition++;
			return iterator(board + curPosition, piece);
		}
		const iterator allOccureneceOfPieceForPlayer(GAME_PIECE piece, int playerNum) {
			int curPosition = 0;
			while ((!board[curPosition] || ((pair<int, GAME_PIECE>)*board[curPosition]).second != piece || ((pair<int, GAME_PIECE>)*board[curPosition]).first != playerNum) && curPosition < COLS * ROWS)
				curPosition++;
			return iterator(board + curPosition,piece, playerNum);
		}
};


