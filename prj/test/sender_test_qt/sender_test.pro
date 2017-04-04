#
# File sender_test.pro
# File created : 04 Apr 2017
# Created by : Davit Kalantaryan (davit.kalantaryan@desy.de)
# This file can be used to produce Makefile for daqadcreceiver application
# for PITZ
#

include(../../lib/common_qt/sys_common.pri)

QT -= core
QT -= gui

INCLUDEPATH += ../../../include
LIBS += -lprotobuf

system(protoc -I=../../../src/proto --cpp_out=../../../src/test ../../../src/proto/senderreceiver.proto)
system(protoc -I=../../../src/proto --cpp_out=../../../src/test ../../../src/proto/sender.proto)

SOURCES += \
    ../../../src/test/main_sender_test.cpp \
    ../../../src/util/aservertcp.cpp \
    ../../../src/util/asocketb.cpp \
    ../../../src/util/asockettcp.cpp \
    ../../../src/test/pitz_test_protoserver.cpp \
    ../../../src/test/sender.pb.cc \
    ../../../src/test/senderreceiver.pb.cc

HEADERS += \
    ../../../src/util/stdafx.h \
    ../../../src/test/protosystemcommon.h \
    ../../../src/test/pitz_test_protoserver.hpp \
    ../../../src/test/sender.pb.h \
    ../../../src/test/senderreceiver.pb.h

OTHER_FILES += \
    ../../../src/proto/senderreceiver.proto \
    ../../../src/proto/sender.proto
