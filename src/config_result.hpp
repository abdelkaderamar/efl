#pragma once

#include <string>
#include <vector>

#include "date.h"

#include "book.hpp"
#include "book_config.hpp"

namespace efl {

  struct period_result_t {
    date::year_month_day _start, _end;
    book_t _book;
    double _price_change;
    std::string to_csv();
  };

  struct config_result_t {
    book_config_t _config;
    std::vector<period_result_t> _results;



    double total_pnl() const;

    std::string to_csv();
  };

}
