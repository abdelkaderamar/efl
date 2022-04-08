#pragma once

#include <map>
#include <memory>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>

#include "book.hpp"
#include "book_config.hpp"
#include "config_result.hpp"
#include "simulator_config.hpp"
#include "stock_data.hpp"

namespace efl {
  class abstract_simulator {
  public:
    abstract_simulator(simulator_config_t& config, std::map<std::string, std::vector<stock_data_t>>& d) :
      _stock_data{d},
      _config{config}
    {}

    virtual void simulate();
    virtual std::shared_ptr<book_t> simulate(const stock_data_t& sd, const book_config_t& book_cfg);
    virtual void generate_output(const stock_data_t& sd, const book_config_t& book_config, const book_t& book) = 0;
    virtual void generate_output();

    virtual void buy(book_t& b, const book_config_t& cfg, const double price,
                     const date::year_month_day& date);
    virtual void sell(book_t& b, const book_config_t& cfg,
                      const double& price,
                      const double& sell_price,
                      const date::year_month_day& date);

    virtual bool buy_signal(ohlc_t mkt_data, const book_config_t& cfg,
                            const book_t& b) = 0;
    virtual bool sell_signal(ohlc_t mkt_data, const book_config_t& cfg,
                             const book_t& b) = 0;

  protected:
    std::map<std::string, std::vector<stock_data_t>> _stock_data;
    simulator_config_t _config;
    std::map<int, std::vector<config_result_t>> _sim_results;
  };
}
