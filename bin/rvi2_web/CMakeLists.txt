set(RVI2_WEB_SOURCES
	src/main.cpp
)

add_executable(rvi2_web ${RVI2_WEB_SOURCES})
target_include_directories(rvi2_web 
	PUBLIC include
	PUBLIC ${CMAKE_SOURCE_DIR}/third-party/wt/src
	PUBLIC ${CMAKE_BINARY_DIR}/third-party/wt)
target_link_libraries(rvi2_web rvi2.host wt wthttp)