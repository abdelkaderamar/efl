#include "yahoo_quote.hpp"

namespace efl::sources::yahoo
{
    template <typename T>
    void get_if_contain(const nlohmann::json &j, const std::string &key,
                        T &property)
    {
        if (j.contains(key))
        {
            j.at(key).get_to(property);
        }
    }
    void yahoo_quote_t::from_json(const nlohmann::json &j)
    {
        get_if_contain(j, "region", region);
        get_if_contain(j, "quoteType", quoteType);
        get_if_contain(j, "typeDisp", typeDisp);
        get_if_contain(j, "quoteSourceName", quoteSourceName);
        get_if_contain(j, "customPriceAlertConfidence", customPriceAlertConfidence);
        get_if_contain(j, "regularMarketChangePercent", regularMarketChangePercent);
        get_if_contain(j, "regularMarketPrice", regularMarketPrice);
        get_if_contain(j, "currency", currency);
        get_if_contain(j, "exchangeTimezoneName", exchangeTimezoneName);
        get_if_contain(j, "exchangeTimezoneShortName", exchangeTimezoneShortName);
        get_if_contain(j, "gmtOffSetMilliseconds", gmtOffSetMilliseconds);
        get_if_contain(j, "market", market);
        get_if_contain(j, "exchange", exchange);
        get_if_contain(j, "shortName", shortName);
        get_if_contain(j, "longName", longName);
        get_if_contain(j, "marketState", marketState);
        get_if_contain(j, "firstTradeDateMilliseconds", firstTradeDateMilliseconds);
        get_if_contain(j, "regularMarketDayLow", regularMarketDayLow);
        get_if_contain(j, "regularMarketVolume", regularMarketVolume);
        get_if_contain(j, "regularMarketPreviousClose", regularMarketPreviousClose);
        get_if_contain(j, "bid", bid);
        get_if_contain(j, "ask", ask);
        get_if_contain(j, "bidSize", bidSize);
        get_if_contain(j, "askSize", askSize);
        get_if_contain(j, "fullExchangeName", fullExchangeName);
        get_if_contain(j, "financialCurrency", financialCurrency);
        get_if_contain(j, "regularMarketOpen", regularMarketOpen);
        get_if_contain(j, "averageDailyVolume3Month", averageDailyVolume3Month);
        get_if_contain(j, "averageDailyVolume10Day", averageDailyVolume10Day);
        get_if_contain(j, "fiftyTwoWeekLowChange", fiftyTwoWeekLowChange);
        get_if_contain(j, "fiftyTwoWeekLowChangePercent", fiftyTwoWeekLowChangePercent);
        get_if_contain(j, "fiftyTwoWeekRange", fiftyTwoWeekRange);
        get_if_contain(j, "fiftyTwoWeekHighChange", fiftyTwoWeekHighChange);
        get_if_contain(j, "fiftyTwoWeekHighChangePercent", fiftyTwoWeekHighChangePercent);
        get_if_contain(j, "fiftyTwoWeekLow", fiftyTwoWeekLow);
        get_if_contain(j, "fiftyTwoWeekHigh", fiftyTwoWeekHigh);
        get_if_contain(j, "earningsTimestamp", earningsTimestamp);
        get_if_contain(j, "earningsTimestampStart", earningsTimestampStart);
        get_if_contain(j, "earningsTimestampEnd", earningsTimestampEnd);
        get_if_contain(j, "trailingAnnualDividendRate", trailingAnnualDividendRate);
        get_if_contain(j, "trailingPE", trailingPE);
        get_if_contain(j, "trailingAnnualDividendYield", trailingAnnualDividendYield);
        get_if_contain(j, "epsTrailingTwelveMonths", epsTrailingTwelveMonths);
        get_if_contain(j, "epsForward", epsForward);
        get_if_contain(j, "sharesOutstanding", sharesOutstanding);
        get_if_contain(j, "bookValue", bookValue);
        get_if_contain(j, "fiftyDayAverage", fiftyDayAverage);
        get_if_contain(j, "fiftyDayAverageChange", fiftyDayAverageChange);
        get_if_contain(j, "fiftyDayAverageChangePercent", fiftyDayAverageChangePercent);
        get_if_contain(j, "twoHundredDayAverage", twoHundredDayAverage);
        get_if_contain(j, "twoHundredDayAverageChange", twoHundredDayAverageChange);
        get_if_contain(j, "twoHundredDayAverageChangePercent", twoHundredDayAverageChangePercent);
        get_if_contain(j, "marketCap", marketCap);
        get_if_contain(j, "forwardPE", forwardPE);
        get_if_contain(j, "priceToBook", priceToBook);
        get_if_contain(j, "sourceInterval", sourceInterval);
        get_if_contain(j, "exchangeDataDelayedBy", exchangeDataDelayedBy);
        get_if_contain(j, "averageAnalystRating", averageAnalystRating);
        get_if_contain(j, "priceHint", priceHint);
        get_if_contain(j, "regularMarketChange", regularMarketChange);
        get_if_contain(j, "regularMarketTime", regularMarketTime);
        get_if_contain(j, "regularMarketDayHigh", regularMarketDayHigh);
        get_if_contain(j, "regularMarketDayRange", regularMarketDayRange);
        get_if_contain(j, "symbol", symbol);
    }
}
