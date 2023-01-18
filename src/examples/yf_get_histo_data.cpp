#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "efl/util/fmt_util.hpp"
#include "efl/sources/yahoo/yahoo_provider.hpp"

using namespace efl::sources::yahoo;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    yahoo_provider provider;

    auto quotes = provider.quote("SGO.PA,AAPL,T,AMC,META");
    for (auto& quote: quotes) {
        spdlog::info("Symbol: \t{}\t LastPx: {}", quote.symbol, quote.regularMarketPrice);
    }
    

    std::string filename = "cac40.json";
    if (argc > 1) {
        filename = argv[1];
    }
    std::ifstream f(filename);
    if (!f.is_open()) {
        spdlog::error("Failed to open {}", filename);
        return 1;
    }
    json data = json::parse(f);

    date::year_month_day start_date{date::year(2000), date::month(1), date::day(1)};
    date::year_month_day end_date{date::year(2023), date::month(1), date::day(1)};

    auto download_histo_data = [&provider, &start_date, &end_date](const std::string& symbol) {
        auto histo_data = provider.histo(symbol, start_date, end_date);
        std::ofstream csv_file;
        csv_file.open (symbol + ".csv");
        csv_file << yahoo_ohlcv_t::csv_header() << std::endl;
        for (auto& kvp : histo_data._data) {
            spdlog::info("{}: {}", kvp.first, kvp.second.to_string());
            csv_file << kvp.second.to_csv() << std::endl;
        }
        csv_file.close();
    };
    for (auto& ind : data) { // loop through indices
        spdlog::info("[## {} ##]", ind);
        auto stocks = ind["stocks"];
        for (auto& s : stocks) {
            std::string ticker = s["ticker"].get<std::string>();
            try
            {
                download_histo_data(ticker);
            }
            catch (std::exception& e) {
                spdlog::error("Error fetching histo data for {}. Error=[{}]", ticker, e.what());
            }
            catch (...) {
                spdlog::error("Error fetching histo data for {}.", ticker);
            }
        }
    }
    return 0;
}