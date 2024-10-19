wget --header="Content-Type: application/json" \
     --method=POST \
     --body-data='{
         "operation": "check_existence",
         "device_id": "test_device_123",
         "start_time": "1629326412",
         "end_time": "1729326420"
     }' \
     https://ut1z7nb5hf.execute-api.ap-northeast-1.amazonaws.com/dev
    