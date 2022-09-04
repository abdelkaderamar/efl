#include <iostream>

#include "efl/sources/yahoo/yahoo_provider.hpp"

using namespace efl::sources::yahoo;

int main(int argc, char *argv[])
{
    yahoo_provider provider;

    provider.quote("SGO.PA,AAPL,T,AMC,META");

    provider.histo("AMC");
    return 0;
}