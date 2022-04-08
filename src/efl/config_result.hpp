#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "date.h"

#include "book.hpp"
#include "book_config.hpp"

namespace efl {

  struct result_key_t {
    std::string _stock;
    date::year_month_day _start;
    date::year_month_day _end;

    bool operator < (const result_key_t& other) const {
      if (_stock == other._stock) {
        if (_start == other._start) return _end < other._end;
        else return _start < other._start;
      }
      return _stock < other._stock;
    }
  };

  struct period_result_t {
    date::year_month_day _start, _end;
    std::shared_ptr<book_t> _book;
    double _price_change;
    std::string to_csv();

    bool operator < (const period_result_t& other) {
      return _start < other._start;
    }
  };

  struct config_result_t {

    config_result_t(const std::string& stock) : _stock{stock} {}

    std::string _stock;
    book_config_t _config;
    period_result_t _result;

    double total_pnl() const;

    std::string to_csv();

    bool operator < (const config_result_t& other) {
      return _stock < other._stock;
    } 

    std::string header() const;
  };

}
