#include "efl/stock_data.hpp"

#include <iostream>

#include <gtest/gtest.h>

TEST(ohlc, ctor) {
    efl::ohlc_t d;

    EXPECT_EQ(0, d.open);
    EXPECT_EQ(0, d.low);
    EXPECT_EQ(0, d.high);
    EXPECT_EQ(0, d.close);
    EXPECT_EQ(0, d.volume);
    EXPECT_FALSE(d.date.ok());
}

TEST(stock_data, ctor) {
    std::map<date::year_month_day, efl::ohlc_t> m;
    efl::stock_data_t sd{"SGO.csv", m};

    EXPECT_EQ("SGO.csv", sd.get_filename());
    EXPECT_EQ(0, sd.get_data().size());

    efl::ohlc_t d = {45.12, 45.01, 45.99, 45.87, 256156, 
        date::year_month_day{date::year(2022), date::month(11), date::day(1)}
    };

    sd.add_ohlc(d);
    EXPECT_EQ(1, sd.get_data().size());
}


TEST(stock_data, varitation) {
    std::map<date::year_month_day, efl::ohlc_t> m;
    efl::stock_data_t sd{"SGO.csv", m};

    EXPECT_EQ("SGO.csv", sd.get_filename());
    EXPECT_EQ(0, sd.get_data().size());

    date::year_month_day d1 = date::year_month_day{date::year(2022), date::month(11), date::day(1)};
    efl::ohlc_t ohlc1 = {45.12, 45.01, 45.99, 45.87, 256156, d1 };
    sd.add_ohlc(ohlc1);
    EXPECT_EQ(1, sd.get_data().size());

    date::year_month_day d2 = date::year_month_day{date::year(2022), date::month(11), date::day(2)};
    efl::ohlc_t ohlc2 = {45.22, 45.21, 46.01, 46.07, 3248610, d2 };
    sd.add_ohlc(ohlc2);
    EXPECT_EQ(2, sd.get_data().size());

    date::year_month_day d3 = date::year_month_day{date::year(2022), date::month(11), date::day(3)};
    efl::ohlc_t ohlc3 = {45.12, 45.01, 45.99, 45.87, 256156, d3 };
    sd.add_ohlc(ohlc3);
    EXPECT_EQ(3, sd.get_data().size());

    EXPECT_EQ(0, sd.variation());

    date::year_month_day d4 = date::year_month_day{date::year(2022), date::month(11), date::day(30)};
    efl::ohlc_t ohlc4 = {90.24, 90.01, 92.99, 91.74, 556156, d4 };
    sd.add_ohlc(ohlc4);
    EXPECT_EQ(4, sd.get_data().size());

    EXPECT_EQ(1, sd.variation()); // +100% between 2022/11/1 and 2022/11/30 close
    EXPECT_DOUBLE_EQ(2, sd.price_change());
    EXPECT_EQ(d1, sd.start_period());
    EXPECT_EQ(d4, sd.end_period());
    EXPECT_DOUBLE_EQ(45.87, sd.start_period_price());
    EXPECT_DOUBLE_EQ(91.74, sd.end_period_price());

    // add data for a date between 11/1 and 11/30
    date::year_month_day d5 = date::year_month_day{date::year(2022), date::month(11), date::day(15)};
    efl::ohlc_t ohlc5 = {70.24, 70.01, 72.99, 71.74, 556156, d5 };
    sd.add_ohlc(ohlc5);
    EXPECT_EQ(5, sd.get_data().size());

    EXPECT_EQ(1, sd.variation()); // still +100% between 2022/11/1 and 2022/11/30 close
    EXPECT_DOUBLE_EQ(2, sd.price_change());
    EXPECT_EQ(d1, sd.start_period());
    EXPECT_EQ(d4, sd.end_period());
    EXPECT_DOUBLE_EQ(45.87, sd.start_period_price());
    EXPECT_DOUBLE_EQ(91.74, sd.end_period_price());


}

