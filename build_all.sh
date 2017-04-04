#!/bin/bash
#
# file: build_all.sh
#
# $Date 2017/04/04 22:10 $
#
# purpose:	t...
#
# author:	Davit Kalantaryan  (davit.kalantaryan@desy.de)
#

SCRIPT_DIR=`pwd`
ROOT_DIR=$SCRIPT_DIR

#cd $SCRIPT_DIR

cd $ROOT_DIR/prj/test/sender_test_qt
qmake sender_test.pro
#make clean
make

cd $ROOT_DIR/prj/test/receiver_test_qt
qmake receiver_test.pro
#make clean
make


if [[ "$OSTYPE" == "linux-gnu" ]]; then
	BINARY_DIR0=$ROOT_DIR/sys/`lsb_release -c | cut -f 2`/bin
	BINARY_DIR=$ROOT_DIR/sys/`lsb_release -c | cut -f 2`/bin
elif [[ "$OSTYPE" == "darwin"* ]]; then
	BINARY_DIR0=$ROOT_DIR/sys/mac/bin
	BINARY_DIR=$ROOT_DIR/sys/mac/bin/gui_wallet.app/Contents/MacOS
elif [[ "$OSTYPE" == "cygwin" ]]; then
        echo "POSIX compatibility layer and Linux environment emulation for Windows"
elif [[ "$OSTYPE" == "msys" ]]; then
        echo " Lightweight shell and GNU utilities compiled for Windows (part of MinGW)"
elif [[ "$OSTYPE" == "win32" ]]; then
        echo "this can happen."
elif [[ "$OSTYPE" == "freebsd"* ]]; then
        echo " ..."
else
        echo "Unknown."
fi


echo "Please find all binaries here: "$BINARY_DIR0
