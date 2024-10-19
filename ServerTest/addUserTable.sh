wget --header="Content-Type: application/json" \
     --post-data='{ "operation": "add", "user_id": "user123", "user_data": { "name": "John Doe", "age": 30 } }' \
     -O - https://dm5ezuv5ai.execute-api.ap-northeast-1.amazonaws.com/dev