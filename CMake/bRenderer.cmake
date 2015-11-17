# ---- brenderer_set_external_prefixes ----
#
function(brenderer_set_custom_prefixes)
    list(APPEND prefixes "${BRENDERER_EXPORT_DIR}")
    
    # Platform and architecture
    if(APPLE)
        set(BRENDERER_TARGET_PLATFORM "osx" CACHE STRING "System platform")
    elseif(UNIX)
        set(BRENDERER_TARGET_PLATFORM "linux" CACHE STRING "System platform")
    elseif(WIN32)
        set(BRENDERER_TARGET_PLATFORM "win" CACHE STRING "System platform")
    endif()

    file(GLOB subdir ${BRENDERER_EXTERNAL_DIR}/*)
    foreach(dir ${subdir})
        if(IS_DIRECTORY ${dir})
            list(APPEND prefixes "${dir}")
            if(EXISTS "${dir}/${BRENDERER_TARGET_PLATFORM}" AND IS_DIRECTORY "${dir}/${BRENDERER_TARGET_PLATFORM}")
                list(APPEND prefixes "${dir}/${BRENDERER_TARGET_PLATFORM}")
            endif()
        endif()
    endforeach()

    if(NOT WIN32)
        list(APPEND prefixes "$ENV{HOME}")
    endif()

    set(BRENDERER_CUSTOM_PREFIXES "${prefixes}"
        CACHE STRING "Custom prefix paths for package lookup" FORCE)
    #message(STATUS "\nBRENDERER_CUSTOM_PREFIXES=${BRENDERER_CUSTOM_PREFIXES}\n")
endfunction()
