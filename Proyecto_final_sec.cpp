//Proyecto final en secuencial
//Alumno: Angel Adrian Castañeda Flores
//Librerias a utilizar
#include <iostream>
#include <cstdlib>
#include <math.h> // para usar el operador ceil
#include <time.h> //para el tiempo de ejecucion
//namespace
using namespace std;
//Programa principal
int main(int argc, char *argv[]){
	//Declaracion de variables
	int dim;
	dim = strtol(argv[1], nullptr, 0);;
	int *matrizA, *matrizB, *matrizC;
	int filasA, columnasA, aux;
	int filasB, columnasB;
	int filasC, columnasC;
	filasA = dim;
	columnasA = dim;
	filasB = dim;
	columnasB = dim;
	clock_t inicio;
	double tiempo;
	//Se cambia la semilla
	srand(time(NULL));
	matrizA = new int[filasA*columnasA];
	matrizB = new int[filasB*columnasB];
	//Generacion de la matriz A
	for(int i = 0; i<filasA; i++){
		for(int j = 0; j<columnasA; j++){
			matrizA[(columnasA*i)+j] = (rand() % 10+1);
		}
	}
	//Impresion de la matriz A
	/*cout << "matrizA" << endl;
	for(int i = 0; i<filasA; i++){
		for(int j = 0; j<columnasA; j++){
			cout << matrizA[(columnasA*i)+j] << "\t";
		}
		cout << endl;
	}*/
	//Generacion de la matriz B
	for(int i = 0; i<filasB; i++){
		for(int j = 0; j<columnasB; j++){
			matrizB[(columnasB*i)+j] = (rand() % 10+1);
		}
	}
	//Impresion de la matriz B
	/*cout << "matrizB" << endl;
	for(int i = 0; i<filasB; i++){
		for(int j = 0; j<columnasB; j++){
			cout << matrizB[(columnasB*i)+j] << "\t";
		}
		cout << endl;
	}*/
	//Suma de matrices A y B
	//Comparacion de dimensiones para la suma de matrices A y B
	if(columnasA == columnasB && filasA == filasB){
		//Se comienza a contar el tiempo para la suma
		inicio = clock();
		//se le asigna memoria a la matriz C
		filasC = filasA;
		columnasC = columnasA;
		matrizC = new int[filasC*columnasC];
		//Se realiza la suma de matrices
		for(int i = 0; i<filasC; i++){
			for(int j = 0; j<columnasC; j++){
				matrizC[(columnasC*i)+j] = matrizA[(columnasA*i)+j] + matrizB[(columnasB*i)+j];
			}
		}
		//Impresion de la suma de la matriz A con B
		/*cout << "Suma de A con B" << endl;
		for(int i = 0; i<filasC; i++){
			for(int j = 0; j<columnasC; j++){
				cout << matrizC[(columnasC*i)+j] << "\t";
			}
		cout << endl;
		}*/
		//Se libera la memoria
		delete[] matrizC;
		//Se obtiene la diferencia de tiempos y se imprime el tiempo de ejecucion
		tiempo = (clock()-inicio)/(double)CLOCKS_PER_SEC;
		cout << "El tiempo de ejecución de la suma es: " << tiempo << endl;
	} else {
		cout << "No se puede realizar la suma por incompatibilidad de dimensiones" << endl;
	}
	//Resta de matrices A y B
	//Comparacion de dimensiones para la resta de matrices A y B
	if(columnasA == columnasB && filasA == filasB){
		//Se comienza a contar el tiempo para la resta
		inicio = clock();
		//Se le asigna memoria a la matriz C
		filasC = filasA;
		columnasC = columnasA;		
		matrizC = new int[filasC*columnasC];
		//Se realiza la resta de matrices
		for(int i = 0; i<filasC; i++){
			for(int j = 0; j<columnasC; j++){
				matrizC[(columnasC*i)+j] = matrizA[(columnasA*i)+j] - matrizB[(columnasB*i)+j];
			}
		}
		//Impresion de la resta de las mastriz A con B
		/*cout << "Resta de A con B" << endl;
		for(int i = 0; i<filasC; i++){
			for(int j = 0; j<columnasC; j++){
				cout << matrizC[(columnasC*i)+j] << "\t";
			}
			cout << endl;
		}*/
		delete[] matrizC;
		//Se obtiene la diferencia de tiempos y se imprime el tiempo de ejecucion
		tiempo = (clock()-inicio)/(double)CLOCKS_PER_SEC;
		cout << "El tiempo de ejecución de la resta es: " << tiempo << endl;		
	} else {
		cout << "No se puede realizar la resta por incompatibilidad de dimensiones" << endl;
	}
	//Transpuesta de la matriz A
	//Asignacion de memoria a la matriz C
	//Se comienza a contar el tiempo para la transpuesta
	inicio = clock();
    columnasC = filasA;
    filasC =  columnasA;
    matrizC = new int[filasC*columnasC];
    //Se realiza la transpuesta de A
	for(int i = 0; i<filasC; i++){
		for(int j = 0; j<columnasC; j++){
			matrizC[(columnasC*i)+j] = matrizA[(columnasA*j)+i];
		}
	}
	//Impresion de la transpuesta de A
	/*cout << "Transpuesta de A" << endl;
	for(int i = 0; i<filasC; i++){
		for(int j = 0; j<columnasC; j++){
			cout << matrizC[(columnasC*i)+j] << "\t";
		}
		cout << endl;
	}*/
	//Se libera la memoria de la matriz C
	delete[] matrizC;
	//Se obtiene la diferencia de tiempos y se imprime el tiempo de ejecucion
	tiempo = (clock()-inicio)/(double)CLOCKS_PER_SEC;
	cout << "El tiempo de ejecución de la transpuesta es: " << tiempo << endl;
	//Multiplicacion de matrices
	if(columnasA == filasB){
		//Se comienza a contar el tiempo para la multiplicacion
		inicio = clock();
		//Asignacion de la memoria a la matriz C
		filasC = filasA;
		columnasC = columnasB;
		matrizC = new int[filasC*columnasC];
		//Multiplicacion de matrices
		aux = 0;
		for(int i=0;i<columnasC;i++){
			for(int j=0;j<columnasB; j++){
				for(int k=0;k<columnasA;k++){
					aux = matrizA[(columnasA*i)+k]*matrizB[(columnasB*k)+j] + aux;
				}	
			matrizC[(columnasC*i)+j] = aux;
			aux = 0;				
			}
		}
		//Impresion del resultado de A por B
		/*cout << "Mult A por B" << endl;
		for(int i = 0; i<filasC; i++){
			for(int j = 0; j<columnasC; j++){
				cout << matrizC[(columnasC*i)+j] << "\t";
			}
			cout << endl;
		}*/
		delete[] matrizC;
		//Se obtiene la diferencia de tiempos y se imprime el tiempo de ejecucion
		tiempo = (clock()-inicio)/(double)CLOCKS_PER_SEC;
		cout << "El tiempo de ejecución de la multiplicacion es: " << tiempo << endl;
	} else {
		cout << "No se puede realizar la multiplicacion por incompatibilidad de dimensiones" << endl;
	}
	//liberacion de memoria de la matriz A, B y C
    delete[] matrizA;
    delete[] matrizB;
	return 0;
}