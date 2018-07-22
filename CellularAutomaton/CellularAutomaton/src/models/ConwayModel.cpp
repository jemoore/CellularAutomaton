/*
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 * Any live cell with fewer than two live neighbors dies, as if by under population.
 * Any live cell with two or three live neighbors lives on to the next generation.
 * Any live cell with more than three live neighbors dies, as if by overpopulation.
 * Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/
#include <ConwayModel.h>
#include <chrono>
#include <functional>
#include <random>

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

const CellModel ConwayModel::getRandomCellModel(const unsigned int /*r*/, const unsigned int /*c*/)
{
	auto seed = 
		std::chrono::high_resolution_clock::now().time_since_epoch().count();
	auto state = 
		std::bind(std::uniform_int_distribution<int>(0, 1), std::mt19937(seed));

	if (state()) {
		return aliveModel_;
	}
	
	return deadModel_;
}

/*
* Any live cell with fewer than two live neighbors dies, as if by under population.
* Any live cell with two or three live neighbors lives on to the next generation.
* Any live cell with more than three live neighbors dies, as if by overpopulation.
* Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/
void ConwayModel::updateCellModel(CellModel& cmodel, const VecOfCellModel& neighbors)
{
	unsigned int alive = 0;

	for (auto n : neighbors) {
		if (n.getState() == &aliveState_) {
			++alive;
		}
	}

	if (cmodel.getState() == &aliveState_) {
		if (alive < 2 || alive > 3) {
			cmodel = deadModel_;
		}
	}
	else {
		if (alive == 3) {
			cmodel = aliveModel_;
		}
	}
}
