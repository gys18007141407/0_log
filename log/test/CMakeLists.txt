add_compile_options(-std=c++11 -I ${PROJECT_SOURCE_DIR}/src/include)

add_executable(test_logfile LogFileTest.cpp)
add_executable(test_sync_log SyncLogTest.cpp)
add_executable(test_async_log AsyncLogTest.cpp)

target_link_libraries(test_logfile log pthread)
target_link_libraries(test_sync_log log pthread)
target_link_libraries(test_async_log log pthread)