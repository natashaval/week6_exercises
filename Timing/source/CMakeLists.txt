# add Timing executable
add_executable(timing main.cpp)
# target_link_libraries(timing PUBLIC eigen)
# add_subdirectory(eigen)
# target_include_directories(timing PUBLIC ${CMAKE_SOURCE_DIR}/include /home/natashaval/eigen-3.4.0/)

target_include_directories(timing PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(timing PUBLIC /home/natashaval/eigen-3.4.0/)
# target_include_directories means add /include and /home/natashaval/eigen-3.4.0/ to `timing`
# target_include_directories(eigen PUBLIC /home/natashaval/eigen-3.4.0/) # IS WRONG