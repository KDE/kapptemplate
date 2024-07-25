#! /usr/bin/env bash
$EXTRACTRC src/application/*.kcfg >> rc.cpp
$XGETTEXT rc.cpp `find -name \*.cpp -o -name \*.qml` -o $podir/kapptemplate.pot
rm -f rc.cpp
