# **gsEDGE - Sistema de Economia de Energia com Arduino**  

## **Sobre**  
O projeto **gsEDGE** foi desenvolvido para criar um sistema de economia de energia eficiente, ideal para ambientes com baixo fluxo de pessoas, como garagens. O sistema utiliza sensores para detectar movimento e distância, acendendo a iluminação apenas quando necessário, e também permite programar horários para ligar e apagar outra lâmpada, otimizando o consumo energético.  

### **Integrantes:**
-Kauã Rodrigues
-Felipe Santos 
-Gustavo Naoto 

### **Repositorio github**
- https://github.com/kauarodrigues1/gsEDGE
- 
### **Simulador no wokwi**
- https://wokwi.com/projects/415188382719653889

## **Tecnologias utilizadas**  

### **Hardware**  
- **Arduino**  
- 1 Placa de ensaio  
- 2 Resistores  
- 1 LED Verde (indicador do sensor de proximidade)  
- 1 LED Amarelo (indicador da luz programável)  
- 1 Sensor de Distância Ultrassônico  
- 1 RTC (Real Time Clock)  
- 1 LCD I2C  
- 16 Cabos jumpers macho para macho  
- 1 Cabo USB Tipo A para Tipo B  

### **Software**  
- Arduino IDE  
- Wokwi  

## **Instalação**  
1. Baixe e instale o **Arduino IDE**.  
2. Copie o código do projeto no **Wokwi**.  
3. Cole o código na **IDE do Arduino**.  
4. Certifique-se de que as bibliotecas necessárias estão instaladas.  
5. Conecte seu Arduino ao computador.  
6. Selecione a placa correta em **Ferramentas > Placa** (por exemplo, Arduino Uno).  
7. Selecione a porta correta em **Ferramentas > Porta**.  
8. Carregue o código no Arduino clicando no botão **"Upload"**.  

## **Utilização**  
1. Instale o sistema no ambiente que deseja monitorar.  
2. Conecte o sistema à energia via USB.  
3. A tela LCD exibirá informações do sistema, como horário, distância detectada e status das lâmpadas.  
4. O sistema funciona da seguinte forma:  
   - **Sensor Ultrassônico:**  
     - Detecta a presença de objetos ou pessoas no ambiente com base na distância.  
     - Liga o **LED Verde** e a iluminação automaticamente ao detectar movimento dentro do alcance programado, apagando após determinado tempo de inatividade.  
   - **Programação de Lâmpada Secundária:**  
     - O RTC permite configurar horários específicos para ligar e apagar outra lâmpada.  
     - O status da lâmpada programada é indicado pelo **LED Amarelo**.  
