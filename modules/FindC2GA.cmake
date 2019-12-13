# Find Libc2ga
#
#  C2GA_FOUND        - True if Libc2ga found.
#  C2GA_INCLUDE_DIRS - where to find Libc2ga include files
#  C2GA_LIBRARIES    - where to find Libc2ga binary libraries


# find include path
find_path (C2GA_INCLUDE_DIR 
		NAMES c2ga
		HINTS /usr/local/include)

# find library file
find_library (C2GA_LIBRARY 
		NAMES c2ga
		HINTS /usr/local/lib/ )


set(C2GA_LIBRARIES ${C2GA_LIBRARY})
set(C2GA_INCLUDE_DIRS ${C2GA_INCLUDE_DIR})

# handle the QUIETLY and REQUIRED arguments and set C2GA_FOUND to TRUE if
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (C2GA DEFAULT_MSG 
                                   C2GA_LIBRARIES C2GA_INCLUDE_DIRS)

mark_as_advanced(C2GA_INCLUDE_DIR C2GA_LIBRARIE)





