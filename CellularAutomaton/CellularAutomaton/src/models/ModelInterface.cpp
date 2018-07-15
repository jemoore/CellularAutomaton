#include <ModelInterface.h>

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

const CellState* CellModel::getState() {
	return state_;
}

CellColor CellModel::getColor() {
	return color_;
}

BoardModel::BoardModel(unsigned int rowCount, unsigned int colCount) :
	row_count_(rowCount),
	column_count_(colCount)
{

}

BoardModel::~BoardModel() {

}

unsigned int BoardModel::getRowCount() {
	return row_count_;
}

unsigned int BoardModel::getColumnCount() {
	return column_count_;
}

void BoardModel::initialize() {

}

void BoardModel::runModel() {
	
}

