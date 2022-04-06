#include "abstract_simulator.hpp"

#include <cmath>
#include <iostream>

namespace efl {

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
