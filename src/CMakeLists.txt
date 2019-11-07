add_definitions(-DUNICODE -D_UNICODE)

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
                )

target_include_directories(zoom_bot PRIVATE 
                            ${ZOOM_SDK_INCLUDE}
                            ${DUI_SDK_INCLUDE}
                            )


target_link_libraries(zoom_bot 
                        ${ZOOM_SDK_LIB}
                        ${DUI_SDK_LIB}
                      )