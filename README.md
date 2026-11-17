# Reprodutor de Músicas com Arduino

Projeto da disciplina CCP020 - Digital Experience Ultimate (FEI)

**Alunos:**
- Enzo Ginez Souza - 22.126.043-3
- Felipe Hernandes Giroldo - 22.126.034-2
- João Pedro Miguel Bezerra - 22.126.026-8

---
## LINK GITHUB:
https://github.com/joaopmbz/Projeto_Digital
## Introdução

A proposta do projeto era montar um reprodutor de músicas com Arduino, parecido com um MP3 player bem simples. O usuário escolhe a música num menu que aparece no display LCD, usando os botões de cima e de baixo, e depois pode dar play, pausar e parar. Dois LEDs mostram o estado: o verde acende quando a música está tocando e o vermelho quando está pausada. O som sai por um buzzer.

Achamos o tema legal porque junta quase tudo que a gente viu nas aulas de Arduino: entradas digitais com botão, saídas com LED, o `tone()` do buzzer e o display. No começo parecia simples, mas na hora de juntar tudo apareceram bastante problemas, principalmente na montagem do display e na parte de pausar a música no meio.

## Metodologia e materiais

### Materiais usados

- 1 Arduino UNO
- 1 display LCD 16x2 com módulo I2C (chip PCF8574)
- 4 botões (UP, DOWN, PLAY/PAUSE e STOP)
- 1 LED verde e 1 LED vermelho
- 2 resistores de 220 Ω (um para cada LED)
- 1 buzzer
- 1 protoboard
- Jumpers (macho-macho e macho-fêmea para o LCD)
- Cabo USB

### Ligações

Os botões UP, DOWN, PLAY/PAUSE e STOP ficaram nos pinos 7, 6, 5 e 4. O buzzer está no pino 8, o LED verde no 9 e o vermelho no 10. O LCD usa só quatro fios por causa do módulo I2C: SDA no A4, SCL no A5, e o VCC e o GND no 5V e no GND do Arduino.

Os botões estão ligados entre o pino e o GND, sem resistor externo. No código usamos `INPUT_PULLUP`, então o botão solto lê `HIGH` e apertado lê `LOW`. Os LEDs têm o resistor de 220 Ω em série para não queimar.

### Como foi feito

Primeiro montamos o circuito no Tinkercad para testar sem risco de estragar nada. Depois passamos para o Arduino de verdade.

O código foi feito em etapas, e cada etapa virou um commit aqui no repositório:

1. Mostrar o menu com o nome das músicas no LCD
2. Fazer os botões UP e DOWN mudarem a música selecionada
3. Colocar as músicas para tocar no buzzer
4. Fazer o pause e o stop funcionarem
5. Colocar um bonequinho dançando no display enquanto a música toca

As músicas ficam guardadas em duas matrizes: uma com a frequência de cada nota (em Hz) e outra com o tempo de cada nota em milissegundos. Cada linha é uma música, e quando o tempo é 0 significa que a música acabou. As músicas escolhidas foram Tetris (que na verdade é uma música folclórica russa chamada Korobeiniki), No Salão do Rei da Montanha (Grieg), Pour Elise (Beethoven), Marcha Turca (Mozart) e Can-can (Offenbach).

A parte que deu mais trabalho foi o pause. Se a gente usasse só `delay()` com o tempo da nota, o Arduino ficava "travado" esperando e não percebia o botão sendo apertado. A solução foi esperar o tempo da nota de 10 em 10 milissegundos e, a cada volta, ver se o PLAY ou o STOP foram apertados. Assim dá para pausar ou parar a qualquer momento.

O bonequinho dançando foi feito com o `createChar` do LCD, que deixa criar desenhos de 5x8 pixels. Fizemos dois desenhos (braços pra cima e braços abertos) e o código troca entre eles a cada nota.

## Experimentos

### Simulação no Tinkercad

<img width="700" alt="Circuito no Tinkercad" src="https://github.com/user-attachments/assets/7e6fe7b9-78fd-474b-a64b-69b2f9bb3892" />

Antes de montar no Arduino de verdade, simulamos o circuito inteiro no Tinkercad. Fomos testando cada parte separada (primeiro só o LCD, depois os botões, depois os LEDs e o buzzer) e só no final juntamos tudo no código completo.

### Montagem física

<img width="400" alt="Montagem física" src="https://github.com/user-attachments/assets/74bfbe20-c62e-4582-8c86-d078f9cf97bb" />

Na montagem de verdade o display também não acendeu na primeira vez. O problema era a cor dos fios: no módulo I2C o VCC estava no fio verde e a gente tinha ligado o vermelho no 5V achando que era o positivo. Depois de conferir os nomes escritos no módulo (GND, VCC, SDA, SCL) e religar, funcionou.

Na IDE do Arduino também tivemos uns erros simples, tipo esquecer de selecionar a placa (erro de "Missing FQBN") e colar o código em cima do exemplo que a IDE já cria, o que deixava uma chave `}` sobrando.

### Vídeo

[Vídeo do projeto funcionando](https://youtube.com/shorts/Ag2AFL_kje8)

## Tecnologias

- **Arduino UNO** e **Arduino IDE 2**
- **Linguagem C/C++** do Arduino
- **Tinkercad** para simular o circuito antes de montar
- **Biblioteca LiquidCrystal_I2C** para o display
- **Git e GitHub** para guardar as versões do código

Funções do Arduino usadas: `pinMode`, `digitalRead`, `digitalWrite`, `tone`, `noTone`, `delay`, e do LCD: `init`, `backlight`, `clear`, `setCursor`, `print`, `createChar` e `write`.

## Conclusão

O projeto funcionou como pedido: dá para escolher entre as 5 músicas no menu, tocar, pausar, continuar e parar, e os LEDs mostram o que está acontecendo.

O que mais aprendemos foi que montar o circuito errado dá tanto trabalho quanto errar no código. Vários problemas que pareciam ser do programa na verdade eram um fio no lugar errado. Testar cada parte separada antes de juntar tudo ajudou muito a achar onde estava o erro. Também entendemos melhor por que o `delay()` atrapalha quando o programa precisa ficar lendo botões ao mesmo tempo.

Uma melhoria que daria para fazer depois seria guardar músicas maiores usando a memória flash (`PROGMEM`), porque a memória RAM do UNO é pequena, ou trocar o buzzer por um alto-falante para o som ficar melhor.
