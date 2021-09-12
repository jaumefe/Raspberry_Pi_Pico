#ifdef PICO_DEFAULT_LED_PIN
#define LED_PIN PICO_DEFAULT_LED_PIN
#endif

const int DHT_PIN = 34;
const int MAX_TIMINGS = 85; //enviament màxim de trames (3 d'inici + 5 enviaments de 8 bits x 8 bits x 2 (Per duplicitat per enviar dades))

typedef struct
{
    float humidity;
    float temperature;
} DHT_reading;

void readFromDHT(DHT_reading *measure);

int main(){
    stdio_init_all(); //Method used to enable the stdio support for UART
    gpio_init(DHT_PIN);
    while(1){
        DHT_reading measure;
        readFromDHT(&measure);
        printf("Humidity = %.1f%%, Temperature = %.1f%%\n", measure.humidity, measure.temperature)
        sleep_ms(2000);
    }
}

void readFromDHT(DHT_reading* measure){
    uint previous = 1;
    int data[5] = {0,0,0,0,0};
    uint j = 0;
    //activation of the sensor
    gpio_set_dir(DHT_PIN, GPIO_OUT);
    gpio_put(DHT_PIN, FALSE);
    sleep_ms(20);
    gpio_set_dir(DHT_PIN, GPIO_IN);
    for(int i = 0; i < MAX_TIMINGS; i++){
        uint count = 0;
        while (previous == gpio_get(DHT_PIN)){
            count++;
            sleep_us(1);
            if(count == 255) break;
        }
        previous = gpio_get(DHT_PIN);
        if ((i >= 4) && (i % 2 == 0)){
            data[j / 8] <<= 1;
            if count( > 16) data[j / 8] |= 1;
            j++;
        }
        if ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))) {
            result->humidity = (float) ((data[0] << 8) + data[1]) / 10;
            if (result->humidity > 100) {
                result->humidity = data[0];
            }
            result->temp_celsius = (float) (((data[2] & 0x7F) << 8) + data[3]) / 10;
            if (result->temp_celsius > 125) {
                result->temp_celsius = data[2];
            }
            if (data[2] & 0x80) {
                result->temp_celsius = -result->temp_celsius;
            }
         } else {
             printf("Bad data\n");
        }
    }
}
