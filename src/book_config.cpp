#include "book_config.hpp"

#include <sstream>

namespace efl {

  std::string book_config_t::to_csv() const {
    std::ostringstream oss;
    oss << total_amount << "," << order_amount << "," << delta << "," << empty_book_duration;
    return oss.str();
  }

  std::ostream& operator<<(std::ostream& os, const efl::book_config_t& cfg)
  {
    os << "Total Amount = " << cfg.total_amount
       << ", Order Amount = " << cfg.order_amount
       << ", Delta = " << cfg.delta
       << ", Empty book duration = " << cfg.empty_book_duration;
    return os;
  }

}
