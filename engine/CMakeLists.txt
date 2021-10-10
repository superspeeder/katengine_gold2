project("Engine")

file(GLOB_RECURSE ENGINE_SOURCE CONFIGURE_DEPENDS src/cpp/*.cpp )

add_library(katengine ${ENGINE_SOURCE})
target_include_directories(katengine PUBLIC src/include)
target_link_libraries(katengine PUBLIC glm::glm glad::glad glfw spdlog::spdlog)
add_library(kat::engine ALIAS katengine)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(katengine PUBLIC KAT_DEBUG)
endif()
