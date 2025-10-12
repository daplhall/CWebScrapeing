include(FetchContent)
include(ExternalProject)
#========= Req ==========#
find_package(CURL REQUIRED)
find_package(LibXml2 REQUIRED)


FetchContent_Declare(
    robotstxt_download
    GIT_REPOSITORY git@github.com:google/robotstxt.git
    GIT_TAG 86d5836ba2d5a0b6b938ab49501be0e09d9c276c
)
FetchContent_MakeAvailable(robotstxt_download)
target_include_directories(robots
    PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/_deps/robotstxt_download-src/
)


#========= GTest ==========#
if (CMAKE_TESTING_ENABLED)
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)

	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG        v1.17.0
	)

	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest) # might need to be placed together with robots
endif()
