add_subdirectory(Input)
add_subdirectory(Helpers)
add_subdirectory(Renderer)
add_subdirectory(ZombieMgr)

add_subdirectory(Game)

add_library(TinyEngine INTERFACE)

target_link_libraries(TinyEngine INTERFACE Helpers ZombieMgr Renderer Game)
