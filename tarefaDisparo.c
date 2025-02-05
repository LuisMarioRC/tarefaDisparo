#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Estrutura para os pinos e configurações
typedef struct {
    uint blue;
    uint red;
    uint green;
    uint button;
    uint time;
} Config;

// Definição dos pinos globais
static Config config = {
    .blue = 11,   // LED RGB - Blue
    .red = 12,    // LED RGB - Red
    .green = 13,  // LED RGB - Green
    .button = 5,  // Botão A
    .time = 3000  // Tempo em milissegundos (3 segundos)
};

// Estados dos LEDs
typedef enum {
    ALL_OFF,
    ALL_ON,
    TWO_ON,
    ONE_ON
} LedState;

static LedState current_state = ALL_OFF;
static bool sequence_active = false;
static absolute_time_t last_button_press;

// Protótipos de funções
void inicializarHardware(Config* cfg);
bool timer_callback(struct repeating_timer* t);
void button_callback(uint gpio, uint32_t events);

// Inicializa os pinos GPIO
void inicializarHardware(Config* cfg) {
    // Configuração dos LEDs
    gpio_init(cfg->blue);
    gpio_set_dir(cfg->blue, GPIO_OUT);
    gpio_put(cfg->blue, 0);

    gpio_init(cfg->red);
    gpio_set_dir(cfg->red, GPIO_OUT);
    gpio_put(cfg->red, 0);

    gpio_init(cfg->green);
    gpio_set_dir(cfg->green, GPIO_OUT);
    gpio_put(cfg->green, 0);

    // Configuração do botão
    gpio_init(cfg->button);
    gpio_set_dir(cfg->button, GPIO_IN);
    gpio_pull_up(cfg->button);  // Mudado para pull-up
}

// Função para atualizar os LEDs
void update_leds(LedState state) {
    switch (state) {
        case ALL_ON:
            gpio_put(config.blue, 1);
            gpio_put(config.red, 1);
            gpio_put(config.green, 1);
            break;
        case TWO_ON:
            gpio_put(config.blue, 0);
            gpio_put(config.red, 1);
            gpio_put(config.green, 1);
            break;
        case ONE_ON:
            gpio_put(config.blue, 0);
            gpio_put(config.red, 0);
            gpio_put(config.green, 1);
            break;
        case ALL_OFF:
            gpio_put(config.blue, 0);
            gpio_put(config.red, 0);
            gpio_put(config.green, 0);
            break;
    }
}

// Função de callback para o temporizador
bool timer_callback(struct repeating_timer* t) {
    if (!sequence_active) return true;

    switch (current_state) {
        case ALL_ON:
            current_state = TWO_ON;
            break;
        case TWO_ON:
            current_state = ONE_ON;
            break;
        case ONE_ON:
            current_state = ALL_OFF;
            sequence_active = false;
            break;
        case ALL_OFF:
            // Não deve ocorrer
            break;
    }

    update_leds(current_state);
    return true;
}

// Função de callback para o botão
void button_callback(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time();
    
    // Debounce simples de 200ms
    if (absolute_time_diff_us(last_button_press, now) < 200000) {
        return;
    }
    last_button_press = now;

    // Só inicia nova sequência se não houver uma em andamento
    if (!sequence_active && current_state == ALL_OFF) {
        sequence_active = true;
        current_state = ALL_ON;
        update_leds(ALL_ON);
    }
}

int main() {
    stdio_init_all();
    inicializarHardware(&config);

    // Inicializa o timestamp do último pressionamento do botão
    last_button_press = get_absolute_time();

    // Configura a interrupção do botão
    gpio_set_irq_enabled_with_callback(config.button, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    // Configura o temporizador com intervalo de 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(config.time, timer_callback, NULL, &timer);

    // Loop principal
    while (true) {
        tight_loop_contents();
    }
}