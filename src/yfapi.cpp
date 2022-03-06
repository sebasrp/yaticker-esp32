#include <yfapi.h>
#include <HTTPClient.h>
#include <WiFi.h>

YahooFinanceAPI::YahooFinanceAPI()
{
    _base_url = "https://query2.finance.yahoo.com/v8/finance/chart/";
}

JsonObject YahooFinanceAPI::get_ticker_data(String ticker, String period, String interval)
{
    JsonObject result = JsonObject();
    HTTPClient http;
    http.useHTTP10(true);
    http.setTimeout(HTTP_TIMEOUT);
    http.begin(_base_url + ticker);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
        DynamicJsonDocument doc(ESP.getMaxAllocHeap() - 2048);
        DeserializationError error = deserializeJson(doc, http.getStream());
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return result;
        }
        result = doc["chart"]["result"][0];
    }
    else
    {
        Serial.print("Error Code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
    return result;
}

String YahooFinanceAPI::get_ticker_info(String ticker)
{
    return "";
}