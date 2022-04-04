#include "simulator_config.hpp"

namespace efl {

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
       {"delta_type", cfg.delta_type},
       {"delta_value", cfg.delta_value},
       {"empty_book_duration", cfg.empty_book_duration},
       {"fees", cfg.fees},
       {"tax", cfg.tax}
      };
  }

  void from_json(const json& j, simulator_config_t& cfg) {
    j.at("total_amount_type").get_to(cfg.total_amount_type);
    j.at("total_amount").get_to(cfg.total_amount);
    j.at("order_amount").get_to(cfg.order_amount);
    j.at("delta_type").get_to(cfg.delta_type);
    j.at("delta_value").get_to(cfg.delta_value);
    j.at("empty_book_duration").get_to(cfg.empty_book_duration);
    j.at("fees").get_to(cfg.fees);
    j.at("tax").get_to(cfg.tax);
  }

  std::vector<book_config_t> generate_book_config(const simulator_config_t& cfg) {
    std::vector<book_config_t> v;
    for (double total_amount = cfg.total_amount.min;
         total_amount <= cfg.total_amount.max;
         total_amount += cfg.total_amount.step) {
      for (double order_amount = cfg.order_amount.min;
           order_amount <= cfg.order_amount.max;
           order_amount += cfg.order_amount.step) {
        for (double delta = cfg.delta_value.min;
             delta <= cfg.delta_value.max;
             delta += cfg.delta_value.step) {
          for (int ebd = cfg.empty_book_duration.min;
               ebd <= cfg.empty_book_duration.max;
               ebd += cfg.empty_book_duration.step) {
            v.push_back(book_config_t
                        {
                         .total_amount = total_amount,
                         .order_amount = order_amount,
                         .delta = delta,
                         .fees = cfg.fees,
                         .tax = cfg.tax,
                         .empty_book_duration = ebd
                        });
          }
        }
      }
    }
    return v;
  }

}
