#include "pico/stdlib.h"
#include <string.h> // Para usar a função memset e strcmp
#include <stdio.h>

const uint ROW_PINS[4] = {8, 7, 6, 5};     // Linhas: R1, R2, R3, R4
const uint COL_PINS[4] = {4, 3, 2, 28};    // Colunas: C1, C2, C3, C4

#define LED_PIN1 13 // LED 1 (azul) conectado ao pino 13
#define LED_PIN2 11 // LED 2 (vermelho) conectado ao pino 11
#define LED_PIN3 12 // LED 3 (verde) conectado ao pino 12
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

// Função para capturar uma senha do teclado
void captura_senha(char *password) {
    int index = 0;
    gpio_put(LED_PIN1, 1);  // Acende o LED azul ao começar a captura
    while (index < 4) {
        char key = scan_keypad();
        if (key != '\0' && key >= '0' && key <= '9') {
            password[index++] = key;
            gpio_put(LED_PIN2, 1);  // Acende o LED vermelho para mostrar atividade (digitando)
            sleep_ms(100);
            gpio_put(LED_PIN2, 0);  // Desliga o LED vermelho
        }
        sleep_ms(100);
    }
    password[4] = '\0'; // Finaliza a string
    gpio_put(LED_PIN1, 0); // Apaga o LED azul após a captura da senha
}

// Função para verificar a senha digitada
void verifica_senha() {
    int index = 0;
    gpio_put(LED_PIN1, 1);  // Acende o LED azul ao começar a verificação
    while (index < 4) {
        char key = scan_keypad();
        if (key != '\0' && key >= '0' && key <= '9') {
            entered_senha[index++] = key;
            // Não acende LEDs aqui, apenas coleta os dados
        }
        sleep_ms(100);
    }
    entered_senha[4] = '\0'; // Finaliza a string
    gpio_put(LED_PIN1, 0);   // Apaga o LED azul após a verificação

    // Verifica se as senhas são iguais
    if (strcmp(set_senha, entered_senha) == 0) {
        gpio_put(LED_PIN3, 1);  // Acende o LED verde para senha correta
        sleep_ms(2000);         // Aguarda 2 segundos
        gpio_put(LED_PIN3, 0);  // Apaga o LED verde
    } else {
        gpio_put(LED_PIN2, 1);  // Acende o LED vermelho para senha errada
        gpio_put(BUZZER_PIN, 1);  // Aciona o buzzer para senha incorreta
        sleep_ms(2000);           // Aguarda 2 segundos
        gpio_put(LED_PIN2, 0);  // Apaga o LED vermelho
        gpio_put(BUZZER_PIN, 0);  // Desliga o buzzer
    }
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

    // Limpa as variáveis de senha antes de capturar uma nova
    memset(set_senha, 0, sizeof(set_senha));
    memset(entered_senha, 0, sizeof(entered_senha));

    // Captura a senha
    printf("Defina sua senha (4 dígitos):\n");
    captura_senha(set_senha); // Captura a senha do usuário

    // Aguardar um momento antes de tentar a senha
    sleep_ms(2000);  // Espera 2 segundos

    // Tentativa de verificação da senha
    printf("Digite sua senha para verificação:\n");
    verifica_senha();  // Chama a função de verificação

    return 0;
}