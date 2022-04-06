#include "csv_helper.hpp"

#include <sstream>

namespace efl {

  std::string csv_helper::to_csv(book_t& b, const double& current_price) {
    std::ostringstream oss;
    oss << b.to_csv(current_price);
    return oss.str();
  }

}
