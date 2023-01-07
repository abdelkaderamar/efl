#include "efl/simulator_config.hpp"

#include <gtest/gtest.h>

TEST(interval, ctor) 
{
    // default ctor
    {
        efl::interval_t i;
        EXPECT_EQ(0, i.min);
        EXPECT_EQ(0, i.max);
        EXPECT_EQ(1, i.step);
    }
    {
        efl::interval_t i { .min = 1, .max = 10, .step = 2, };
        EXPECT_EQ(1, i.min);
        EXPECT_EQ(10, i.max);
        EXPECT_EQ(2, i.step);
    }
} 
TEST(interval, to_and_from_json) 
{
    efl::interval_t i { 1, 10, 0.1 };

    EXPECT_EQ(1, i.min);
    EXPECT_EQ(10, i.max);
    EXPECT_EQ(0.1, i.step);

    nlohmann::json j;
    efl::to_json(j, i);

    EXPECT_EQ(1, j["min"]);
    EXPECT_EQ(10, j["max"]);
    EXPECT_EQ(0.1, j["step"]);

    j["min"] = 2;
    j["max"] = 20;
    j["step"] = 0.2;

    efl::from_json(j, i);

    EXPECT_EQ(2, i.min);
    EXPECT_EQ(20, i.max);
    EXPECT_EQ(0.2, i.step);
}

TEST(simulator_config, to_and_from_json) 
{
    efl::simulator_config_t sim_config;
    nlohmann::json j;

    efl::to_json(j, sim_config);

    efl::from_json(j, sim_config);
}

TEST(simulator_config, generate_book_configs) 
{
    efl::simulator_config_t sim_config{
        .total_amount_type = "capped",
        .total_amount = {},
        .order_amount = {},
        .delta_buy_type = "fixed",
        .delta_buy_value = {},
        .delta_sell_type = "fixed",
        .delta_sell_value = {},
        .empty_book_duration = {},
        .fees = 1,
        .tax = 0.03,
        .filename = "config.json",        
    };
    nlohmann::json j;

    auto v = efl::generate_book_config(sim_config);

    EXPECT_EQ(1, v.size());
}