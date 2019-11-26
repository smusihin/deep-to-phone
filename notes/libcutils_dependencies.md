dynamic section libcutils

    arm-linux-gcc-4.4.3/bin/arm-linux-objdump from_phone/libcutils.so -p
    
    Dynamic Section:
    PLTGOT               0x0000e100
    PLTRELSZ             0x000002e8
    JMPREL               0x00002cdc
    PLTREL               0x00000011
    REL                  0x00002fc4
    RELSZ                0x00000020
    RELENT               0x00000008
    RELCOUNT             0x00000009
    SYMTAB               0x00000990
    SYMENT               0x00000010
    STRTAB               0x00001b70
    STRSZ                0x0000116a
    HASH                 0x000000f4
    NEEDED               liblog.so
    NEEDED               libc.so
    NEEDED               libstdc++.so
    NEEDED               libm.so
    SONAME               libcutils.so   // can be replaced to NEEDED libxxxxxx.so 
    INIT_ARRAY           0x0000e000
    INIT_ARRAYSZ         0x00000008
    FINI_ARRAY           0x0000e008
    FINI_ARRAYSZ         0x0000000c
    TEXTREL              0x00000000
    SYMBOLIC             0x00000000
    FLAGS                0x00000006
    
  
    


    


