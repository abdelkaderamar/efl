Add_Executable ( dummy_strat 
   dummy_strat_simulator.cpp 
   dummy_strat.cpp )

Target_link_libraries ( dummy_strat
   strat_sim_lib)
