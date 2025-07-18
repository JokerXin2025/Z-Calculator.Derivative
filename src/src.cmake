list(APPEND INCPATH "${CMAKE_CURRENT_LIST_DIR}")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/Headers_Lib.h")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/Parser.c")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/Parser.h")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/Printer.c")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/Printer.h")

list(APPEND INCPATH "${CMAKE_CURRENT_LIST_DIR}/model")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/model/_Derivative.c")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/model/_Derivative.h")

list(APPEND INCPATH "${CMAKE_CURRENT_LIST_DIR}/utils")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/utils/node.c")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/utils/node.h")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/utils/node_type.c")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/utils/node_type.h")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/utils/trans.c")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/utils/trans.h")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/utils/variable.c")
list(APPEND SOURCES "${CMAKE_CURRENT_LIST_DIR}/utils/variable.h")
