set(executable_name all_tests)

set(evalarray_dir ${CMAKE_CURRENT_SOURCE_DIR}/../evalarray)
set(include_files
  ${evalarray_dir}/evalarray.h
)

set(source_files
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(${executable_name} ${source_files} ${include_files})
target_include_directories(${executable_name} PRIVATE ${evalarray_dir} ${CMAKE_CURRENT_SOURCE_DIR})
add_test(all ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${executable_name})
