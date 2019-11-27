#!/bin/sh
echo
echo "Create and push binary"
../arm-linux-gcc-4.4.3/bin/arm-linux-as -o first.o first.s
../arm-linux-gcc-4.4.3/bin/arm-linux-ld -o first first.o
adb push first /data/local/tmp/first
adb shell chmod 766 /data/local/tmp/first
echo "Create and push shell"
echo '/data/local/tmp/first ; echo $?' > test_asm.sh
adb push test_asm.sh /data/local/tmp/test_asm.sh
adb shell chmod 766 /data/local/tmp/test_asm.sh
echo
echo "Start......"
adb shell /data/local/tmp/test_asm.sh
#remove temporary files
rm test_asm.sh
rm first.o
rm first
echo
