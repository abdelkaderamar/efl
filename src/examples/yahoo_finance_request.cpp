#include <iostream>

#include "efl/util/net/https_client_helper.hpp"

int main(int argc, char *argv[])
{
    std::string result = efl::util::net::https_client_helper::request("query1.finance.yahoo.com", "/v7/finance/quote?symbols=SGO.PA");

    std::cout << std::endl
              << result << std::endl;
}
