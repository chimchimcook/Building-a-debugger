add_library(libsdb libsdb.cpp)
target_sources(
	libsdb
	PRIVATE
	process.cpp
)
add_library(sdb::libsdb ALIAS libsdb)

# lib default output name: lib${target_name}.a
set_target_properties(
	libsdb
	PROPERTIES OUTPUT_NAME sdb
)

target_compile_features(libsdb PUBLIC cxx_std_17)
target_include_directories(libsdb
	PUBLIC

	# The user uses an installed libsdb.
	$<INSTALL_INTERFACE:include>

	# The user uses a version in the build tree, likely linking the sdb executable.
	$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_SOURCE_DIR}/src/include
)

# where it is installed.
include(GNUInstallDirs)
install(TARGETS libsdb
	EXPORT sdb-targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# install the public headers.
install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# save export information to a file.
install(
	EXPORT sdb-targets
	FILE sdb-config.cmake
	NAMESPACE sdb::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sdb
)
