#include <gtest/gtest.h>
#include "hello2.h"

TEST(test_parse, len) {
  ASSERT_EQ(len(), 5);
}