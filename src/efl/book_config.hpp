#pragma once

#include <ostream>
#include <string>

namespace efl {

  struct book_config_t {
    double total_amount = 0.0;
    double order_amount = 0.0;
    double delta_buy = 0.0;
    double delta_sell = 0.0;
    double fees = 0.0;
    double tax = 0.0;
    int empty_book_duration = 0;

    std::string to_csv() const;

    std::string to_string() const;
  };

  std::ostream& operator<<(std::ostream& os, const book_config_t& cfg);

}

