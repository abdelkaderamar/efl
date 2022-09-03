add_subdirectory ( util )
add_subdirectory ( sources )

Add_Library ( strat_sim_lib
  stock_data.cpp
  csv_parser.cpp
  book.cpp
  abstract_simulator.cpp
  simulator_config.cpp
  book_config.cpp
  csv_helper.cpp
  file_helper.cpp
  config_result.cpp
  )
