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
system(protoc -I=../../../src/proto --cpp_out=../../../src/test ../../../src/proto/receiver.proto)

SOURCES += \
    ../../../src/util/asocketb.cpp \
    ../../../src/util/asockettcp.cpp \
    ../../../src/test/main_receiver_test.cpp \
    ../../../src/test/receiver.pb.cc \
    ../../../src/test/senderreceiver.pb.cc

HEADERS += \
    ../../../src/util/stdafx.h \
    ../../../src/test/protosystemcommon.h \
    ../../../src/test/senderreceiver.pb.h \
    ../../../src/test/receiver.pb.h \
    ../../../src/test/senderreceiver.pb.h

OTHER_FILES += \
    ../../../src/proto/senderreceiver.proto \
    ../../../src/proto/receiver.proto
