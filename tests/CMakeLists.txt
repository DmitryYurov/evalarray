set(evalarray_dir ${CMAKE_CURRENT_SOURCE_DIR}/../evalarray)
set(include_files
  ${evalarray_dir}/evalarray.h
)

# basic operations on evalarray
add_executable(BasicOps ${CMAKE_CURRENT_SOURCE_DIR}/BasicOps.cpp ${include_files})
target_include_directories(BasicOps PRIVATE ${evalarray_dir} ${CMAKE_CURRENT_SOURCE_DIR})
add_test(BasicOps ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BasicOps)
