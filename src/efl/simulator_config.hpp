#pragma once

#include <map>
#include <string>
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
    static const std::vector<std::string> STATIC_FIELDS;

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

    std::map<std::string, double> dyn_params_number;
    std::map<std::string, std::string> dyn_params_string;
    std::map<std::string, json> dyn_params_json;
  };


  void to_json(json& j, const interval_t& interval);
  void from_json(const json& j, interval_t& interval);

  void to_json(json& j, const simulator_config_t& cfg);
  void from_json(const json& j, simulator_config_t& cfg);

  std::vector<book_config_t> generate_book_config(const simulator_config_t& sim_cfg);

}
