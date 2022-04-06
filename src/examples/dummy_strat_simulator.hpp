#pragma once

#include "efl/abstract_simulator.hpp"

namespace efl
{
    class dummy_strat_simulator : public abstract_simulator
    {
    public:
        dummy_strat_simulator(simulator_config_t &config, std::map<std::string, std::vector<stock_data_t>> &data) : 
            abstract_simulator(config, data)
        {
        }

        void simulate() override;

        book_t simulate(const stock_data_t& sd, const book_config_t& book_cfg) override;
    
        void generate_output() override;

        bool buy_signal(ohlc_t mkt_data, const book_config_t& cfg,
                            const book_t& b) override;
        
        bool sell_signal(ohlc_t mkt_data, const book_config_t& cfg,
                             const book_t& b) override;
    };
}