greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets

QT += opengl

# Add more folders to ship with the application, here
folder_01.source = html
folder_01.target = .
DEPLOYMENTFOLDERS = folder_01

# Define TOUCH_OPTIMIZED_NAVIGATION for touch optimization and flicking
#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    mailbox.cpp \
    message.cpp \
    httpserver.cpp \
    qhttpserver.cpp \
    qhttpresponse.cpp \
    qhttpconnection.cpp \
    qhttprequest.cpp \
    http_parser.cpp \
    glwidget.cpp \
    qwsserver.cpp \
    qwssocket.cpp

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    mailbox.h \
    message.h \
    httpserver.h \
    qhttpserver.h \
    qhttpresponse.h \
    qhttpconnection.h \
    qhttprequest.h \
    http_parser.h \
    glwidget.h \
    qwsserver.h \
    qwssocket.h
