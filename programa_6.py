                  programa_6.py                               
import time
from datetime import datetime
import math
import os
import serial
from smbus2 import SMBus
from bme280 import BME280
import mysql.connector

# =====================================
# FUNCIONES METEOROLOGICAS
# =====================================

def punto_rocio(temp, hum):
    a = 17.27
    b = 237.7
    alpha = ((a * temp) / (b + temp)) + math.log(hum / 100.0)
    return (b * alpha) / (a - alpha)

def sensacion_termica(temp, hum):
    return (-8.784695 +
            1.61139411 * temp +
            2.338549 * hum +
            -0.14611605 * temp * hum +
            -0.012308094 * temp**2 +
            -0.016424828 * hum**2 +
            0.002211732 * temp**2 * hum +
            0.00072546 * temp * hum**2 +
            -0.000003582 * temp**2 * hum**2)

# =====================================
# CONFIGURACIÓN DE SENSORES Y BD
# =====================================

# Sensor BME280
bus = SMBus(1)
bme280 = BME280(i2c_dev=bus)

# Conexión Base de Datos
db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="3and1D0*",  # ✅ Se recomienda usar os.environ.get("DB_PASSWORD")
    database="balun_canan"
)
cursor = db.cursor()

# Conexión Arduino Serial
try:
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    time.sleep(2)  # Esperar a que Arduino reinicie
except Exception as e:
    print(f"❌ No se pudo abrir el puerto serial: {e}")
    ser = None

# =====================================
# LECTURA DE ARDUINO
# =====================================

def leer_arduino():
 if ser is None:
        return None, None, None, None, None, None, None

    try:
        line = ser.readline().decode('utf-8').strip()
        if line:
            valores = line.split(',')
            if len(valores) == 7:
                print(f"📥 Datos recibidos Arduino: {line}")
                temp_A = float(valores[0])
                temp_ext_A = float(valores[1])
                presion_A = float(valores[2])
                anemometro = float(valores[3])
                precipitacion = float(valores[4])
                humedad_A = float(valores[5])
                ppm_A = float(valores[6])

                return temp_A, temp_ext_A, presion_A, anemometro, precipitacion>
            else:
                print(f"⚠️ Datos incompletos. Esperados 7, llegaron {len(valores>
    except ValueError as ve:
        print("❌ Error al convertir dato de Arduino a float:", ve)
    except Exception as e:
        print("❌ Error inesperado en lectura Serial:", e)

    return None, None, None, None, None, None, None

# =====================================
# BUCLE PRINCIPAL
# =====================================

print('Comienzo de lectura en 3 segundos...')
time.sleep(3)

contador = 0

with open('datosa.csv', 'a', buffering=1) as f:
  while True:
        try:
            # 1. Lectura BME280
            temperatura = bme280.get_temperature()
            presion = bme280.get_pressure()
            humedad = bme280.get_humidity()

            # 2. Cálculos Meteorológicos
            dew = punto_rocio(temperatura, humedad)
            heat = sensacion_termica(temperatura, humedad)

            # 3. Lectura Arduino (¡Ahora asigna los datos reales!)
            temp_A, temp_ext_A, presion_A, anemometro, precipitacion, humedad_A, ppm_A = leer_arduino()

            # 4. Fecha y Hora
            now = datetime.now()
            fecha_hora = now.strftime("%Y-%m-%d %H:%M:%S")

            # 5. Monitor Serial (Consola)
            print(f"{fecha_hora} | BME280: {temperatura:.2f}°C | {presion:.2f} hPa | {humedad:.2f}%")
            print(f"   → Rocío: {dew:.2f}°C | Sensación: {heat:.2f}°C")
            print(f"   → Arduino: Temp={temp_A}, TempExt={temp_ext_A}, Pres={presion_A}, Ane={anemometro}, Prec={precipitacion}, Hum={humedad_A}, PPM={ppm_A}")

            # 6. Validación de Datos del BME280
            if -40 < temperatura < 85 and 300 < presion < 1100:

                # Guardar en CSV
                f.write(f"{fecha_hora},{temperatura:.2f},{presion:.2f},{humedad:.2f},{dew:.2f},{heat:.2f},"
                        f"{temp_A},{temp_ext_A},{presion_A},{anemometro},{precipitacion},{humedad_A},{ppm_A}\n")
                f.flush()

                # Reconexión Base de Datos si se pierde
                db.ping(reconnect=True)

                # Ajustamos el SQL. Asegúrate de que las columnas coincidan exactamente en cantidad con los %s
                sql = """
                INSERT INTO Datos_Arduino 
                (fecha, temperatura, presion, humedad, punto_rocio, sensacion_termica, 
 temp_A, temp_ext_A, presion_A, anemometro, precipitacion, humedad_A, ppm_A) 
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
                """

                valores_db = (
                    fecha_hora, temperatura, presion, humedad, dew, heat,
                    temp_A, temp_ext_A, presion_A, anemometro, precipitacion, humedad_A, ppm_A
                )

                cursor.execute(sql, valores_db)

                # Control del Commit cada 10 registros
                contador += 1
                if contador >= 10:
                    db.commit()
                    print("¡Lote de 10 registros guardado en la Base de Datos!")
                    contador = 0

            else:
                print(" Dato BME280 fuera de rango seguro.")

        except Exception as e:
            print(" Error general en el bucle:", e)

        time.sleep(900)
