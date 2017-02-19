#include<Request.h>

Request::Request(){
    //init
}
char* Request::str2char(string str){
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}
string Request::Sensor_json(float temp,float hum){
    
    char buf[10];
    MbedJSONValue json;
    std::string s;
    
    sprintf(buf,"%2f",temp);
    json["TEMPERATURE"] = buf;
    sprintf(buf,"%2f",hum);
    json["HUMIDITY"] = buf;
    s = json.serialize();
    return s;
}
string Request::OnOff_json(int sw){
    //char buf[5];
    MbedJSONValue json;
    std:string s;
    //other type to str
    //sprintf(buf,"%d",sw);
    json["IS_ON"] = sw;
    s = json.serialize();
    return s;
}
void Request::Sensor_http_post(string json){
    //set header
    char str[128];
    char* cstr = str2char(json);
    HTTPText text(str,128);
    HTTPText post(cstr);
    
    printf("put data=%s\n",json.c_str());
    
    int ret = http.post(Sensor_url,post,&text);
    if (!ret) {
        printf("Executed POST successfully - read %d characters\n", strlen(str));
        printf("Result: %s\n", str);
        return;
    } else {
        printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
        return;
    }
}
void Request::OnOff_http_post(string json){
    char str[128];
    char* cstr = str2char(json);
    HTTPText text(str,128);
    HTTPText post(cstr);
    printf("put data=%s\n",json.c_str());
    
    int ret = http.post(Switch_url,post,&text);
    if (!ret) {
        printf("Executed POST successfully - read %d characters\n", strlen(str));
        printf("Result: %s\n", str);
        return;
    } else {
        printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
        return;
    }
}
int Request::Result_http_post(){
    char* null = "{}";
    char str[128];
    HTTPText text(str,128);
    HTTPText post(null,4);
    int ret = http.post(Status_url,post,&text);
    if (!ret) {
        printf("Executed POST successfully - read %d characters\n", strlen(str));
        //printf("Result: %s\n", str);
        //std:string re;
        int return_value = extraction_json(str);
        printf("Return value =%d\n",return_value);
        return return_value;
    } else {
        printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
        return -1;
    }
}
int Request::extraction_json(char* response){
    MbedJSONValue json;
    //const char* temp = response.c_str();
    parse(json,response);
    int myvalue = json["RESULT"].get<int>();
    return myvalue;
}
    