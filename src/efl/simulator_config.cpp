#include "simulator_config.hpp"
#include <iostream>

namespace efl {

  const std::vector<std::string> simulator_config_t::STATIC_FIELDS = {
      "total_amount_type",
      "total_amount",
      "order_amount",
      "delta_buy_type",
      "delta_buy_value",
      "delta_sell_type",
      "delta_sell_value",
      "empty_book_duration",
      "fees",
      "tax"
    };

  void parse_dynamic_params(const json& j, simulator_config_t& cfg) {
    for (auto &elt : j.items())
    {
      if (std::find(simulator_config_t::STATIC_FIELDS.begin(), simulator_config_t::STATIC_FIELDS.end(), elt.key()) ==
          simulator_config_t::STATIC_FIELDS.end())
      {
        if (elt.value().is_number()) {
          std::cout << "Adding a number " << elt.key() << " = " << elt.value() << std::endl;
          cfg.dyn_params_number[elt.key()] = elt.value();
        }
        else if (elt.value().is_string()) {
          std::cout << "Adding a string " << elt.key() << " = " << elt.value() << std::endl;
          cfg.dyn_params_string[elt.key()] = elt.value();
        }
        else if (elt.value().is_object()) {
          std::cout << "Adding a json " << elt.key() << " = " << elt.value() << std::endl;
          cfg.dyn_params_json[elt.key()] = elt.value();
        }
      }
    }
  }

  void to_json(json& j, const interval_t& interval)
  {
    j = json
      {
       {"min", interval.min},
       {"max", interval.max},
       {"step", interval.step}
      };
  }

  void from_json(const json& j, interval_t& interval)
  {
    j.at("min").get_to(interval.min);
    j.at("max").get_to(interval.max);
    j.at("step").get_to(interval.step);
  }

  void to_json(json& j, const simulator_config_t& cfg) {
    j = json
      {
       {"total_amount_type", cfg.total_amount_type},
       {"total_amount", cfg.total_amount},
       {"order_amount", cfg.order_amount},
       {"delta_buy_type", cfg.delta_buy_type},
       {"delta_buy_value", cfg.delta_buy_value},
       {"delta_sell_type", cfg.delta_sell_type},
       {"delta_sell_value", cfg.delta_sell_value},
       {"empty_book_duration", cfg.empty_book_duration},
       {"fees", cfg.fees},
       {"tax", cfg.tax}
      };
  }

  void from_json(const json& j, simulator_config_t& cfg) {
    j.at("total_amount_type").get_to(cfg.total_amount_type);
    j.at("total_amount").get_to(cfg.total_amount);
    j.at("order_amount").get_to(cfg.order_amount);
    j.at("delta_buy_type").get_to(cfg.delta_buy_type);
    j.at("delta_buy_value").get_to(cfg.delta_buy_value);
    j.at("delta_sell_type").get_to(cfg.delta_sell_type);
    j.at("delta_sell_value").get_to(cfg.delta_sell_value);
    j.at("empty_book_duration").get_to(cfg.empty_book_duration);
    j.at("fees").get_to(cfg.fees);
    j.at("tax").get_to(cfg.tax);
    parse_dynamic_params(j, cfg);
  }

  std::vector<book_config_t> generate_book_config(const simulator_config_t &cfg)
  {
    std::vector<book_config_t> v;
    for (double total_amount = cfg.total_amount.min;
         total_amount <= cfg.total_amount.max;
         total_amount += cfg.total_amount.step)
    {
      for (double order_amount = cfg.order_amount.min;
           order_amount <= cfg.order_amount.max;
           order_amount += cfg.order_amount.step)
      {
        for (double delta_buy = cfg.delta_buy_value.min;
             delta_buy <= cfg.delta_buy_value.max;
             delta_buy += cfg.delta_buy_value.step)
        {
          for (double delta_sell = cfg.delta_sell_value.min;
               delta_sell <= cfg.delta_sell_value.max;
               delta_sell += cfg.delta_sell_value.step)
          {
            for (int ebd = cfg.empty_book_duration.min;
                 ebd <= cfg.empty_book_duration.max;
                 ebd += cfg.empty_book_duration.step)
            {
              v.push_back(book_config_t{
                  .total_amount = total_amount,
                  .order_amount = order_amount,
                  .delta_buy = delta_buy,
                  .delta_sell = delta_sell,
                  .fees = cfg.fees,
                  .tax = cfg.tax,
                  .empty_book_duration = ebd});
            }
          }
        }
      }
    }
    return v;
  }
}
