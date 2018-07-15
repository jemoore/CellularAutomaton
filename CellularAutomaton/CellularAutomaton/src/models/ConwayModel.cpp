/*
 * Any live cell with fewer than two live neighbors dies, as if by under population.
 * Any live cell with two or three live neighbors lives on to the next generation.
 * Any live cell with more than three live neighbors dies, as if by overpopulation.
 * Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/
#include <ConwayModel.h>

using namespace jem_models;

const CellState ConwayModel::aliveState_;
const CellState ConwayModel::deadState_;

const CellColor ConwayModel::aliveColor_ = white;
const CellColor ConwayModel::deadColor_  = black;

const CellModel ConwayModel::aliveModel_(&aliveState_, aliveColor_);
const CellModel ConwayModel::deadModel_(&deadState_, deadColor_);

ConwayModel::ConwayModel(unsigned int rowCnt, unsigned int colCount) :
BoardModel(rowCnt, colCount)
{

}

const CellModel& ConwayModel::getRandomCellModel()
{
	return aliveModel_;
	//CellModel cm(aliveState_, aliveColor_);
	//return cm;
}

void ConwayModel::updateCellModel(CellModel& cmodel, const std::vector<const CellModel*>& neighbors)
{
	cmodel.setColor(black);
}
