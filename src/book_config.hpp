#pragma once

#include <ostream>
#include <string>

namespace efl {

  struct book_config_t {
    double total_amount;
    double order_amount;
    double delta;
    double fees;
    double tax;
    int empty_book_duration;

    std::string to_csv() const;
  };

  std::ostream& operator<<(std::ostream& os, const book_config_t& cfg);

}

