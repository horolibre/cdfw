#!/usr/bin/env bash

# Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
# Use of this source code is governed by a GPLv3 license that can be found in
# the LICENSE file.

function main {
  local script_dir
  script_dir=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
  cd "${script_dir}/.."

  find cdfw/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format --style=file -i
  find test/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format --style=file -i
}

main

