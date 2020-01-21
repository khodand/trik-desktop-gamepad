#!/bin/bash
set -euxo pipefail
case $OS_NAME in
  macOS)
    ;;
  Linux)
    docker stop builder
    ;;
  *) exit 1 ;;
esac
