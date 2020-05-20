#add include to directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

#set the proper macros
set(LIBRARY_SRVR server)
set(LIBRARY_RASP raspio)
set(LIBRARY_LOGG jvlogger)

set(SRC_FILES_SRVR libserver.c)
set(SRC_FILES_RASP libraspio.c)
set(SRC_FILES_LOGG jvlogger.c)

set(INCLUDE_FILES_SRVR ${CMAKE_CURRENT_SOURCE_DIR}/../include/libserver.h)
set(INCLUDE_FILES_RASP ${CMAKE_CURRENT_SOURCE_DIR}/../include/libraspio.h)
set(INCLUDE_FILES_LOGG ${CMAKE_CURRENT_SOURCE_DIR}/../include/jvlogger.h)

#add the library
add_library(${LIBRARY_SRVR} SHARED ${SRC_FILES_SRVR} ${INCLUDE_FILES_SRVR})
add_library(${LIBRARY_RASP} SHARED ${SRC_FILES_RASP} ${INCLUDE_FILES_RASP})
add_library(${LIBRARY_LOGG} SHARED ${SRC_FILES_LOGG} ${INCLUDE_FILES_LOGG})

#installing the library
install (TARGETS ${LIBRARY_SRVR} DESTINATION lib)
install (TARGETS ${LIBRARY_RASP} DESTINATION lib)
install (TARGETS ${LIBRARY_LOGG} DESTINATION lib)

install (FILES ${INCLUDE_FILES_SRVR} DESTINATION include)
install (FILES ${INCLUDE_FILES_RASP} DESTINATION include)
install (FILES ${INCLUDE_FILES_LOGG} DESTINATION include)
