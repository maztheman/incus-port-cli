add_executable(incus-port-cli "")

target_sources(incus-port-cli PRIVATE main.cpp runit.cpp)

target_link_libraries(incus-port-cli PRIVATE restinio::restinio fmt::fmt)