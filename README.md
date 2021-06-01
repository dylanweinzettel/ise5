# Especificaciones

Los dos archivos sobre los que van a tener que trabajar son el `main.cpp` y el `libs/bmp180.cpp`. Van a encontrar el circuito ya armado en la carpeta `sch`. El algoritmo que desarrollen va a tener que:

- Leer constantemente cada una de las entradas digitales conectadas al conjunto de llaves y, de acuerdo a la que se seleccione, mostrar la presión medida por el sensor en la unidad determinada.
- Si no hay ninguna llave seleccionada, el display tiene que estar limpio.
- El display debe mostrar al lado del valor la unidad de presión.

Asuman que nunca va a haber mas de una llave seleccionada. El algoritmo principal tienen que trabajarlo en el `main.cpp`. Dentro del `bmp180.cpp`, van a encontrar un método `float getPressure(uint8_t)` que van a tener que trabajar. Este toma como argumento un número entero entre el 0 y el 7 que representan una de las unidades. En el `bmp180.h` van a encontrar las definiciones que son:

```c
#define Pa    0
#define hPa   1
#define kPa   2
#define atm   3
#define mmHg  4
#define Bar   5
#define PSI   6
#define Torr  7
```

Luego de resolverlo, prueben el resultado y saquen screenshot de el circuito mostrando la presión en tres unidades distintas y armen un `README.md` con lo siguiente:

```
# BMP180

Alumno: Apellido y nombre
Curso: Curso
Materia: Adquisición de Datos

[Imagen 1]
[Imagen 2]
[Imagen 3]
```

## Orientación

- El `getPressure` debe evaluar el tipo de unidad que se quiere, hacer la conversión de Pascales a esta y luego devolver el valor como `float`. Pueden considerar usar una serie de `if` o un `switch.. case`.
- Pueden usar `digitalRead(pin)` para leer el estado de los pines digitales. Tienen que pasar como argumento el pin que quieren, en este caso, los pines van del 8 al 15.
- Recuerden que la unidad original de la convierten es siempre Pascales.

# Como probar el código

Una vez que tengan todo listo, vayan a la terminal, asegúrense que apunte a la carpeta donde están trabajando y escriban:

```
make -f makefile.mk
```

Corrigan los errores, si los hubiera. De no haberlos, va a aparecer un `bmp180.hex` que van a tener que cargar en el microcontrolador en el circuito de Proteus. Pueden corroborar los resultados comparando con algún conversor de unidades online.

## Como entregar

Pongan el `README.md`, el `main.cpp`, el `bmp180.cpp` y las imágenes en una carpeta y corran en una terminal:

```
git init
git add README.md main.cpp bmp180.cpp img1.png img2.pmg img3.png
git commit -m "Initial commit"
git checkout -b ise5/2021/presion/bmp180
git push https://github.com/trq20/USERNAME.git ise5/2021/presion/bmp180
```

Recuerden de cambiar `USERNAME` por su nombre de usuario en GitHub. Pueden verificar si la entrega se hizo visitando la rama del repositorio en `https://github.com/trq20/USERNAME/tree/ise5/2021/presion/bmp180`.
