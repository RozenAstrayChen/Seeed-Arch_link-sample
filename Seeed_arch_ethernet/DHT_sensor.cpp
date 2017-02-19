#include<DHT_sensor.h>
DHT_sensor::DHT_sensor(){
    c = 0.0f;
    h = 0.0f;
};
void DHT_sensor::read_sensor(DHT sensor){
    int error = sensor.readData();
    if(error==0){
        //printf("success!!\n");
        c = sensor.ReadTemperature(CELCIUS);
        h = sensor.ReadHumidity();
        return;
    }else{
        printf("error! error =%s\n",error);
        c = 0.0f;
        h = 0.0f;
        return;
    }
}
float DHT_sensor::get_celcius(){
    return c;
}
float DHT_sensor::get_humi(){
    return h;
}
