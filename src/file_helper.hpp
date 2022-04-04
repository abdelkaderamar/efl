#pragma once

#include <filesystem>
#include <map>
#include <set>
#include <string>

namespace efl {

  class file_helper {
  public:
    static void get_csv_files(const std::filesystem::path& p,
                              std::map<std::string, std::set<std::string>>& csv_files);
  };
}
