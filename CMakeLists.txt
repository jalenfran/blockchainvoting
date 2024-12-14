cmake_minimum_required(VERSION 3.19)
project(votingGUI LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(votingGUI
    WIN32 MACOSX_BUNDLE
    src/qt/main.cpp
    src/qt/mainwindow.cpp
    include/qt/mainwindow.h
    src/qt/mainwindow.ui
    include/qt/loginwindow.h src/qt/loginwindow.cpp src/qt/loginwindow.ui
    include/qt/registerwindow.h src/qt/registerwindow.cpp src/qt/registerwindow.ui
    include/qt/resultswindow.h src/qt/resultswindow.cpp src/qt/resultswindow.ui
    include/qt/votingscreen.h src/qt/votingscreen.cpp src/qt/votingscreen.ui
    include/qt/loadingdialog.h src/qt/loadingdialog.cpp src/qt/loadingdialog.ui


    # non QT files
    src/logic/blockchain.cpp src/logic/hashing.cpp src/logic/UserManager.cpp
    src/logic/utilities.cpp src/logic/VotingCounter.cpp include/logic/blockchain.h
    include/logic/hashing.h include/logic/UserManager.h include/logic/utilities.h
    include/logic/VotingCounter.h


)

qt_add_translations(
    TARGETS votingGUI
    TS_FILES votingGUI_en_US.ts
)

target_link_libraries(votingGUI
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS votingGUI
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET votingGUI
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
