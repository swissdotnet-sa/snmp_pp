project(snmp++)
cmake_minimum_required(VERSION 2.8)

add_executable(snmpGet snmpGet.cpp)
target_link_libraries(snmpGet
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpSet snmpSet.cpp)
target_link_libraries(snmpSet
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpNext snmpNext.cpp)
target_link_libraries(snmpNext
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpNextAsync snmpNextAsync.cpp)
target_link_libraries(snmpNextAsync
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpWalk snmpWalk.cpp)
target_link_libraries(snmpWalk
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpBulk snmpBulk.cpp)
target_link_libraries(snmpBulk
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpTraps snmpTraps.cpp)
target_link_libraries(snmpTraps
    PUBLIC
        snmp++::snmp++
)

add_executable(receive_trap receive_trap.cpp)
target_link_libraries(receive_trap
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpInform snmpInform.cpp)
target_link_libraries(snmpInform
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpPasswd snmpPasswd.cpp)
target_link_libraries(snmpPasswd
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpWalkThreads snmpWalkThreads.cpp)
target_link_libraries(snmpWalkThreads
    PUBLIC
        snmp++::snmp++
)

add_executable(snmpDiscover snmpDiscover.cpp)
target_link_libraries(snmpDiscover
    PUBLIC
        snmp++::snmp++
)

add_executable(test_app test_app.cpp)
target_link_libraries(test_app
    PUBLIC
        snmp++::snmp++
)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
find_package(boost 1.69 EXACT)
add_executable(receive_trap_asio receive_trap_asio.cpp)
target_link_libraries(receive_trap_asio
    PUBLIC
        snmp++::snmp++
        boost::boost
)