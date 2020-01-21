#!/bin/bash
set -euxo pipefail

echo "$VERA"
case $OS_NAME in
  macOS)
    echo "macOS install.sh"
    REQURED_PACKAGES="qt ccache python@2 python@3"
    for p in $REQURED_PACKAGES ; do
      rmdir $CELLAR_CACHE_DIR/$p && brew install $p \
      || brew link --force $p
    done
  ;;

  Linux)
    echo "Linux install.sh"
    docker pull trikset/linux-builder
    docker run -d -v $HOME:$HOME:rw -w `pwd` --name builder trikset/linux-builder Xvfb :0
    if [[ "$CONFIG" == "debug" ]]
    then
      pip install --user codecov
    fi
    ;;
  *) exit 1 ;;
esac
