**Breve descrição**

Este projeto tem por objetivo controlar a operação de uma matriz de LEDs RGB do tipo WS2812B e buzzers por meio da placa Raspberry Pi Pico W e do Wokwi integrado ao VS Code. A matriz de LEDs contém 5 linhas e cinco colunas, com conexões e posicionamento iguais aos verificados na placa de desenvolvimento BitDogLab. Um buzzer está conectado no GPIO 10 e o outro, no 21. Para controlar os LEDs e buzzers, o microcontrolador tem como entradas digitais as teclas de um teclado matricial com as teclas referentes aos dígitos decimais, as letras maiúsculas de A até D, o caractere hash sign e o caractere asterisc.


**Instruções de uso**

A tecla A desliga todos os LEDs.
A tecla B liga todos os LEDs na cor azul com 100% de intensidade.
A tecla C liga todos os LEDs na cor vermelha com 80% de intensidade.
A tecla D liga todos os LEDs na cor verde com 50% de intensidade.
A tecla # liga todos os LEDs na cor branca com 20% de intensidade.
A tecla * faz a Raspberry Pi Pico W sair do modo de execução e habilitar o modo de gravação via software (reboot).
Cada uma das teclas de 0 a 2 faz a matriz de LEDs exibir uma animação diferente. Como esta tarefa foi realizada por somente 3 alunos, foram implementadas somente 3 animações!

Se for usada a placa BitDogLab, ao invés do Wokwi, a animação selecionada pelo caractere '2' pode ser complementada com um sinal sonoro emitido pelos buzzers. Neste caso, o teclado do computador deve ser utilizado. Para isso, somente o arquivo tarefaTecladoLdes.c deve ser alterado nas linhas 101, 115 e 120, de acordo com os comentários adicionados nestas respectivas linhas. Esta solução foi testada porque o core1 precisou ser usado para gerar o sinal de áudio, já que tanto animações, quanto sinais sonoros são produzidos com o auxílio de diferentes delays e a animação mencionada deve ser exibida em sincronismo com o referido sinal sonoro.

Vídeos: https://youtu.be/0t8WhFfryZk    https://youtu.be/WCT3at54Fpc

No primeiro vídeo foi utilizado o Wokwi e no segundo foi utilizada a BitDogLab.