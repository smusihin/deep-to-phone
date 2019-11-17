adb shell
$ busybox uname -a
Linux localhost 2.6.35.7 #1 PREEMPT Thu Jan 10 16:06:47 KST 2013 armv6l GNU/Linux

adb shell cat /proc/version
Linux version 2.6.35.7 (official.torino@androide) (gcc version 4.4.3 (GCC) ) #1 PREEMPT Thu Jan 10 16:06:47 KST 2013

adb shell cat /proc/cpuinfo
Processor	: ARMv6-compatible processor rev 5 (v6l)
BogoMIPS	: 832.90
Features	: swp half thumb fastmult vfp edsp java 
CPU implementer	: 0x41
CPU architecture: 6TEJ
CPU variant	: 0x1
CPU part	: 0xb36
CPU revision	: 5

Hardware	: BCM21553 ThunderbirdEDN31 platform
Revision	: 0000
Serial		: 36323a6859c900ec


   
#push to /data/local/tmp/test.sh
adb shell sh /data/local/tmp/test.sh
    
#get gcc-4.4.3:
    git clone https://github.com/andyjhf/arm-linux-gcc-4.4.3.git
    
#install lib32z:
sudo apt install lib32z
    
#build helloworld.c
arm-linux-gcc-4.4.3/bin/arm-linux-gcc helloworld.c -static -o helloworld-arm

#pull to phone:
adb push helloworld-arm /data/local/tmp/helloworld-arm
    
#run:
adb shell /data/local/tmp/helloworld-arm



    
    
    
    
    
    


 








