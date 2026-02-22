add_subdirectory(Input)
add_subdirectory(Renderer)

add_subdirectory(Game)

add_library(TinyEngine INTERFACE)

target_link_libraries(TinyEngine INTERFACE Renderer Game)
