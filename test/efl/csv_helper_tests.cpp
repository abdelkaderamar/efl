#include "efl/csv_helper.hpp"

#include <gtest/gtest.h>

TEST(csv_helper, book_to_csv) {
    efl::book_config_t cfg { .total_amount = 1000, };
    efl::book_t b{cfg};
    auto s = efl::csv_helper::to_csv(b, 2.5);

    EXPECT_EQ("1000,0,0,0,0,0", s);
}