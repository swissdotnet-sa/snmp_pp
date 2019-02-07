add_executable(snmp_pp-tests
    test_main.cpp
    parse_trap_test.cpp)

find_package(doctest)

target_link_libraries(snmp_pp-tests
    PRIVATE
    snmp_pp::snmp_pp
    doctest::doctest
)