# csc-431-template
Template repo to create github classroom for csc 431

# Building Parser

To build and use the parser, ensure that the antlr and javax jar files are on
your classpath. You likely want to add something like the following to 
your ~/.bashrc file, assuming that you check out this repository in
$HOME/courses/csc431.

```
BASE_DIR=$HOME/courses/csc431

export CLASSPATH="$BASE_DIR/given_parser/antlr-4.12.0-complete.jar:$CLASSPATH"
export CLASSPATH="$BASE_DIR/given_parser/javax.json-1.0.4.jar:$CLASSPATH"
```

## Using the Parser

Now you should be able to use the built parser via

`java MiniCompiler <source.mini>`


# Provided Test Script

The `compiler_test.sh` is provided to demonstrate some semblance of an 
automated testing framework. You may use this directly if you setup
your compiler and infrastructure similar to the scripts assumptions. 
You may also simply build your own if you are comfortable with some
other framework.

Regardless, you will want some kind of a regression suite setup so that
changes during future modules do not break previous functionality.


# Using the LLVM Toolchain on ARM server

Included is a script called `enable_llvm_toolchain.sh` 

If you run this on the arm.csc.calpoly.edu server, you should be able to use 
all of the llvm v7.0.1 toolchain natively. 

```
[07:15:14] srbeard@arm:~/courses/csc431/csc-431-template $ opt --version
-bash: opt: command not found
[07:15:16] srbeard@arm:~/courses/csc431/csc-431-template $ ./enable_llvm_scl.sh
[07:15:19] srbeard@arm:~/courses/csc431/csc-431-template $ opt --version
LLVM (http://llvm.org/):
  LLVM version 7.0.1
  Optimized build.
  Default target: aarch64-unknown-linux-gnu
  Host CPU: (unknown)
```
