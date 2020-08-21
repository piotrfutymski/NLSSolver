cmake_minimum_required(VERSION 3.0.0)
project(NLSSolver VERSION 0.1.0)

find_package(wxWidgets COMPONENTS core base REQUIRED)

include_directories("include")
include_directories("boost_1_72_0")

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h" )


include(CTest)
include( "${wxWidgets_USE_FILE}" )
enable_testing()

add_executable(NLSSolver ${SOURCES} ${HEADERS})

target_link_libraries(NLSSolver mpfr)
target_link_libraries(NLSSolver ${wxWidgets_LIBRARIES})
target_link_libraries(NLSSolver dl)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
