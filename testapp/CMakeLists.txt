project("TestApp")

file(GLOB_RECURSE TESTAPP_SOURCE CONFIGURE_DEPENDS src/cpp/*.cpp )
add_executable(testapp ${TESTAPP_SOURCE})
target_include_directories(testapp PUBLIC src/include)
target_link_libraries(testapp PRIVATE kat::engine)
