#-----------------------------------------------------------------------------
set(CLP ${MODULE_NAME})

#-----------------------------------------------------------------------------
add_executable(${CLP}Test ${CLP}Test.cxx)
target_link_libraries(${CLP}Test
    vtkIO
    )

set_target_properties(${CLP}Test PROPERTIES LABELS ${CLP})
    
set(TEST_DATA_DIR ${PROJECT_SOURCE_DIR}/Testing/TestData)

set(testname ${CLP}_SampleTest)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
        --minimumlength 10
        --maximumlength 800
        --stoppingCurvature 0.8
        --stepLength 0.5
        --label 1
        ${TEMP}/sampleDirections.nrrd
        ${TEST_DATA_DIR}/sampleFinslerCosts.nii.gz
        ${TEST_DATA_DIR}/sampleSeeds.nii.gz
        ${TEMP}/sampleFibers.vtp
    )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})

# This runs a program that checks the output and compares to the one expected:
set(testname ${CLP}_SampleCompare)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
    ModuleEntryPoint
    ${TEST_DATA_DIR}/sampleFibers.vtp
    ${TEMP}/sampleFibers.vtp
    )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})

set(testname ${CLP}_CleanResults)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
    ModuleEntryPoint
    rm
    ${TEMP}/sampleDirections.nrrd
    ${TEMP}/sampleFibers.vtp
    )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})
