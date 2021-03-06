/**
* @file tests/llvmir2hll/optimizer/optimizers/remove_all_casts_optimizer_tests.cpp
* @brief Tests for the @c remove_all_casts_optimizer module.
* @copyright (c) 2017 Avast Software, licensed under the MIT license
*/

#include <gtest/gtest.h>

#include "llvmir2hll/ir/empty_stmt.h"
#include "llvmir2hll/ir/tests_with_module.h"
#include "llvmir2hll/optimizer/optimizers/remove_all_casts_optimizer.h"

using namespace ::testing;

namespace llvmir2hll {
namespace tests {

/**
* @brief Tests for the @c remove_all_casts_optimizer module.
*/
class RemoveAllCastsOptimizerTests: public TestsWithModule {};

TEST_F(RemoveAllCastsOptimizerTests,
OptimizerHasNonEmptyID) {
	ShPtr<RemoveAllCastsOptimizer> optimizer(
		new RemoveAllCastsOptimizer(module));

	EXPECT_TRUE(!optimizer->getId().empty()) <<
		"the optimizer should have a non-empty ID";
}

TEST_F(RemoveAllCastsOptimizerTests,
InEmptyBodyThereIsNothingToOptimize) {
	// Optimize the module.
	Optimizer::optimize<RemoveAllCastsOptimizer>(module);

	// Check that the output is correct.
	ASSERT_TRUE(isa<EmptyStmt>(testFunc->getBody())) <<
		"expected EmptyStmt, got " << testFunc->getBody();
	EXPECT_TRUE(!testFunc->getBody()->hasSuccessor()) <<
		"expected no successors of the statement, but got " <<
		testFunc->getBody()->getSuccessor();
}

} // namespace tests
} // namespace llvmir2hll
