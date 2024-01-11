#include <MsTimer2.h>

#define MEASURE_PERIOD 500  // время периода измерения
#define BITNESS_ANALOG 1024 // разрядность сигнала
#define VOLTAGE_MAX 5.0     // максимальное напряжение на входе

int TimeCount;      // счетчик времени
int InputCod;       // код входного напряжения
float InputVoltage; // входное напряжение в В
float GetMilS;       // Счетчик миллисекунд

void  timerInterupt() {
  TimeCount++;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);                 // установка режима аналогового входа для A0

  Serial.begin(9600);                 // инициализируем порт, скорость 9600
  MsTimer2::set(1, timerInterupt);    // прерывания по таймеру, период 1 мс
  MsTimer2::start();                  // разрешение прерывания
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( TimeCount >= MEASURE_PERIOD ) {
    TimeCount = 0;
    
    InputCod = analogRead(A0);                                         // чтение напряжения на входе A3
    InputVoltage = ( (float)InputCod * VOLTAGE_MAX / BITNESS_ANALOG ); // пересчет кода в напряжение (В)

     // передача данных через последовательный порт
    //Serial.print("/"U":/"); Serial.print("/"%d"/", inputVoltage, 2);  Serial.print("\r\n");   Serial.print(" {\"U=\": \"%d\",\" I\": \"%d\"} ", inputVoltage, (inputVoltage/2), 2, 2 );
     GetMilS = millis();
     Serial.write("("); Serial.print(GetMilS, 0); Serial.write(") ");
     Serial.write("{\"U\": \""); Serial.print(InputVoltage*100, 2); Serial.write("\"}"); Serial.print("\r\n");
     
     GetMilS = millis();
     Serial.write("("); Serial.print(GetMilS, 0); Serial.write(") ");
     Serial.write("{\"I\": \""); Serial.print(InputVoltage, 2); Serial.write("\"}"); Serial.print("\r\n");
  }  
}
