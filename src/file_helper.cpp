#include "file_helper.hpp"

#include <iostream>

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

}
