#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"


#define TAG "RS485_ECHO_APP"

#define RS485_TXD                (17)
#define RS485_RXD                (16)
#define RS485_RTS                (12)
#define GPIO_485_TX_EN           (12)
#define GPIO_OUTPUT_PIN_SEL      ((1ULL<<GPIO_485_TX_EN))

#define RS485_UART_PORT_NUM      (2)
#define RS485_UART_BAUD_RATE     (38400)
#define RS485_TASK_STACK_SIZE    (4096)

#define BUF_SIZE (1024)

static void rs485_task(void *arg)
{
    // 데이터 
    uint8_t data[BUF_SIZE];

    // UART 옵션 설정
    uart_config_t uart_config = {
        .baud_rate = RS485_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    int intr_alloc_flags = 0;

    // UART 인터럽트를 IRAM에 배치
    // Menuconfig에서 설정하거나 "#if & #endif" 제거해 사용 가능
    // 해당 옵션을 사용하지 않으면 SPI 플래시 작업 중 UART 데이터를 손실 할 수 있다고 함.
#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    // GPIO 설정
    gpio_config_t io_conf;
    // 인터럽트 비활성
    io_conf.intr_type = GPIO_INTR_DISABLE;
    // 출력 모드
    io_conf.mode = GPIO_MODE_OUTPUT;
    // GPIO 비트 마스크 e.g.GPIO12
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    // 풀다운 비활성
    io_conf.pull_down_en = 0;
    // 풀업 비활성
    io_conf.pull_up_en = 0;
    // 설정!
    gpio_config(&io_conf);

    // UART 드라이버 로드
    ESP_ERROR_CHECK(uart_driver_install(RS485_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    // 옵션 설정
    ESP_ERROR_CHECK(uart_param_config(RS485_UART_PORT_NUM, &uart_config));
    // 핀 설정
    ESP_ERROR_CHECK(uart_set_pin(RS485_UART_PORT_NUM, RS485_TXD, RS485_RXD, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    ESP_LOGI(TAG, "Start ");

    // 데이터 수신 모드
    gpio_set_level(GPIO_485_TX_EN, false);

    while (1) {
        // 데이터 받기, 타임아웃 20 ms
        int len = uart_read_bytes(RS485_UART_PORT_NUM, data, BUF_SIZE, 20 / portTICK_RATE_MS);

        // 받은 데이터가 있다면
        if(len > 0) { 
            // 받은 데이터 출력
            printf("[ ");
            for (int i = 0; i < len; i++) {
                printf("0x%.2X ", (uint8_t)data[i]);                
            }
            printf("] \n");            

            // 데이터 송신 모드
            gpio_set_level(GPIO_485_TX_EN, true);

            // 받은 데이터 그대로 데이터 전송
            uart_write_bytes(RS485_UART_PORT_NUM, (const char *) data, len);

            // 데이터 전송 완료까지 대기, 타임아웃 100ms
            uart_wait_tx_done(RS485_UART_PORT_NUM, 100 / portTICK_RATE_MS);

            // 데이터 수신 모드
            gpio_set_level(GPIO_485_TX_EN, false);
        }
    }
}

void app_main(void)
{
    xTaskCreate(rs485_task, "rs485_uart_task", RS485_TASK_STACK_SIZE, NULL, 10, NULL);
}
