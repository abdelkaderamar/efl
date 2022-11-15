#pragma once

#include <filesystem>
#include <map>
#include <set>
#include <string>

namespace efl {

  class simulator_config_t;
  class stock_data_t;

  class file_helper {
  public:
    static void get_csv_files(const std::filesystem::path &p,
                              std::map<std::string, std::set<std::string>> &csv_files);

    static std::string get_result_filename(const simulator_config_t &sim_config,
                                           const std::string& stock);
  };
}
