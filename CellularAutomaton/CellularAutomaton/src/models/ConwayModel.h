#ifndef CONWAY_MODEL_H_
#define CONWAY_MODEL_H_

#include <ModelInterface.h>

namespace jem_models {

class ConwayModel : public BoardModel {
public:

	ConwayModel(unsigned int rowCnt, unsigned int colCount);

	virtual const CellModel getRandomCellModel(const unsigned int r, const unsigned int c);

	virtual void updateCellModel(CellModel& cmodel, const VecOfCellModel& neighbors);

protected:
	static const CellState aliveState_;
	static const CellState deadState_;
	static const CellColor aliveColor_;
	static const CellColor deadColor_;

	static const CellModel aliveModel_;
	static const CellModel deadModel_;
};

}

#endif