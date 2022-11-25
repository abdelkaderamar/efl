#include <gtest/gtest.h>

#include "efl/book.hpp"

efl::book_config_t get_book_config() {
    efl::book_config_t config;
    config.total_amount = 10000;
    config.order_amount = 500;
    config.delta_buy = 5;
    config.delta_sell = 5;
    config.fees = 0.99;
    config.tax = 0.03;
    config.empty_book_duration = 0;
    return config;
}

TEST(book_row_tests, ctor)
{
    efl::book_row_t r;
    EXPECT_EQ(0, r.price);
    EXPECT_EQ(0, r.qty);
    EXPECT_FALSE(r.date.ok());
}

TEST(book_row_tests, comparison) {
    efl::book_row_t r1, r2;
    r1.price = 1.1;
    r2.price = 1.2;
    EXPECT_TRUE(r1 < r2);
    EXPECT_FALSE(r2 < r1);
    r1.price = 1.2;
    EXPECT_FALSE(r1 < r2);
    EXPECT_FALSE(r2 < r1);
}

TEST(book_row_tests, to_csv) {
    efl::book_row_t b = {1.1, 100, 
        date::year_month_day{date::year(2022), date::month(11), date::day(1)}};
    std::string csv = b.to_csv();
    EXPECT_EQ("1.1,100,2022-11-01", csv);
}

TEST(trade_tests, ctor) {
    efl::trade_t t;
    EXPECT_EQ(0.0, t.buy_price);
    EXPECT_EQ(0.0, t.sell_price);
    EXPECT_EQ(0, t.qty);
    EXPECT_FALSE(t.date.ok());
}

TEST(trade_tests, to_csv) {
    efl::trade_t t {1.1, 1.2, 400, 
        date::year_month_day{date::year(2022), date::month(11), date::day(1)}};
    EXPECT_EQ(1.1, t.buy_price);
    EXPECT_EQ(1.2, t.sell_price);
    EXPECT_EQ(400, t.qty);
    EXPECT_TRUE(t.date.ok());

    EXPECT_EQ("2022-11-01,400,1.1,1.2", t.to_csv());
}

TEST(book_tests, ctor) {
    efl::book_config_t config = get_book_config();
    efl::book_t book{config};

    EXPECT_EQ(config.total_amount, book.current_notional());
    EXPECT_EQ(-1, book.last_buy_price());
    EXPECT_EQ(-1, book.last_sell_price());
    EXPECT_EQ(0, book.last_share_price());
}

TEST(book_tests, add_order) {
    efl::book_config_t config = get_book_config();
    efl::book_t book{config};

    book.add_order(1.1, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});
    book.set_last_share_price(1.1);

    double book_pnl = book.compute_book_pnl();
    double global_fees = 400*1.1*config.tax/100+config.fees;
    EXPECT_DOUBLE_EQ(-global_fees, book_pnl);
}

TEST(book_tests, add_order_exceeds_max_notional) {
    efl::book_config_t config = get_book_config();
    efl::book_t book{config};

    for (int i=0; i<22; i++) {
        book.add_order(1.1, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});
    }
    // 22 order of 440 = 9680
    // initial notional is 10000
    double global_fees = (22 * 400 * 1.1 * config.tax/100.0) + (22*config.fees);
    EXPECT_NEAR(320 - global_fees, book.current_notional(), 1e-8);

    book.add_order(1.1, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});
    // The order is not executed and the notional remains the same
    EXPECT_NEAR(320 - global_fees, book.current_notional(), 1e-8);
}

TEST(book_tests, sell_order) {
    efl::book_config_t config = get_book_config();
    efl::book_t book{config};

    book.add_order(1.1, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});

    book.sell_order(1.1, 1.2, date::year_month_day{date::year(2022), date::month(11), date::day(10)});
    book.set_last_share_price(1.2);

    double book_pnl = book.compute_book_pnl();
    EXPECT_EQ(0, book_pnl);
    
}

TEST(book_tests, trade) {
    efl::book_config_t config = get_book_config();
    efl::book_t book{config};

    book.add_order(1.1, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});

    book.sell_order(1.1, 1.2, date::year_month_day{date::year(2022), date::month(11), date::day(10)});
    book.set_last_share_price(1.2);

    auto global_fees = (400*1.1*config.tax/100) + 2*(config.fees);

    double trade_pnl = book.compute_trades_pnl();
    EXPECT_NEAR(40-global_fees, trade_pnl, 1e-8);

    double book_pnl = book.compute_book_pnl();
    EXPECT_EQ(0, book_pnl);
}

TEST(book_tests, pnl) {
    efl::book_config_t config = get_book_config();
    efl::book_t book{config};

    book.add_order(1, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});
    book.add_order(1.1, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});

    book.sell_order(1.1, 1.2, date::year_month_day{date::year(2022), date::month(11), date::day(10)});
    book.set_last_share_price(1.2);

    double book_pnl = book.compute_book_pnl();
    EXPECT_DOUBLE_EQ(book_pnl, book.compute_book_pnl_x(book.last_share_price()));
    double trade_pnl = book.compute_trades_pnl();

    auto global_fees = (400*1.1*config.tax/100) + 2*(config.fees);

    // trade of 400@(1.2-1.1)
    EXPECT_NEAR(40-global_fees, trade_pnl, 1e-8);

    double pnl = book.compute_pnl();
    EXPECT_DOUBLE_EQ(trade_pnl + book_pnl, pnl);
}

TEST(book_tests, book_value) {
    efl::book_config_t config = get_book_config();
    efl::book_t book{config};

    book.add_order(1.1, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});
    book.add_order(1.2, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});
    book.add_order(1.3, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});
    book.add_order(1.4, 400, date::year_month_day{date::year(2022), date::month(11), date::day(1)});

    book.set_last_share_price(1.2);

    EXPECT_DOUBLE_EQ(4*400*1.2, book.compute_book_value());
}

TEST(book_tests, to_csv) {
    efl::book_config_t config1 = get_book_config();
    efl::book_t book1{config1};

    EXPECT_EQ("10000,0,0,0,0,0", book1.to_csv());
}

TEST(book_tests, comparison) {
    efl::book_config_t config1 = get_book_config();
    efl::book_t book1{config1};

    efl::book_config_t config2 = get_book_config();
    config2.delta_buy = 10;
    config2.delta_sell = 10;
    efl::book_t book2{config2};

    EXPECT_FALSE(book1 < book2);
    EXPECT_FALSE(book2 < book1);
}