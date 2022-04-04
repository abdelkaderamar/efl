#pragma once

#include <iostream>
#include <map>

#include "date.h"

#include "stock_data.hpp"

namespace date {
  class year_month_day;
}


namespace efl {

  class csv_parser {
  public:
    csv_parser(char separator = ',') : _separator{separator}
    {
    }

    void parse(std::istream& is);
    std::map<date::year_month_day, ohlc_t> parse(const std::string& filename);

    static void clean_token(std::string& str, bool is_numeric = false);

    date::year_month_day parse_date(const std::string& str);
    double parse_volume(const std::string& str);
    double parse_variation(const std::string& str);
  private:
    char _separator;
  };

}
