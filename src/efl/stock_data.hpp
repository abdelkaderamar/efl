#pragma once

#include "date.h"

#include <map>
#include <string>

namespace efl {

  struct ohlc_t {
    double open;
    double high;
    double low;
    double close;
    double volume;
    date::year_month_day date;
  };

  class stock_data_t {
  public:
    stock_data_t(const std::string& filename,
               std::map<date::year_month_day, ohlc_t> data) :
      _filename{filename},
      _data{data}
    {}

    const std::string& get_filename() const { return _filename; }

    const bool is_valid() const { return _data.size() > 0; }

    const std::map<date::year_month_day, ohlc_t> get_data() const { return _data; }

    const date::year_month_day start_period() const { return _data.begin()->first; }
    const date::year_month_day end_period() const { return _data.rbegin()->first; }

    const double start_period_price () const { return _data.begin()->second.close; }
    const double end_period_price() const { return _data.rbegin()->second.close; }

    const double price_change() const { return end_period_price() / start_period_price(); }

    double variation() const;

    void add_ohlc(const ohlc_t& data);

  private:
    std::string _filename;
    std::map<date::year_month_day, ohlc_t> _data;
  };

}
