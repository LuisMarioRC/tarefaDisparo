# Controle de LED RGB com Temporizador - RP2040
## Tarefa: Controle de LEDs com Botão e Temporizador
### Descrição
Este repositório contém o código-fonte de um projeto desenvolvido em Linguagem C, utilizando o Pico SDK, para implementar uma sequência de LEDs controlada por botão em um microcontrolador Raspberry Pi Pico. O projeto foi testado no simulador **Wokwi** e utiliza um temporizador repetitivo (`repeating_timer`) para controlar a sequência de desligamento dos LEDs em intervalos regulares.

A solução implementa estratégias para:  
1. Controle dos LEDs RGB com sequência específica  
2. Acionamento por botão com tratamento de debounce  
3. Uso de temporizadores para intervalos definidos  
4. Gerenciamento de estados dos LEDs  

## Funcionalidades
1. **Sequência de LEDs**:
   - Ao pressionar o botão, todos os LEDs acendem simultaneamente  
   - Após 3 segundos, o LED azul apaga  
   - Após mais 3 segundos, o LED vermelho apaga  
   - Após mais 3 segundos, o LED verde apaga  
   - O ciclo só pode ser reiniciado quando todos os LEDs estiverem apagados  

2. **Controle por Botão**:
   - Implementação de debounce via software  
   - Botão bloqueado durante a execução da sequência  
   - Novo acionamento permitido apenas após sequência completa  

3. **Temporizador**:
   - Controle preciso de intervalos de 3 segundos entre estados  
   - Gerenciamento automático da sequência  
   - Temporizador repetitivo para transições suaves  

4. **Simulação no Wokwi**:
   - Testado e validado no simulador Wokwi  

## Pré-requisitos
1. **Hardware Necessário**:
   - Raspberry Pi Pico (RP2040)  
   - LED RGB  
   - Botão pushbutton  
   - Resistores apropriados  

2. **Ambiente de Desenvolvimento**:
   - Visual Studio Code ou outro editor compatível  
   - Pico SDK configurado  
   - Compilador GCC para C  
   - Ferramentas de gravação e execução no Raspberry Pi Pico  
   - Simulador Wokwi (https://wokwi.com) para testes virtuais  

## Como Usar
1. **Clone o repositório**:
    ```bash
    git clone https://github.com/LuisMarioRC/tarefaDisparo.git
    ```

2. **Navegue até o diretório do projeto**:
    ```bash
    cd tarefaDisparo
    ```

3. **Compile o código com o Pico SDK**:
   - Certifique-se de que o Pico SDK está configurado corretamente  
   - No terminal, execute:  
     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```

4. **Grave o programa no Raspberry Pi Pico**:
   - Conecte o Pico ao computador  
   - Segure o botão BOOTSEL enquanto conecta para entrar no modo de armazenamento USB  
   - Arraste o arquivo `.uf2` gerado na pasta `build` para o dispositivo  
 

5. **Execute o programa**:
   - Pressione o botão para iniciar a sequência  
   - Observe a sequência de desligamento dos LEDs  
   - Aguarde o ciclo completo para novo acionamento  

## Testes no Wokwi
Para testar o projeto no simulador Wokwi:
1. Crie um novo projeto para Raspberry Pi Pico
2. Configure os pinos conforme especificado no código
3. Copie o código-fonte para o simulador
4. Execute e teste o funcionamento

### Líder do Projeto
- <b><a href="https://github.com/LuisMarioRC">Luis Mario</a></b>