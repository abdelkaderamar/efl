#include "yahoo_histo_data.hpp"

#include <iomanip>
#include <sstream>

#include <spdlog/spdlog.h>

#include "efl/sources/yahoo/yahoo_helper.hpp"
#include "efl/util/fmt_util.hpp"

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

    std::string yahoo_ohlcv_t::csv_header() 
    {
        return "Date,Open,Low,High,Close,Adj Close,Volume";
    }

    std::string yahoo_ohlcv_t::to_csv() const 
    {
        if (is_valid()) {
            return fmt::format("{},{},{},{},{},{},{}",
                _date, _open, _low, _high, _close, _adj_close, _volume);
        }
        return std::string();
    }

    void yahoo_ohlcv_t::from_csv(const std::string& line, char separator /*=  ','*/) {
        std::array<std::string, 7> tokens;
        ushort idx = 0;
        std::stringstream ss{line};
        std::string token;
        while (std::getline(ss, token, separator)) {
            tokens[idx++] = token;
            if (idx == tokens.size()) {
                break;
            }
        }

        idx = 0;
        spdlog::debug("[{}]", tokens[idx]);
        _date = yahoo_helper::parse_date(tokens[idx++]);

        spdlog::debug("[{}]", tokens[idx]);
        _open = std::stod(tokens[idx++]);

        spdlog::debug("[{}]", tokens[idx]);
        _low = std::stod(tokens[idx++]);

        spdlog::debug("[{}]", tokens[idx]);
        _high = std::stod(tokens[idx++]);

        spdlog::debug("[{}]", tokens[idx]);
        _close = std::stod(tokens[idx++]);

        spdlog::debug("[{}]", tokens[idx]);
        _adj_close = std::stod(tokens[idx++]);

        spdlog::debug("[{}]", tokens[idx]);
        _volume = std::stod(tokens[idx++]);
    }
}