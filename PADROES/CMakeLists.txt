cmake_minimum_required(VERSION 3.16)
project(HidrometroQt)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

set(SOURCES
    src/main.cpp
    src/Fluxo.cpp
    src/Medicao.cpp
    src/Hidrometro.cpp
    src/HidrometroApp.cpp
)

set(HEADERS
    src/Fluxo.h
    src/Medicao.h
    src/Hidrometro.h
    src/HidrometroApp.h
)

qt_add_executable(HidrometroQt
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(HidrometroQt
    Qt6::Widgets
    Qt6::Gui
    Qt6::Core
)
