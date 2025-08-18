# Copy image files
file(GLOB IMAGE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.png")
foreach(img ${IMAGE_FILES})
    configure_file("${img}" ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

# Copy JSON files
file(GLOB JSON_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.json")
foreach(json ${JSON_FILES})
    configure_file("${json}" ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

# Copy sound files
file(GLOB SOUND_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.wav"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.mp3"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.ogg"
)
foreach(sound ${SOUND_FILES})
    configure_file("${sound}" ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

# Copy text files
file(GLOB TEXT_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.md"
)
foreach(text ${TEXT_FILES})
    configure_file("${text}" ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

# Copy font files
file(GLOB FONT_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.ttf"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.otf"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.woff"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.woff2"
)
foreach(font ${FONT_FILES})
    configure_file("${font}" ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()