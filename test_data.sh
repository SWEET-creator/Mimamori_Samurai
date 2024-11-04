#!/bin/bash

# 定義するラベルの配列
labels=("eye" "face")

# デバイスID
device_id="test_device_123"

# サーバーURL
url="https://ut1z7nb5hf.execute-api.ap-northeast-1.amazonaws.com/dev"

# bboxのデータ
bbox="[100, 200, 150, 250]"

# 各ラベルについてリクエストを送信
for label in "${labels[@]}"
do
    wget --header="Content-Type: application/json" \
         --method=POST \
         --body-data="{
             \"operation\": \"add\",
             \"device_id\": \"$device_id\",
             \"record_data\": {
                 \"label\": \"$label\",
                 \"bbox\": $bbox
             }
         }" \
         "$url"
done
