cmake_minimum_required(VERSION 3.21)

#   Read project version from local file
file(READ "${CMAKE_SOURCE_DIR}/VERSION" PROJECT_VERSION_FILE)
set(PROJECT_VERSION "${PROJECT_VERSION_FILE}")
string(STRIP "${PROJECT_VERSION}" PROJECT_VERSION)

#   The project definition
project(Z-Calculator.Derivative
        LANGUAGES C
        VERSION ${PROJECT_VERSION}
)

#   Required C-lang standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

#   Import sources and headers
include(include/include.cmake)
include(src/src.cmake)

#   Add static library
add_library(libzcd-static STATIC ${SOURCES} ${HEADERS})
target_include_directories(libzcd-static PRIVATE ${INCPATH})

#   Add shared library
add_library(libzcd-shared SHARED ${SOURCES} ${HEADERS})
target_include_directories(libzcd-shared PRIVATE ${INCPATH})

#   Add the executable target
add_executable(zcd
        ${SOURCES} ${HEADERS}
        src/Console.c
        src/Console.h
        src/Printer.c
        src/Printer.h
)
target_include_directories(zcd PRIVATE ${INCPATH})


#  Install all interface files
install(FILES ${HEADERS}
        DESTINATION include)

#   Install all libs
install(TARGETS libzcd-static libzcd-shared
        EXPORT libzcd
        LIBRARY DESTINATION lib         # Shared library install target directory
        ARCHIVE DESTINATION lib         # Static library install target directory
)

#   Install the executable
install(TARGETS zcd
        EXPORT zcd
        RUNTIME DESTINATION bin
)

