#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int main(void) {
    CURL *curl;
    CURLcode res;

    // POSTデータ
    const char *post_data = "{ \"operation\": \"check_existence\", \"user_id\": \"user123\" }";
    const char *url = "https://dm5ezuv5ai.execute-api.ap-northeast-1.amazonaws.com/dev";

    // cURLの初期化
    curl = curl_easy_init();
    if (curl) {
        // URLの設定
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // POSTデータの設定
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

        // Content-Typeヘッダーの設定
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 出力を標準出力に設定
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);

        // リクエストの実行
        res = curl_easy_perform(curl);

        // エラーの確認
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // 後処理
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return 0;
}
