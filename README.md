## Especificaciones

Luego de resolverlo, prueben el resultado y saquen screenshot de el circuito mostrando la presión en tres unidades distintas y armen un `README.md` con lo siguiente:

```
# DHT11

Alumno: Apellido y nombre
Curso: Curso
Materia: Adquisición de Datos

[Imagen 1]
```

## Orientación


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
