#include "pico/stdlib.h"

const uint ROW_PINS[4] = {8, 7, 6, 5};     // Linhas: R1, R2, R3, R4
const uint COL_PINS[4] = {4, 3, 2, 28};    // Colunas: C1, C2, C3, C4

#define LED_PIN1 13 // LED 1 conectado ao pino 13
#define LED_PIN2 12 // LED 2 conectado ao pino 12
#define LED_PIN3 11 // LED 3 conectado ao pino 11
#define BUZZER_PIN 21 // Buzzer conectado ao pino 21

const char KEYPAD[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
    
char set_senha[5];     // Senha criada pelo usuário
char entered_senha[5]; // Senha digitada

// Função para varrer o teclado e identificar a tecla pressionada
char scan_keypad()
{
    for (int row = 0; row < 4; row++)
    {
        gpio_put(ROW_PINS[row], 0); // Ativa a linha colocando em LOW
        for (int col = 0; col < 4; col++)
        {
            if (!gpio_get(COL_PINS[col])) // Se a tecla for pressionada
            {
                gpio_put(ROW_PINS[row], 1); // Restaura a linha para HIGH
                return KEYPAD[row][col];    // Retorna a tecla pressionada
            }
        }
        gpio_put(ROW_PINS[row], 1); // Linha volta para HIGH após a varredura
    }
    return '\0'; // Nenhuma tecla pressionada
}

// Configuração dos pinos do teclado
void setup_keyboard()
{
    for (int i = 0; i < 4; i++)
    {
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(ROW_PINS[i], GPIO_OUT);
        gpio_put(ROW_PINS[i], 1); // Nível alto por padrão
    }

    for (int i = 0; i < 4; i++)
    {
        gpio_init(COL_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_IN);
        gpio_pull_up(COL_PINS[i]); // Pull-up interno
    }
}
void setup_buzzer()
{
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

// Função para acender o LED azul
void led_azul() {
    gpio_put(LED_PIN1, 1);
    sleep_ms(2000); // LED azul aceso por 2 segundos
    gpio_put(LED_PIN1, 0);
}

// Função para capturar uma senha do teclado
void captura_senha(char *password) {
    int index = 0;
    while (index < 4) {
        char key = scan_keypad();
        if (key != '\0' && key >= '0' && key <= '9') {
            password[index++] = key;
            printf("Número digitado: %c\n", key);
        }
        sleep_ms(100);
    }
    password[4] = '\0'; // Finaliza a string
    printf("Senha capturada: %s\n", password);
}

int main()
{
    setup_keyboard();
    setup_buzzer();

    // Configuração dos LEDs
    gpio_init(LED_PIN1);
    gpio_set_dir(LED_PIN1, GPIO_OUT);
    gpio_init(LED_PIN2);
    gpio_set_dir(LED_PIN2, GPIO_OUT);
    gpio_init(LED_PIN3);
    gpio_set_dir(LED_PIN3, GPIO_OUT);

    printf("Defina sua senha (4 dígitos):\n");
    captura_senha(set_senha); // Captura a senha inicial
    printf("Senha definida!\n");
    led_azul(); // Sinaliza o fim da digitação

    while (1)
    {
        char key = scan_keypad();
        if (key != '\0') // Se alguma tecla foi pressionada
        {
            printf("Tecla pressionada: %c\n", key);
            if (key == 'A') // Aciona o LED 1
            {
                gpio_put(LED_PIN1, 1);
            }
            else if (key == 'B') // Aciona o LED 2
            {
                gpio_put(LED_PIN2, 1);
            }
            else if (key == 'C') // Aciona o LED 3
            {
                gpio_put(LED_PIN3, 1);
            }
            else if (key == '1') // Aciona o Buzzer
            {
                gpio_put(BUZZER_PIN, 1); // Liga o buzzer
            }
            else // Desliga todos os LEDs para outras teclas
            {
                gpio_put(LED_PIN1, 0);
                gpio_put(LED_PIN2, 0);
                gpio_put(LED_PIN3, 0);
                gpio_put(BUZZER_PIN, 0); // Desliga o buzzer
            }
        }
        sleep_ms(100);
    }

    return 0;
}