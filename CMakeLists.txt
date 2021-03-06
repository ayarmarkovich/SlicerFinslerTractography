cmake_minimum_required(VERSION 2.8.9)

project(FinslerTractography)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "http://www.nitrc.org/projects/finslertract/")
set(EXTENSION_CATEGORY "Tractography")
set(EXTENSION_CONTRIBUTORS "Antonio Tristan-Vega, Alex Yarmarkovich (Isomics), Demian Wassermann, Peter Savadjiev, Carl-Fredrik Westin")
set(EXTENSION_DESCRIPTION "This module implements the Finsler tractography method with HARDI data described by J. Melonakos et al.")
set(EXTENSION_ICONURL "https://raw.githubusercontent.com/ayarmarkovich/SlicerFinslerTractography/master/finsler.png")
set(EXTENSION_SCREENSHOTURLS "http://www.nitrc.org/project/list_screenshots.php?group_id=464&screenshot_id=402")

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(FinslerBacktracing)
add_subdirectory(FinslerTractography)

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})

