#include <gtest/gtest.h>
#include <vector>
#include "../lib/matrix.hpp"

//row tests

class Test_row_ : public ::testing::Test
{
    protected:

    void SetUp() override
    {
        for (int i = 0; i < 100; ++i)
            v.push_back (rand () % 500 - 250);

        r1 = new matrix::row_ <int> {v.begin(), v.end(), 100};
    }

    std::vector <int> v{};

    matrix::row_ <int> *r1;
};

TEST_F (Test_row_, Operator_equal)
{
    EXPECT_EQ (*r1, *r1);
}

TEST_F (Test_row_, Operator_assignment)
{
    matrix::row_ <int> r2{};

    r2 = *r1;

    EXPECT_EQ (*r1, r2);
}

TEST_F (Test_row_, CopyConstruct)
{
    matrix::row_ <int> r2{*r1};

    EXPECT_EQ (*r1, r2);
}

TEST_F (Test_row_, MoveConstruct)
{
    matrix::row_ <int> r3 {*r1};
    matrix::row_ <int> r2 = std::move (*r1);

    EXPECT_EQ (r2, r3);    
}

TEST_F (Test_row_, MoveAssignment)
{
    matrix::row_ <int> r2 {*r1};
    matrix::row_ <int> r3 {};

    r3 = std::move (*r1);

    EXPECT_EQ (r2, r3);
}

//matrix tests

class Test_matrix_ : public ::testing::Test
{
    protected:

    void SetUp() override
    {
        for (int i = 0; i < 100; ++i)
            v.push_back (rand () % 500 - 250);

        m1 = new matrix::matrix_ <int> {v.begin(), v.end(), 10};
    }

    std::vector <int> v{};

    matrix::matrix_ <int> *m1;
};

TEST_F (Test_matrix_, Operator_equal)
{
    EXPECT_EQ (*m1, *m1);
}

TEST_F (Test_matrix_, Operator_assignment)
{
    matrix::matrix_ <int> m2{};

    m2 = *m1;

    EXPECT_EQ (*m1, m2);
}

TEST_F (Test_matrix_, CopyConstruct)
{
    matrix::matrix_ <int> m2{*m1};

    EXPECT_EQ (*m1, m2);
}

TEST_F (Test_matrix_, MoveConstruct)
{
    matrix::matrix_ <int> m3 {*m1};
    matrix::matrix_ <int> m2 = std::move (*m1);

    EXPECT_EQ (m2, m3);    
}

TEST_F (Test_matrix_, MoveAssignment)
{
    matrix::matrix_ <int> m2 {*m1};
    matrix::matrix_ <int> m3 {};

    m3 = std::move (*m1);

    EXPECT_EQ (m2, m3);
}