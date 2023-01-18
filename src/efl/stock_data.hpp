#pragma once

#include "date.h"

#include <map>
#include <string>

namespace efl {

  struct ohlcv_t {
    double _open = 0.0;
    double _high = 0.0;
    double _low = 0.0;
    double _close = 0.0;
    double _volume = 0.0;
    date::year_month_day _date;
  };

  class stock_data_t {
  public:
    stock_data_t(const std::string& stock_id,
               std::map<date::year_month_day, ohlcv_t> data) :
      _stock_id{stock_id},
      _data{data}
    {}

    const std::string& get_stock_id() const { return _stock_id; }

    const bool is_valid() const { return _data.size() > 0; }

    const std::map<date::year_month_day, ohlcv_t> get_data() const { return _data; }

    const date::year_month_day start_period() const { return _data.begin()->first; }
    const date::year_month_day end_period() const { return _data.rbegin()->first; }

    const double start_period_price () const { return _data.begin()->second._close; }
    const double end_period_price() const { return _data.rbegin()->second._close; }

    const double price_change() const { return end_period_price() / start_period_price(); }

    double variation() const;

    void add_ohlc(const ohlcv_t& data);

  private:
    std::string _stock_id;
    std::map<date::year_month_day, ohlcv_t> _data;
  };

}
