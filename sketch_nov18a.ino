#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// Definições para configuração de log e fuso horário
#define LOG_OPTION 1
#define SERIAL_OPTION 0
#define UTC_OFFSET -3 // Ajuste para o fuso horário UTC-3

// Configuração do display LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 RTC; // Objeto para comunicação com o RTC

// Variáveis de controle de tempo
unsigned long currentMillis;
unsigned long previousMillis = 0;
const long updateInterval = 5000; // Intervalo para atualização do display

unsigned long lastSlideshowUpdate = 0;
const long slideshowInterval = 5000; // Intervalo para mudança de modo de exibição
int displayMode = 0;

// Mensagens de alerta
String alertMessage;
String alertMessage2;

// Definição dos pinos
const int ledGreen = 8;    // LED verde para proximidade
const int ledGreen2 = 11;  // LED verde para horário programado
const int trigPin = 9;     // Pino Trigger do sensor ultrassônico
const int echoPin = 10;    // Pino Echo do sensor ultrassônico

void setup() {
    lcd.init();           // Inicializa o LCD
    lcd.backlight();      // Ativa a luz de fundo do LCD
    RTC.begin();          // Inicializa o RTC

    // Configura os pinos como entrada ou saída
    pinMode(ledGreen, OUTPUT);
    pinMode(ledGreen2, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);

    Serial.begin(9600);   // Inicializa a comunicação serial
}

void loop() {
    DateTime now = RTC.now(); // Obtém o horário atual do RTC
    long duracao, distancia;

    // Envia um pulso ultrassônico para medir distância
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duracao = pulseIn(echoPin, HIGH); // Mede o tempo do retorno do pulso
    distancia = duracao * 0.034 / 2;  // Calcula a distância em cm

    currentMillis = millis();
    if (currentMillis - lastSlideshowUpdate >= slideshowInterval) {
        lastSlideshowUpdate = currentMillis;
        displayMode = (displayMode + 1) % 1; // Alterna entre modos de exibição
    }

    // Ajusta o horário com o offset UTC
    DateTime adjustedTime = DateTime(now.unixtime() + UTC_OFFSET * 3600);

    lcd.clear();
    if (displayMode == 0) {
        // Exibe a data e a hora ajustadas no LCD
        lcd.setCursor(0, 0);
        lcd.print("DATA: ");
        lcd.print(adjustedTime.day() < 10 ? "0" : "");
        lcd.print(adjustedTime.day());
        lcd.print("/");
        lcd.print(adjustedTime.month() < 10 ? "0" : "");
        lcd.print(adjustedTime.month());
        lcd.print("/");
        lcd.print(adjustedTime.year());

        lcd.setCursor(0, 1);
        lcd.print("HORA: ");
        lcd.print(adjustedTime.hour() < 10 ? "0" : "");
        lcd.print(adjustedTime.hour());
        lcd.print(":");
        lcd.print(adjustedTime.minute() < 10 ? "0" : "");
        lcd.print(adjustedTime.minute());
        lcd.print(":");
        lcd.print(adjustedTime.second() < 10 ? "0" : "");
        lcd.print(adjustedTime.second());
    }

    // Exibe a distância no console serial
    Serial.print("Distância: ");
    Serial.print(distancia);
    Serial.println(" cm");

    // Exibe mensagens de alerta no LCD, se houver
    if (alertMessage.length() > 0) {
        lcd.clear();
        lcd.print(alertMessage);
        lcd.setCursor(0, 1);
        lcd.print(alertMessage2);
        delay(10000); // Mantém a mensagem na tela por 10 segundos
    }

    // Acende LED se a distância for menor que 30 cm
    if (distancia < 30) {
        digitalWrite(ledGreen, HIGH);
        alertMessage = "Lampada ligada";
        alertMessage2 = "por proximidade";
    } else {
        alertMessage = "";
        digitalWrite(ledGreen, LOW);
        Serial.println("Lampada desligada por falta proximidade");
    }

    // Liga ou desliga o LED no horário programado
    if (adjustedTime.hour() == 16 && adjustedTime.minute() == 11 && adjustedTime.second() == 0) {
        digitalWrite(ledGreen2, HIGH);
        alertMessage = "Lampada ligada";
        alertMessage2 = ":D";
    } else if (adjustedTime.hour() == 16 && adjustedTime.minute() == 12 && adjustedTime.second() == 0) {
        digitalWrite(ledGreen2, LOW);
        alertMessage = "Lampada desligada";
        alertMessage2 = ":D";
    }

    delay(1000); 
}
