#include "abstract_simulator.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

#include "efl/file_helper.hpp"

namespace efl {

  void abstract_simulator::simulate() {
    std::cout << "## " << _stock_data.size() << " shares to simulate" << std::endl;

    std::vector<book_config_t> book_configs = generate_book_config(_config);
    std::cout << "## " << book_configs.size() << " book config generated" << std::endl;


    int index = 1;
    for (const auto& e : _stock_data) {
      std::cout << "## For share " << e.first << " we have " << e.second.size() << " data files" << std::endl;
      for (const auto &d : e.second)
      {
        for (const auto &book_cfg : book_configs)
        {
          config_result_t config_result{d.get_filename()};
          config_result._config = book_cfg;
          auto b = simulate(d, book_cfg);
          period_result_t period_result{
              ._start = d.start_period(),
              ._end = d.end_period(),
              ._book = b,
              ._price_change = d.price_change(),
          };
          result_key_t key{
              ._stock = d.get_filename(),
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
      b->set_last_share_price(d.second.close);
      // std::cout << "Processing data of " << d.first << std::endl;
      if (buy_signal(d.second, book_cfg, *b))
      {
        buy(*b, book_cfg, d.second.close, d.first);
      }
      else if (sell_signal(d.second, book_cfg, *b))
      {
        double min_price = b->get_min_price();
        sell(*b, book_cfg, min_price, d.second.close, d.first);
      }
    }

    std::cout << "For config " << book_cfg << std::endl
              << "PNL = " << b->compute_pnl() << ", Trade PNL = " << b->compute_trades_pnl() << ", Book PNL = " << b->compute_book_pnl() << std::endl;

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
        // std::cout << "## " << cr._config.to_csv() << std::endl;
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
