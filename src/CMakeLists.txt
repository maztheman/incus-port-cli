add_executable(incus-port-cli "")

target_sources(incus-port-cli PRIVATE main.cpp runit.cpp)

target_link_libraries(incus-port-cli PRIVATE restinio::restinio fmt::fmt)

if (PROJECT_IS_TOP_LEVEL)
    install(TARGETS incus-port-cli DESTINATION bin)
endif()