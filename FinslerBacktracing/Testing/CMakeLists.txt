#-----------------------------------------------------------------------------
set(CLP ${MODULE_NAME})

#-----------------------------------------------------------------------------
add_executable(${CLP}Test ${CLP}Test.cxx)
add_dependencies(${CLP}Test ${CLP})
target_link_libraries(${CLP}Test ${CLP}Lib)
set_target_properties(${CLP}Test PROPERTIES LABELS ${CLP})

add_executable(${CLP}_Compare ${CLP}_Compare.cxx)
target_link_libraries(${CLP}_Compare ${ITK_LIBRARIES}
    vtkIO
    )
set_target_properties(${CLP}_Compare PROPERTIES LABELS ${CLP})
    
set(TEST_DATA_DIR ${PROJECT_SOURCE_DIR}/FinslerBacktracing/Testing/TestData)
set(TEMP "${CMAKE_BINARY_DIR}/Testing/Temporary")

set(testname ${CLP}_SampleTest)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
        ${CLP}Test
        --minimumlength 10
        --maximumlength 800
        --stoppingCurvature 0.8
        --stepLength 0.5
        --label 1
        ${TEST_DATA_DIR}/sampleDirections.nrrd
        ${TEST_DATA_DIR}/sampleFinslerCosts.nii.gz
        ${TEST_DATA_DIR}/sampleSeeds.nii.gz
        ${TEMP}/sampleFibers.vtk
    )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})

# This runs a program that checks the output and compares to the one expected:
set(testname ${CLP}_SampleCompare)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}_Compare>
    ${TEST_DATA_DIR}/sampleFibers.vtk
    ${TEMP}/sampleFibers.vtk
    )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})

#set(testname ${CLP}_CleanResults)
#add_test(${MODULE_NAME}_CleanResults
#        rm
#        ${TEMP}/sampleDirections.nrrd
#        ${TEMP}/sampleFibers.vtk
#    )
#set_property(TEST ${testname} PROPERTY LABELS ${CLP})
