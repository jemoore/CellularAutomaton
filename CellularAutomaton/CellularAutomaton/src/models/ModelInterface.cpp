#include <ModelInterface.h>
#include <assert.h>

using namespace jem_models;

CellState::CellState() {

}

CellState::~CellState() {

}

CellModel::CellModel(const CellState* state, CellColor color) :
state_(state),
color_(color)
{

}

void CellModel::setState(const CellState* state) {
	state_ = state;
}

void CellModel::setColor(CellColor color) {
	color_ = color;
}

const CellState* CellModel::getState() const {
	return state_;
}

CellColor CellModel::getColor() const {
	return color_;
}

BoardModel::BoardModel(unsigned int rowCount, unsigned int colCount) :
	row_count_(rowCount),
	column_count_(colCount),
	activeBoard_(&board1_)
{
}

BoardModel::~BoardModel() {

}

unsigned int BoardModel::getRowCount() const{
	return row_count_;
}

unsigned int BoardModel::getColumnCount() const{
	return column_count_;
}

void BoardModel::getNeighbors(VecOfCellModelPtrs& n, const unsigned int r, const unsigned int c) const {
	unsigned int row_above = 0;
	unsigned int row_below = 0;
	unsigned int col_left = 0;
	unsigned int col_right = 0;

	row_above = r == 0 ? row_count_ - 1 : r - 1;
	row_below = r == row_count_ - 1 ? 0 : r + 1;
	col_left = c == 0 ? column_count_ - 1 : c - 1;
	col_right = c == column_count_ - 1 ? 0 : c + 1;

	n.push_back((*activeBoard_)[r][col_left]);
	n.push_back((*activeBoard_)[row_above][c]);
	n.push_back((*activeBoard_)[r][col_right]);
	n.push_back((*activeBoard_)[row_below][c]);
	n.push_back((*activeBoard_)[row_above][col_left]);
	n.push_back((*activeBoard_)[row_below][col_left]);
	n.push_back((*activeBoard_)[row_above][col_right]);
	n.push_back((*activeBoard_)[row_below][col_right]);

}


void BoardModel::initialize(BoardType& b) {
	b.resize(row_count_);

	for (unsigned int r = 0; r < row_count_; r++) {
		for (unsigned int c = 0; c < column_count_; c++) {
			b[r].push_back(getRandomCellModel(r,c));
		}
	}
}

void BoardModel::initialize() {
	initialize(board1_);
	initialize(board2_);
}

void BoardModel::runModel() {
	BoardType* b = getNonActiveBoard();

	for (unsigned int r = 0; r < row_count_; r++) {
		for (unsigned int c = 0; c < column_count_; c++) {
			VecOfCellModelPtrs n;
			getNeighbors(n, r, c);
			const CellModel** active_cm = &((*b)[r][c]);
			const CellModel** cm = &((*b)[r][c]);
			cm = active_cm;
			updateCellModel(*cm, n);
		}
	}

	activeBoard_ = b;
}

CellColor BoardModel::getColor(unsigned int r, unsigned int c) const{
	assert(r < row_count_ && c < column_count_);

	return (*activeBoard_)[r][c]->getColor();
}

BoardModel::BoardType* BoardModel::getNonActiveBoard() {
	return (activeBoard_ == &board1_ ? &board2_ : &board1_);
}
