#include <string>
#include "ConwayModel.h"

#include <gtest/gtest.h>

#include <vector>

using namespace jem_models;

typedef  std::vector<unsigned int> UINTVEC;

class MockConwayModel : public ConwayModel {
public:
	MockConwayModel(
		const unsigned int rows, 
		const unsigned int cols,
		UINTVEC& alive_rows,
		UINTVEC& alive_cols
	) :
		ConwayModel(rows, cols),
		alive_rows_(alive_rows),
		alive_cols_(alive_cols)
	{
	}

	void printModel() {
		std::cout << std::endl << std::endl;

		for (unsigned int r = 0; r < getRowCount(); r++) {
			for (unsigned int c = 0; c < getColumnCount(); c++) {
				CellColor color = getColor(r, c);
				if (color == getAliveColor()) {
					std::cout << '@';
				}
				else {
					std::cout << ' ';
				}
				if (c != getColumnCount() - 1) {
					std::cout << ',';
				}
			}
			std::cout << std::endl;
		}
	}

	// return live cell model for a live cell with tow live neighbors
	virtual const CellModel getRandomCellModel(const unsigned int r, const unsigned int c) {
		CellModel emptyCellModel;

		if (alive_rows_.size() != alive_cols_.size()) {
			return emptyCellModel;
		}
		for (size_t i = 0; i < alive_rows_.size(); i++) {
			if (r == alive_rows_[i] && c == alive_cols_[i]) {
				return aliveModel_;
			}
		}

		return deadModel_;
	}

	bool isInitializedAsExpected()
	{
		for (unsigned int r = 0; r < getRowCount(); r++) {
			for (unsigned int c = 0; c < getColumnCount(); c++) {
				CellColor color = getColor(r, c);

				bool is_alive = false;
				for (size_t i = 0; i < alive_rows_.size(); i++) {
					if (r == alive_rows_[i] && c == alive_cols_[i]) {
						is_alive = true;
						break;
					}
				}
				if (is_alive) {
					if (color != getAliveColor()) {
						return false;
					}
				}
				else {
					if (color != getDeadColor()) {
						return false;
					}
				}
			}
		}
		return true;
	}

	CellColor getAliveColor() { return aliveColor_; }
	CellColor getDeadColor() { return deadColor_; }

	UINTVEC alive_rows_;
	UINTVEC alive_cols_;
};


class ConwayTests : public ::testing::Test
{
protected:
	// virtual void SetUp() {}

	// virtual void TearDown() {}
};

TEST_F(ConwayTests, gettertest )
{
	const unsigned int rows = 10;
	const unsigned int cols = 20;

	ConwayModel model(rows, cols);

	EXPECT_EQ(model.getRowCount(), rows);
	EXPECT_EQ(model.getColumnCount(), cols);

	model.initialize();

	EXPECT_EQ(model.getRowCount(), rows);
	EXPECT_EQ(model.getColumnCount(), cols);

}

TEST_F(ConwayTests, random_cellmodel_test)
{
	const unsigned int rows = 10;
	const unsigned int cols = 20;
	
	ConwayModel model(rows, cols);

	const unsigned int row = 1;
	const unsigned int col = 2;

	CellModel cell_model =
		model.getRandomCellModel(row, col);

	// For ConwayModel, does not matter if
	// model initialized yet or not.  Will
	// still get back a random CellModel
	ASSERT_TRUE(cell_model.getState() != NULL);

	model.initialize();

	cell_model = model.getRandomCellModel(row, col);

	// Should still get back a random CellModel
	// after ConwayModel is initialized. 
	ASSERT_TRUE(cell_model.getState() != NULL);

	// For ConwayModel, the passed in row, col is not used
	// so does not matter if value is greater than the total
	// number of rows/columns the model was created with.

	cell_model = model.getRandomCellModel(rows + row, cols + col);

	// Should still get back a random CellModel
	// after ConwayModel is initialized. 
	ASSERT_TRUE(cell_model.getState() != NULL);
}

// Any live cell with fewer than two live neighbors dies, as if by under population.
TEST_F(ConwayTests, rule_1_no_live_neighbor)
{
	const unsigned int rows = 10;
	const unsigned int cols = 20;

	UINTVEC alive_rows { 5 };
	UINTVEC alive_cols { 5 };

	MockConwayModel model(rows, cols, alive_rows, alive_cols);
	model.initialize();
	model.printModel();

	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < cols; c++) {
			CellColor color = model.getColor(r, c);
			if (r == alive_rows[0] && c == alive_cols[0]) {
				ASSERT_EQ(color, model.getAliveColor());
				break;
			}
			else {
				ASSERT_EQ(color, model.getDeadColor());
				break;
			}
		}
	}

	model.printModel();
	model.runModel();
	model.printModel();

	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < cols; c++) {
			CellColor color = model.getColor(r, c);
			ASSERT_EQ(color, model.getDeadColor());
		}
	}
}

// Any live cell with fewer than two live neighbors dies, as if by under population.
TEST_F(ConwayTests, init_for_rule_1_one_live_neighbor)
{
	const unsigned int rows = 10;
	const unsigned int cols = 20;

	UINTVEC alive_rows{ 5, 6 };
	UINTVEC alive_cols{ 5, 5 };

	MockConwayModel model(rows, cols, alive_rows, alive_cols);

	model.initialize();
	model.printModel();

	ASSERT_TRUE(model.isInitializedAsExpected());

	model.printModel();
	model.runModel();
	model.printModel();


	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < cols; c++) {
			CellColor color = model.getColor(r, c);
			ASSERT_EQ(color, model.getDeadColor());
		}
	}
}

// Any live cell with two or three live neighbors lives on to the next generation.
// Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
TEST_F(ConwayTests, init_for_rule_2_two_live_neighbors)
{
	const unsigned int rows = 10;
	const unsigned int cols = 20;

	UINTVEC alive_rows{ 4, 5, 6 };
	UINTVEC alive_cols{ 4, 5, 6 };

	// @ - alive cell
	//   4 5 6   // 
	// 4 @       // 4,4 will die
	// 5   @     // 5,5 has 2 live neighbors, will remain alive
	// 6     @   // 6,6 will die

	MockConwayModel model(rows, cols, alive_rows, alive_cols);

	model.initialize();
	model.printModel();

	ASSERT_TRUE(model.isInitializedAsExpected());

	model.printModel();
	model.runModel();
	model.printModel();

	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < cols; c++) {
			CellColor color = model.getColor(r, c);
			if ((r == 5 && c == 5)) {
				ASSERT_EQ(color, model.getAliveColor());
			}
			else {
				ASSERT_EQ(color, model.getDeadColor());
			}
		}
	}
}

// Any live cell with two or three live neighbors lives on to the next generation.
// Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
TEST_F(ConwayTests, init_for_rules_2_4_two_live_neighbors)
{
	const unsigned int rows = 10;
	const unsigned int cols = 20;

	UINTVEC alive_rows{ 4, 5, 6 };
	UINTVEC alive_cols{ 4, 5, 5 };

	// @ - alive cell
	//   4 5    // + 5,4 will come alive due to fourth rule
	// 4 @      // 4,4 will die
	// 5 + @    // 5,5 has 2 live neighbors
	// 6   @    // 6,5 will die

	MockConwayModel model(rows, cols, alive_rows, alive_cols);

	model.initialize();
	model.printModel();

	ASSERT_TRUE(model.isInitializedAsExpected());

	model.printModel();
	model.runModel();
	model.printModel();

	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < cols; c++) {
			CellColor color = model.getColor(r, c);
			if( (r == 5 && c == 5) ||
				(r == 5 && c == 4)
			){
				ASSERT_EQ(color, model.getAliveColor());
			}
			else {
				ASSERT_EQ(color, model.getDeadColor());
			}
		}
	}
}

// Any live cell with two or three live neighbors lives on to the next generation.
// Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
TEST_F(ConwayTests, init_for_rules_3_4_four_live_neighbors)
{
	const unsigned int rows = 10;
	const unsigned int cols = 20;

	UINTVEC alive_rows{ 4, 4, 5, 6, 6 };
	UINTVEC alive_cols{ 4, 6, 5, 4, 6 };

	// @ - alive cell
	//   4 5 6   // + (4,5)(5,4)(5,6)(6,5) will come alive due to fourth rule
	// 4 @ + @   // all alive cells will die
	// 5 + @ +   // 
	// 6 @ + @   //

	MockConwayModel model(rows, cols, alive_rows, alive_cols);

	model.initialize();
	model.printModel();

	ASSERT_TRUE(model.isInitializedAsExpected());

	model.printModel();
	model.runModel();
	model.printModel();

	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < cols; c++) {
			CellColor color = model.getColor(r, c);
			if ((r == 4 && c == 5) ||
				(r == 5 && c == 4) ||
				(r == 5 && c == 6) ||
				(r == 6 && c == 5)
				) {
				ASSERT_EQ(color, model.getAliveColor());
			}
			else {
				ASSERT_EQ(color, model.getDeadColor());
			}
		}
	}

	// @ - alive cell
	//   4 5 6   // 
	// 4   @     // 
	// 5 @   @   // 
	// 6   @     //
	model.printModel();
	// Cell pattern is now such that no cells should die 
	// and none should come alive
	model.runModel();

	model.printModel();

	for (unsigned int r = 0; r < rows; r++) {
		for (unsigned int c = 0; c < cols; c++) {
			CellColor color = model.getColor(r, c);
			if ((r == 4 && c == 5) ||
				(r == 5 && c == 4) ||
				(r == 5 && c == 6) ||
				(r == 6 && c == 5)
				) {
				ASSERT_EQ(color, model.getAliveColor());
			}
			else {
				ASSERT_EQ(color, model.getDeadColor());
			}
		}
	}

}
