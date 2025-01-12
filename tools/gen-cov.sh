#!/usr/bin/env bash

# Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
# Use of this source code is governed by a GPLv3 license that can be found in
# the LICENSE file.

function main {
  local script_dir
  script_dir=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
  cd "${script_dir}/.."

  # Reinitialize the coverage directory.
  rm -rf ./coverage
  mkdir coverage

  # Generate coverage data.
  export LLVM_PROFILE_FILE="./coverage/cdfw.%p.profraw"
  local env="macos-cov"
  pio test -e "${env}"
  if [ $? -ne 0 ]; then
    echo "Failed to generate coverage data."
    exit 1
  fi

  # Generate the coverage report(s).
  export PATH=/Library/Developer/CommandLineTools/usr/bin:$PATH
  llvm-profdata merge -sparse coverage/*.profraw -o coverage/cdfw.profdata
  if [ $? -ne 0 ]; then
    echo "Failed to merge coverage data."
    exit 1
  fi

  local inst_bin=.pio/build/"${env}"/program
  llvm-cov show -instr-profile=coverage/cdfw.profdata "${inst_bin}" \
    -sources cdfw/ > coverage/coverage_view.txt
  if [ $? -ne 0 ]; then
    echo "Failed to generate coverage view."
    exit 1
  fi

  llvm-cov report -instr-profile=coverage/cdfw.profdata "${inst_bin}" \
    -sources cdfw/ > coverage/coverage_report.txt
  if [ $? -ne 0 ]; then
    echo "Failed to generate coverage report."
    exit 1
  fi

  llvm-cov export -format=lcov -instr-profile=coverage/cdfw.profdata "${inst_bin}" \
    -sources cdfw/ > coverage/cdfw.lcov
  if [ $? -ne 0 ]; then
    echo "Failed to generate coverage report."
    exit 1
  fi
}

main

