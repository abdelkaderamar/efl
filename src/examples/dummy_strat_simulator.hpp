#pragma once

#include <map>
#include <vector>

#include "efl/abstract_simulator.hpp"
#include "efl/config_result.hpp"

namespace efl
{
    class dummy_strat_simulator : public abstract_simulator
    {
    public:
        dummy_strat_simulator(simulator_config_t &config, std::map<std::string, std::vector<stock_data_t>> &data) : 
            abstract_simulator(config, data), _last_close{-1.0}
        {
        }

        void simulate() override;

        std::shared_ptr<book_t> simulate(const stock_data_t& sd, const book_config_t& book_cfg) override;
    
        void generate_output(const stock_data_t& sd, const book_config_t& book_config, const book_t& book) override;

        void generate_output() override;

        bool buy_signal(ohlcv_t mkt_data, const book_config_t& cfg,
                            const book_t& b) override;
        
        bool sell_signal(ohlcv_t mkt_data, const book_config_t& cfg,
                             const book_t& b) override;

    protected:

        double _last_close;
    };
}