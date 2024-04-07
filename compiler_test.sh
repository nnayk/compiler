#!/bin/bash

make clean -s
make -s

BASE_DIR=$HOME/courses/csc431

export CLASSPATH="$BASE_DIR/given_parser/antlr-4.12.0-complete.jar:$CLASSPATH"
export CLASSPATH="$BASE_DIR/given_parser/javax.json-1.0.4.jar:$CLASSPATH"

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

INS_ERRORS=tests/milestone1/ins/*
EXPECTED_ERRORS=tests/milestone1/expected
OUTS_ERRORS=tests/milestone1/outs

INSCFG=tests/milestone2/cfg/ins/*
EXPECTEDCFG=tests/milestone2/cfg/expected
OUTSCFG=tests/milestone2/cfg/outs

BENCHMARKS=tests/milestone2/benchmarks/*

errors_flag=false
cfg_flag=false

function runBenchmarkTests()
{
    local flag=$1

    for benchmark in $BENCHMARKS; do
          f=$(basename -- "${benchmark/*.mini}")
          llvm="$benchmark/$f.ll"

          echo "=======================[$flag]======================="
          echo ""
          echo "TESTING: $f"
          java MiniCompiler $benchmark/$f.mini > $llvm $flag
          echo -n "Number of lines in LLVM: "
          cat $llvm | sed '/^\s*$/d' | wc -l
          echo ""

          if clang -o $benchmark/$f $llvm ; then

              echo "Checking Normal Input..."
              $benchmark/$f < $benchmark/input > $benchmark/output
              if diff $benchmark/output $benchmark/output.expected &>/dev/null; then
                echo -e "${GREEN}SUCCESS${NC}"
              else
                echo -e "${RED}FAIL${NC}"
              fi

              echo "Checking Longer Input..."
              $benchmark/$f < $benchmark/input.longer > $benchmark/output.longer
              if diff $benchmark/output.longer $benchmark/output.longer.expected &>/dev/null; then
                echo -e "${GREEN}SUCCESS${NC}"
              else
                echo -e "${RED}FAIL${NC}"
              fi
          else
              echo -e "${RED}FAIL${NC}"
              continue
          fi
          echo ""
        done
}

function runExpectedErrors()
{
      for in_file in $INS_ERRORS; do
          f=$(basename -- "${in_file}")
          out=$OUTS_ERRORS/$f.out
          expected=$EXPECTED_ERRORS/$f.expected

          echo "===================[errors]======================="
          echo ""
          echo "TESTING: $f"
          java MiniCompiler $in_file > $out -errors
          echo ""

          if  diff $out $expected &>/dev/null; then
            echo -e "${GREEN}SUCCESS${NC}"
          else
            echo -e "${RED}FAIL${NC}"
          fi

      done
}

function runCFGTests()
{
      for in_file in $INSCFG; do
          f=$(basename -- "${in_file}")
          out=$OUTSCFG/$f.out
          expected=$EXPECTEDCFG/$f.expected

          echo "=======================[cfg]======================="
          echo ""
          echo "TESTING: $f"
          java MiniCompiler $in_file > $out -cfg
          echo ""

          if  diff $out $expected &>/dev/null; then
            echo -e "${GREEN}SUCCESS${NC}"
          else
            echo -e "${RED}FAIL${NC}"
          fi

      done
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        -errors)
            runExpectedErrors
            ;;
        -cfg)
            runCFGTests
            ;;
        -stack)
            runBenchmarkTests "-stack"
            ;;
        -ssa)
            runBenchmarkTests "-ssa"
            ;;
        -opt)
            runBenchmarkTests "-opt"
            ;;
        *)
            echo "Unknown flag: $1"
            exit 1
            ;;
    esac
    shift
done



