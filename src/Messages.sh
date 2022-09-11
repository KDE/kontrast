#! /bin/sh
# SPDX-FileCopyrightText: None
# SPDX-License-Identifier: CC0-1.0

$XGETTEXT `find . -name \*.qml -o -name \*.cpp` -o $podir/kontrast.pot
