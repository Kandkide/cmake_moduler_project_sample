#!/bin/bash
# enact-build-install-all-in-one.sh-1.0.1

# スクリプトが存在するディレクトリを取得
SCRIPT_DIR=$(cd $(dirname $0) && pwd)

# Alternative 1
# サブディレクトリの検索
SUB_DIRS=$(find "$SCRIPT_DIR" -maxdepth 1 -mindepth 1 -type d -not -path '*/.*')

# # Alternative 2
# # 優先的に処理するサブディレクトリを手動で指定
# PRIORITY_DIRS="$SCRIPT_DIR/kkd-honly $SCRIPT_DIR/kkd-lib"

# # 残りのサブディレクトリを検索
# ALL_DIRS=$(find "$SCRIPT_DIR" -maxdepth 1 -mindepth 1 -type d -not -path '*/.*')
# OTHER_DIRS=""

# # 自動検出されたディレクトリから優先ディレクトリを除外
# for dir in $ALL_DIRS; do
#     if [[ ! " $PRIORITY_DIRS " =~ " $dir " ]]; then
#         OTHER_DIRS="$OTHER_DIRS $dir"
#     fi
# done

# # 優先ディレクトリとその他のディレクトリを結合
# SUB_DIRS="$PRIORITY_DIRS $OTHER_DIRS"
# # Alternative 2 (end)

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
