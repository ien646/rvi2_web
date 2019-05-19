set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin/rvi2_web)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin/rvi2_web)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin/rvi2_web)

set(RVI2_WEB_SOURCES
	src/main.cpp
    src/cozy_widget.cpp
    src/frame_utils.cpp
)

add_executable(rvi2_web ${RVI2_WEB_SOURCES})

target_include_directories(
    rvi2_web 
    PUBLIC include
    PRIVATE $<TARGET_PROPERTY:wt,INCLUDE_DIRECTORIES>
)

target_link_libraries(rvi2_web rvi2.host wt	wthttp)

get_property(RVI2_DATA_DIR GLOBAL PROPERTY RVI2_DATA_DIR)

file(COPY ${PROJECT_SOURCE_DIR}/bin/rvi2_web/shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${RVI2_DATA_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ./css DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ./js DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
