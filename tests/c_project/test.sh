#!/bin/sh

cd tests/c_project || exit 1

../../bin/smake || exit 1

./hello || exit 1

rm -f hello