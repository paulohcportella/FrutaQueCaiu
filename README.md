# 🎮 Fruta que Caiu

Um jogo casual feito em C, jogável diretamente no terminal. O objetivo é mover a cesta para capturar frutas que caem do topo da tela. Cada fruta tem uma pontuação específica. O jogador deve tentar obter a maior pontuação possível dentro de 60 segundos!

Alunos:

- Paulo Portella (phcp@cesar.school)
- João Antônio Sampaio (jasf@cesar.school)
- Juliana Van Der Linden ()


## 🧩 Objetivo

Desenvolver um jogo interativo em linha de comando utilizando os conceitos aprendidos na disciplina de Programação Imperativa e Funcional:

- Uso de `structs` e ponteiros
- Alocação dinâmica de memória
- Listas encadeadas
- Leitura e escrita de arquivos
- Manipulação de matriz (tela)
- Timer, teclado e atualização gráfica com a biblioteca `cli-lib`


## 🚀 Como Rodar o Jogo

### 1. Clone ou baixe o projeto

Se estiver usando Git:
🔧 Como compilar o jogo
Abra o terminal e entre na pasta do projeto.

Execute:

Copiar
Editar
make
Se preferir fazer manualmente:

Copiar
Editar
gcc main.c cli-lib/screen.c cli-lib/keyboard.c cli-lib/timer.c -lncurses -o frutaquecaiu


▶️ Como rodar o jogo

No terminal, digite:

Copiar
Editar
./frutaquecaiu
Ou, se estiver usando o Makefile:

Copiar
Editar
make run

🎮 Como jogar
← seta para esquerda: move a cesta para a esquerda

→ seta para direita: move a cesta para a direita

ENTER: encerra a partida a qualquer momento

Pegue as frutas que caem e ganhe pontos

A partida dura 60 segundos

🏆 Leaderboard
Ao final de cada partida, sua pontuação é salva automaticamente no arquivo leaderboard.txt.

Você pode visualizar o Top Score no menu principal (opção 2).


🧪 Observação
O uso de emojis (como 🍌🍎) pode não funcionar bem em alguns terminais antigos.


👨‍🏫 Professores
Tiago Barros – tgfb@cesar.school

Pamela Bezerra – ptlb@cesar.school
