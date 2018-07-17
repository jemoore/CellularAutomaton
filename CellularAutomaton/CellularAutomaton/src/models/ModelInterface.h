#ifndef MODEL_INTERFACE_H
#define MODEL_INTERFACE_H

#include <memory>
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

	const CellState* getState() const;
	CellColor getColor() const;

private:
	const CellState* state_;
	CellColor color_;
};

class BoardModel {
public:
	typedef std::vector<const CellModel*> VecOfCellModelPtrs;

	BoardModel(unsigned int rowCount, unsigned int colCount);
	virtual ~BoardModel();

	virtual unsigned int getRowCount() const;
	virtual unsigned int getColumnCount() const;

	virtual const CellModel* getRandomCellModel(const unsigned int r, const unsigned int c) = 0;

	virtual void updateCellModel(const CellModel*& cmodel, const VecOfCellModelPtrs& neighbors) = 0;

	virtual void getNeighbors(VecOfCellModelPtrs& n, const unsigned int r, const unsigned int c) const;

	virtual void initialize();
	virtual void runModel();

	CellColor getColor(unsigned int r, unsigned int c) const;

protected:
	typedef std::vector< VecOfCellModelPtrs > BoardType;

	virtual void initialize(BoardType& b);

	virtual BoardType* getNonActiveBoard();

private:
	unsigned int row_count_;
	unsigned int column_count_;

	BoardType board1_;
	BoardType board2_;
	BoardType* activeBoard_;
};

}

#endif
