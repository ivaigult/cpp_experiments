add_executable(pp_gen pp_gen.c)

add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/pp.h"
  COMMAND $<TARGET_FILE:pp_gen> 100 > pp.h
  DEPENDS $<TARGET_FILE:pp_gen>
  COMMENT "Generating pp.h"
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(gen_header DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/pp.h")

add_executable(pp_test pp_test.c)
target_include_directories(pp_test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(pp_test gen_header)

add_executable(matrix examples/matrix.c)
target_include_directories(matrix PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(matrix gen_header)

