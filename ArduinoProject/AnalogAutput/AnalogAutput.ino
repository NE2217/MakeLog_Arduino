#define MEASURE_PERIOD 500  // время периода измерения
#define ADC_RAW_MAX 1024    // разрядность сигнала
#define VOLTAGE_MAX 5.0     // максимальное напряжение на входе

#define VOLTAGE_CALC(raw) raw * VOLTAGE_MAX / ADC_RAW_MAX //получение напряжения на АЦП

uint16_t AdcRaw;                // код входного напряжения
float InputVoltage;             // входное напряжение в В

uint32_t LocalTime = millis();  // Счетчик миллисекунд

void f_TimeReset()
{
  LocalTime=millis();
}

bool f_IsTimeOut (){
  if(millis() - LocalTime == MEASURE_PERIOD)
  {
    f_TimeReset();
    return true;
  }
  return false;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);                   // установка режима аналогового входа для A0
  pinMode(A1, INPUT);                   // установка режима аналогового входа для A1

  Serial.begin(9600);                   // инициализируем порт, скорость 9600
}

void loop() {
  // put your main code here, to run repeatedly:

  uint32_t TimeStamp = millis();

  if ( f_IsTimeOut() ) 
  {
    
    AdcRaw = analogRead(A0);                                         // чтение напряжения на входе A3
    InputVoltage = VOLTAGE_CALC( (float)AdcRaw );                    // пересчет кода в напряжение (В)

     // передача данных через последовательный порт
     Serial.write("{\"TimeStamp\": \""); Serial.print(TimeStamp, DEC); Serial.write("\"} ");
     Serial.write("{\"U\": \""); Serial.print(InputVoltage*100, 2); Serial.write("\"} ");
     Serial.write("{\"I\": \""); Serial.print(InputVoltage, 2); Serial.write("\"}"); Serial.print("\r\n");

  }  
}
