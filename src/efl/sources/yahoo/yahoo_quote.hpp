#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace efl::sources::yahoo
{
    struct yahoo_quote_t
    {
        void from_json(const nlohmann::json &j);

        // "language": "en-US", // not used
        std::string region;          // "US",
        std::string quoteType;       // "EQUITY",
        std::string typeDisp;        // "Equity",
        std::string quoteSourceName; // "Delayed Quote",
        // "triggerable": false, // not used
        std::string customPriceAlertConfidence; // "LOW",
        double regularMarketChangePercent;      // 3.6943297,
        double regularMarketPrice;              // 40.98,
        std::string currency;                   // "EUR",
        // "messageBoardId": "finmb_875777", // not used
        std::string exchangeTimezoneName;      // "Europe/Paris",
        std::string exchangeTimezoneShortName; // "CEST",
        double gmtOffSetMilliseconds;          // 7200000,
        std::string market;                    // "fr_market",
        // "esgPopulated": false,
        std::string exchange;              // "PAR",
        std::string shortName;             // "SAINT GOBAIN",
        std::string longName;              // "Compagnie de Saint-Gobain S.A.",
        std::string marketState;           // "CLOSED",
        double firstTradeDateMilliseconds; // 946886400000,
        double regularMarketDayLow;   // 39.92,
        double regularMarketVolume;        // 1265265,
        double regularMarketPreviousClose; // 39.52,
        double bid;
        double ask;
        double bidSize;
        double askSize;
        std::string fullExchangeName;             // "Paris",
        std::string financialCurrency;            // "EUR",
        double regularMarketOpen;                 // 40.1,
        double averageDailyVolume3Month;          // 1258290,
        double averageDailyVolume10Day;           // 1164960,
        double fiftyTwoWeekLowChange;             // 1.7949982,
        double fiftyTwoWeekLowChangePercent;      // 0.045808297,
        std::string fiftyTwoWeekRange;            // "39.185 - 67.12",
        double fiftyTwoWeekHighChange;            // -26.140003,
        double fiftyTwoWeekHighChangePercent;     // -0.38945177,
        double fiftyTwoWeekLow;                   // 39.185,
        double fiftyTwoWeekHigh;                  // 67.12,
        double earningsTimestamp;                 // 1658930400,
        double earningsTimestampStart;            // 1658930400,
        double earningsTimestampEnd;              // 1658930400,
        double trailingAnnualDividendRate;        // 1.63,
        double trailingPE;                        // 8.609243,
        double trailingAnnualDividendYield;       // 0.04124494,
        double epsTrailingTwelveMonths;           // 4.76,
        double epsForward;                        // 5.73,
        double sharesOutstanding;                 // 512302016,
        double bookValue;                         // 44.323,
        double fiftyDayAverage;                   // 42.8002,
        double fiftyDayAverageChange;             // -1.8202019,
        double fiftyDayAverageChangePercent;      // -0.04252788,
        double twoHundredDayAverage;              // 53.164875,
        double twoHundredDayAverageChange;        // -12.1848755,
        double twoHundredDayAverageChangePercent; // -0.22919033,
        double marketCap;                         // 20994136064,
        double forwardPE;                         // 7.1518326,
        double priceToBook;                       // 0.92457634,
        double sourceInterval;                    // 15,
        double exchangeDataDelayedBy;             // 15,
        std::string averageAnalystRating;         // "2.0 - Buy",
        // "tradeable": false,
        // "cryptoTradeable": false,
        double priceHint;                  // 2,
        double regularMarketChange;        // 1.4599991,
        double regularMarketTime;          // 1662133061,
        double regularMarketDayHigh;       // 41.165,
        std::string regularMarketDayRange; // "39.92 - 41.165",
        std::string symbol;                // "SGO.PA"
    };
}