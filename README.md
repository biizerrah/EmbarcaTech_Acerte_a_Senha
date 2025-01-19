# Projeto Acerte a Senha

## EmbarcaTech – Subgrupo 2 (Grupo 07)

### ATIVIDADE COLABORATIVA - Controle de pinos GPIO com o emprego de um teclado matricial

#### O projeto desenvolvido pelo grupo teve como objetivo criar um sistema de senha utilizando um teclado matricial 4x4, LEDs e um buzzer, simulados no ambiente Wokwi com o microcontrolador Raspberry Pi Pico W. Para realizar a atividade, a equipe se organizou dividindo tarefas de acordo com as preferências de cada integrante, utilizando o GitHub como ferramenta de gerenciamento e colaboração.
#### O funcionamento do sistema foi estruturado da seguinte forma: o teclado matricial 4x4 foi configurado para permitir a entrada de uma senha de 4 dígitos. Durante o processo de digitação, o LED azul permanece aceso, indicando que o sistema está pronto para capturar a senha. A cada número registrado, o LED vermelho pisca rapidamente, fornecendo feedback ao usuário. Quando os 4 dígitos forem preenchidos, o sistema realizará a comparação entre a senha digitada e uma senha previamente armazenada.
#### Caso a senha estiver correta, o LED verde acenderá, sinalizando que a validação foi bem-sucedida. Por outro lado, se a senha estiver incorreta, o LED vermelho acenderá e o buzzer emitirá um som, alertando o usuário sobre o erro e verificações constantes de entrada de dados sinalizadas através do LED vermelho.

### Requisitos para funcionamento da simulação no VScode:

## Instalação de Pré-requisitos

Para configurar o ambiente de desenvolvimento, siga as instruções abaixo:

### 1. Instalar o Visual Studio Code
- Acesse o site oficial e faça o download: [Visual Studio Code](https://code.visualstudio.com/).
- Instale o programa e configure conforme necessário.

### 2. Instalar o CMake
- Baixe o instalador do CMake: [CMake](https://cmake.org/download/).
- Durante a instalação, marque a opção **"Add CMake to the system PATH"**.
- Conclua a instalação.

### 3. Instalar o GCC para ARM
- Baixe o compilador ARM GNU em: [GCC ARM Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm).
- Após a instalação, adicione o diretório do executável ao **PATH**:
  - Vá para **Configurações do Sistema > Variáveis de Ambiente**.
  - Edite a variável `Path` e adicione:
    ```
    C:\Program Files (x86)\Arm GNU Toolchain\<versão>\bin
    ```
  - Substitua `<versão>` pela versão instalada.

### 4. Instalar o Git
- Faça o download: [Git para Windows](https://git-scm.com/).
- Instale o programa e configure-o.
- Abra o terminal (Git Bash ou CMD) e configure seu nome e e-mail:
  ```bash
  git config --global user.name "Seu Nome"
  git config --global user.email "seu.email@exemplo.com"

Aqui está [a apresentação](https://www.youtube.com/watch?v=ivlpjV28Tj8) em forma de vídeo do funcionamento do projeto.

