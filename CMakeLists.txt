# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
cmake_minimum_required(VERSION 3.0)


include_directories (/usr/local/include/)

message(${PROJECT_SOURCE_DIR})

link_directories(${PROJECT_SOURCE_DIR}/../)

add_executable (motion motion_example.c appControlHandler.c)

target_link_libraries(motion freespace m)


