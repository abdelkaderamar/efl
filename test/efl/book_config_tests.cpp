#include "efl/book_config.hpp"

#include <gtest/gtest.h>

TEST(book_config, ctor) {
    efl::book_config_t cfg;

    EXPECT_EQ(0, cfg.total_amount);
    EXPECT_EQ(0, cfg.order_amount);
    EXPECT_EQ(0, cfg.delta_buy);
    EXPECT_EQ(0, cfg.delta_sell);
    EXPECT_EQ(0, cfg.fees);
    EXPECT_EQ(0, cfg.tax);
}

TEST(book_config, to_csv) {
    {
        efl::book_config_t cfg;
        EXPECT_EQ("0,0,0,0,0", cfg.to_csv());
    }
    {
        efl::book_config_t cfg { .total_amount = 1000, .order_amount = 100, .delta_buy = 2, .delta_sell = 3,
            .fees = 0.99, .tax  = 0.03, };

        EXPECT_EQ("1000,100,2,3,0", cfg.to_csv());

    }
}

TEST(book_config, to_string) {
    efl::book_config_t cfg;


    EXPECT_EQ("Total Amount = 0, Order Amount = 0, Buy Delta = 0, Sell Delta = 0, Empty book duration = 0",
        cfg.to_string());
}