#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
bool sensor_ok = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("🔧 Iniciando MPU6050...");

  if (mpu.begin(0x68)) {
    Serial.println("✅ Sensor MPU6050 detectado!");
    sensor_ok = true;

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    Serial.println("⚙️ Sensor configurado.");
  } else {
    Serial.println("❌ Sensor MPU6050 não detectado!");
  }
}

void loop() {
  if (sensor_ok) {
    sensors_event_t a, g, temp;

    unsigned long start = millis();
    mpu.getEvent(&a, &g, &temp);
    unsigned long duration = millis() - start;

    if (duration > 100) {
      Serial.print("⚠️ Leitura lenta ou travada: ");
      Serial.print(duration);
      Serial.println(" ms");
    }

    Serial.printf("Accel: X=%.2f Y=%.2f Z=%.2f m/s²\n", a.acceleration.x, a.acceleration.y, a.acceleration.z);
    Serial.printf("Gyro : X=%.2f Y=%.2f Z=%.2f rad/s\n", g.gyro.x, g.gyro.y, g.gyro.z);
    Serial.printf("Temp : %.2f °C\n", temp.temperature);
    Serial.println("-----------------------------");

  } else {
    Serial.println("Sensor indisponível.");
  }

  delay(500);
}
