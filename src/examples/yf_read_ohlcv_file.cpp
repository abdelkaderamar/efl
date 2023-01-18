#include <fstream>
#include <iostream>

#include <spdlog/spdlog.h>

#include "efl/sources/yahoo/yahoo_helper.hpp"
#include "efl/util/fmt_util.hpp"

using namespace efl::sources::yahoo;

void print_usage(const std::string &command)
{
    spdlog::info("Usage: {} <symbol> <csv file>", command);
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        spdlog::error("Syntax error");
        print_usage(argv[0]);
        return 1;
    }

    auto histo_data = yahoo_helper::parse_histo_csv_file(argv[1], argv[2]);
    spdlog::info("Histo data for {} contains {} data", histo_data._symbol, histo_data._data.size());
    for (auto& it : histo_data._data) {
        spdlog::info("Date: {}", it.first);
    }
    return 0;
}