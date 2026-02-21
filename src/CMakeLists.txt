add_subdirectory(Renderer)

add_library(TinyEngine INTERFACE)

target_link_libraries(TinyEngine INTERFACE Renderer)
