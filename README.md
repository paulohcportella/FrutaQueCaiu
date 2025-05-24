
# 🎮 Fruta que Caiu

Um jogo casual feito em C, jogável diretamente no terminal. O objetivo é mover a cesta para capturar frutas que caem do topo da tela. Cada fruta tem uma pontuação específica. O jogador deve tentar obter a maior pontuação possível dentro de 60 segundos!

---

## 👥 Alunos

- **Paulo Portella** – phcp@cesar.school  
- **João Antônio Sampaio** – jasf@cesar.school  
- **Juliana Van Der Linden** – jvdlm@cesar.school

---

## 🧩 Objetivo

Desenvolver um jogo casual interativo em linha de comando utilizando os conceitos aprendidos na disciplina de **Programação Imperativa e Funcional**, como:

- Uso de `structs` e ponteiros  
- Alocação dinâmica de memória  
- Listas encadeadas  
- Leitura e escrita de arquivos  
- Manipulação de matriz (posição de tela)  
- Timer, teclado e tela com a biblioteca `cli-lib`

---


## 🚀 Como Rodar o Jogo

### 1. Pré-requisitos

Certifique-se de ter:

- O compilador `gcc` instalado
- A biblioteca `ncurses` instalada

#### Instalação no Linux (Ubuntu/Debian):
```bash
sudo apt update
sudo apt install build-essential libncurses5-dev libncursesw5-dev
```

#### Instalação no macOS (com Homebrew):
```bash
brew install ncurses
```

---

### 2. Compile o jogo

Abra o terminal dentro da pasta do projeto e rode:

```bash
make
```

---

### 3. Execute o jogo

Depois de compilar, execute o jogo com:

```bash
make run
```

---

### 4. Controles do jogo

- `←` seta para esquerda: move a cesta para a esquerda  
- `→` seta para direita: move a cesta para a direita  
- `ENTER`: encerra a partida

---

## 🏆 Leaderboard

Ao final de cada partida, sua pontuação é salva automaticamente no arquivo:

```
leaderboard.txt
```

Para ver o **Top Score**, selecione a opção **2** no menu principal.

---

## 🧪 Observações

- O uso de **emojis** (🍎🍌🍇) pode causar sobreposição ou erros de alinhamento em terminais antigos.
- Recomendado utilizar:
  - **Terminal.app (macOS)**
  - **Ubuntu Terminal moderno**

---

## 👨‍🏫 Professores

- **Tiago Barros** – tgfb@cesar.school  
- **Pamela Bezerra** – ptlb@cesar.school

## Video do Jogo

https://github.com/user-attachments/assets/0083e26f-b25b-48f1-95b6-0515c78d7f68

