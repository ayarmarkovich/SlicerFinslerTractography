  add_executable(${CLP}Test ${CLP}Test.cxx)
  target_link_libraries(${CLP}Test ${ITK_LIBRARIES} )
  
  set(TEST_DATA_DIR ${PROJECT_SOURCE_DIR}/Testing/TestData)
  
  if (Slicer_SOURCE_DIR)
    # This is a Slicer build
    if(Slicer_BINARY_DIR)
        # And this is for Slicer4. It requires calling the CLI with the full path
        set(OUTPUT_DIR ${Slicer_BINARY_DIR}/Testing)
        set(Slicer_EXE ${Slicer_BINARY_DIR}/Slicer)
        SET(RUNEXEC
            ${Slicer_EXE}
            --launch
            "${Slicer_BINARY_DIR}/lib/Slicer-${Slicer_VERSION_MAJOR}.${Slicer_VERSION_MINOR}/cli-modules/${CLP}"
        )
        SET(COMPEXEC
            ${Slicer_EXE}
            --launch
            "${Slicer_BINARY_DIR}/bin/${CLP}Test"
        )
    endif(Slicer_BINARY_DIR)
    
  else( Slicer_SOURCE_DIR )
    set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/Testing)
    SET( RUNEXEC ${CMAKE_BINARY_DIR}/${CLP} )
    SET( COMPEXEC ${CMAKE_BINARY_DIR}/${CLP}Test )
  endif (Slicer_SOURCE_DIR)

  # This runs the module with testing parameters:
  add_test(${PROJECT_NAME}_SampleTest
    ${RUNEXEC}
    --mi 50
    --cf -10
    --la 0.006
    --lsh 6
    --lcc test
    --numdir 26
    ${TEST_DATA_DIR}/dumbDWIData.nrrd
    ${TEST_DATA_DIR}/dumbSeeds.nii.gz
    ${OUTPUT_DIR}/finsler_distance_map.nii.gz
  )

  # This runs a program that checks the output and compares to the one expected:
  add_test(${PROJECT_NAME}_SampleCompare
    ${COMPEXEC}
    ${OUTPUT_DIR}/finsler_distance_map.nii.gz 
    ${TEST_DATA_DIR}/finsler_distance_map.nii.gz
  )

  add_test(${PROJECT_NAME}_SampleTest2
    ${RUNEXEC}
    --mi 50
    --cf -10
    --la 0.006
    --lsh 6
    --lcc test
    --numdir 26
    --useThreads
    ${TEST_DATA_DIR}/dumbDWIData.nrrd
    ${TEST_DATA_DIR}/dumbSeeds.nii.gz
    ${OUTPUT_DIR}/finsler_distance_map2.nii.gz
  )

  # This runs a program that checks the output and compares to the one expected:
  add_test(${PROJECT_NAME}_SampleCompare2
    ${COMPEXEC}
    ${OUTPUT_DIR}/finsler_distance_map2.nii.gz 
    ${TEST_DATA_DIR}/finsler_distance_map.nii.gz
  )

  add_test(${PROJECT_NAME}_SampleTest3
    ${RUNEXEC}
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
    ${OUTPUT_DIR}/finsler_distance_map3.nii.gz
  )

  # This runs a program that checks the output and compares to the one expected:
  add_test(${PROJECT_NAME}_SampleCompare3
    ${COMPEXEC}
    ${OUTPUT_DIR}/finsler_distance_map3.nii.gz 
    ${TEST_DATA_DIR}/finsler_distance_map.nii.gz
  )
