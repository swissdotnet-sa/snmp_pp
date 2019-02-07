cmake_minimum_required(VERSION 3.12)
project(snmp_pp VERSION 3.3.11)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

add_compile_definitions(SNMP_PP_VERSION_STRING="${PROJECT_VERSION}")
add_compile_definitions(SNMP_PP_VERSION=${PROJECT_VERSION_MAJOR})
add_compile_definitions(SNMP_PP_RELEASE=${PROJECT_VERSION_MINOR})
add_compile_definitions(SNMP_PP_PATCHLEVEL=${PROJECT_VERSION_PATCH})

add_library(snmp_pp
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
add_library(snmp_pp::snmp_pp ALIAS snmp_pp)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

target_link_libraries(snmp_pp
    PUBLIC
        ${OPENSSL_SSL_LIBRARY}
        ${OPENSSL_CRYPTO_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(snmp_pp
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

install(TARGETS snmp_pp
        EXPORT snmp_ppTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*")

install(EXPORT snmp_ppTargets
        FILE snmp_ppConfig.cmake
        NAMESPACE snmp_pp::
        DESTINATION lib/cmake/snmp_pp
)

option(BUILD_EXAMPLES "Build examples." OFF)
if(BUILD_EXAMPLES)
    add_subdirectory(consoleExamples)
endif()

option(BUILD_TESTS "Build tests." OFF)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()