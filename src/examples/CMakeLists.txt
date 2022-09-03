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
   efl_yahoo )
