# Glob all .c sources in subfolders
file(GLOB_RECURSE APP_SOURCES
    "Control/*.c"
    "Features/*.c"
    "Peripherals/*.c"
    "Middleware/*.c"  # optional
    "*.c"        # <-- include top-level App .c files too   
)

# Add them to the main project target
target_sources(${PROJECT_NAME} PRIVATE ${APP_SOURCES})

# Optional: include your headers
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Control"
    "${CMAKE_CURRENT_SOURCE_DIR}/Features"
    "${CMAKE_CURRENT_SOURCE_DIR}/Peripherals"
    "${CMAKE_CURRENT_SOURCE_DIR}/Middleware"
)
