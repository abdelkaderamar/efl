#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

#include "efl/sources/yahoo/yahoo_provider.hpp"

using namespace efl::sources::yahoo;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    std::ifstream f("investing-indices.json");
    json data = json::parse(f);

    yahoo_provider provider;

    for (auto& ind : data) { // loop through indices
        std::cout << "[## " << ind << " ##]" << std::endl;
        auto stocks = ind["stocks"];
        for (auto& s : stocks) {
            std::string ticker = s["ticker"].get<std::string>();
            std::cout << ticker << std::endl;
            auto quotes = provider.quote(ticker);
            for (auto& q : quotes) {
                std::cout << ticker << ": " << q.longName << std::endl;
            }
        }
    }

    

    // provider.histo("AMC");
    return 0;
}