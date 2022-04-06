#pragma once

#include <limits>
#include <ostream>
#include <set>
#include <vector>

#include "date.h"

#include "book_config.hpp"

namespace efl {

  struct book_row_t {
    double price;
    int qty;
    date::year_month_day date;
    bool operator<(const book_row_t& other) const { return price < other.price; }
    std::string to_csv() const;
  };

  std::ostream& operator<<(std::ostream& os, const book_row_t& row);

  struct trade_t {
    double buy_price;
    double sell_price;
    int qty;
    date::year_month_day date;
    std::string to_csv() const;
  };

  class book_t {
  public:
    book_t(const book_config_t& config) :
      _book_config{config}, _current_notional{config.total_amount},
      _last_buy_price{-1}, _last_sell_price{-1},
      _max_book_buy_value{0},
      _trade_pnl{NAN}, _book_pnl{NAN}, _pnl{NAN}
    {}

    void add_order(const double& price, const int qty, const date::year_month_day& date);
    void sell_order(const double& price, const double& sell_price, const date::year_month_day& date);

    const std::set<book_row_t>& get_orders() const { return _rows; }

    bool is_empty() const { return _rows.size() == 0; }

    size_t size() const { return _rows.size(); }

    const book_row_t& get_min() const { return *(_rows.begin()); }

    const book_row_t& get_max() const {
      auto it = _rows.end();
      --it;
      return *it;
    }

    double get_min_or_last_buy_price() const {
      if (is_empty()) return _last_buy_price;
      return get_min().price;
    }

    double get_min_price() const {
      if (is_empty()) return std::numeric_limits<double>::max();
      return get_min().price;
    }

    const double& last_buy_price() const { return _last_buy_price; }
    const double& last_sell_price() const { return _last_sell_price; }
    const double& last_share_price() const { return _last_share_price; }

    void set_last_share_price(const double& price) { _last_share_price = price; }

    const date::year_month_day& last_buy_date() const { return _last_buy_date; }
    const date::year_month_day& last_sell_date() const { return _last_sell_date; }

    double compute_trades_pnl();

    double compute_book_pnl_x(const double& current_price);
    double compute_book_pnl();

    double compute_pnl_x(const double& current_price);
    double compute_pnl();

    std::string to_csv(const double& current_price);
    std::string to_csv();

    double compute_book_value() const;

    double book_buy_value() const;

    double pnl() const { return _pnl; }

    double pnl_in_prct() const { return _pnl/_book_config.total_amount; }


    double account_value() const { return _current_notional + compute_book_value(); }

    double get_price_change(const double& price) const { return -1.0 + (_last_share_price/price); }

    bool operator<(const book_t& other) const;
  protected:
  private:
    std::set<book_row_t> _rows;
    book_config_t _book_config;
    double _current_notional;
    double _last_buy_price;
    date::year_month_day _last_buy_date;
    double _last_sell_price;
    date::year_month_day _last_sell_date;
    std::vector<trade_t> _trades;
    double _last_share_price;
    double _max_book_buy_value;
    double _trade_pnl, _book_pnl, _pnl;
  };
}
