#!/bin/bash
set -euxo pipefail
case ${{ runner.os }} in
  macOS)
    ;;
  Linux)
    docker stop builder
    ;;
  *) exit 1 ;;
esac
