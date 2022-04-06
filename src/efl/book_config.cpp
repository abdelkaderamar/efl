#include "book_config.hpp"

#include <sstream>

namespace efl {

  std::string book_config_t::to_csv() const {
    std::ostringstream oss;
    oss << total_amount << "," << order_amount << "," << delta_buy << "," << delta_sell << "," << empty_book_duration;
    return oss.str();
  }

  std::ostream& operator<<(std::ostream& os, const efl::book_config_t& cfg)
  {
    os << "Total Amount = " << cfg.total_amount
       << ", Order Amount = " << cfg.order_amount
       << ", Buy Delta = " << cfg.delta_buy
       << ", Sell Delta = " << cfg.delta_sell
       << ", Empty book duration = " << cfg.empty_book_duration;
    return os;
  }

}
