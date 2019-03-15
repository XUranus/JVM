# JVM
this is a toy Java Virtual Machine implemented by C++ ,support java8 or higher

(only support two native methods: `System.out.print()` and `System.out.println()` ,and not support `invokedynamic` yet)

## Build
Require
 - linux/macOS
 - C++11
 - libzip

```
cd path/to/JVM
mkdir build
cd build
cmake ..
make
```

## Run
run `./JVM` requires a java runtime `rt.jar` which can be find in `lib/jre/lib/rt.jar`

move `jre` folder to excutable file root
```
cd /path/to/JVM/lib
mv jre ../build
```
and then run
```
./JVM [className]
```
or if you want to specify a rt.jar path:
```
./JVM -cp [userPath] [className]
```
## Full Usage
```
./JVM <options> [classname]
```
options: 
 - `-help` :show help
 - `-version` :show version
 - `-cp` :specify classpath
 - `-verbose:class` :show class loading process
 - `-verbose:inst` :show instruction excuting 
 - `-classpy` :show classpy info,like `javap -verbose [classname]`

## TODO
 - implement native
 - implement exception handler
 - implement annotation attribute
 - implement GC algorithm

## Screenshot
a fibonacci test case:

![](screenshot/demo1.png)

show class loading process and instructions excuting:

![](screenshot/demo2.png)