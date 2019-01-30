#Find libspnav

find_path(LIBSPNAV_INCLUDE_DIR NAMES spnav.h HINTS ${LIBSPNAV_DIR}/include/)
find_library(LIBSPNAV_LIBRARY spnav HINTS ${LIBSPNAV_DIR} PATH_SUFFIXES lib lib64)


mark_as_advanced(LIBSPNAV_INCLUDE_DIR LIBSPNAV_LIBRARY)


if(LIBSPNAV_INCLUDE_DIR AND LIBSPNAV_LIBRARY)
    add_library(libspnav::libspnav UNKNOWN IMPORTED)
    set_target_properties(libspnav::libspnav PROPERTIES 
                            IMPORTED_LOCATION ${LIBSPNAV_LIBRARY}
                            INTERFACE_INCLUDE_DIRECTORIES ${LIBSPNAV_INCLUDE_DIR})
    
endif()


include(FindPackageHandleStandardArgs)

set(FAIL_MESSAGE "could not find libspnav. If it is installed in a non-standard location, try setting LIBSPNAV_DIR to the root of the installation")

find_package_handle_standard_args(libspnav ${FAIL_MESSAGE} LIBSPNAV_LIBRARY LIBSPNAV_INCLUDE_DIR)

