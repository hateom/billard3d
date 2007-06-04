TEMPLATE = app

DESTDIR = ./bin
TARGET = board_tool

DEPENDPATH += . ui
DEPENDPATH += . src
INCLUDEPATH += . include

OBJ_DIR = ./obj
UI_DIR  = ./ui
MOC_DIR = ./moc
DEPENDPATH += . src
OBJECTS_DIR = ./obj
OBJMOC = ./obj

UICOBJECTS = ./obj
UI_HEADERS_DIR = ./include
UI_SOURCES_DIR = ./src

# Input
FORMS += ui/mainform.ui
SOURCES += 	src/main.cpp src/mainform.cpp src/canvas.cpp src/draw_manager.cpp src/vector2.cpp src/boardobj.cpp
HEADERS += 	include/mainform.h include/canvas.h \
			include/draw_manager.h include/board.h include/vector2.h include/boardobj.h
