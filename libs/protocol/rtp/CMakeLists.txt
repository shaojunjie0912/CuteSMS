#source files
file(GLOB_RECURSE MMS_RTP_LIB_SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}/*.h" 
                                        "${CMAKE_CURRENT_SOURCE_DIR}/*.c" 
                                        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" 
                                        "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

add_library(cutesms-rtp STATIC ${MMS_RTP_LIB_SOURCES})
add_dependencies(cutesms-rtp 
    libboost
    libjsoncpp
    libboringssl
    cutesms-base
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(cutesms-rtp 
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_include_directories(cutesms-rtp 
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(cutesms-rtp
    boost_system.a
    boost_serialization.a
    boost_date_time.a
    boost_regex.a
    boost_coroutine.a
    boost_thread.a
    boost_context.a
    boost_program_options.a
    ssl.a 
    crypto.a
    libjsoncpp.a
    libz.a
    libyaml-cpp.a
    dl
    pthread
    cutesms-base
)

install(TARGETS cutesms-rtp ARCHIVE DESTINATION lib)