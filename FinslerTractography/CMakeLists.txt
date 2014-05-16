
#-----------------------------------------------------------------------------
set(MODULE_NAME FinslerTractography)

#-----------------------------------------------------------------------------
SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  LOGO_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/Resources/NAMICLogo.h
  TARGET_LIBRARIES ${ITK_LIBRARIES}
  INCLUDE_DIRECTORIES
     ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
     ${CMAKE_CURRENT_SOURCE_DIR}/HARDI-ITK
  ADDITIONAL_SRCS
     ${CMAKE_CURRENT_SOURCE_DIR}/HARDI-ITK/sphericalHarmonics.cxx
     ${CMAKE_CURRENT_SOURCE_DIR}/HARDI-ITK/sh2hot.cxx
  )
#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()
