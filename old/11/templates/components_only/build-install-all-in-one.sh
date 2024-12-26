#!/bin/bash

# スクリプトが存在するディレクトリを取得
SCRIPT_DIR=$(cd $(dirname $0) && pwd)

# ビルドディレクトリの名前
BUILD_DIR="${SCRIPT_DIR}/build"

# 引数の確認: インストールを実行するかどうか
INSTALL_PROJECT="on"
if [ "$1" == "no-install" ]; then
    INSTALL_PROJECT="off"
fi

# CMakeによる構成
echo "Running CMake configuration..."
cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR" -DRUN_EXECUTABLE_POST_BUILD="off"
if [ $? -ne 0 ]; then
    echo "CMake configuration failed."
    exit 1
fi

# CMakeによるビルド
echo "Building project..."
cmake --build "$BUILD_DIR"
if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

# インストールを実行する場合のみ実行
if [ "$INSTALL_PROJECT" == "on" ]; then
    echo "Installing project..."
    sudo cmake --install "${BUILD_DIR}"
    if [ $? -ne 0 ]; then
        echo "Install failed."
        exit 1
    fi
    echo "Project installed successfully."
else
    echo "Skipping installation step."
fi

echo "Build completed successfully."

# スクリプトの終了
exit 0
