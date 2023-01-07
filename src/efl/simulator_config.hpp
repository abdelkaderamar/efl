#pragma once

#include <vector>

#include <nlohmann/json.hpp>

#include "book_config.hpp"

using json = nlohmann::json;

namespace efl {

  struct interval_t {
    double min = 0;
    double max = 0;
    double step = 1;
  };

  struct simulator_config_t {
    std::string total_amount_type;
    interval_t total_amount;
    interval_t order_amount;
    std::string delta_buy_type;
    interval_t delta_buy_value;
    std::string delta_sell_type;
    interval_t delta_sell_value;
    interval_t empty_book_duration;
    double fees;
    double tax;

    std::string filename;
  };


  void to_json(json& j, const interval_t& interval);
  void from_json(const json& j, interval_t& interval);

  void to_json(json& j, const simulator_config_t& cfg);
  void from_json(const json& j, simulator_config_t& cfg);

  std::vector<book_config_t> generate_book_config(const simulator_config_t& sim_cfg);

}
