#ifndef YFAPI_H
#define YFAPI_H

#include <Arduino.h>
#include <ArduinoJson.h>

class YahooFinanceAPI
{
private:
    String _base_url;
    String build_url(String ticker, String period, String interval);

public:
    YahooFinanceAPI();

    // Retrieves ticker data given period and interval
    // period: Time period to query. Valid periods: 1d,5d,1mo,3mo,6mo,1y,2y,5y,10y,ytd,max
    // interval: granularity of the data. Valid intervals: 1m,2m,5m,15m,30m,60m,90m,1h,1d,5d,1wk,1mo,3mo
    JsonObject get_ticker_data(String ticker, String period, String interval);
    String get_ticker_info(String ticker);
};
#endif