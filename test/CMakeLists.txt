Set (TEST_SOURCES 
    efl/book_tests.cpp
    efl/stock_data_tests.cpp
    )

Add_Executable ( efl_tests efl_tests.cpp ${TEST_SOURCES})

Target_Link_Libraries ( efl_tests
    strat_sim_lib
    gtest_main gmock
)