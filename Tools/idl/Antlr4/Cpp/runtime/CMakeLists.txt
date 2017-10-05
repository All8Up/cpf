
include_directories(
  ${PROJECT_SOURCE_DIR}/runtime/src
  ${PROJECT_SOURCE_DIR}/runtime/src/atn
  ${PROJECT_SOURCE_DIR}/runtime/src/dfa
  ${PROJECT_SOURCE_DIR}/runtime/src/misc
  ${PROJECT_SOURCE_DIR}/runtime/src/support
  ${PROJECT_SOURCE_DIR}/runtime/src/tree
  ${PROJECT_SOURCE_DIR}/runtime/src/tree/pattern
  ${PROJECT_SOURCE_DIR}/runtime/src/tree/xpath
)


file(GLOB libantlrcpp_SRC
  "${PROJECT_SOURCE_DIR}/runtime/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/atn/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/dfa/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/misc/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/support/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/tree/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/tree/pattern/*.cpp"
  "${PROJECT_SOURCE_DIR}/runtime/src/tree/xpath/*.cpp"
)

add_library(antlr4_static STATIC ${libantlrcpp_SRC})

set(LIB_OUTPUT_DIR "${CMAKE_HOME_DIRECTORY}/dist") # put generated libraries here.
message(STATUS "Output libraries to ${LIB_OUTPUT_DIR}")

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  target_link_libraries(antlr4_static ${UUID_LIBRARIES})
elseif(APPLE)
  target_link_libraries(antlr4_static ${COREFOUNDATION_LIBRARY})
endif()

if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  set(disabled_compile_warnings "-Wno-overloaded-virtual")
  if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(disabled_compile_warnings "${disabled_compile_warnings} -Wno-dollar-in-identifier-extension -Wno-four-char-constants")
  elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(disabled_compile_warnings "${disabled_compile_warnings} -Wno-multichar")
  endif()
endif ()

set(extra_share_compile_flags "")
set(extra_static_compile_flags "")
if (WIN32)
  set(extra_share_compile_flags "-DANTLR4CPP_EXPORTS")
  set(extra_static_compile_flags "-DANTLR4CPP_STATIC")
endif(WIN32)

set_target_properties(antlr4_static
                      PROPERTIES VERSION   ${ANTLR_VERSION}
                                 SOVERSION ${ANTLR_VERSION}
                                 OUTPUT_NAME antlr4-runtime
                                 ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR}
                                 COMPILE_FLAGS "${disabled_compile_warnings} ${extra_static_compile_flags}")

install(TARGETS antlr4_static
        ARCHIVE DESTINATION lib)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/runtime/src/" 
        DESTINATION "include/antlr4-runtime"
        COMPONENT dev 
        FILES_MATCHING PATTERN "*.h"
        )



