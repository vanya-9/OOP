#include <gtest/gtest.h>
#include <iostream>
#include "CircularBuffer.h"

TEST(CircularBufferTest, DefaultConstructor) {
  CircularBuffer buffer;
  ASSERT_EQ(buffer.size(), 0);
  ASSERT_EQ(buffer.capacity(), default_size);
  ASSERT_TRUE(buffer.empty());
  ASSERT_EQ(buffer.front(), '\0');
  ASSERT_EQ(buffer.back(), '\0');
}

TEST(CircularBufferTest, ConstructorWithCapacity) {
  CircularBuffer buffer(10);
  ASSERT_EQ(buffer.size(), 0);
  ASSERT_EQ(buffer.capacity(), 10);
  ASSERT_TRUE(buffer.empty());
  ASSERT_EQ(buffer.front(), '\0');
  ASSERT_EQ(buffer.back(), '\0');
}

TEST(CircularBufferTest, ConstructorWithFill) {
  CircularBuffer buffer(5, 'a');
  ASSERT_EQ(buffer.size(), 5);
  ASSERT_EQ(buffer.capacity(), 5);
  ASSERT_FALSE(buffer.empty());
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(buffer[i], 'a');
  }
  ASSERT_EQ(buffer.front(), 'a');
  ASSERT_EQ(buffer.back(), 'a');
}

TEST(CircularBufferTest, CopyConstructor) {
  CircularBuffer buffer(5, 'a');
  buffer.push_back('x');
  buffer.push_back('y');
  buffer.push_back('z');
  CircularBuffer buffer_two(buffer);
  ASSERT_EQ(buffer_two.size(), buffer.size());
  ASSERT_EQ(buffer_two.capacity(), buffer.capacity());
  for (int i = 0; i < buffer.size(); ++i) {
    ASSERT_EQ(buffer_two[i], buffer[i]);
  }
  ASSERT_EQ(buffer_two.front(), buffer.front());
  ASSERT_EQ(buffer_two.back(), buffer.back());
  ASSERT_EQ(buffer_two.size(), buffer.size());
  ASSERT_EQ(buffer_two.capacity(), buffer.capacity());
  ASSERT_EQ(buffer_two.front(), 'a');
  ASSERT_EQ(buffer_two.back(), 'z');
}

TEST(CircularBufferTest, OperatorGetByIndex) {
  CircularBuffer buffer(5, 'a');
  buffer.push_back('x');
  buffer.push_back('y');
  buffer.push_back('z');
  buffer.push_back('n');
  buffer.push_back('r');
  buffer.push_back('l');
  ASSERT_EQ(buffer[0], 'y');
  ASSERT_EQ(buffer[1], 'z');
  ASSERT_EQ(buffer[2], 'n');
  ASSERT_EQ(buffer[3], 'r');
  ASSERT_EQ(buffer[4], 'l');
}

TEST(CircularBufferTest, OperatorAt) {
  CircularBuffer buffer(5, 'a');
  buffer.push_back('x');
  buffer.push_back('y');
  buffer.push_back('z');
  buffer.push_back('n');
  buffer.push_back('r');
  buffer.push_back('l');
  ASSERT_EQ(buffer[0], 'y');
  ASSERT_EQ(buffer[1], 'z');
  ASSERT_EQ(buffer[2], 'n');
  ASSERT_EQ(buffer[3], 'r');
  ASSERT_EQ(buffer[4], 'l');
  ASSERT_THROW(buffer.at(5), std::invalid_argument);
  ASSERT_THROW(buffer.at(-1), std::invalid_argument);
  ASSERT_THROW(buffer.at(30), std::invalid_argument);
}

TEST(CircularBufferTest, FrontOnEmptyBuffer) {
  CircularBuffer buffer;
  ASSERT_EQ(buffer.front(), '\0');
}

TEST(CircularBufferTest, FrontOnFullBuffer) {
  CircularBuffer buffer(3);
  buffer.push_back('A');
  buffer.push_back('B');
  buffer.push_back('C');
  ASSERT_EQ(buffer.front(), 'A');
  buffer.push_back('D');
  ASSERT_EQ(buffer.front(), 'B');
}

TEST(CircularBufferTest, FrontAfterPushFront) {
  CircularBuffer buffer(3);
  buffer.push_back('B');
  buffer.push_back('C');
  buffer.push_front('A');
  ASSERT_EQ(buffer.front(), 'A');
  buffer.push_front('D');
  ASSERT_EQ(buffer.at(0), 'D');
  ASSERT_EQ(buffer.front(), 'D');
}

TEST(CircularBufferTest, BackInEmptyBuffer) {
  CircularBuffer cb(5);
  ASSERT_EQ(cb.size(), 0);
  ASSERT_EQ(cb.back(), '\0');
}

TEST(CircularBufferTest, BackAfterOverflow) {
  CircularBuffer cb(3);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');
  cb.push_back('D');

  ASSERT_EQ(cb.back(), 'D');
  ASSERT_EQ(cb.size(), 3);
}

TEST(CircularBufferTest, BackAfterPopBack) {
  CircularBuffer cb(3);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');

  cb.pop_back();
  ASSERT_EQ(cb.back(), 'B');
  ASSERT_EQ(cb.size(), 2);
}

TEST(CircularBufferTest, SizeOfEmptyBuffer) {
  CircularBuffer cb(5);
  ASSERT_EQ(cb.size(), 0);
}

TEST(CircularBufferTest, SizeAfterPushingElements) {
  CircularBuffer cb(5);
  cb.push_back('A');
  ASSERT_EQ(cb.size(), 1);

  cb.push_back('B');
  ASSERT_EQ(cb.size(), 2);

  cb.push_back('C');
  ASSERT_EQ(cb.size(), 3);
}

TEST(CircularBufferTest, SizeAfterOverflow) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');
  cb.push_back('D');
  cb.push_back('E');

  cb.push_back('F');

  ASSERT_EQ(cb.size(), 5);
}

TEST(CircularBufferTest, SizeAfterPopBack) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');
  cb.pop_back();

  ASSERT_EQ(cb.size(), 2);
}

TEST(CircularBufferTest, SizeAfterPopFront) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');
  cb.pop_front();

  ASSERT_EQ(cb.size(), 2);
}

TEST(CircularBufferTest, SizeAfterClearing) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  cb.clear();

  ASSERT_EQ(cb.size(), 0);
}

TEST(NotEmptyAfterMultiplePushBacksTest, AfterAddingMultipleElements) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  ASSERT_FALSE(cb.empty());
}

TEST(EmptyAfterPopTest, AfterRemovingElement) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.pop_front();
  ASSERT_TRUE(cb.empty());
}

TEST(FullBufferTest, NewlyCreatedBuffer) {
  CircularBuffer cb(5);
  ASSERT_FALSE(cb.full());
}

TEST(FullBufferTest, AfterOverflow) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');
  cb.push_back('D');
  cb.push_back('E');
  cb.push_back('F');
  ASSERT_TRUE(cb.full());
}

TEST(FullBufferTest, AfterClear) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');
  cb.push_back('D');
  cb.push_back('E');
  cb.clear();
  ASSERT_FALSE(cb.full());
}

TEST(ReserveBufferTest, NewlyCreatedBuffer) {
  CircularBuffer cb(5);
  ASSERT_EQ(cb.reserve(), 5);
}

TEST(ReserveBufferTest, AfterPushingMultipleElements) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');
  ASSERT_EQ(cb.reserve(), 2);
}

TEST(ReserveBufferTest, AfterFillingBuffer) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');
  cb.push_back('D');
  cb.push_back('E');
  ASSERT_EQ(cb.reserve(), 0);
}

TEST(CapacityBufferTest, DefaultCapacity) {
  CircularBuffer cb;
  ASSERT_EQ(cb.capacity(), 4);
}

TEST(CapacityBufferTest, CustomCapacity) {
  CircularBuffer cb(10);
  ASSERT_EQ(cb.capacity(), 10);
}

TEST(CapacityBufferTest, CapacityAfterResize) {
  CircularBuffer cb(5);
  cb.resize(15);
  ASSERT_EQ(cb.capacity(), 15);
}

TEST(SetCapacityTest, ReduceCapacity) {
  CircularBuffer cb(10);
  cb.push_back('A');
  cb.push_back('B');
  cb.set_capacity(5);
  ASSERT_EQ(cb.capacity(), 5);
  ASSERT_EQ(cb.size(), 2);
}

TEST(SetCapacityTest, ClearAfterSetCapacity) {
  CircularBuffer cb(10);
  cb.push_back('A');
  cb.set_capacity(5);
  cb.clear();
  ASSERT_EQ(cb.capacity(), 5);
  ASSERT_EQ(cb.size(), 0);
}

TEST(ResizeTest, ResizeToLargerSize) {
  CircularBuffer cb(3);
  cb.push_back('A');
  cb.push_back('B');
  cb.resize(5, 'C');

  ASSERT_EQ(cb.size(), 2);
  ASSERT_EQ(cb.capacity(), 5);
  ASSERT_EQ(cb[2], 'C');
  ASSERT_EQ(cb[3], 'C');
  ASSERT_EQ(cb[4], 'C');
}

TEST(ResizeTest, ResizeToSameSize) {
  CircularBuffer cb(4);
  cb.push_back('A');
  cb.push_back('B');
  cb.resize(4);
  ASSERT_EQ(cb.size(), 2);
  ASSERT_EQ(cb.capacity(), 4);
}

TEST(ResizeTest, ResizeToZero) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.resize(0);

  ASSERT_EQ(cb.size(), 0);
  ASSERT_EQ(cb.capacity(), 0);
}

TEST(ResizeTest, ResizeWithDefaultItem) {
  CircularBuffer cb(3);
  cb.push_back('A');
  cb.resize(5);
  ASSERT_EQ(cb.capacity(), 5);
  ASSERT_EQ(cb[1], '\0');
  ASSERT_EQ(cb[2], '\0');
}

TEST(CircularBufferAssignmentTest, SelfAssignment) {
  CircularBuffer cb1(5);
  cb1.push_back(1);
  cb1.push_back(2);

  cb1 = cb1;

  EXPECT_EQ(cb1.size(), 2);
  EXPECT_EQ(cb1.front(), 1);
  EXPECT_EQ(cb1.back(), 2);
}

TEST(CircularBufferAssignmentTest, AssignmentToEmptyBuffer) {
  CircularBuffer cb1(5);
  CircularBuffer cb2(3);

  cb1.push_back(1);
  cb1.push_back(2);

  cb2 = cb1;

  EXPECT_EQ(cb2.size(), 2);
  EXPECT_EQ(cb2.front(), 1);
  EXPECT_EQ(cb2.back(), 2);
}

TEST(CircularBufferAssignmentTest, AssignmentWithDifferentSizes) {
  CircularBuffer cb1(5);
  CircularBuffer cb2(3);

  cb1.push_back(1);
  cb1.push_back(2);
  cb1.push_back(3);

  cb2 = cb1;

  EXPECT_EQ(cb2.size(), 3);
  EXPECT_EQ(cb2.front(), 1);
  EXPECT_EQ(cb2.back(), 3);
}

TEST(CircularBufferAssignmentTest, AssignmentToLargerBuffer) {
  CircularBuffer cb1(3);
  CircularBuffer cb2(5);

  cb1.push_back(1);
  cb1.push_back(2);

  cb2 = cb1;

  EXPECT_EQ(cb2.size(), 2);
  EXPECT_EQ(cb2.front(), 1);
  EXPECT_EQ(cb2.back(), 2);
}

TEST(CircularBufferSwapTest, SwapEmptyBuffers) {
  CircularBuffer cb1(5);
  CircularBuffer cb2(5);

  cb1.swap(cb2); 

  EXPECT_TRUE(cb1.empty());
  EXPECT_TRUE(cb2.empty());
}

TEST(CircularBufferSwapTest, SwapEmptyAndNonEmptyBuffer) {
  CircularBuffer cb1(5);
  CircularBuffer cb2(5);

  cb2.push_back(1);
  cb2.push_back(2);

  cb1.swap(cb2);

  EXPECT_TRUE(cb2.empty());
  EXPECT_EQ(cb1.size(), 2);
  EXPECT_EQ(cb1.front(), 1);
  EXPECT_EQ(cb1.back(), 2);
}

TEST(CircularBufferSwapTest, SwapWithDifferentSizes) {
  CircularBuffer cb1(5);
  CircularBuffer cb2(3);

  cb1.push_back(1);
  cb1.push_back(2);
  cb1.push_back(3);

  cb2.push_back(4);

  cb1.swap(cb2);

  EXPECT_EQ(cb1.size(), 1);
  EXPECT_EQ(cb1.front(), 4);

  EXPECT_EQ(cb2.size(), 3);
  EXPECT_EQ(cb2.front(), 1);
  EXPECT_EQ(cb2.back(), 3);
}

TEST(CircularBufferPushBackTest, PushBackToEmptyBuffer) {
  CircularBuffer cb(5);
  cb.push_back(10);

  EXPECT_EQ(cb.size(), 1);
  EXPECT_EQ(cb.front(), 10);
  EXPECT_EQ(cb.back(), 10);
  EXPECT_FALSE(cb.empty());
}

TEST(CircularBufferPushBackTest, PushBackToNonEmptyBuffer) {
  CircularBuffer cb(5);
  cb.push_back(1);
  cb.push_back(2);

  EXPECT_EQ(cb.size(), 2);
  EXPECT_EQ(cb.front(), 1);
  EXPECT_EQ(cb.back(), 2);
}

TEST(CircularBufferPushBackTest, PushBackToFullBufferMultipleTimes) {
  CircularBuffer cb(2);
  cb.push_back(1);
  cb.push_back(2);
  EXPECT_EQ(cb.size(), 2);
  EXPECT_EQ(cb.front(), 1);
  EXPECT_EQ(cb.back(), 2);
  cb.push_back(3);
  EXPECT_EQ(cb.size(), 2);
  EXPECT_EQ(cb.front(), 2);
  EXPECT_EQ(cb.back(), 3);
  cb.push_back(4);
  EXPECT_EQ(cb.size(), 2);
  EXPECT_EQ(cb.front(), 3);
  EXPECT_EQ(cb.back(), 4);
}

TEST(CircularBufferPushFrontTest, PushFrontToEmptyBuffer) {
  CircularBuffer cb(5);
  cb.push_front(10);

  EXPECT_EQ(cb.size(), 1);
  EXPECT_EQ(cb.front(), 10);
  EXPECT_EQ(cb.back(), 10);
  EXPECT_FALSE(cb.empty());
}

TEST(CircularBufferPushFrontTest, PushFrontWhenBufferIsNotFull) {
  CircularBuffer cb(5);
  cb.push_back(1);
  cb.push_back(2);
  cb.push_front(0);

  EXPECT_EQ(cb.size(), 3);
  EXPECT_EQ(cb.front(), 0);
  EXPECT_EQ(cb.back(), 2);
}

TEST(CircularBufferPushFrontTest, PushFrontWhenBufferIsFull) {
  CircularBuffer cb(3);
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);
  EXPECT_EQ(cb.size(), 3);
  cb.push_front('k');

  EXPECT_EQ(cb.size(), 3);
  EXPECT_EQ(cb.front(), 'k');
  EXPECT_EQ(cb.back(), 2);
}

TEST(CircularBufferPopBackTest, PopBackFromMultipleElements) {
  CircularBuffer cb(5);
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);

  EXPECT_EQ(cb.size(), 3);
  cb.pop_back();
  EXPECT_EQ(cb.size(), 2);
  EXPECT_EQ(cb.back(), 2);
}

TEST(CircularBufferPopBackTest, PopBackInFullBuffer) {
  CircularBuffer cb(3);
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);

  EXPECT_EQ(cb.size(), 3);
  cb.pop_back();
  EXPECT_EQ(cb.size(), 2);
  EXPECT_EQ(cb.back(), 2);
}

TEST(CircularBufferPopBackTest, PopBackMultipleTimes) {
  CircularBuffer cb(5);
  cb.push_back(1);
  cb.push_back(2);
  cb.push_back(3);

  cb.pop_back();
  EXPECT_EQ(cb.size(), 2);
  cb.pop_back();
  EXPECT_EQ(cb.size(), 1);
  cb.pop_back();
  EXPECT_EQ(cb.size(), 0);
  EXPECT_TRUE(cb.empty());
}

TEST(CircularBufferPopBackTest, PopBackFromEmptyBuffer) {
  CircularBuffer cb(5);
  ASSERT_THROW(cb.pop_back(), std::invalid_argument);
  EXPECT_TRUE(cb.empty());
}

TEST(CircularBufferTest, popFrontFromSingleElementBuffer) {
  CircularBuffer cb;
  cb.push_back('A');
  cb.pop_front();
  ASSERT_TRUE(cb.empty());
  ASSERT_THROW(cb.pop_front(), std::invalid_argument);
}

TEST(CircularBufferTest, popFrontOnFullBuffer) {
  CircularBuffer cb(3);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');

  cb.pop_front();
  ASSERT_EQ(cb.front(), 'B');
  ASSERT_EQ(cb.size(), 2);
}

TEST(CircularBufferTest, InsertIntoEmptyBuffer) {
  CircularBuffer cb;
  cb.insert(0, 'A');
  ASSERT_EQ(cb.front(), 'A');
  ASSERT_EQ(cb.size(), 1);
}

TEST(CircularBufferTest, InsertAtLastPosition) {
  CircularBuffer cb;
  cb.push_back('A');
  cb.insert(1, 'B');
  ASSERT_EQ(cb.back(), 'B');
  ASSERT_EQ(cb.size(), 2);
  ASSERT_THROW(cb.insert(5, 'C'), std::invalid_argument);
  ASSERT_THROW(cb.insert(-1, 'B'), std::invalid_argument);
}

TEST(CircularBufferTest, InsertInFullBuffer) {
  CircularBuffer cb(2);
  cb.push_back('A');
  cb.push_back('B');

  cb.insert(0, 'C');
  ASSERT_EQ(cb.front(), 'C');
  ASSERT_EQ(cb.size(), 2);
}

#include <gtest/gtest.h>
#include "CircularBuffer.h"

TEST(EraseTest, EraseMiddleElements) {
  CircularBuffer buffer;
  buffer.push_back('a');
  buffer.push_back('b');
  buffer.push_back('c');
  buffer.push_back('d');

  buffer.erase(1, 3);
  EXPECT_EQ(buffer.size(), 2);
  EXPECT_EQ(buffer.front(), 'a');
  EXPECT_EQ(buffer.back(), 'd');
}

TEST(EraseTest, EraseAllElements) {
  CircularBuffer buffer;
  buffer.push_back('a');
  buffer.push_back('b');
  buffer.push_back('c');
  buffer.push_back('d');

  buffer.erase(0, 4);
  EXPECT_EQ(buffer.size(), 0);
}

TEST(EraseTest, EraseInvalidRange) {
  CircularBuffer buffer;
  buffer.push_back('a');
  buffer.push_back('b');
  buffer.push_back('c');
  buffer.push_back('d');

  EXPECT_THROW(buffer.erase(2, 1), std::invalid_argument);
  EXPECT_THROW(buffer.erase(-1, 2), std::invalid_argument);
  EXPECT_THROW(buffer.erase(0, 5), std::invalid_argument);
}

TEST(EraseTest, EraseAllFromMiddleWhenHeadNotZero) {
  CircularBuffer buffer(4);
  buffer.push_back('a');
  buffer.push_back('b');
  buffer.push_back('c');
  buffer.push_back('d');

  buffer.pop_front();
  buffer.pop_front();
  buffer.erase(0, 2);
  EXPECT_EQ(buffer.size(), 0);
}

TEST(EraseTest, EraseMiddleElementsWithHeadNotZero) {
  CircularBuffer buffer(7);
  buffer.push_back('a');
  buffer.push_back('b');
  buffer.push_back('c');
  buffer.push_back('d');
  buffer.push_back('e');
  buffer.push_back('f');
  buffer.push_back('g');

  buffer.pop_front();
  buffer.pop_front();

  buffer.erase(0, 3);

  EXPECT_EQ(buffer.size(), 2);
  EXPECT_EQ(buffer.front(), 'f');
  EXPECT_EQ(buffer.back(), 'g');
}

TEST(CircularBufferTest, ClearNonEmptyBuffer) {
  CircularBuffer cb(5);
  cb.push_back('A');
  cb.push_back('B');
  cb.push_back('C');

  cb.clear();

  ASSERT_EQ(cb.size(), 0);
  ASSERT_TRUE(cb.empty());
  cb.clear();
  ASSERT_TRUE(cb.empty());
}

TEST(CircularBufferTest, NotEqualBuffersWithDifferentContent) {
  CircularBuffer cb1(5);
  CircularBuffer cb2(5);

  cb1.push_back('A');
  cb1.push_back('B');
  cb1.push_back('C');

  cb2.push_back('X');
  cb2.push_back('Y');
  cb2.push_back('Z');

  ASSERT_FALSE(cb1 == cb2);
  ASSERT_TRUE(cb1 != cb2);
}

TEST(CircularBufferTest, NotEqualBuffersWithDifferentCapacity) {
  CircularBuffer cb1(3);
  CircularBuffer cb2(5);

  ASSERT_FALSE(cb1 == cb2);
  ASSERT_TRUE(cb1 != cb2);
}

TEST(CircularBufferTest, NotEqualBuffersWithDifferentSizes) {
  CircularBuffer cb1(5);
  CircularBuffer cb2(5);

  cb1.push_back('A');
  cb1.push_back('B');
  cb1.push_back('C');

  cb2.push_back('A');
  cb2.push_back('B');

  ASSERT_FALSE(cb1 == cb2);
  ASSERT_TRUE(cb1 != cb2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}