#!/bin/bash
set -euxo pipefail
case $1 in
  macOS)
    ;;
  Linux)
    docker stop builder
    ;;
  *) exit 1 ;;
esac
