
set(SOURCE_FILES  RTree.cpp RTree.h LinearSplit.cpp LinearSplit.h GreeneSplit.cpp GreeneSplit.h Rectangle.cpp Rectangle.h IOControl.cpp IOControl.h commontypes.h SplitHeuristic.cpp SplitHeuristic.h RTreeController.cpp RTreeController.h SplitBuilder.cpp SplitBuilder.h FilenameGenerator.cpp FilenameGenerator.h RandomRectangleGenerator.cpp RandomRectangleGenerator.h)
add_library(RTreeLib ${SOURCE_FILES})


if (WIN32)
    set(BOOST_ROOT "C:/Program Files (x86)/boost_1_60_0/")
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREAD ON)

    include_directories(${BOOST_ROOT})
    link_directories(${BOOST_ROOT}/stage/lib) # add this before add_executable()
endif()


add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} RTreeLib)



if(NOT MSVC)
    find_package(Boost REQUIRED COMPONENTS serialization)

    if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        target_link_libraries(${TARGET_NAME} ${Boost_LIBRARIES})
    endif()
endif()

#main.cpp