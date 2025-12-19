# Pak alle .c bestanden in deze folder en subfolders
file(GLOB_RECURSE CUSTOM_DRIVER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# Voeg toe aan het hoofdproject (PROJECT_NAME moet gedefinieerd zijn in de parent)
target_sources(${PROJECT_NAME} PRIVATE ${CUSTOM_DRIVER_SOURCES})

# Voeg deze map toe voor includes, 
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
