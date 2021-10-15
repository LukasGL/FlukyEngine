# FlukyEngine

Motor de juegos desarrollado en C++ para el ramo CC5512 - Arquitectura de Motores de Juegos, enfocado en juegos de plataforma 3D que utilizan figuras simples.

## Dependencias

Todas las dependencias del proyecto están en la carpeta `thirdParty/`

- [ImGui](https://github.com/ocornut/imgui) para gui de depuración.
- [GLFW](https://www.glfw.org/) para la creación y manejo de ventanas e input.
- [glad](https://glad.dav1d.de/) para cargar las funciones de OpenGL.
- [glm](https://glm.g-truc.net/0.9.9/index.html) para algebra lineal.
- [dr_wav](https://mackron.github.io/dr_wav.html) para cargar archivos .wav desde disco.

- [OpenAL-Soft](https://github.com/kcat/openal-soft) para la implementación del sistema de audio.
- [BGFX](https://github.com/bkaradzic/bgfx) como librería encargada del renderizado de figuras en 3 dimensiones.
- [Easy3D](https://github.com/LiangliangNan/Easy3D) como segunda librería de renderizado (incluida por posibles errores, no esta siendo utilizada por el momento).

## Software/Libreria externas necesarias

Para generar el proyecto, solución o makefiles se necesita [CMake 3.8+](https://cmake.org/), y de OpenGL4.5 para funcionar.

## Importando el proyecto

Clonar el repositorio

`git clone ...`

Luego como tiene dependencias de otros repositorios hace falta ejecutar lo siguiente (Ojo! solo será necesario la primera vez)

`git submodule update --init --recursive`

Si los submódulos se actualizan se deberá ejecutar 

`git submodule update --recursive`

Y listo! solo queda generar la `Build` del motor.

(Es posible que si hay errores en el build se deba a que no está Doxygen instalado, descargar instalador desde [aquí](https://www.doxygen.nl/files/doxygen-1.9.2-setup.exe))

## Generando la solución o makefiles y el proceso de compilación

La solución solamente ha sido probada en Windows 10 y directamente de Visual Studio 2019. Y el paso principal es generar el `Build` del `CMakeLists.txt` que se define el proyecto, en este caso el que se encuentra afuera de las carpetas. 

Los ejemplos serán generados automáticamente y serán los siguientes:

- `ex_audio.exe` Para la prueba del audio
- `ex_cube.exe` Para la prueba del renderizado de figuras y además el testeo de inputs desde joysticks (se podrán mover los cubos)
- `ex_world.exe` Para la prueba de la creación del mundo
- `ex_text.exe` (No terminado)

Toda la explicación puede ser vista en el video de la demostración haciendo clic [aquí](https://youtu.be/E3vkcPsZdg8)

## Como crear aplicaciones usando el motor

Para crear un juego se debe utilizar la plantilla `examples-fluky/ex_world.cpp`, la cual se encarga solamente de generar un mundo. Dentro de las 3 funciones principales se tendrá que desarrollar lo que el usuario desee.

Por ejemplo si se revisan el archivo `examples-fluky/ex_cube.cpp` utiliza la misma elaboración del mundo pero esta vez genera el cubo en la función `UserStartUp()`.

Por el momento solo existen 2 funciones extra que el usuario puede añadir a su juego en `UserStartUp()`:

- `CreateFigure()` generará el cubo giratorio en medio de la pantalla
- `PlayWav(filename)` reproduce el archivo wav especificado por el usuario (`filename`)

La utilización de las 2 funciones están en los ejemplos de `examples-fluky`.

## Documentación

Toda la información acerca de las funciones y clases creadas se puede ver mediante [Doxygen](https://www.doxygen.nl/index.html). Para esto se debe tener instalado Doxygen y luego solamente buildear el proyecto. Finalmente la documentación estará en `doc_doxygen/index.html`.

## Screenshots

![ex_cube](images/ex_cube.png)
