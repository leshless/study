#include <gtest/gtest.h>
#include "queue.hpp"  
using namespace queue;

class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(QueueTest, IsInitiallyEmpty) {
    auto queue = Queue();
    EXPECT_TRUE(queue.IsEmpty());
    EXPECT_EQ(queue.Size(), 0);
}

TEST_F(QueueTest, PushIncreasesSize) {
    auto queue = Queue();
    queue.Push(10);
    EXPECT_FALSE(queue.IsEmpty());
    EXPECT_EQ(queue.Size(), 1);
}

TEST_F(QueueTest, PopReturnsCorrectValue) {
    auto queue = Queue();
    queue.Push(42);
    queue.Push(24);
    
    EXPECT_EQ(queue.Pop(), 42);
    EXPECT_EQ(queue.Size(), 1);
    EXPECT_EQ(queue.Pop(), 24);
    EXPECT_TRUE(queue.IsEmpty());
}

TEST_F(QueueTest, FirstReturnsFirstElement) {
    auto queue = Queue();
    queue.Push(100);
    queue.Push(200);
    
    EXPECT_EQ(queue.First(), 100);
    queue.Pop();
    EXPECT_EQ(queue.First(), 200);
}

TEST_F(QueueTest, LastReturnsLastElement) {
    auto queue = Queue();
    queue.Push(100);
    queue.Push(200);
    queue.Push(300);
    
    EXPECT_EQ(queue.Last(), 300);
    queue.Pop();
    EXPECT_EQ(queue.Last(), 300);
}

TEST_F(QueueTest, MinReturnsCorrectMinimum) {
    auto queue = Queue();
    queue.Push(5);
    queue.Push(3);
    queue.Push(7);
    queue.Push(2);
    queue.Push(8);
    
    EXPECT_EQ(queue.Min(), 2);
    queue.Pop();     EXPECT_EQ(queue.Min(), 2);
    queue.Pop();     EXPECT_EQ(queue.Min(), 2);
    queue.Pop();     EXPECT_EQ(queue.Min(), 2);
    queue.Pop();     EXPECT_EQ(queue.Min(), 8);
}

TEST_F(QueueTest, MinWithNegativeNumbers) {
    auto queue = Queue();
    queue.Push(-5);
    queue.Push(10);
    queue.Push(-3);
    queue.Push(7);
    
    EXPECT_EQ(queue.Min(), -5);
    queue.Pop();     EXPECT_EQ(queue.Min(), -3);
}

TEST_F(QueueTest, MinWithSameValues) {
    auto queue = Queue();
    queue.Push(5);
    queue.Push(5);
    queue.Push(5);
    
    EXPECT_EQ(queue.Min(), 5);
    queue.Pop();
    EXPECT_EQ(queue.Min(), 5);
}

TEST_F(QueueTest, MinWithSingleElement) {
    auto queue = Queue();
    queue.Push(42);
    
    EXPECT_EQ(queue.Min(), 42);
}

TEST_F(QueueTest, MinAfterMultipleOperations) {
    auto queue = Queue();
    queue.Push(10);
    queue.Push(5);
    queue.Push(15);
    queue.Push(3);
    
    EXPECT_EQ(queue.Min(), 3);
    queue.Pop();     EXPECT_EQ(queue.Min(), 3);
    queue.Pop();     EXPECT_EQ(queue.Min(), 3);
    queue.Pop();     EXPECT_EQ(queue.Min(), 3);
    queue.Pop();     EXPECT_TRUE(queue.IsEmpty());
}

TEST_F(QueueTest, PopOnEmptyQueueThrows) {
    auto queue = Queue();
    EXPECT_THROW(queue.Pop(), std::exception);
}

TEST_F(QueueTest, FirstOnEmptyQueueThrows) {
    auto queue = Queue();
    EXPECT_THROW(queue.First(), std::exception);
}

TEST_F(QueueTest, LastOnEmptyQueueThrows) {
    auto queue = Queue();
    EXPECT_THROW(queue.Last(), std::exception);
}

TEST_F(QueueTest, MinOnEmptyQueueThrows) {
    auto queue = Queue();
    EXPECT_THROW(queue.Min(), std::exception);
}

TEST_F(QueueTest, ComplexOperationSequence) {
    auto queue = Queue();
    
    queue.Push(10);
    queue.Push(5);
    queue.Push(8);
    queue.Push(3);
    
    EXPECT_EQ(queue.Size(), 4);
    EXPECT_EQ(queue.Min(), 3);
    EXPECT_EQ(queue.First(), 10);
    EXPECT_EQ(queue.Last(), 3);
    
    EXPECT_EQ(queue.Pop(), 10);
    EXPECT_EQ(queue.Size(), 3);
    EXPECT_EQ(queue.Min(), 3);
    EXPECT_EQ(queue.First(), 5);
    
    queue.Push(2);
    queue.Push(7);
    
    EXPECT_EQ(queue.Size(), 5);
    EXPECT_EQ(queue.Min(), 2);
    EXPECT_EQ(queue.Last(), 7);
    
    EXPECT_EQ(queue.Pop(), 5);
    EXPECT_EQ(queue.Pop(), 8);
    EXPECT_EQ(queue.Pop(), 3);
    EXPECT_EQ(queue.Pop(), 2);
    EXPECT_EQ(queue.Pop(), 7);
    
    EXPECT_TRUE(queue.IsEmpty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}