#include "dummy_strat_simulator.hpp"

#include <fstream>
#include <iostream>

#include "efl/config_result.hpp"

namespace efl 
{
    void  dummy_strat_simulator::simulate() {
        std::cout << "## " << _stock_data.size() << " shares to simulate" << std::endl;

        std::vector<book_config_t> book_configs = generate_book_config(_config);
        std::cout << "## " << book_configs.size() << " book config generated" << std::endl;

        int index = 1;
        for (const auto &e : _stock_data)
        {
            std::cout << "## For share " << e.first << " we have " << e.second.size() << " data files" << std::endl;
            for (const auto &book_cfg : book_configs)
            {
                config_result_t config_result{e.first};
                config_result._config = book_cfg;
                for (const auto &d : e.second)
                {
                    auto b = simulate(d, book_cfg);
                    period_result_t period_result{
                        ._start = d.start_period(),
                        ._end = d.end_period(),
                        ._book = b,
                        ._price_change = d.price_change(),
                    };
                    config_result._results.push_back(period_result);
                }
                _sim_results[index].push_back(config_result);
                ++index;
            }
        }
    }

    book_t dummy_strat_simulator::simulate(const stock_data_t &sd, const book_config_t &book_config) 
    {
        book_t b{book_config};
        auto &data = sd.get_data();
        for (auto &d : data)
        {
            b.set_last_share_price(d.second.close);
            // std::cout << "Processing data of " << d.first << std::endl;
            if (buy_signal(d.second, book_config, b))
            {
                buy(b, book_config, d.second.close, d.first);
            }
            else if (sell_signal(d.second, book_config, b))
            {
                double min_price = b.get_min_price();
                sell(b, book_config, min_price, d.second.close, d.first);
            }
        }

        std::cout << "For config " << book_config << std::endl
                  << "PNL = " << b.compute_pnl() << ", Trade PNL = " << b.compute_trades_pnl() << ", Book PNL = " << b.compute_book_pnl() << std::endl;

        return b;
    }

    void  dummy_strat_simulator::generate_output() {
        std::cout << "## " << _sim_results.begin()->second.begin()->_results.size() << std::endl;
        std::ofstream out;
        out.open("results.csv");
        out << _sim_results.begin()->second.begin()->header() << std::endl;
        for (auto &r : _sim_results)
        {
            for (auto &cr : r.second)
            {
                out << cr.to_csv() << std::endl;
                std::cout << "## " << cr._config.to_csv() << std::endl;
            }
        }
        out.close();
    }

    bool dummy_strat_simulator::buy_signal(ohlc_t mkt_data, const book_config_t &cfg,
                                           const book_t &b)
    {
        double close = 0, prev_close = 0;
        if (close > prev_close) return true;
        else return false;
        return true;
    }

    bool dummy_strat_simulator::sell_signal(ohlc_t mkt_data, const book_config_t &cfg,
                                            const book_t &b)
    {
        double close = 0, prev_close = 0;
        if (close < prev_close) return true;
        else return false;
        return true;
    }
}