set(target_name tests)
set(evalarray_dir ${CMAKE_CURRENT_SOURCE_DIR}/../evalarray)

set(SOURCES
    ${evalarray_dir}/evalarray.h
    ITest.h
    TestContainer.h
    main.cpp
    BasicOperations.cpp
    TestContainer.cpp
)

# basic operations on evalarray
add_executable(${target_name} ${SOURCES})
target_include_directories(${target_name} PRIVATE ${evalarray_dir} ${CMAKE_CURRENT_SOURCE_DIR})
