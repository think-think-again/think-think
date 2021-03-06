QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    battlescene.cpp \
    boss.cpp \
    dialogue.cpp \
    gameboard.cpp \
    gem.cpp \
    harmlabel.cpp \
    main.cpp \
    mainmenu.cpp \
    myglobalvariants.cpp \
    mywindow.cpp \
    player.cpp \
    skill.cpp \
    skill1.cpp \
    skill2.cpp \
    skill3.cpp \
    skill4.cpp \
    skillhoverlayer.cpp \
    startbutton.cpp

HEADERS += \
    battlescene.h \
    boss.h \
    dialogue.h \
    gameboard.h \
    gem.h \
    harmlabel.h \
    mainmenu.h \
    myglobalvariants.h \
    mywindow.h \
    player.h \
    skill.h \
    skill1.h \
    skill2.h \
    skill3.h \
    skill4.h \
    skillhoverlayer.h \
    startbutton.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    think-think.qrc
