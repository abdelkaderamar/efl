Add_Executable ( dummy_strat 
   dummy_strat_simulator.cpp 
   dummy_strat.cpp )

Target_link_libraries ( dummy_strat
   strat_sim_lib)

Add_Executable ( yahoo_finance_request 
   yahoo_finance_request.cpp 
)

Target_link_libraries ( yahoo_finance_request
   efl_net pthread)

Add_Executable ( yf_get_histo_data 
   yf_get_histo_data.cpp 
)

Target_link_libraries ( yf_get_histo_data
   efl_yahoo strat_sim_lib pthread)

Add_Executable ( sqlite_manager_example 
sqlite_manager_example.cpp 
)

Target_link_libraries ( sqlite_manager_example
   efl_yahoo strat_sim_lib
   #efl_persistence 
   pthread
)

Add_Executable ( yf_get_quotes
   yf_get_quotes.cpp
)

Target_link_libraries ( yf_get_quotes
   efl_yahoo strat_sim_lib
   pthread)

Configure_File (
   cac40.json 
   cac40.json
)
