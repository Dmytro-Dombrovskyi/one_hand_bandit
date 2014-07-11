
QT      += core gui widgets
QMAKE_CXXFLAGS += -std=c++11

TARGET   += OneHandBandit
TEMPLATE += app


HEADERS += \
    banditwindow.h

SOURCES += \
    banditwindow.cpp \
    Bandit_main.cpp

RESOURCES += \
    my_resource.qrc
