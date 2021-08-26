## Especificaciones

Van a tener que trabajar sobre el `main.cpp` y el `libs/DHT.cpp`. El objetivo es armar un programa que haga una lectura del sensor y muestre en el LCD la temperatura en la primer fila en grados C y en la segunda fila la humedad en %.

Para lograr eso, en el `DHT.cpp` van a tener que terminar dos funciones `ExtractTemperature` y `ExtractHumidity`. En ambos casos, lo que tienen que conseguir es la temperatura o al humedad a partir de dos variables parciales (`highTemperature` y `lowTemperature` para la temperatura y `highHumidity` y `lowHumidity` para la humedad), donde `high` es la parte entera de la variable y `low` la decimal. Estas funciones tienen que devolver ese valor.

Ejemplo:

```
highTemeprature = 27 | lowTemperature = 10 => temperature = 27.10
highHumidity = 73 | lowHumidity = 22 => humidity = 73.22
```

En el `main.cpp` tienen que hacer una lectura con `dht.read()` y mostrar los valores en el LCD con su valor correspondiente. 

Luego de resolverlo, prueben el resultado y saquen screenshot de el circuito mostrando la presión en tres unidades distintas y armen un `README.md` con lo siguiente:

```
# DHT11

Alumno: Apellido y nombre
Curso: Curso
Materia: Adquisición de Datos

[Imagen 1]
```

## Orientación

- El `dht.read()` tiene dos argumentos que necesitamos pasarle, el primero es la variable para la temperatura y el segundo para la humedad. Para usarlo, tenemos que hacer algo como esto:

```cpp
float t, h;

dht.read(&t, &h);
```

## Como probar el código

Una vez que tengan todo listo, vayan a la terminal, asegúrense que apunte a la carpeta donde están trabajando y escriban:

```
make -f makefile.mk
```

Corrigan los errores, si los hubiera. De no haberlos, va a aparecer un `dht11.hex` que van a tener que cargar en el microcontrolador en el circuito de Proteus. Pueden corroborar los resultados comparando con algún conversor de unidades online.

## Como entregar

Pongan el `README.md`, el `main.cpp`, el `dht.cpp` y las imágenes en una carpeta y corran en una terminal:

```
git init
git add README.md main.cpp dht.cpp img.PNG
git commit -m "Initial commit"
git checkout -b ise5/2021/humedad/dht11
git push https://github.com/trq20/USERNAME.git ise5/2021/humedad/dht11
```

Recuerden de cambiar `USERNAME` por su nombre de usuario en GitHub. Pueden verificar si la entrega se hizo visitando la rama del repositorio en `https://github.com/trq20/USERNAME/tree/ise5/2021/humedad/dht11`.
