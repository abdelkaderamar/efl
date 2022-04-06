#include "book.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>

namespace efl {

  std::ostream& operator << (std::ostream& os, const efl::book_row_t& row) {
    os << row.qty << "@" << row.price << "[" << row.date << "]";
    return os;
  }

  std::string book_row_t::to_csv() const {
    std::ostringstream oss;
    oss << price << "," << qty << "," << date;
    return oss.str();
  }

  std::string trade_t::to_csv() const {
    std::ostringstream oss;
    oss << date << "," << qty << "," << buy_price << "," << sell_price;
    return oss.str();
  }


  void book_t::add_order(const double& price, const int qty, const date::year_month_day& date) {
    double order_notional = qty * price;
    if (order_notional > _current_notional) {
      std::cerr << "Remaining amount = " << _current_notional <<
        ". Can't buy " << qty << " shares @ " << price << " | " << date << std::endl;
      return;
    }
    _rows.insert(book_row_t{
                          .price = price,
                          .qty = qty,
                          .date = date
      });
    _last_buy_price = price;
    _last_buy_date = date;
    _current_notional -= order_notional;
    double buy_fees = _book_config.fees + (order_notional * _book_config.tax/100.0);
    _current_notional -= buy_fees;
    _max_book_buy_value = std::max(_max_book_buy_value, book_buy_value());
    std::cout << "Buy " << qty << " shares @ " << price << " | " << date <<
      " | Remaining = " << _current_notional << " | ";
    std::copy(_rows.begin(), _rows.end(), std::ostream_iterator<book_row_t>(std::cout, " "));
    std::cout << std::endl;
  }

  void book_t::sell_order(const double& price, const double& sell_price, const date::year_month_day& date) {
    auto is_same_price = [&price](book_row_t row){ return row.price == price; };

    auto it = std::find_if(_rows.begin(), _rows.end(), is_same_price);
    if (it != _rows.end()) {
      trade_t t {
               .buy_price = price,
               .sell_price = sell_price,
               .qty = it->qty
      };
      _rows.erase(it);
      _trades.push_back(t);
      _current_notional += it->qty * sell_price;
      double sell_fees = _book_config.fees;
      _current_notional -= sell_fees;
      _last_sell_price = sell_price;
      _last_sell_date = date;
      std::cout << "Sell " << it->qty << " shares @ " << sell_price << " | " << date <<
        " | Remaining = " << _current_notional;
      std::copy(_rows.begin(), _rows.end(), std::ostream_iterator<book_row_t>(std::cout, " "));
      std::cout << std::endl;

    }
  }

  double book_t::compute_trades_pnl() {
    double pnl = 0;
    for(auto& t : _trades) {
      double global_fees = 2*_book_config.fees + // buy and sell fees
        (t.qty * t.buy_price * _book_config.tax/100.0);
      pnl += t.qty * (t.sell_price - t.buy_price);
      pnl -= global_fees;
    }
    _trade_pnl = pnl;
    return pnl;
  }

  double book_t::compute_book_pnl_x(const double& current_price)  {
    double pnl = 0;
    for(auto& r : _rows) {
      double global_fees = _book_config.fees +
        (r.qty * r.price * _book_config.tax/100.0);
      pnl += (r.qty * (current_price - r.price)) - global_fees;
    }
    _book_pnl = pnl;
    return pnl;
  }

  double book_t::compute_book_pnl()  {
    return compute_book_pnl_x(_last_share_price);
  }

  double book_t::compute_pnl_x(const double& current_price)  {
    _pnl = compute_trades_pnl() + compute_book_pnl_x(current_price);

    return _pnl;
  }

  double book_t::compute_pnl()  {
    _pnl = compute_trades_pnl() + compute_book_pnl_x(_last_share_price);
    return _pnl;
  }

  std::string book_t::to_csv(const double& current_price) {
    if (std::isnan(_pnl)) compute_pnl_x(current_price);

    std::ostringstream oss;
    oss << account_value() << "," << _pnl << "," << pnl_in_prct() << "," << _trade_pnl << "," << _book_pnl << "," << _max_book_buy_value;
    return oss.str();
  }

  std::string book_t::to_csv() {
    return to_csv(_last_share_price);
  }


  double book_t::compute_book_value() const {
    double value = 0;
    value = std::accumulate(_rows.begin(), _rows.end(), 0.0,
                            [this](double sum, const book_row_t& row) { return sum + (_last_share_price*row.qty); });
    return value;

  }

  double book_t::book_buy_value() const {
    double value = 0;
    value = std::accumulate(_rows.begin(), _rows.end(), 0.0,
                            [](double sum, const book_row_t& row) { return sum + (row.price*row.qty); });

    return value;
  }

  bool book_t:: operator<(const book_t& other) const {
    if (std::isnan(_pnl) || std::isnan(other._pnl)) return false;
    return _pnl < other._pnl;
  }

}
