
#include "HTTPClient.h"
#include<MbedJSONValue.h>
static char* Sensor_url = "your url";
static char* Switch_url = "your url";
static char* Status_url = "your url";

//static HTTPMap map;

class Request {
public:
    HTTPClient http;
    Request();
    string Sensor_json(float temp,float hum);
    string OnOff_json(int sw);
    void test_get();
    void Sensor_http_post(string json);
    void OnOff_http_post(string json);
    int Result_http_post();
    int extraction_json(char*);
    
    char* str2char(string str);
    
};