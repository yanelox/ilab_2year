#include <gtest/gtest.h>
#include "../lib/tree.hpp"

class TestTree_ : public ::testing::Test
{
    protected:

    void SetUp() override
    {
        for (int i = 0; i < 100; ++i)
        {
            t.push (i);
            t_.push (i);
        }
    }

    tree::Tree_ t{};
    tree::Tree_ t_{};
};

TEST_F (TestTree_, Operator_equal)
{
    EXPECT_EQ (t, t_);
}

TEST_F (TestTree_, CopyConstruct)
{
    tree::Tree_ t1 {t};

    EXPECT_EQ (t, t1);
}

TEST_F (TestTree_, Operator_assignment)
{
    tree::Tree_ t1{};

    t1 = t;

    EXPECT_EQ (t, t1);
}
