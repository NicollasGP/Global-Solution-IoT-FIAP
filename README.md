# 💧 HidroSafe – Monitoramento de Nível da Água com IoT

Sistema IoT de monitoramento em tempo real de níveis de água para prevenção de enchentes, utilizando sensores ultrassônicos, ESP32, protocolo MQTT e dashboard no Node-RED.

---

## 👥 Integrantes

* Guilherme Guimarães - RM 557074 / 2TDSA
* Nicollas Guedes Pontes - RM 556850 / 2TDSB
* Matheus Oliveira de Luna - RM 555547 / 2TDSA

---

## 🔍 Visão Geral

O projeto **HidroSafe** simula uma solução de monitoramento para áreas de risco de alagamento. Por meio de sensores conectados a um ESP32 e utilizando o protocolo MQTT, o sistema envia os dados coletados em tempo real para o Node-RED, que processa, interpreta e exibe essas informações em um painel visual.

A proposta atende aos critérios da disciplina **Disruptive Architectures: IoT, IOB & Generative IA**, integrando sensores, atuadores, conectividade, gateway, protocolo padrão e um dashboard funcional.

---

## 🛠️ Tecnologias Utilizadas

* **ESP32** (simulado no Wokwi)
* **Sensor ultrassônico HC-SR04**
* **LEDs e buzzer**
* **Protocolo MQTT** (HiveMQ broker)
* **Node-RED**
* **Node-RED Dashboard**
* **JSON para troca de mensagens**

---

## 🌐 Projeto no Wokwi

🔗 Acesse a simulação: [https://wokwi.com/projects/432668574653513729](https://wokwi.com/projects/432668574653513729)

---

## 🔧 Node-RED

* ⚠️ É necessário instalar o pacote `node-red-dashboard` no Node-RED.
* 📂 O fluxo do Node-RED está disponível na pasta `node-red`.
* 📊 Acesse o dashboard localmente via: [http://localhost:1880/ui](http://localhost:1880/ui)

---

## 🎥 Vídeo

📺 Assista ao vídeo pitch da solução:
🔗 *https://youtu.be/rJZaIE5rJwk?si=2y5ZPMIrLTlTHyLi*

---

## 📁 Estrutura do Projeto

```
📂 codigo-fonte-wokwi/       → Código da simulação IoT no Wokwi
📂 node-red/                 → Fluxo exportado do Node-RED (.json)
📂 dashboard/                → Link da interface do painel
📂 descritivo-solucao/       → PDF com a descrição completa da solução
📄 README.md                 → Este arquivo
```

---

## ▶️ Como Executar

1. Instale o Node-RED em sua máquina.
2. Instale o pacote `node-red-dashboard`:
3. Acesse o editor do Node-RED em `http://localhost:1880/`.
4. Importe o fluxo JSON disponível na pasta `node-red/`.
5. Inicie o Node-RED e acesse o painel em: [http://localhost:1880/ui](http://localhost:1880/ui)
6. Para simular o dispositivo, abra o projeto no Wokwi:
   🔗 [https://wokwi.com/projects/432668574653513729](https://wokwi.com/projects/432668574653513729)
