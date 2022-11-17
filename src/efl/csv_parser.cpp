#include "csv_parser.hpp"

#include <iostream>
#include <regex>

#include "csv.h"
#include "date.h"
#include <spdlog/spdlog.h>

#include "efl/util/fmt_util.hpp"

namespace efl {

  // @deprecated
  void csv_parser::parse(std::istream& is) {
    while (is) {
      std::string line;
      std::getline(is, line);
      std::string::size_type prev = 0;
      std::string::size_type pos = 0;
      while ((pos = line.find(_separator, pos)) != std::string::npos) {
        std::string token = line.substr(prev, pos-prev);
        //clean_token(token);
        spdlog::debug("[{}]", token);
        prev = ++pos;
      }
    }
  }

  std::map<date::year_month_day, ohlc_t> csv_parser::parse(const std::string& filename) {

    std::map<date::year_month_day, ohlc_t> data;

    io::CSVReader<7,
                  io::trim_chars<' ', '\t'> ,
                  io::double_quote_escape<',', '"'>
                  > csv_reader{filename};
    std::string date_str, last_str, open_str, high_str, low_str, volume_str,
      variation_str;
    // skip the header
    csv_reader.read_header(io::ignore_no_column,
                           "Date","Dernier","Ouv.","Plus Haut","Plus Bas",
                           "Vol.","Variation %");
    while (csv_reader.read_row(date_str, last_str, open_str, high_str, low_str,
                               volume_str, variation_str)) {
      // TODO: catch error, validate data
      clean_token(date_str, false);
      clean_token(last_str, true);
      clean_token(open_str, true);
      clean_token(high_str, true);
      clean_token(low_str, true);
      clean_token(volume_str, true);
      clean_token(variation_str, true);
      spdlog::info("[{}][{}][{}][{}][{}][{}][{}]", 
              date_str, last_str, open_str, high_str, low_str, volume_str, variation_str);
      auto date = parse_date(date_str);
      if (date.ok()) {
        spdlog::info("{} correctly parsed", date);
      }
      else {
        spdlog::warn("{} is not a valid date", date_str);
      }
      double close = std::stod(last_str);
      double open = std::stod(open_str);
      double high = std::stod(high_str);
      double low = std::stod(low_str);
      double volume = parse_volume(volume_str);
      double variation = parse_variation(variation_str);
      spdlog::info("Close = {}, Open = {}, High = {}, Low = {}, Volume = {}, Variation = {}",
        close, open, high, low, volume, variation);

      ohlc_t day_data
        {
         .open = open,
         .high = high,
         .low = low,
         .close = close,
         .volume = volume,
         .date = date
        };

      data[day_data.date] = day_data;
    }

    return data;
  }

  void csv_parser::clean_token(std::string& str, const bool is_numeric/* = false*/) {
    if (str.size() == 0) return;
    if (str[0] == '"') str = str.substr(1);
    if (str[str.size()-1] == '"') str = str.substr(0, str.size()-1);

    if (is_numeric) {
      std::replace(str.begin(), str.end(), ',', '.');
    }
  }

  date::year_month_day csv_parser::parse_date(const std::string& str)
  {
    static std::regex re("([0-3][0-9])/([0-1][0-9])/([0-9]{4})");
    std::smatch m;
    if (std::regex_match(str, m, re)) {
      if (m.size() == 4) {
        auto day = date::day{(unsigned)std::stoi(m[1])};
        auto month = date::month{(unsigned)std::stoi(m[2])};
        auto year = date::year{std::stoi(m[3])};

        return date::year_month_day{year, month, day};
      }
    }

    return date::year_month_day{};
  }

  double csv_parser::parse_volume(const std::string& str) {
    long multiplier = 1;
    char last_char = str.back();
    switch (last_char) {
    case 'K': multiplier = 1000;
      break;
    case 'M': multiplier = 1000000;
      break;
    default:
      multiplier = 1;
    }
    if (multiplier == 1) {
      return std::stod(str);
    }
    else {
      return multiplier * std::stod(str.substr(0, str.size()-1));
    }
  }

  double csv_parser::parse_variation(const std::string& str) {
    char last_char = str.back();
    if (last_char != '%') {
      return std::stod(str);
    }
    else {
      return std::stod(str.substr(0, str.size()-1));
    }
    return 0;
  }

}
