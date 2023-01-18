#include "abstract_simulator.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

#include <spdlog/spdlog.h>

#include "efl/file_helper.hpp"
#include "efl/util/fmt_util.hpp"

namespace efl {

  void abstract_simulator::simulate() {
    spdlog::info("## {} shares to simulate", _stock_data.size());

    std::vector<book_config_t> book_configs = generate_book_config(_config);
    spdlog::info("## {} book config generated", book_configs.size());


    int index = 1;
    for (const auto& e : _stock_data) {
      spdlog::info("## For share {} we have {} data files", e.first, e.second.size());
      for (const auto &d : e.second)
      {
        for (const auto &book_cfg : book_configs)
        {
          config_result_t config_result{d.get_stock_id()};
          config_result._config = book_cfg;
          auto b = simulate(d, book_cfg);
          period_result_t period_result{
              ._start = d.start_period(),
              ._end = d.end_period(),
              ._book = b,
              ._price_change = d.price_change(),
          };
          result_key_t key{
              ._stock = d.get_stock_id(),
              ._start = d.start_period(),
              ._end = d.end_period(),
          };
          config_result._result = period_result;
          _sim_results[index].push_back(config_result);
        }
        ++index;
      }
    }
  }

  std::shared_ptr<book_t> abstract_simulator::simulate(const stock_data_t &sd, const book_config_t &book_cfg)
  {
    std::shared_ptr<book_t> b = std::make_shared<book_t>(book_cfg);
    auto &data = sd.get_data();
    for (auto &d : data)
    {
      b->set_last_share_price(d.second._close);
      spdlog::debug("Processing data of {}", d.first);
      if (buy_signal(d.second, book_cfg, *b))
      {
        buy(*b, book_cfg, d.second._close, d.first);
      }
      else if (sell_signal(d.second, book_cfg, *b))
      {
        double min_price = b->get_min_price();
        sell(*b, book_cfg, min_price, d.second._close, d.first);
      }
    }

    spdlog::info("For config {}", book_cfg.to_string());
    spdlog::info("PNL = {}, Trade PNL = {}, Book PNL = {}",
                 b->compute_pnl(), b->compute_trades_pnl(), b->compute_book_pnl());
    return b;
  }

  void abstract_simulator::generate_output() {
    for (auto &r : _sim_results)
    {
      std::ofstream out;
      out.open(file_helper::get_result_filename(_config, r.second.begin()->_data_filename));
      out << _sim_results.begin()->second.begin()->header() << std::endl;
      for (auto &cr : r.second)
      {
        out << cr.to_csv() << std::endl;
      }
      out.close();
    }
  }

  void abstract_simulator::buy(book_t& b, const book_config_t& cfg,
                               const double price,
                               const date::year_month_day& date) {
    double qty = std::floor(cfg.order_amount/price);
    b.add_order(price, qty, date);
  }

  void abstract_simulator::sell(book_t& b, const book_config_t& cfg,
                                const double& price,
                                const double& sell_price,
                                const date::year_month_day& date) {
    b.sell_order(price, sell_price, date);
  }

}
