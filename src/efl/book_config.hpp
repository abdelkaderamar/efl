#pragma once

#include <ostream>
#include <string>

namespace efl {

  struct book_config_t {
    double total_amount;
    double order_amount;
    double delta_buy;
    double delta_sell;
    double fees;
    double tax;
    int empty_book_duration;

    std::string to_csv() const;

    std::string to_string() const;
  };

  std::ostream& operator<<(std::ostream& os, const book_config_t& cfg);

}

