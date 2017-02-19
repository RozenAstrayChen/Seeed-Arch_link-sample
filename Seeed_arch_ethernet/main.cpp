#include<main.h>
#include<Request.h>
#include<DHT_sensor.h>


int main() {
    mbed_mac_address((char *)MAC_Addr);
    //#if USE_DHCP
    int ret = ethernet.init(MAC_Addr);
    //#else
    //int ret = ethernet.init(MAC_Addr,IP_Addr,IP_Subnet,IP_Gateway);
    //#endif
    if (!ret) {
        pc.printf("Initialized, MAC: %s\r\n", ethernet.getMACAddress());
        ret = ethernet.connect();
        if (!ret) {
            pc.printf("IP: %s, MASK: %s, GW: %s\r\n",
                      ethernet.getIPAddress(), ethernet.getNetworkMask(), ethernet.getGateway());
        } else {
            pc.printf("Error ethernet.connect() - ret = %d\r\n", ret);
            
            exit(0);
        }
    } else {
        pc.printf("Error ethernet.init() - ret = %d\r\n", ret);
        exit(0);
    }
    //post
    Request rq;
    //DHT
    DHT_sensor dht;
    while(1){
        wait(0.5f);
        dht.read_sensor(sensor);
        printf("temp=%4.2f humi=%4.2f\r\n",dht.get_celcius(),dht.get_humi());
        string sensor_json = rq.Sensor_json(dht.get_celcius(),dht.get_humi());
        string sw_json = rq.OnOff_json(PIR_sensor());
        rq.Sensor_http_post(sensor_json);
        //wait(0.5f);
        rq.OnOff_http_post(sw_json);
        //wait(0.5f);
        status_check(rq.Result_http_post());
        
    }
    
}
void status_check(int value){
    if(value<=0){
        led =0;
        return;
    }else{
        led = 1;
    }
}
int PIR_sensor(){
    if (!alarm){
            //printf("finding\n");
            led1=1;
            wait(2);
            return 0;
    }else if(alarm){
            //printf("finding\n");
            led1=0;
            return 1;
            //wait(0.5f);
    }
}
