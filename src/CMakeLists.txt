add_subdirectory(Math)
add_subdirectory(Input)
add_subdirectory(Helpers)
add_subdirectory(ZombieMgr)
add_subdirectory(Renderer)
add_subdirectory(Button)
add_subdirectory(Game)

add_library(TinyEngine INTERFACE)

target_link_libraries(TinyEngine INTERFACE Math Input Helpers ZombieMgr Renderer Button Game)
