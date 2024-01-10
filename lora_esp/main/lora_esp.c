// #include <stdio.h>
// #include <string.h>
// #include <driver/uart.h>
// #include <driver/gpio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"



// #define BUF_SIZE (1024)

// void app_main(void)
// {
//     // Configure a UART peripheral.
//     uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
//     };
//     uart_param_config(UART_NUM_2, &uart_config);
//     uart_set_pin(UART_NUM_2, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);
//     uart_driver_install(UART_NUM_2, BUF_SIZE * 2, 0, 0, NULL, 0);

//     uint8_t *data = (uint8_t *)malloc(BUF_SIZE);

//     while (1)
//     {
//         // Prepare data to be sent to LoRa device
//         const char *test_str = "Hello, LoRa!";
//         uart_write_bytes(UART_NUM_2, test_str, strlen(test_str));

//         // Echo the sent data on serial monitor
//         printf("Sent to LoRa: %s\n", test_str);

//         // Read data from LoRa device
//         int length = 0;
//         ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_2, (size_t *)&length));
//         length = uart_read_bytes(UART_NUM_2, data, length, 20 / portTICK_PERIOD_MS);

//         while (length == 0)
//         {
//             ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_2, (size_t *)&length));
//             length = uart_read_bytes(UART_NUM_2, data, length, 20 / portTICK_PERIOD_MS);
//             vTaskDelay(20 / portTICK_PERIOD_MS);
//         }

//         data[length] = 0; // Null-terminate whatever we received
//         printf("Received from LoRa: %s\n", data);

//         vTaskDelay(5000 / portTICK_PERIOD_MS);
//     }

//     free(data);
// }

#include <stdio.h>
#include <string.h>
#include "lora.h"

#define ECHO_TEST_TXD (GPIO_NUM_17)
#define ECHO_TEST_RXD (GPIO_NUM_16)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)


void app_main(void)
{
    lora_uart_initialize(115200, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);
    char *data = (char *)malloc(BUF_SIZE);

    while (1)
    {
        // Send data
        lora_uart_send("Hello, LoRa! This is a Packet test");

        // Receive data
        lora_uart_receive(data, 10000);

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

    free(data);
}
