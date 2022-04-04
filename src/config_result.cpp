#include "config_result.hpp"

#include <iostream>
#include <numeric>
#include <sstream>

namespace efl {

  std::string period_result_t::to_csv() {
    std::ostringstream oss;
    oss << _start << "," << _end << "," << _book.to_csv() << "," << _price_change;
    return oss.str();
  }

  double config_result_t::total_pnl() const {
    double total = std::accumulate(_results.begin(), _results.end(), 0.0,
                                   [](double sum, const period_result_t& pr) { return sum + pr._book.pnl(); });
    for (const auto& pr : _results) {
      std::cout << "@@ " << pr._book.pnl() << std::endl;
    }
    std::cout << "@@ Total = " << total << std::endl;
    return total;
  }

  std::string config_result_t::to_csv() {
    std::ostringstream oss;
    double global_pnl = total_pnl();
    oss << _config.to_csv() << "," << global_pnl << "," << global_pnl/_config.total_amount;
    for (auto& r : _results) {
      oss << "," << r.to_csv();
    }
    return oss.str();
  }

}
