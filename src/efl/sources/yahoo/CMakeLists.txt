add_library ( efl_yahoo
  yahoo_provider.cpp
  yahoo_config.cpp
  yahoo_helper.cpp
  yahoo_quote.cpp
  yahoo_histo_data.cpp
)

target_link_libraries( efl_yahoo
  efl_net
  nlohmann_json::nlohmann_json )