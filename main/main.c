#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include <inttypes.h>
#include "include/wifi.h"
#include "include/mqtt.h"
#include "include/dht11.h"
#include "include/gpio.h"

SemaphoreHandle_t conexaoWifiSemaphore;
SemaphoreHandle_t conexaoMQTTSemaphore;

void sendInformation(char* info ,int data, char* topic) {
  char msg[200];
  sprintf(msg, info, data);
  mqtt_envia_mensagem(topic, msg);
}

void conectadoWifi(void * params) {
  while(true) {
    if(xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY)) {
      mqtt_start();
    }
  }
}

void DHT11(void *params) {
    while (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY)) {
        while (true) {
            struct dht11_reading data = getInformation();
            if (data.status == 0 || (data.temperature > 0 && data.humidity > 0)) {
              sendInformation("{\"temperature\": %d}", data.temperature, "v1/devices/me/telemetry");
              sendInformation("{\"umidade\": %d}", data.humidity, "v1/devices/me/attributes");
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

void BUZZER(void *params) {
  configureBuzzer();
  playSound();
}

void mqttTask(void *params) {
  xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
}

void dht11Task(void *params) {
  xTaskCreate(&DHT11, "Coleta de temperatura e umidade", 4096, NULL, 1, NULL);
}

void buzzerTask(void *params) {
  xTaskCreate(&BUZZER, "Acionamento buzzer", 4096, NULL, 1, NULL);
}


void app_main(void)
{
    // Inicializa o NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    conexaoWifiSemaphore = xSemaphoreCreateBinary();
    conexaoMQTTSemaphore = xSemaphoreCreateBinary();
    wifi_start();

    pthread_t tid[2];

    configureLED();
    pthread_create(&tid[0], NULL, (void *)mqttTask, (void *)NULL);
    pthread_create(&tid[1], NULL, (void *)dht11Task, (void *)NULL);
    // pthread_create(&tid[1], NULL, (void *)buzzerTask, (void *)NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    // pthread_join(tid[1], NULL);
}
