#include "file_helper.hpp"

#include <iostream>
#include <filesystem>
#include "simulator_config.hpp"
#include "stock_data.hpp"

namespace fs = std::filesystem;

namespace efl {

  void file_helper::get_csv_files(const std::filesystem::path& p,
                                  std::map<std::string, std::set<std::string>>& csv_files)
  {
    for (const fs::directory_entry& de : fs::directory_iterator(p)) {
      if (fs::exists(de) && fs::is_directory(de)) {
        std::cout << "# " << de.path().filename() << std::endl;
        std::string name = de.path().filename();
        std::set<std::string> files;
        for (const fs::directory_entry& e : fs::directory_iterator(de)) {
          if (fs::exists(e) && fs::is_regular_file(e) &&
              e.path().string().ends_with(".csv")) {
            files.insert(e.path().string());
          }
        }
        if (files.size() > 0) {
          csv_files[name] = files;

        }
      }
    }
  }

  std::string file_helper::get_result_filename(const simulator_config_t &sim_config,
                                               const std::string& stock)
  {
    std::filesystem::path p1{sim_config.filename};
    std::filesystem::path p2{stock};
    std::string s = p1.stem().string() + "-" + p2.filename().stem().string() + ".csv";
    std::cout << "## " << stock << " => " << s << std::endl;
    return s;
  }
}
