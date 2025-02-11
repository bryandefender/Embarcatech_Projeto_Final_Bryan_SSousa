/*  
  PROJETO FINAL - EMBARCATECH 2024/2025 - Instituto Federal do Ceará
  Bryan Santos Sousa 
  Turma: Microcode 
  Mentora: Gabriela

  GitHub: https://github.com/bryandefender
  Repositório:https://github.com/bryandefender/Embarcatech_Projeto_Final_Bryan_SSousa 

*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

//Define o pino 9 para receber os dados do DHT11 -> No esquemático do rasp pico W esse pino é o GP9.

#define DHT_PIN 9

/*  _______________________________________________________________________
    INICIO CODIGO CORRESPONDENTE AO SENSOR DE TEMPERATURA E UMIDADE DHT11
    _______________________________________________________________________
*/

// Struct(Estrutura) para armazenar as variáveis correspondentes a temperatura e umidade.
typedef struct {
    float temp;
    float humid;
} DHT11_Dados;

// Função que faz a leitura do sensor DHT11
bool readDHT11(DHT11_Dados *data) {
    uint8_t data_bytes[5] = {0};
    uint8_t counter = 0;
    uint8_t bit_index = 7;

    // Comandos que iniciam a comunicação
    gpio_set_dir(DHT_PIN, GPIO_OUT);
    gpio_put(DHT_PIN, 0);
    sleep_ms(18); // Sinal baixo(LOW) por 18ms
    gpio_put(DHT_PIN, 1);
    sleep_us(40); // Sinal alto(HIGH) por 40μs

    // Configura pino como entrada
    gpio_set_dir(DHT_PIN, GPIO_IN);
    busy_wait_us(10);

    // Espera a resposta do enviada pelo sensor
    while (gpio_get(DHT_PIN) == 1);
    while (gpio_get(DHT_PIN) == 0);
    while (gpio_get(DHT_PIN) == 1);

    // Lê 40 bits de dados
    for (int i = 0; i < 40; i++) {
        while (gpio_get(DHT_PIN) == 0);
        uint64_t start_time = time_us_64();
        while (gpio_get(DHT_PIN) == 1);
        uint64_t duration = time_us_64() - start_time;

        if (duration > 40) { // Bit 1
            data_bytes[counter] |= (1 << bit_index);
        }

        if (bit_index == 0) {
            bit_index = 7;
            counter++;
        } else {
            bit_index--;
        }
    }

    // Verifica checksum
    if (data_bytes[4] == (data_bytes[0] + data_bytes[1] + data_bytes[2] + data_bytes[3])) {
        data->humid = data_bytes[0];
        data->temp = data_bytes[2];
        return true;
    }

    return false;
}
/*  _______________________________________________________________________
    //FIM DA IMPLEMENTAÇÃO DO CÓDIDO CORRESPONDENTE AO DHT11
    _______________________________________________________________________
*/
//
//
//
/*  _______________________________________________________________________
    INICIO CODIGO CORRESPONDENTE AO SERVO MOTOR MICROSERVO SG90
    _______________________________________________________________________
*/
 
// Controle um servo em graus ou milissegundos
float clockDiv = 64;
float wrap = 39062;

void setMiliseg(int PIN_SERVO, float miliseg)
{
    pwm_set_gpio_level(PIN_SERVO, (miliseg/20000.f)*wrap);
}

void setServo(int PIN_SERVO, float iniciaMiliseg)
{
    gpio_set_function(PIN_SERVO, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PIN_SERVO);

    pwm_config config = pwm_get_default_config();
    
    uint64_t clockspeed = clock_get_hz(5);
    clockDiv = 64;
    wrap = 39062;

    while (clockspeed/clockDiv/50 > 65535 && clockDiv < 256) clockDiv += 64; 
    wrap = clockspeed/clockDiv/50;

    pwm_config_set_clkdiv(&config, clockDiv);
    pwm_config_set_wrap(&config, wrap);

    pwm_init(slice_num, &config, true);

    setMiliseg(PIN_SERVO, iniciaMiliseg);
}

////////////////////////////////////////////////////////////////////////////////////

void controlarVazaoAgua(int PIN_SERVO, float temperatura) {
    if (temperatura >= 31.0) {
        setMiliseg(PIN_SERVO, 2200); // Abre a válvula (180°) oringal 2500
        sleep_ms(30000); // Mantém a válvula aberta por 10 segundos
    } else {
        setMiliseg(PIN_SERVO, 1100); // Mantém a válvula fechada (90°)
    }
}

int main() {
    stdio_init_all();

    gpio_init(DHT_PIN); // Inicializa o DHT

    DHT11_Dados dht_dados; // Cria o tipo dht_dados para usar as variáveis temp e humid criadas na struct DHT_11_Dados

    int PIN_SERVO = 22; // Define o pino GPIO para o servo motor
    gpio_init(PIN_SERVO);
    setServo(PIN_SERVO, 1100); // Inicializa o servo motor na posição neutra (90°)

    while (true) {
        if (readDHT11(&dht_dados)) {
            printf("____________________.__________________\n");
            printf("|Temperatura: %.1f°C | Umidade: %.1f%% |\n", dht_dados.temp, dht_dados.humid);
            controlarVazaoAgua(PIN_SERVO, dht_dados.temp); // Controla a vazão de água com base na temperatura
        } else {
            printf("ERRO NA LEITURA\n");
        }

        sleep_ms(2000); // Intervalo sugerido para se fazer as leituras, menos que isso não é adequado.
    }

    return 0;
}

    

