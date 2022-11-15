#include "yahoo_histo_data.hpp"

#include <iomanip>

namespace efl::sources::yahoo
{
    std::ostream& operator<<(std::ostream& os, const yahoo_ohlcv_t& ohlcv) {
        os << "Open:" << std::left << std::setw(10) << ohlcv._open << "\t"
           << "Low:" << std::left << std::setw(10) << ohlcv._low << "\t"
           << "High:" << std::left << std::setw(10) << ohlcv._high << "\t"
           << "Close:" << std::left << std::setw(10) << ohlcv._close << "\t"
           << "Adj Close:" << std::left << std::setw(10) << ohlcv._adj_close << "\t"
           << "Volume:" << std::left << std::setw(10) << ohlcv._volume;
        return os;
    }

}