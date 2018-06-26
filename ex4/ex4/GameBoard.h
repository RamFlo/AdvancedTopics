#ifndef GAMEBOARD_H
#define GAMEBOARD_H

//--------------------------
// GameBoard class
//--------------------------

// @authors Guy Keller, Ram Shimon TAU - Advanced Topics in Programming - 2018 Semester B

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
		//Get the piece info for the piece in the requested location, or nullptr if no piece in this location.
		PieceInfo<GAME_PIECE> getPiece(int row, int col) {
			if (board[row*COLS + col] == nullptr)
				return nullptr;
			return make_unique<const std::pair<int, GAME_PIECE>>(*(board[row*COLS + col]));
		}
		//this method sets the piece into the board.
		//It returns the piece info, for the piece that was previously in this location, or nullptr if there was no piece in this location.
		PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player) {
			PieceInfo<GAME_PIECE> previousPiece = this->getPiece(row, col);
			board[row*COLS + col] = std::make_unique<const std::pair<int, GAME_PIECE>>(std::make_pair(player, piece));
			return previousPiece;
		}

		class iterator {
			PieceInfo<GAME_PIECE>* square;
			int pos, playerFilter;
			GAME_PIECE pieceFilter;
			bool filterByPlayer, filterByPiece;

			//this method find the next iterator position according to the iterator's filter and the board's contents.
			void findNextPosition() {
				while ((pos<ROWS*COLS) && ((!(*this->square)) || (filterByPlayer && (pair<int, GAME_PIECE>(**(this->square))).first != playerFilter) || (filterByPiece && (pair<int, GAME_PIECE>(**(this->square))).second != pieceFilter))) {
					this->square++;
					pos++;
				}
			}
		public:
			//non-filtered iterator constructor
			iterator(PieceInfo<GAME_PIECE>* curSquare) :square(curSquare), pos(0), filterByPlayer(false), filterByPiece(false) {}
			//filtered iterator by player constructor
			iterator(PieceInfo<GAME_PIECE>* curSquare, int player) : square(curSquare), pos(0), playerFilter(player), filterByPlayer(true), filterByPiece(false) {}
			//filtered iterator by piece constructor
			iterator(PieceInfo<GAME_PIECE>* curSquare, GAME_PIECE piece) : square(curSquare), pos(0), pieceFilter(piece), filterByPlayer(false), filterByPiece(true) {}
			//filtered iterator by piece and player constructor
			iterator(PieceInfo<GAME_PIECE>* curSquare, GAME_PIECE piece, int player) : square(curSquare), pos(0), playerFilter(player), pieceFilter(piece), filterByPlayer(true), filterByPiece(true)  {}

			iterator begin() {
				findNextPosition();
				return *this;
			}
			iterator end() {
				return iterator(square + ROWS * COLS - pos);
			}

			iterator operator++() {
				this->square++;
				pos++;
				findNextPosition();
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

		iterator begin() {
			int curPosition = 0;
			while (!board[curPosition] && curPosition < COLS * ROWS)
				curPosition++;
			return board + curPosition;
		}
		iterator end() {
			return board + COLS * ROWS;
		}
		//Iterating over all Pieces of a certain player
		iterator allPiecesOfPlayer(int playerNum) {
			int curPosition = 0;
			return iterator(board + curPosition, playerNum);
		}
		//Iterating over a certain Piece for all players
		iterator allOccureneceOfPiece(GAME_PIECE piece) {
			int curPosition = 0;
			return iterator(board + curPosition, piece);
		}
		//Iterating over a certain Piece for a certain player
		iterator allOccureneceOfPieceForPlayer(GAME_PIECE piece, int playerNum) {
			int curPosition = 0;
			return iterator(board + curPosition,piece, playerNum);
		}
};

#endif
