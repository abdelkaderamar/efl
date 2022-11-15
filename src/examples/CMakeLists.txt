Add_Executable ( dummy_strat 
   dummy_strat_simulator.cpp 
   dummy_strat.cpp )

Target_link_libraries ( dummy_strat
   strat_sim_lib)

Add_Executable ( yahoo_finance_request 
   yahoo_finance_request.cpp 
)

Target_link_libraries ( yahoo_finance_request
   efl_net)

Add_Executable ( yahoo_provider_example 
   yahoo_provider_example.cpp 
)

Target_link_libraries ( yahoo_provider_example
   efl_yahoo strat_sim_lib)

Add_Executable ( sqlite_manager_example 
sqlite_manager_example.cpp 
)

Target_link_libraries ( sqlite_manager_example
   efl_yahoo strat_sim_lib
   #efl_persistence 
)

Add_Executable ( investing_ticker_yahoo_checker
   investing_ticker_yahoo_checker.cpp
)

Target_link_libraries ( investing_ticker_yahoo_checker
   efl_yahoo strat_sim_lib
   #efl_persistence 
)
