# Sistema-meteorologico-Preparatoriano

Código de una estación meteorológica Balun Canan desarrollada por un grupo de estudiantes de preparatoria como parte de un proyecto STEM presentado para la Fundación MetLife y el movimiento STEM.

---

# Español

## Descripción del Proyecto

Este proyecto consiste en una estación meteorológica educativa diseñada y programada por estudiantes de preparatoria con el objetivo de fomentar el aprendizaje científico, el monitoreo ambiental y el desarrollo tecnológico.

El sistema recopila datos atmosféricos y ambientales en tiempo real utilizando sensores compatibles con Arduino.  
Su propósito es demostrar cómo los sistemas embebidos de bajo costo pueden utilizarse para monitoreo climático, experimentación científica e investigación educativa.

La estación fue desarrollada como un prototipo funcional capaz de medir condiciones ambientales tanto en exteriores como en zonas de sombra para realizar comparaciones y pruebas.

Este repositorio contiene el código fuente utilizado para leer sensores, procesar información ambiental y mostrar telemetría mediante comunicación Serial.

---

## Características

- Monitoreo de presión atmosférica mediante BME280
- Medición de temperatura ambiental
- Monitoreo de humedad relativa
- Medición de velocidad del viento y direccion.
- Mediciones pluviales
- Comparación entre temperatura exterior y en sombra
- Salida de telemetría en tiempo real por Serial
- Arquitectura modular basada en Arduino

---

## Tecnologías y Hardware

El proyecto utiliza:

- Microcontrolador compatible con Arduino
- Sensor atmosférico BME280
- Sensores DHT11 de humedad y temperatura
- Bus de comunicación I2C
- Salida Serial para telemetría

---

## Librerías Utilizadas

Este proyecto utiliza las siguientes librerías de Arduino:

- `Wire.h`
- `Adafruit_BME280`
- `Adafruit_Sensor`
- `DHT`
- `DHT_U`

---

## Créditos

Agradecimientos especiales a los desarrolladores y mantenedores de las librerías de código abierto utilizadas en este proyecto:

- [Adafruit BME280 Library](https://github.com/adafruit/Adafruit_BME280_Library)
- [Adafruit Unified Sensor Library](https://github.com/adafruit/Adafruit_Sensor)
- [DHT Sensor Library by Adafruit](https://github.com/adafruit/DHT-sensor-library)
- [Arduino Wire Library Documentation](https://www.arduino.cc/reference/en/language/functions/communication/wire/)

Este proyecto no sería posible sin la comunidad open-source de Arduino y STEM.

---

## Propósito Educativo

Este repositorio fue creado principalmente para:

- Educación STEM
- Monitoreo ambiental
- Aprendizaje de sistemas embebidos
- Práctica de integración de sensores
- Experimentación científica
- Proyectos de ingeniería a nivel preparatoria

El proyecto fue desarrollado como un prototipo educativo, por lo que algunos sistemas e implementaciones pueden permanecer experimentales o simplificados.

---

## Equipo y Colaboración

Esta estación meteorológica fue desarrollada colaborativamente por un grupo de estudiantes de preparatoria interesados en ciencia, ingeniería, programación y tecnologías ambientales.

El proyecto fue creado como parte de una iniciativa educativa relacionada con:

- El movimiento STEM
- Programas de innovación científica y tecnológica
- Desarrollo de prototipos educativos para la Fundación MetLife

---

## Notas

- Aun no se programa las funciones de mediciones de velocidad del viento y pluviales debido a la falta de estos sensores.
- La precisión de los sensores puede variar dependiendo de las condiciones ambientales y la calibración.
- Este repositorio funciona tanto como recurso de aprendizaje como referencia funcional de prototipo.

---

## Contribuciones

Las sugerencias, mejoras y comentarios son bienvenidos.

Posibles mejoras futuras incluyen:

- Dashboard web para monitoreo climático
- Sensores más precisos
- Soporte para tarjetas SD

---

# English

## Project Description

This project is the Balun Canan weather station designed and programmed by high school students to promote scientific learning, environmental monitoring, and STEM development.

The system collects real-time atmospheric and environmental data using Arduino-compatible sensors.  
Its purpose is to demonstrate how low-cost embedded systems can be used for climate monitoring, scientific experimentation, and educational research.

The station was developed as a functional prototype capable of measuring environmental conditions both outdoors and in shaded areas for comparison and testing purposes.

This repository contains the source code used to read sensor data, process environmental information, and display telemetry through Serial communication.

---

## Features

- Atmospheric pressure monitoring using BME280
- Environmental temperature measurement
- Relative humidity monitoring
- Wind speed and direction measurement
- Rainfall measurement
- Outdoor and shaded temperature comparison
- Real-time Serial telemetry output
- Arduino-based modular architecture

---

## Technologies and Hardware

The project uses:

- Arduino-compatible microcontroller
- BME280 atmospheric pressure sensor
- DHT11 humidity and temperature sensors
- I2C communication bus
- Serial telemetry output

---

## Libraries Used

This project uses the following Arduino libraries:

- `Wire.h`
- `Adafruit_BME280`
- `Adafruit_Sensor`
- `DHT`
- `DHT_U`

---

## Credits

Special thanks to the developers and maintainers of the open-source libraries used in this project:

- [Adafruit BME280 Library](https://github.com/adafruit/Adafruit_BME280_Library)
- [Adafruit Unified Sensor Library](https://github.com/adafruit/Adafruit_Sensor)
- [DHT Sensor Library by Adafruit](https://github.com/adafruit/DHT-sensor-library)
- [Arduino Wire Library Documentation](https://www.arduino.cc/reference/en/language/functions/communication/wire/)

This project would not be possible without the open-source Arduino and STEM communities.

---

## Educational Purpose

This repository was created mainly for:

- STEM education
- Environmental monitoring
- Embedded systems learning
- Sensor integration practice
- Scientific experimentation
- High school engineering projects

The project was developed as an educational prototype, so some systems and implementations may remain experimental or simplified.

---

## Team and Collaboration

This weather station was developed collaboratively by a group of high school students interested in science, engineering, programming, and environmental technologies.

The project was created as part of an educational initiative connected to:

- The STEM movement
- Scientific and technological innovation programs
- Educational prototype development for the MetLife Foundation

---

## Notes

- The wind speed and rainfall measurement functions have not yet been programmed due to the lack of these sensors.
- Sensor accuracy may vary depending on environmental conditions and calibration.
- This repository serves as both a learning resource and a functional prototype reference.

---

## Contributions

Suggestions, improvements, and feedback are welcome.

Possible future improvements include:

- Online weather monitoring dashboard
- More accurate sensors
- SD card storage support
