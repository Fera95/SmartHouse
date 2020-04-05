 #add include to directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

#set the proper macros
set(LIBRARY_SRVR server)
set(LIBRARY_RASP raspio)

set(SRC_FILES_SRVR libserver.c)
set(SRC_FILES_RASP libraspio.c)

set(INCLUDE_FILES_SRVR ${CMAKE_CURRENT_SOURCE_DIR}/../include/libserver.h)
set(INCLUDE_FILES_RASP ${CMAKE_CURRENT_SOURCE_DIR}/../include/libraspio.h)

#add the library
add_library(${LIBRARY_SRVR} SHARED ${SRC_FILES_SRVR} ${INCLUDE_FILES_SRVR})
add_library(${LIBRARY_RASP} SHARED ${SRC_FILES_RASP} ${INCLUDE_FILES_RASP})

#installing the library
install (TARGETS ${LIBRARY_SRVR} DESTINATION lib)
install (TARGETS ${LIBRARY_RASP} DESTINATION lib)

install (FILES ${INCLUDE_FILES_SRVR} DESTINATION include)
install (FILES ${INCLUDE_FILES_RASP} DESTINATION include)
