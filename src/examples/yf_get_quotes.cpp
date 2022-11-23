#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "efl/sources/yahoo/yahoo_provider.hpp"

using namespace efl::sources::yahoo;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
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

    yahoo_provider provider;

    for (auto& ind : data) { // loop through indices
        spdlog::info("[## {} ##]", ind);
        auto stocks = ind["stocks"];
        for (auto& s : stocks) {
            std::string ticker = s["ticker"].get<std::string>();
            std::string name = s["name"].get<std::string>();
            spdlog::info("STOCK: {} | {}", name, ticker);
            auto quotes = provider.quote(ticker);
            if (quotes.size() == 0) {
                spdlog::warn("STOCK Failed to get the quote for {}", ticker);
                continue;
            }
            for (auto& q : quotes) {
                spdlog::info("STOCK: {}: {} {}", ticker, q.longName, q.exchange);
                if (q.exchange != "PAR") {
                    spdlog::info("STOCK: {}/{}/{} is not listed in Paris", ticker, name, q.longName);
                }
            }
        }
    }

    

    // provider.histo("AMC");
    return 0;
}