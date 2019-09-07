QT += quick
!wasm:QT += widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        fakesns4q.cpp \
        main.cpp

HEADERS += \
  fakesns4q.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


SOURCES += platform.cpp
HEADERS += platform.h
wasm {
  DEFINES+=BUILD_FOR_WASM
  SOURCES += platform_wasm.cpp
} else {
  SOURCES += platform_desktop.cpp
}

# update html file
update_html.target = update_html
update_html.commands = sed -i s/qtlogo.svg/$${TARGET}.png/g $$OUT_PWD/$${TARGET}.html >&2
QMAKE_EXTRA_TARGETS += update_html
# copy logo file
copy_logo.target = copy_logo
copy_logo.commands = $(COPY) $$shell_path($$PWD/$${TARGET}.png) $$shell_path($$OUT_PWD)
copy_logo.depends = update_html
QMAKE_EXTRA_TARGETS += copy_logo

contains(QMAKE_HOST.os, Windows){
  QMAKE_POST_LINK += mingw32-make copy_logo
}else{
  QMAKE_POST_LINK += make copy_logo
}

