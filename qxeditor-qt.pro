QT = gui \
    core \
    script \
    declarative \
    webkit
CONFIG += qt \
    warn_on \
    console   \
    debug
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/dialog.ui \
    ui/MainDialog.ui \
    src/QuestActionsDialog.ui \
    src/QuestSettingsDialog.ui \
    src/SimpleVerWidget.ui \
    src/SimpleEdgeWidget.ui \
    src/QlVerWidget.ui \
    src/QlEdgeWidget.ui \
    src/VerDialog.ui \
    src/EdgeDialog.ui \
    src/QlGraphWidget.ui \
    src/SimpleGraphWidget.ui \
    src/QmEquationDialog.ui \
    src/PlayerDialog.ui \
    src/SettingsDialog.ui
HEADERS = \
    src/GraphView.h \
    src/VerItem.h \
    src/EdgeItem.h \
    src/MainDialogImpl.h \
    src/AbstractGraphReader.h \
    src/JSONGraphReader.h \
    src/AbstractGraphWriter.h \
    src/JSONGraphWriter.h \
    src/QuestActionsDialog.h \
    src/QuestSettingsDialog.h \
    src/JavascriptHighlighter.h \
    src/ScriptEdit.h \
    src/QMGraph.h \
    src/QMReader.h \
    src/QMGraphReader.h \
    src/BinaryReader.h \
    src/BlockScript.h \
    src/QMScriptToBsConverter.h \
    src/Transliter.h \
    src/BsToTagConverter.h \
    src/BsToESMAScriptConverter.h \
    src/QuestLogic.h \
    src/SimpleGraph.h \
    src/BaseGraph.h \
    src/QlGraph.h \
    src/QlQMInfoReader.h \
    src/SimpleVerWidget.h \
    src/SimpleEdgeWidget.h \
    src/QlVerWidget.h \
    src/QlEdgeWidget.h \
    src/VerDialog.h \
    src/EdgeDialog.h \
    src/BaseWidgets.h \
    src/QlGraphWidget.h \
    src/SimpleGraphWidget.h \
    src/QlGraphWidget.h \
    src/SimpleGraphWidget.h \
    src/QlJSONInfoWriter.h \
    src/ECMAScriptToBsConverter.h \
    src/QlJSONInfoReader.h \
    src/Error.h \
    src/stringoper.h \
    src/ParseError.h \
    src/QmEqToBsConverter.h \
    src/QmEquationDialog.h \
    src/PlayerDialog.h \
    src/SettingsDialog.h
SOURCES = \
    src/main.cpp \
    src/GraphView.cpp \
    src/EdgeItem.cpp \
    src/VerItem.cpp \
    src/MainDialogImpl.cpp \
    src/AbstractGraphReader.cpp \
    src/JSONGraphReader.cpp \
    src/AbstractGraphWriter.cpp \
    src/JSONGraphWriter.cpp \
    src/QuestActionsDialog.cpp \
    src/QuestSettingsDialog.cpp \
    src/JavascriptHighlighter.cpp \
    src/ScriptEdit.cpp \
    src/QMGraph.cpp \
    src/QMReader.cpp \
    src/QMGraphReader.cpp \
    src/BinaryReader.cpp \
    src/BlockScript.cpp \
    src/QMScriptToBsConverter.cpp \
    src/Transliter.cpp \
    src/BsToTagConverter.cpp \
    src/BsToESMAScriptConverter.cpp \
    src/QuestLogic.cpp \
    src/SimpleGraph.cpp \
    src/BaseGraph.cpp \
    src/QlGraph.cpp \
    src/QlQMInfoReader.cpp \
    src/SimpleVerWidget.cpp \
    src/SimpleEdgeWidget.cpp \
    src/QlVerWidget.cpp \
    src/QlEdgeWidget.cpp \
    src/VerDialog.cpp \
    src/EdgeDialog.cpp \
    src/BaseWidgets.cpp \
    src/QlGraphWidget.cpp \
    src/SimpleGraphWidget.cpp \
    src/QlJSONInfoWriter.cpp \
    src/ECMAScriptToBsConverter.cpp \
    src/QlJSONInfoReader.cpp \
    src/Error.cpp \
    src/stringoper.cpp \
    src/QmEqToBsConverter.cpp \
    src/QmEquationDialog.cpp \
    src/PlayerDialog.cpp \
    src/SettingsDialog.cpp
TEMPLATE = app
INCLUDEPATH += src

OTHER_FILES += \
    player/css/playerui.css \
    player/index.html \
    player/quest.info \
    player/quests.json \
    player/js/playerUI.js \
    player/js/player.js \
    player/js/misc.js \
    player/js/mainFunctions.js \
    player/js/jquery-1.6.2.min.js \
    player/js/gridUI.js \
    player/quests/testQuotes.json \
    player/quests/test.json \
    player/quests/main.json \
    player/quests/Gobsavr.qm.json \
    player/quests/Bondiana.qm.json \
    player/quests/bank2.json \
    player/quests/bank.json \
    todo.txt \
    player/player.html \
    scripts/genQuestFile.py \
    scripts/manager.py \
    scripts/settings.cfg
