#include <iostream>

#include <spdlog/spdlog.h>

#include "efl/util/fmt_util.hpp"
#include "efl/sources/yahoo/yahoo_provider.hpp"

using namespace efl::sources::yahoo;

int main(int argc, char *argv[])
{
    yahoo_provider provider;

    auto quotes = provider.quote("SGO.PA,AAPL,T,AMC,META");
    for (auto& quote: quotes) {
        spdlog::info("Symbol: \t{}\t LastPx:", quote.symbol, quote.regularMarketPrice);
    }
    
    date::year_month_day start{date::year(2022), date::month(1), date::day(1)};
    date::year_month_day end{date::year(2022), date::month(11), date::day(1)};
    auto histo_data = provider.histo("AMC", start, end);
    for (auto& kvp : histo_data._data) {
        spdlog::info("{}: {}", kvp.first, kvp.second.to_string());
    }
    return 0;
}