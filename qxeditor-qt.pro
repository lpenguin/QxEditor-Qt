QT = gui \
    core \
    script
CONFIG += qt \
    warn_on \
    console \
    debug
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/dialog.ui \
    ui/VerDialog.ui \
    ui/EdgeDialog.ui \
    ui/MainDialog.ui \
    src/QuestActionsDialog.ui \
    src/QuestSettingsDialog.ui
HEADERS = \
    src/Graph.h \
    src/Ver.h \
    src/Edge.h \
    src/GraphView.h \
    src/VerItem.h \
    src/EdgeItem.h \
    src/VerDialogImpl.h \
    src/EdgeDialogImpl.h \
    src/MainDialogImpl.h \
    src/AbstractGraphReader.h \
    src/JSONGraphReader.h \
    src/AbstractGraphWriter.h \
    src/JSONGraphWriter.h \
    src/QuestActionsDialog.h \
    src/QuestSettingsDialog.h \
    src/JavascriptHighlighter.h \
    src/ScriptEdit.h
SOURCES = \
    src/main.cpp \
    src/Ver.cpp \
    src/Graph.cpp \
    src/Edge.cpp \
    src/GraphView.cpp \
    src/EdgeItem.cpp \
    src/VerItem.cpp \
    src/VerDialogImpl.cpp \
    src/EdgeDialogImpl.cpp \
    src/MainDialogImpl.cpp \
    src/AbstractGraphReader.cpp \
    src/JSONGraphReader.cpp \
    src/AbstractGraphWriter.cpp \
    src/JSONGraphWriter.cpp \
    src/QuestActionsDialog.cpp \
    src/QuestSettingsDialog.cpp \
    src/JavascriptHighlighter.cpp \
    src/ScriptEdit.cpp
TEMPLATE = app
INCLUDEPATH += src
OTHER_FILES += 111.txt \
    2222.txt