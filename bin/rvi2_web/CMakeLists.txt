set(RVI2_WEB_SOURCES
	src/main.cpp
)

add_executable(rvi2_web ${RVI2_WEB_SOURCES})
target_include_directories(rvi2_web 
	PUBLIC include
	PUBLIC ${CMAKE_SOURCE_DIR}/third-party/wt/src
	PUBLIC ${CMAKE_BINARY_DIR}/third-party/wt)
	
target_link_libraries(rvi2_web 
	rvi2.host 
	wt
	wthttp
)

if("${BOOST_LIBRARYDIR}" STREQUAL "")
	set(BOOST_LIBRARYDIR $ENV{BOOST_LIBRARYDIR})
	if("${BOOST_LIBRARYDIR}" STREQUAL "")
		set(BOOST_LIBRARYDIR ${BOOST_LIB_DIRS})
		if("${BOOST_LIBRARYDIR}" STREQUAL "")
			message(FATAL_ERROR "BOOST_LIBRARYDIR Not set!")
		endif()
	endif()
endif()

target_link_directories(rvi2_web PUBLIC ${BOOST_LIBRARYDIR})