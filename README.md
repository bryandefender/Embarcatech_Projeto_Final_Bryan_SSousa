# SISTEMA DE MONITORAMENTO DE TEMPERATURA E UMIDADE COM IRRIGAÇÃO VIA GOTEJAMENTO.

### 1. Introdução

A automação tem crescido de maneira demasiada nos últimos anos,
principalmente com o advento da Internet das Coisas(IoT). Um dos setores
influenciados é a automação residencial, diversos sensores e atuadores são
utilizados nesse processo, como motores de passo, servo motores, sensores de
umidade/temperatura, e variados protocolos de comunicação sem fio.
Este trabalho apresenta o desenvolvimento do projeto de sistema de
monitoramento e irrigação para plantas domésticas, utilizando sensor de
temperatura e umidade DHT11 e um atuador servo motor SG90.

### 2. Objetivos

O objetivo desse projeto é desenvolver um Sistema de Monitoramento de
Temperatura e Umidade com Irrigação via Gotejamento utilizando um
Raspberry Pi Pico W no qual tem como microcontrolador o RP2040 com
algoritmo embarcado em linguagem C. E no futuro implementar o
monitoramento do funcionamento do sistema via internet.

### 3. Justificativa

Tendo em vista a crescente demanda no setor de automação residencial, o uso desses sistemas é indispensável. O sistema de irrigação e aferição de temperatura e umidade pode suprir a necessidade de irrigar o jardim, caso o usuário fique ausente por muito tempo.

O Raspberry pi pico W com microcontrolador RP2040 unido aos outros componentes, como; DHT11, servo motor, entre outros, é uma plataforma acessível em sua implementação e de baixo custo, demonstrando ser muito versátil e ainda permitir a possibilidade de ser expandida para um sistema mais robusto e podendo ser conectado à dispositivos sem fio e protocolos de comunicação diversos.

### 4. Fluxograma

<img src="https://github.com/bryandefender/Embarcatech_Projeto_Final_Bryan_SSousa/blob/main/imagens_projeto_final/1_Fluxograma_Transparente.png">

### 5. Código

Link do código no Wokwi: [Projeto Final ](https://wokwi.com/projects/422375763892697089)

### 6. Esquemático

<img src="https://github.com/bryandefender/Embarcatech_Projeto_Final_Bryan_SSousa/blob/main/imagens_projeto_final/2_Esquem%C3%A1tico.png">

Descrição imagem 1:

Condutor azul -> Sinal do DHT11 para o pino GP09.
Condutor laranja/amarelo -> Sinal para o servo motor, pino GP22.
Condutor verde + Botão preto -> Utilizado para RESET, pino RUN.
LED verde -> Mostra que a placa está ligada, desliga quando o RESET é pressionado.
Observação¹: Todos os pinos GPIO suportam PWM
Observação²: O Botão RESET foi configurado para evitar desplugar o cabo USB para executar o BOOTSEL.

### 7.Estrutura Física do Sistema

Imagem 2 - Estrutura física do sistema
<img src="https://github.com/bryandefender/Embarcatech_Projeto_Final_Bryan_SSousa/blob/main/imagens_projeto_final/3_Estrutura_F%C3%ADsica.jpg">


Imagem 2.1 - Estrutura física conexões
<img src="https://github.com/bryandefender/Embarcatech_Projeto_Final_Bryan_SSousa/blob/main/imagens_projeto_final/4_Estrutura_F%C3%ADsica_%C3%81erea.jpg">

### 8. Materiais utilizados

	- Raspberry pi pico W com WIFI- (RP2040)
	- Sensor Umidade/Temperatura DHT11
	- Servo Motor - SG90
	- Breadboard(Protoboard)
	- Push button + LED para RESET
	- Condutores AWG22 rígidos e maleáveis 
	- Resistor de 10 Kohm para DHT11
	- Adaptador USB para alimentar o Servo Motor: 5 VCC

### 9. Resultados

Video no youtube mostrando o funcionamento do projeto: [Vídeo](https://youtu.be/4W-uVQUyRb8 )

Como mostrado no vídeo o objetivo principal do projeto foi alcançado, o sensor de temperatura e umidade DHT11 monitora a cada dois segundos a umidade e temperatura e quando a temperatura passa de um valor específico, 31ºC no exemplo do vídeo, o servo motor SG90 abre o orifício de vazão de água. Porém é necessário fazer algumas melhorias no código, como:

Organizar a implementação das funcionalidades do DH11 e do servo motor em bibliotecas separadas.

Implementações futuras podem ser feitas, como criar um servidor para receber os dados em tempo real via protocolo Wifi, também usando o protocolo MQTT, entre outros.

### 10. Referências

BITDOGLAB. Repositório. 2025. Disponível em: https://github.com/BitDogLab. Acesso em: 2025.

