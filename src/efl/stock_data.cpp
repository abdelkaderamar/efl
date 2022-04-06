#include "stock_data.hpp"

namespace efl {

  void stock_data_t::add_ohlc(const ohlc_t& day_data) {
    // TODO check day_data is valid
    _data[day_data.date] = day_data;
  }

  double stock_data_t::variation() const {
    return (_data.rbegin()->second.close/_data.begin()->second.close) - 1;
  }

}
