#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T10:37:36
#
#-------------------------------------------------

QT       += core gui avwidgets
CONFIG -= c++11
QMAKE_CXXFLAGS += -std=c++1z

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smed_project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cc \
        smed_main.cc \
    openvaf.cc \
    ribbon.cc \
    smed_ribbon.cc \
    smed_analysis.cc \
    Balance/ResourceScene.cc \
    Balance/Analysis/AddTaskDlg.cc \
    Balance/Analysis/smed_view.cc \
    Balance/Analysis/ChannelTitle.cc \
    Balance/Analysis/HaChannel.cc \
    Balance/Channel.cc \
    Balance/Block.cc \
    video/progress_label.cpp \
    video/video_widget.cc

HEADERS += \
        smed_main.h \
    openvaf.h \
    ribbon.h \
    utils.hpp \
    smed_ribbon.h \
    smed_analysis.h \
    ResourceScene.h \
    Balance/parameters.hpp \
    Balance/ResourceScene.h \
    Balance/Analysis/AddTaskDlg.h \
    Balance/Analysis/smed_view.h \
    Balance/Analysis/ChannelTitle.h \
    Balance/Analysis/HaChannel.h \
    Balance/Channel.h \
    Balance/Block.h \
    video/progress_label.h \
    video/video_player.hpp \
    video/video_widget.h

FORMS += \
        smed_main.ui \
    smed_analysis.ui \
    Balance/Analysis/AddTaskDlg.ui \
    video/video_widget.ui

LIBS += -lboost_locale
LIBS += -liconv
LIBS += -lboost_filesystem
LIBS += -lboost_system

QMAKE_CXXFLAGS += -Wextra
QMAKE_CXXFLAGS += -Wno-deprecated-declarations
QMAKE_CXXFLAGS += -Werror=write-strings
QMAKE_CXXFLAGS += -Werror=return-type
QMAKE_CXXFLAGS += -Werror=parentheses
QMAKE_CXXFLAGS += -Werror=maybe-uninitialized
