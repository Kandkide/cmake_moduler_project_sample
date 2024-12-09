#!/bin/bash

# スクリプトが存在するディレクトリを取得
SCRIPT_DIR=$(cd $(dirname $0) && pwd)

# サブディレクトリの検索
SUB_DIRS=$(find "$SCRIPT_DIR" -maxdepth 1 -mindepth 1 -type d -not -path '*/.*')

# 特定のスクリプト名
SCRIPT_NAME="build-install-all-in-one.sh"

# サブディレクトリ内でスクリプトを検索
for dir in $SUB_DIRS; do
    if [ -f "$dir/$SCRIPT_NAME" ]; then
        echo "Found $SCRIPT_NAME in $dir, executing..."
        bash "$dir/$SCRIPT_NAME"
        if [ $? -ne 0 ]; then
            echo "Execution of $SCRIPT_NAME failed in $dir."
            exit 1
        fi
        echo "$SCRIPT_NAME executed successfully in $dir."
    else
        echo "$SCRIPT_NAME not found in $dir."
    fi
done

# # スクリプトが見つからない場合
# if [ $? -ne 0 ]; then
#     echo "$SCRIPT_NAME not found in any subdirectories."
#     exit 1
# fi

# スクリプトの終了
exit 0
