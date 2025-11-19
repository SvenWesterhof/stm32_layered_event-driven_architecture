file(GLOB APP_SOURCES
    "control/*.c"
    "features/*.c"
)

target_sources(${PROJECT_NAME} PRIVATE ${APP_SOURCES})
