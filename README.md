# Código ESP32 - Trabalho 2 2022-1

Código da ESP32 integrado ao ThingsBoard para rodar o Trabalho 1 de 2022-1 - Controle de Semáforos


**Disciplina**: FGA0109	- FUNDAMENTOS DE SISTEMAS EMBARCADOS <br>


## Alunos

| Matrícula  | Aluno                          |
| ---------- | ------------------------------ |
| 17/0103200 | Gabriel Alves Hussein          |
| 17/0031438 | Dâmaso Júnio Pereira Brasíleo  |

## Sobre

Consiste na implementação de sensores e atuadores distribuídos baseados na ESP32. A ESP32 está integrada ao Thingsboard e utilizará widgets em um dashboard para acompanhamento das leituras de temperatura e umidades feitas, assim como controle de intensidade do LED. As leituras de temperatura e umidade são realizadas com a inscrição em tópicos via RPC e receberá dados em formato JSON com a temperatura e umidade percebidas pelo sensor, há no total dois tópicos de envio de dados, são eles:

- Temperatura: `v1/devices/me/telemetry`
- Umidade: `v1/devices/me/attributes`

Ao total da implementação temos os seguintes componentes implementados:

- Conexão da placa Wifi via MQTT 
- Leitura de temperature e umidade via sensor DHT11
- LED de controle de intensidade via Thingsboard
- Buzzer 5V para emitir sinais sonoros

## Instalação

**Linguagens**: C<br>

## Execução

Após as instalações necessárias para rodar o projeto execute os seguintes comandos:

## Uso

Ao executar o programa é necessário acessar o Dashboard "Damaso-Gabriel" no Thingsboard e utilizar o widget de intensidade de temperatura, além de acompanhar as leituras de temperatura/umidade.

## Vídeo
Um vídeo foi gravado explicando o funcionamento do código assim como demonstrando o uso do dashboard.

[![Vídeo do projeto](https://img.youtube.com/vi/c8242sJxnDo/3.jpg)](https://www.youtube.com/watch?v=c8242sJxnDo)
