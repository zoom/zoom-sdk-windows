add_definitions(-DUNICODE -D_UNICODE -DNOMINMAX)

# add the executable
add_executable(zoom_bot WIN32
                AuthServiceMgr.cpp
                AuthServiceMgr.h
                DemoUI.cpp
                DemoUI.h
                Main.cpp
                MeetingServiceMgr.cpp
                MeetingServiceMgr.h
                ntundoc.h
                Parameters.h
                PreMeetingServiceMgr.cpp
                PreMeetingServiceMgr.h
                queryHandle.cpp
                RawAudioDataHandler.cpp
                RawAudioDataHandler.h
                RawVideoDataHandler.cpp
                RawVideoDataHandler.h
                orchestrator.proto
                )

target_include_directories(zoom_bot PRIVATE 
                            ${ZOOM_SDK_INCLUDE}
                            ${CMAKE_CURRENT_BINARY_DIR}
                            )


target_link_libraries(zoom_bot 
                        ${ZOOM_SDK_LIB}
                        protobuf::libprotoc protobuf::libprotobuf-lite
                      )

protobuf_generate(TARGET zoom_bot IMPORT_DIRS $ENV{VCPKG_ROOT}/packages/protobuf_${VCPKG_TARGET_TRIPLET}/include)
                      