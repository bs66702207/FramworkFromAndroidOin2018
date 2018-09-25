BUILD_STATIC_JAVA_LIBRARY: JAVA静态库，.class文件打包而成的JAR包，可以在任何虚拟机上运行
BUILD_JAVA_LIBRARY: JAVA共享库，在静态库的基础上进一步打包而成的.dex文件，即android系统使用的dex类库

#LOCAL_MODULE := android.hardware.automotive.vehicle-V2.0-java
#include $(BUILD_JAVA_LIBRARY)
wuj@wuj:~/workspace/codes/M01/1.B1.1/LINUX/android/hardware/interfaces/automotive/vehicle/2.0$ mm
...
[100% 13/13] Copy: out/target/product/M01/system/framework/oat/arm64/android.hardware.automotive.vehicle-V2.0-java.vdex
#out中间文件目录
$ ls out/target/common/obj/JAVA_LIBRARIES/android.hardware.automotive.vehicle-V2.0-java_intermediates   
classes.dex  classes.jack  jack_res_jar_flags  jack-rsc  jack-rsc.java-source-list  javalib.jar  link_type  with-local



#LOCAL_MODULE := android.hardware.automotive.vehicle-V2.0-java-static
#include $(BUILD_STATIC_JAVA_LIBRARY)
wuj@wuj:~/workspace/codes/M01/1.B1.1/LINUX/android/hardware/interfaces/automotive/vehicle/2.0$ mm
...
[100% 4/4] Copy: out/target/product/M01/obj/JAVA_LIBRARIES/android....ware.automotive.vehicle-V2.0-java-static_intermediates/classes.jack
#out中间文件目录
$ ls out/target/common/obj/JAVA_LIBRARIES/android.hardware.automotive.vehicle-V2.0-java-static_intermediates 
classes.jack  jack-rsc  jack-rsc.java-source-list  link_type

#加入LOCAL_JACK_ENABLED := disabled后，发现static编译出现了classes.jar，非static编译则没有
$ ls out/target/common/obj/JAVA_LIBRARIES/android.hardware.automotive.vehicle-V2.0-java-static_intermediates                  
anno  classes  classes-full-debug.jar  classes.jar  link_type

