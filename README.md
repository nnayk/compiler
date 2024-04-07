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
