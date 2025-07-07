# app icon
set(MACOSX_BUNDLE_ICON_FILE "${CMAKE_PROJECT_NAME}.icns")
set(application_icon "${CMAKE_SOURCE_DIR}/res/${MACOSX_BUNDLE_ICON_FILE}")
set_source_files_properties(${application_icon}
                            PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# resource files
file(GLOB_RECURSE assets "${CMAKE_SOURCE_DIR}/res/*")
foreach(FILE ${assets}) 
  get_filename_component(FILENAME ${FILE} NAME)
  # skip .DS_Store files
  if (NOT FILENAME STREQUAL ".DS_Store")   
    file(RELATIVE_PATH NEW_FILE "${CMAKE_SOURCE_DIR}/" ${FILE})
    get_filename_component(PARENT_DIR ${NEW_FILE} DIRECTORY) # parent dir
    set_source_files_properties(${PARENT_DIR} PROPERTIES MACOSX_PACKAGE_LOCATION "res/${PARENT_DIR}")
  endif()
endforeach()

# create macos bundle
add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE
               ${GAME_SRC} "${CMAKE_SOURCE_DIR}/src/ResourcePath.mm" 
               ${application_icon} "${assets}") 

set_target_properties(
  ${CMAKE_PROJECT_NAME}
  PROPERTIES BUNDLE TRUE
             XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
             XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
             XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS "@executable_path/../Frameworks"
             MACOSX_BUNDLE_BUNDLE_NAME "${CMAKE_PROJECT_NAME}"
             MACOSX_BUNDLE_GUI_IDENTIFIER "com.mshirlaw.${CMAKE_PROJECT_NAME}"
             MACOSX_BUNDLE_COPYRIGHT "(c) 2024, Matt Shirlaw"
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
             RESOURCE "${assets}")