#include <ModelInterface.h>
#include <assert.h>

using namespace jem_models;

CellState::CellState() {

}

CellState::~CellState() {

}

CellModel::CellModel() :
state_(NULL),
color_(black)
{

}

CellModel::CellModel(const CellState* state, CellColor color) :
state_(state),
color_(color)
{

}

CellModel::CellModel(const CellModel& cm) {
	this->state_ = cm.getState();
	this->color_ = cm.getColor();
}

CellModel& CellModel::operator=(const CellModel& rhs) {
	this->state_ = rhs.getState();
	this->color_ = rhs.getColor();

	return *this;
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
	column_count_(colCount)
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

const CellModel BoardModel::getCellModel(const unsigned int r, const unsigned int c) const {
	assert(r < row_count_ && c < column_count_);

	return board_[r * column_count_ + c];
}

void BoardModel::getNeighbors(VecOfCellModel& n, const unsigned int r, const unsigned int c) const {
	assert(r < row_count_ && c < column_count_);

	unsigned int row_above = 0;
	unsigned int row_below = 0;
	unsigned int col_left = 0;
	unsigned int col_right = 0;

	row_above = r == 0 ? row_count_ - 1 : r - 1;
	row_below = r == row_count_ - 1 ? 0 : r + 1;
	col_left = c == 0 ? column_count_ - 1 : c - 1;
	col_right = c == column_count_ - 1 ? 0 : c + 1;

	n.push_back(getCellModel(r,col_left));
	n.push_back(getCellModel(row_above,c));
	n.push_back(getCellModel(r,col_right));
	n.push_back(getCellModel(row_below,c));
	n.push_back(getCellModel(row_above,col_left));
	n.push_back(getCellModel(row_below,col_left));
	n.push_back(getCellModel(row_above,col_right));
	n.push_back(getCellModel(row_below,col_right));
}


void BoardModel::initialize() {
	for (unsigned int r = 0; r < row_count_; r++) {
		for (unsigned int c = 0; c < column_count_; c++) {
			board_.push_back(getRandomCellModel(r,c));
		}
	}
}


void BoardModel::runModel() {
	VecOfCellModel b;

	for (unsigned int r = 0; r < row_count_; r++) {
		for (unsigned int c = 0; c < column_count_; c++) {

			VecOfCellModel n;
			getNeighbors(n, r, c);

			CellModel cm = getCellModel(r, c);

			updateCellModel(cm, n);

			b.push_back(cm);
		}
	}

	board_ = std::move(b);
}

CellColor BoardModel::getColor(unsigned int r, unsigned int c) const{
	assert(r < row_count_ && c < column_count_);

	return getCellModel(r,c).getColor();
}

