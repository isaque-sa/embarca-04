**Breve descrição**

Este projeto tem por objetivo controlar a operação de uma matriz de LEDs RGB do tipo WS2812B e buzzers por meio da placa Raspberry Pi Pico W e do Wokwi integrado ao VS Code. A matriz de LEDs contém 5 linhas e cinco colunas, com conexões e posicionamento iguais aos verificados na placa de desenvolvimento BitDogLab. Um buzzer está conectado no GPIO 10 e o outro, no 21. Para controlar os LEDs e buzzers, o microcontrolador tem como entradas digitais as teclas de um teclado matricial com as teclas referentes aos dígitos decimais, as letras maiúsculas de A até D, o caractere hash sign e o caractere asterisc.


**Instruções de uso**

A tecla A desliga todos os LEDs e buzzers.
A tecla B liga todos os LEDs na cor azul com 100% de intensidade
A tecla C liga todos os LEDs na cor vermelha com 80% de intensidade.
A tecla D liga todos os LEDs na cor verde com 50% de intensidade.
A tecla # liga todos os LEDs na cor branca com 20% de intensidade.
A tecla * faz a Raspberry Pi Pico W sair do modo de execução e habilitar o modo de gravação via software (reboot).
Cada uma das teclas de 0 a 9 faz a matriz de LEDs exibir uma animação diferente. Algumas destas animações é complementada com sinal sonoro pelos buzzers.

Vídeo:
