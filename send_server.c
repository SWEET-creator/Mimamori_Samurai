#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// フラグを定義
int flag = 0; // 例: フラグが1になったらリクエスト送信

// Webサーバに情報を送信する関数
void send_data_to_server() {
    CURL *curl;
    CURLcode res;

    // POSTデータ（送信するJSON形式のデータ）
    const char *post_data = "{\"status\": \"flag_triggered\", \"value\": 1}";

    // curl初期化
    curl = curl_easy_init();
    if(curl) {
        // URL設定
        curl_easy_setopt(curl, CURLOPT_URL, "http://example.com/post-endpoint");

        // POSTリクエスト設定
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

        // リクエスト送信
        res = curl_easy_perform(curl);

        // エラーチェック
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // curlクリーンアップ
        curl_easy_cleanup(curl);
    }
}

int main() {
    // 他の初期化処理
    printf("Starting program...\n");

    // フラグが立つかどうかをチェックする処理
    // ここでは簡単に例として1を設定
    flag = 1; // フラグが立ったと仮定

    // フラグが立ったらデータを送信
    if (flag == 1) {
        printf("Flag detected, sending data to server...\n");
        send_data_to_server();
    } else {
        printf("Flag not detected.\n");
    }

    return 0;
}
