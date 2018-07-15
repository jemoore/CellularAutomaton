#ifndef MODEL_INTERFACE_H
#define MODEL_INTERFACE_H

#include <vector>

namespace jem_models {

enum CellColor {
	black = 0,
	white,
	yellow,
	green,
	blue
};

class CellState {
public:
	CellState();
	virtual ~CellState();
};

class CellModel {
public:
	CellModel(const CellState* state, CellColor color);

	void setState(const CellState* state);
	void setColor(CellColor color);

	const CellState* getState();
	CellColor getColor();

private:
	const CellState* state_;
	CellColor color_;
};

class BoardModel {
public:
	BoardModel(unsigned int rowCount, unsigned int colCount);
	virtual ~BoardModel();

	virtual unsigned int getRowCount();
	virtual unsigned int getColumnCount();

	virtual const CellModel& getRandomCellModel() = 0;

	virtual void updateCellModel(CellModel& cmodel, const std::vector<const CellModel*>& neighbors) = 0;

	virtual void initialize();
	virtual void runModel();

private:
	unsigned int row_count_;
	unsigned int column_count_;
};

}

#endif
