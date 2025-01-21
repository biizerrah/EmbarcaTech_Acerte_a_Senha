#define CATCH_CONFIG_MAIN // Define a função principal para o Catch2
#include "catch.hpp"
#include "pico/stdlib.h"
#include "../Acerteasenha.c" // Incluir o arquivo com o código a ser testado

// Teste para a função setup_gpio
TEST_CASE("GPIO setup configura os pinos corretamente", "[gpio]") {
    setup_gpio();
    REQUIRE(gpio_is_enabled(10) == true); // Verifica se o GPIO do LED vermelho está configurado
    REQUIRE(gpio_is_enabled(11) == true); // Verifica se o GPIO do LED verde está configurado
    REQUIRE(gpio_is_enabled(12) == true); // Verifica se o GPIO do LED azul está configurado
}

// Teste para a função control_led
TEST_CASE("control_led altera os estados dos LEDs corretamente", "[led]") {
    control_led(1, 0, 0); // Liga o LED vermelho
    REQUIRE(gpio_get(10) == 1); // LED vermelho ligado
    REQUIRE(gpio_get(11) == 0); // LED verde desligado
    REQUIRE(gpio_get(12) == 0); // LED azul desligado

    control_led(0, 1, 1); // Liga os LEDs verde e azul
    REQUIRE(gpio_get(10) == 0); // LED vermelho desligado
    REQUIRE(gpio_get(11) == 1); // LED verde ligado
    REQUIRE(gpio_get(12) == 1); // LED azul ligado
}

// Teste para a função control_buzzer
TEST_CASE("control_buzzer liga e desliga o buzzer", "[buzzer]") {
    control_buzzer(true); // Liga o buzzer
    REQUIRE(gpio_get(13) == 1); // Buzzer ligado

    control_buzzer(false); // Desliga o buzzer
    REQUIRE(gpio_get(13) == 0); // Buzzer desligado
}
