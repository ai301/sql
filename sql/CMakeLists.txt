include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${SQLITE_INCLUDE_DIR})

link_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(${SQLITE_DEFINITIONS})

set(sql_library_SRCS
  connection.cc
  meta_table.cc
  ref_counted.cc
  statement.cc
  transaction.cc
)

set(sql_library_HDRS
  basictypes.h
  build_config.h
  connection.h
  meta_table.h
  port.h
  ref_counted.h
  statement.h
  transaction.h
  utility.h
)

add_library(sql ${sql_library_SRCS} ${sql_library_HDRS})
target_link_libraries(sql ${SQLITE_LIBRARIES})