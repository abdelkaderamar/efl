#include "efl/simulator_config.hpp"
#include "efl/stock_data.hpp"

#include "dummy_strat_simulator.hpp"



int main(int argc, char* argv[]) {
    efl::simulator_config_t config;
    std::map<std::string, std::vector<efl::stock_data_t>> data;
    
    efl::dummy_strat_simulator simulator{config, data};

    return 0;
}