Add_Library ( efl_net
  https_client.cpp
  https_client_helper.cpp
)

Target_Link_Libraries(efl_net ${Boost_LIBRARIES} ssl crypto boost_system)

Target_Link_Libraries(efl_net spdlog)
