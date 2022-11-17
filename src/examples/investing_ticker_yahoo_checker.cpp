#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "efl/sources/yahoo/yahoo_provider.hpp"

using namespace efl::sources::yahoo;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    std::ifstream f("investing-indices.json");
    json data = json::parse(f);

    yahoo_provider provider;

    for (auto& ind : data) { // loop through indices
        spdlog::info("[## {} ##]", ind);
        auto stocks = ind["stocks"];
        for (auto& s : stocks) {
            std::string ticker = s["ticker"].get<std::string>();
            spdlog::info("{}", ticker);
            auto quotes = provider.quote(ticker);
            for (auto& q : quotes) {
                spdlog::info("{}: {}", ticker, q.longName);
            }
        }
    }

    

    // provider.histo("AMC");
    return 0;
}