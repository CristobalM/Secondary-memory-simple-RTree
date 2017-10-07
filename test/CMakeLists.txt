project(tests)
add_subdirectory(libs/googletest/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

if (WIN32)
    set(BOOST_ROOT "C:/Program Files (x86)/boost_1_60_0/")
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREAD ON)

    include_directories(${BOOST_ROOT})
    link_directories(${BOOST_ROOT}/stage/lib) # add this before add_executable()
endif()



add_executable(tests IOControlTest.cpp ${SOURCE_FILES} RandomGenerationTest.cpp SearchTest.cpp)

target_link_libraries(tests RTreeLib gtest gtest_main)


add_executable(auxtests AuxTests.cpp ${SOURCE_FILES})
target_link_libraries(auxtests RTreeLib gtest gtest_main)



if(NOT MSVC)
    find_package(Boost REQUIRED COMPONENTS serialization filesystem system)
    if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        #target_link_libraries(tests ${Boost_LIBRARIES})
        #target_link_libraries(auxtests ${Boost_LIBRARIES})
    endif()
endif()