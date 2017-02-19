#include<DHT.h>
class DHT_sensor{
    public:
        DHT_sensor();
        void  read_sensor(DHT);
        float get_celcius();
        float get_humi();
    private:
        float c;
        float h;
    
};