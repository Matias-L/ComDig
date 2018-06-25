make:
	gcc -Wall -Werror -pedantic Encoder\ 1.c -o Encoder\ 1
	gcc -Wall -Werror -pedantic Encoder\ 2.c -o Encoder\ 2
	gcc -Wall -Werror -pedantic -std=c99 Decodificador\ convolucional.c -o Decodificador\ convolucional
	gcc -Wall -Werror -pedantic -std=c99 Detector\ optimo.c -o Detector\ optimo
	gcc -Wall -Werror -pedantic -std=c99 fuerza\ bruta.c -o fuerza\ bruta
	$(info Encoder\ 1: Dos salidas Encoder\ 2: Una salida)
clean:
	rm -rf Encoder\ 1
	rm -rf Encoder\ 2
	rm -rf Decodificador\ convolucional
	rm -rf Detector\ optimo
	rm -rf ruido.txt
	rm -rf rand.txt
	rm -rf salidak.txt
	rm -rf salida2k.txt
	#rm -rf grafico.png
	rm -rf fuerza\ bruta
