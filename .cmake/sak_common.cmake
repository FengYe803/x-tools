add_compile_definitions(SAK_AUTHOR="Qsaker")
add_compile_definitions(SAK_EDITION="beta1")
add_compile_definitions(SAK_VERSION="5.1.0")
add_compile_definitions(SAK_STYLE_DEFAULT="Fusion")
add_compile_definitions(SAK_HOST_ADDRESS_ANY="Any")
add_compile_definitions(SAK_CLEAR_MESSAGE_INTERVAL=8000)
add_compile_definitions(SAK_AUTHOR_EMAIL="qsaker@foxmail.com")
add_compile_definitions(SAK_GITEE_REPOSITORY_URL="https://gitee.com/qsaker/QtSwissArmyKnife")
add_compile_definitions(SAK_GITHUB_REPOSITORY_URL="https://github.com/qsaker/QtSwissArmyKnife")

# Set the suffix of the library.
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")

else()
  set(SAK_FILE_SUFFIX "d")
endif()

# Get the last commit.
function(sak_get_last_commit working_dir prefix)
  execute_process(
    COMMAND git log -1 --pretty=%H
    WORKING_DIRECTORY ${working_dir}
    OUTPUT_VARIABLE GIT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  add_compile_definitions(${prefix}_GIT_COMMIT="${GIT_COMMIT}")
endfunction()

# Get last commit time.
function(sak_get_last_commit_time working_dir prefix)
  execute_process(
    COMMAND git log -1 --format=%cd
    WORKING_DIRECTORY ${working_dir}
    OUTPUT_VARIABLE GIT_COMMIT_TIME
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  add_compile_definitions(${prefix}_GIT_COMMIT_TIME="${GIT_COMMIT_TIME}")
endfunction()

# Unzip file and imort it as a sub module.
function(sak_add_subdiretory zip_file_name_without_suffix)
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${zip_file_name_without_suffix}.zip
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/3rd)
  add_subdirectory(3rd/${zip_file_name_without_suffix})
endfunction()

# Find Qt package.
macro(sak_find_qt_package modules)
  find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS ${modules})
  find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${modules})
endmacro()

# Add executable. It can be used by Qt5 and Qt6.
function(sak_add_executable target sources)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/sak/${target}")
  if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${target} MANUAL_FINALIZATION)
  else()
    if(ANDROID)
      add_library(${target} SHARED)
    else()
      add_executable(${target})
    endif()
  endif()

  set(INDEX 0)
  while(INDEX LESS ${ARGC})
      math(EXPR INDEX "${INDEX} + 1")
      target_sources(${target} PRIVATE ${ARGV${INDEX}})
  endwhile()

  if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${target})
  endif()
endfunction()
