
#-----------------------------------------------------------------------------
set(MODULE_NAME FinslerBacktracing)

#-----------------------------------------------------------------------------

#
# SlicerExecutionModel
#
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

#
# VTK
#
if(${VTK_VERSION_MAJOR} GREATER 5)
  set(${PROJECT_NAME}_VTK_COMPONENTS
    vtkCommonCore
    vtkIOLegacy
    vtkIOXML
    )
  find_package(VTK 6.1 COMPONENTS ${${PROJECT_NAME}_VTK_COMPONENTS} REQUIRED)
  include(${VTK_USE_FILE})
endif()

#-----------------------------------------------------------------------------
SEMMacroBuildCLI(
  NAME ${MODULE_NAME}
  LOGO_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/Resources/NAMICLogo.h
  TARGET_LIBRARIES ${ITK_LIBRARIES} ${VTK_LIBRARIES}
  INCLUDE_DIRECTORIES
     ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
  )
#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

