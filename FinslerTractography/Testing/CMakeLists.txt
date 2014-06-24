
#-----------------------------------------------------------------------------
set(CLP ${MODULE_NAME})

#-----------------------------------------------------------------------------
add_executable(${CLP}Test ${CLP}Test.cxx 
     ${PROJECT_SOURCE_DIR}/FinslerTractography/HARDI-ITK/sphericalHarmonics.cxx
     ${PROJECT_SOURCE_DIR}/FinslerTractography/HARDI-ITK/sh2hot.cxx
)
add_dependencies(${CLP}Test ${CLP} ${CLP}Lib)

target_link_libraries(${CLP}Test ${ITK_LIBRARIES})
set_target_properties(${CLP}Test PROPERTIES LABELS ${CLP})

#-----------------------------------------------------------------------------
include_directories(${SlicerExecutionModel_EXTRA_INCLUDE_DIRECTORIES})

add_executable(${CLP}_Compare ${CLP}_Compare.cxx)
target_link_libraries(${CLP}_Compare
  ${ITK_LIBRARIES}
  ${SlicerExecutionModel_EXTRA_EXECUTABLE_TARGET_LIBRARIES}
  )
set_target_properties(${CLP}_Compare PROPERTIES LABELS ${CLP})

#-----------------------------------------------------------------------------
set(TEST_DATA_DIR ${PROJECT_SOURCE_DIR}/FinslerTractography/Testing/TestData)
set(TEMP "${CMAKE_BINARY_DIR}/Testing/Temporary")

set(testname ${CLP}_SampleTest)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  ${CLP}Test
    --mi 50
    --cf -10
    --la 0.006
    --lsh 6
    --lcc test
    --numdir 26
    ${TEST_DATA_DIR}/dumbDWIData.nrrd
    ${TEST_DATA_DIR}/dumbSeeds.nii.gz
    ${TEMP}/finsler_distance_map.nii.gz
  )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})

# This runs a program that checks the output and compares to the one expected:
set(testname ${CLP}_SampleCompare)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}_Compare>
    ${TEMP}/finsler_distance_map.nii.gz 
    ${TEST_DATA_DIR}/finsler_distance_map.nii.gz
  )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})

set(testname ${CLP}_SampleTest2)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  ${CLP}Test
    --mi 50
    --cf -10
    --la 0.006
    --lsh 6
    --lcc test
    --numdir 26
    --useThreads
    ${TEST_DATA_DIR}/dumbDWIData.nrrd
    ${TEST_DATA_DIR}/dumbSeeds.nii.gz
    ${TEMP}/finsler_distance_map2.nii.gz
  )
set_property(TEST ${testname} PROPERTY LABELS ${CLP})


# This runs a program that checks the output and compares to the one expected
set(testname ${CLP}_SampleCompare2)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}_Compare>
    ${TEMP}/finsler_distance_map2.nii.gz 
    ${TEST_DATA_DIR}/finsler_distance_map.nii.gz
  )

set_property(TEST ${testname} PROPERTY LABELS ${CLP})

set(testname ${CLP}_SampleTest3)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  ${CLP}Test
    --mi 50
    --cf -10
    --la 0.006
    --lsh 6
    --lcc test
    --numdir 26
    --useThreads
    --accel
    --accelIter 1
    ${TEST_DATA_DIR}/dumbDWIData.nrrd
    ${TEST_DATA_DIR}/dumbSeeds.nii.gz
    ${TEMP}/finsler_distance_map3.nii.gz
  )

set_property(TEST ${testname} PROPERTY LABELS ${CLP})

# This runs a program that checks the output and compares to the one expected
set(testname ${CLP}_SampleCompare3)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}_Compare>
    ${TEMP}/finsler_distance_map3.nii.gz 
    ${TEST_DATA_DIR}/finsler_distance_map.nii.gz
  )

set_property(TEST ${testname} PROPERTY LABELS ${CLP})

set(testname ${CLP}_SampleTest4)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}Test>
  ${CLP}Test
    --mi 50
    --cf -8
    --la 0.006
    --lsh 6
    --numdir 26
    --accel
    --accelIter 3
    --label 2
    --directionsImage ${TEMP}/sampleDirections.nrrd
    ${TEST_DATA_DIR}/sampleDWI.nrrd
    ${TEST_DATA_DIR}/sampleSeeds.nii.gz
    ${TEMP}/sampleFinslerCosts.nii.gz
  )

set_property(TEST ${testname} PROPERTY LABELS ${CLP})

# This runs a program that checks the output and compares to the one expected
set(testname ${CLP}_SampleCompare4)
add_test(NAME ${testname} COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${CLP}_Compare>
    ${TEMP}/sampleFinslerCosts.nii.gz
    ${TEST_DATA_DIR}/sampleFinslerCosts.nii.gz
  )

set_property(TEST ${testname} PROPERTY LABELS ${CLP})
