#include "dummy_strat_simulator.hpp"

#include <fstream>
#include <iostream>

#include "efl/config_result.hpp"

namespace efl 
{
    void  dummy_strat_simulator::simulate() {
        abstract_simulator::simulate();
    }

    std::shared_ptr<book_t> dummy_strat_simulator::simulate(const stock_data_t &sd, const book_config_t &book_config) 
    {
       return abstract_simulator::simulate(sd, book_config);
    }

    void dummy_strat_simulator::generate_output(const stock_data_t& sd, const book_config_t& book_config, const book_t& book) 
    {

    }

    void  dummy_strat_simulator::generate_output() {
        abstract_simulator::generate_output();
    }

    bool dummy_strat_simulator::buy_signal(ohlc_t mkt_data, const book_config_t &cfg,
                                           const book_t &b)
    {
        double close = mkt_data.close, prev_close = _last_close;
        if (prev_close <= 0) return true; // No previous close, we start by buying
        if (close < prev_close) return true;
        else return false;
        return true;
    }

    bool dummy_strat_simulator::sell_signal(ohlc_t mkt_data, const book_config_t &cfg,
                                            const book_t &b)
    {
        double close = mkt_data.close, prev_close = _last_close;
        if (prev_close <= 0) return false; // No previous close
        if (b.is_empty()) return false; // No equity to sell
        if (close > prev_close) return true;
        else return false;
        return true;
    }
}