#pragma once

#include <string>

#include "book.hpp"

namespace efl {

  class csv_helper {
  public:
    static std::string to_csv(book_t& b, const double& current_price);
  };
}
