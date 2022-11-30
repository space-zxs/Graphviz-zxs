project(clonedGraphviz)   #设置项目名称
cmake_minimum_required(VERSION 3.0)  # cmake 版本
set(Boost_USE_STATIC_LIBS        ON) # only find static libs
#set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(BOOST_ROOT D:/boost_1_80_0)
find_package(Boost)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  message(${Boost_INCLUDE_DIRS} ${Boost_LIBRARIES})
  add_definitions(-DDEBUG1)
  add_executable(clonedGraphviz main.cpp dotinit.cpp rank.cpp ns.cpp mincross.cpp timing.c class1.cpp class2.cpp fastgr.cpp decomp.cpp dotinit.h rank.h ns.h mincross.h class1.h class2.h fastgr.h decomp.h types_bgl.h)
  target_link_libraries(clonedGraphviz m)
endif()
