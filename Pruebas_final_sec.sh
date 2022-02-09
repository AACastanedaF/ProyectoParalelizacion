#Script para las pruebas de secuencial
#Alumno: Angel Adrian Castaneda Flores
#!/bin/bash
#Se compila y se crea el ejecturable del script de c++
g++ Proyecto_final_sec.cpp -o ja
#Se escribe lo que esta entre comillado
echo "Los archivos de salida son:"
#Se realiza un ciclo
#Por cada iteracion se va a escribrir un tamaño de matriz cuadrada
#En ese orden
	for i in 100, 500, 1000, 1500, 2000, 2500, 3000, 4000, 5000
	do 
		#Se escribe el nombre del archivo de salida
		echo "Resultado para prueba de tamaño: "$i
		#se corre el ejecutable con la palabra en la iteracion
		./ja $i
	done
#Se escribe lo que esta entre comillado
echo "Script de Shell Finalizado"