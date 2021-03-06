cmake_minimum_required (VERSION 3.17.0)

project(GBHttpServerFramework)

file(GLOB GBHttpServerFramework_SRC src/*.cpp)

file(GLOB ROUTER_FILES src/*Router.cpp include/*Router.h src/GBPathSegment.cpp include/GBPathSegment.h)
file(GLOB READER_FILES src/*Reader.cpp include/*Reader.h)
file(GLOB WRITER_FILES src/*Writer.cpp include/*Writer.h)

file(GLOB GBHttpServerFramework_HEADER include/*.h)

source_group("Router" FILES ${ROUTER_FILES})
source_group("Reader" FILES ${READER_FILES})
source_group("Writer" FILES ${WRITER_FILES})

add_library(GBHttpServerFramework STATIC ${GBHttpServerFramework_SRC} ${GBHttpServerFramework_HEADER})

set_property(TARGET GBHttpServerFramework PROPERTY CXX_STANDARD 20)

target_compile_definitions(GBHttpServerFramework PRIVATE _UNICODE UNICODE)

#####################################

file(GLOB SAMPLE_SRC sample/*.cpp sample/*.h)

add_executable(Sample ${SAMPLE_SRC})

set_property(TARGET GBHttpServerFramework PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_link_libraries(Sample PRIVATE GBHttpServerFramework ws2_32.lib)

set_property(TARGET Sample PROPERTY CXX_STANDARD 20)

set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT Sample)

