# Uso de Matriz de Leds 5X5 e player de música via buzzer

Este projeto implementa uma exibição interativa em uma matriz de LED 5x5 com acompanhamento musical usando o Raspberry Pi Pico. O display apresenta uma sequência de animações que incluem letras formando a palavra "LOVE", um coração pulsante, uma bandeira arco-íris e efeitos de onda colorida, tudo sincronizado com uma melodia reproduzida através de um buzzer.

## Características

- Matriz de LED WS2818B 5x5 (25 LEDs)
- Reprodução de música através de buzzer
- Múltiplas animações:
  - Exibição sequencial das letras "LOVE"
  - Coração pulsante com efeito de fade
  - Bandeira arco-íris com transição suave
  - Padrão de onda colorida
- Execução multicore para música simultânea

## Hardware Necessário

- Raspberry Pi Pico
- Matriz de LED WS2818B 5x5
- Buzzer
- Cabos de conexão

## Pinagem

- LED Data: GPIO 7
- Buzzer: GPIO 21

## Dependências

- pico-sdk
- hardware/pio
- hardware/pwm
- pico/multicore

## Instalação

1. Configure o ambiente de desenvolvimento do Raspberry Pi Pico
2. Clone este repositório
3. Compile o projeto usando CMAKE
4. Faça o upload do binário para o Raspberry Pi Pico

## Estrutura do Código

O projeto está organizado nas seguintes funções principais:

- `npInit()`: Inicializa a matriz de LED
- `tocar_musica()`: Controla a reprodução da melodia
- `desenharLetras()`: Exibe a sequência "LOVE"
- `desenharCoracao()`: Anima o coração pulsante
- `desenharBandeira()`: Mostra a bandeira arco-íris
- `desenharOnda()`: Cria efeito de onda colorida
- `animar()`: Coordena todas as animações
- `music_thread()`: Thread separada para reprodução da música