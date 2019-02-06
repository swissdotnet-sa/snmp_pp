cmake_minimum_required(VERSION 3.12)
project(snmp++ VERSION 3.3.11)

message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Version: ${PROJECT_VERSION_MAJOR}")
message(STATUS "Version: ${PROJECT_VERSION_MINOR}")
message(STATUS "Version: ${PROJECT_VERSION_PATCH}")

add_compile_definitions(SNMP_PP_VERSION_STRING="${PROJECT_VERSION}")
add_compile_definitions(SNMP_PP_VERSION=${PROJECT_VERSION_MAJOR})
add_compile_definitions(SNMP_PP_RELEASE=${PROJECT_VERSION_MINOR})
add_compile_definitions(SNMP_PP_PATCHLEVEL=${PROJECT_VERSION_PATCH})

add_library(snmp++
    src/address.cpp
    src/asn1.cpp
    src/auth_priv.cpp
    src/counter.cpp
    src/ctr64.cpp
    src/eventlist.cpp
    src/eventlistholder.cpp
    src/gauge.cpp
    src/integer.cpp
    src/log.cpp
    src/md5c.cpp
    src/mp_v3.cpp
    src/msec.cpp
    src/msgqueue.cpp
    src/notifyqueue.cpp
    src/octet.cpp
    src/oid.cpp
    src/pdu.cpp
    src/reentrant.cpp
    src/sha.cpp
    src/snmpmsg.cpp
    src/target.cpp
    src/timetick.cpp
    src/usm_v3.cpp
    src/uxsnmp.cpp
    src/v3.cpp
    src/vb.cpp
)
add_library(snmp++::snmp++ ALIAS snmp++)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

target_link_libraries(snmp++
    PUBLIC
        ${OPENSSL_SSL_LIBRARY}
        ${OPENSSL_CRYPTO_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(snmp++
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    snmp++ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

install(TARGETS snmp++
        EXPORT snmp++Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*")

install(EXPORT snmp++Targets
        FILE snmp++Config.cmake
        NAMESPACE snmp++::
        DESTINATION lib/cmake/snmp++
)

option(BUILD_EXAMPLES "Build examples." OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(consoleExamples)
endif()