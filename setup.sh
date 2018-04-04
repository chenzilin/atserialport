#!/bin/bash

rm -rf libserial
rm -rf SerialPort.h SerialPort.cpp SerialPortConstants.h

tar xzvfpa libserial.tar.gz
#git clone https://github.com/crayzeewulf/libserial.git

cp libserial/src/SerialPort.h ./
cp libserial/src/SerialPort.cpp ./
cp libserial/src/SerialPortConstants.h ./

rm -rf libserial
