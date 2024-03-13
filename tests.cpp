#include "stack.h"
#include "cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest.h"

TEST(Stack_initialization_push_and_top, int) {
    st::stack<int> a;
    a.push(192);
    EXPECT_EQ(a.top(), 192);
}

TEST(Stack_initialization_push_and_top, float) {
    st::stack<float> a;
    a.push(192.192);
    EXPECT_EQ(a.top(), 192.192f);
}

TEST(top, top1) {
    st::stack<int> a;
    a.push(192);
    a.push(123);
    EXPECT_EQ(a.top(), 123);
}

TEST(pop, pop1) {
    st::stack<int> a;
    a.push(192);
    a.push(123);
    a.pop();
    EXPECT_EQ(a.top(), 192);
}

TEST(empty, empty1) {
    st::stack<int> a;
    EXPECT_EQ(a.empty(), true);
}

TEST(empty, empty2) {
    st::stack<int> a;
    a.push(192);
    EXPECT_EQ(a.empty(), false);
}

TEST(copy, copy1) {
    st::stack<int> a;
    a.push(192);
    st::stack<int> b = a;
    EXPECT_EQ(b.top(), 192);
}

TEST(copy_as, copy_as1) {
    st::stack<int> a;
    a.push(192);
    st::stack<int> b;
    b = a;
    EXPECT_EQ(b.top(), 192);
}

TEST(move, move1) {
    st::stack<int> a;
    a.push(192);
    st::stack<int> b = std::move(a);
    EXPECT_EQ(a.empty(), true);
}

TEST(move_as, move_as1) {
    st::stack<int> a;
    a.push(192);
    st::stack<int> b;
    b = std::move(a);
    EXPECT_EQ(a.empty(), true);
}