# Glob all .c sources in subfolders
file(GLOB_RECURSE APP_SOURCES
    "control/*.c"
    "features/*.c"
    "peripherals/*.c"
    "middleware/*.c"  # optional
    "*.c"        # <-- include top-level App .c files too   
)

# Add them to the main project target
target_sources(${PROJECT_NAME} PRIVATE ${APP_SOURCES})

# Optional: include your headers
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/control"
    "${CMAKE_CURRENT_SOURCE_DIR}/features"
    "${CMAKE_CURRENT_SOURCE_DIR}/peripherals"
    "${CMAKE_CURRENT_SOURCE_DIR}/middleware"
)
