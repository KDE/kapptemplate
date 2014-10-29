#! /usr/bin/env bash
$EXTRACTRC src/application/*.ui src/application/*.kcfg >> rc.cpp
$XGETTEXT rc.cpp src/application/*.cpp -o $podir/kapptemplate.pot
rm -f rc.cpp
