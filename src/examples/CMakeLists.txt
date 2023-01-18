Configure_File (
   cac40.json 
   cac40.json
)

###################
# dummy_strat
Add_Executable ( dummy_strat 
   dummy_strat_simulator.cpp 
   dummy_strat.cpp )
Target_link_libraries ( dummy_strat
   strat_sim_lib)

###################
# yf_request
Add_Executable ( yf_request 
   yf_request.cpp 
)
Target_link_libraries ( yf_request
   efl_net pthread)

###################
# yf_get_histo_data
Add_Executable ( yf_get_histo_data 
   yf_get_histo_data.cpp 
)
Target_link_libraries ( yf_get_histo_data
   efl_yahoo strat_sim_lib pthread)
###################

###################
# sqlite_manager_example
Add_Executable ( sqlite_manager_example 
sqlite_manager_example.cpp 
)
Target_link_libraries ( sqlite_manager_example
   efl_yahoo strat_sim_lib
   #efl_persistence 
   pthread
)

###################
# yf_get_quotes 
Add_Executable ( yf_get_quotes
   yf_get_quotes.cpp
)
Target_link_libraries ( yf_get_quotes
   efl_yahoo strat_sim_lib
   pthread)


###################
# yf_read_ohlcv_file
Add_Executable ( yf_read_ohlcv_file
yf_read_ohlcv_file.cpp
)
Target_link_libraries ( yf_read_ohlcv_file
efl_yahoo strat_sim_lib
pthread)