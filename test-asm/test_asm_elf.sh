#!/bin/sh
echo
echo "Create and push binary"
../arm-linux-gcc-4.4.3/bin/arm-linux-as -o shell.o shell.s
../arm-linux-gcc-4.4.3/bin/arm-linux-objdump -d shell.o
../arm-linux-gcc-4.4.3/bin/arm-linux-ld -o shell shell.o

adb push shell /data/local/tmp/shell

echo "Start......"
adb shell /data/local/tmp/shell
#remove temporary files
rm test_asm.sh
rm shell.o
rm shell
echo
