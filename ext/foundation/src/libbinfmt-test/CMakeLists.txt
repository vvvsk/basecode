cmake_minimum_required(VERSION 3.16)
project(basecode-binfmt-test)

add_executable(
    ${PROJECT_NAME}

    test.h
    main.cpp
    ar_tests.cpp
    pe_tests.cpp
    elf_tests.cpp
    coff_tests.cpp
)
target_link_libraries(${PROJECT_NAME} basecode-core basecode-binfmt)
if (NOT MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE -fuse-ld=lld)
endif ()
target_include_directories(
    ${PROJECT_NAME}

    PRIVATE ${PROJECT_SOURCE_DIR}
            ${PROJECT_DIR_BASE}/ext/catch2-2.8.0/single_include
)
