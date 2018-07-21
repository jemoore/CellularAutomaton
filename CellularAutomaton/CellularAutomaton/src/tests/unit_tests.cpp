#include <string>
#include "ConwayModel.h"

#include <gtest/gtest.h>

class ConwayTests : public ::testing::Test
{
};

TEST_F(ConwayTests, simple )
{
	const unsigned int rows = 10;
	const unsigned int cols = 20;
	jem_models::ConwayModel model(rows, cols);

	EXPECT_EQ(model.getRowCount(), rows);
	EXPECT_EQ(model.getColumnCount(), cols);

}
