#include "yahoo_histo_data.hpp"

#include <iomanip>
#include <sstream>

namespace efl::sources::yahoo
{
    bool yahoo_ohlcv_t::is_valid() const {
        return _open > 0 && _low > 0 && _high > 0 && _close > 0 && _date.ok();
    }

    std::string yahoo_ohlcv_t::to_string() const
    {
        std::stringstream ss;
        ss << "Open:" << std::left << std::setw(10) << _open << "\t"
           << "Low:" << std::left << std::setw(10) << _low << "\t"
           << "High:" << std::left << std::setw(10) << _high << "\t"
           << "Close:" << std::left << std::setw(10) << _close << "\t"
           << "Adj Close:" << std::left << std::setw(10) << _adj_close << "\t"
           << "Volume:" << std::left << std::setw(10) << _volume;
        return ss.str();
    }
    std::ostream &operator<<(std::ostream &os, const yahoo_ohlcv_t &ohlcv)
    {
        os << "Open:" << std::left << std::setw(10) << ohlcv._open << "\t"
           << "Low:" << std::left << std::setw(10) << ohlcv._low << "\t"
           << "High:" << std::left << std::setw(10) << ohlcv._high << "\t"
           << "Close:" << std::left << std::setw(10) << ohlcv._close << "\t"
           << "Adj Close:" << std::left << std::setw(10) << ohlcv._adj_close << "\t"
           << "Volume:" << std::left << std::setw(10) << ohlcv._volume;
        return os;
    }
}