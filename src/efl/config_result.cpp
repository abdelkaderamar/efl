#include "config_result.hpp"

#include <iostream>
#include <numeric>
#include <sstream>

namespace efl {

  std::string period_result_t::to_csv() {
    std::ostringstream oss;
    oss << _start << "," << _end << "," << _book->to_csv() << "," << _price_change;
    return oss.str();
  }

  double config_result_t::total_pnl() const {
    return _result._book->pnl();
  }

  std::string config_result_t::to_csv() {
    std::ostringstream oss;
    double global_pnl = total_pnl();
    oss << _config.to_csv() << "," << global_pnl << "," << global_pnl/_config.total_amount
        << "," << _result.to_csv();
    return oss.str();
  }

  std::string config_result_t::header() const {
    std::ostringstream oss;
    oss << "Total Amount,Order Amount,Buy Delta,Sell Delta,Empty Book Duration,Total PNL,Total PNL %"
        << ",Start,End,Account,Pnl,Pnl %,Trade PNL,Book PNL,Max Book Value,Price Evolution %";
    return oss.str();
  }
}
