wget --header="Content-Type: application/json" \
     --method=POST \
     --body-data='{
         "operation": "add",
         "device_id": "test_device_123",
         "record_data": {
             "label": "test_label",
             "bbox": [100, 200, 150, 250]
         }
     }' \
     https://ut1z7nb5hf.execute-api.ap-northeast-1.amazonaws.com/dev