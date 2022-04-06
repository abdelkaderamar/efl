#include "dummy_strat_simulator.hpp"

namespace efl 
{
    void  dummy_strat_simulator::simulate() {}

    book_t dummy_strat_simulator::simulate(const stock_data_t &sd, const book_config_t &book_config) 
    {
        book_t book{book_config};
        return book;
    }

    void  dummy_strat_simulator::generate_output() {}

    bool dummy_strat_simulator::buy_signal(ohlc_t mkt_data, const book_config_t &cfg,
                                           const book_t &b)
    {
        return true;
    }

    bool dummy_strat_simulator::sell_signal(ohlc_t mkt_data, const book_config_t &cfg,
                                            const book_t &b)
    {
        return true;
    }
}