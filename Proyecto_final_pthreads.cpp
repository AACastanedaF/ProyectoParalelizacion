//Proyecto final en pthreads
//Alumno: Angel Adrian Castaneda Flores
//El codigo se encuentra mejor explicado en el reporte
//Para compilar usar Ubuntu
//g++ -pthread Nombre.cpp -o salida
//./salida
//librerias a utilizar
#include <iostream>
#include <cstdlib>
#include <math.h> // para usar el operador ceil
#include <time.h> //para el tiempo de ejecucion
//Libreria que permite la paralelizacion de procesos
#include <pthread.h>
using namespace std;
//Declaración de variables globales
int n_threads = 8; 
//matrices
int *matrizA;
int *matrizB;
int *matrizC;
//filas y columnas de cada matriz
int filasA;
int columnasA;
int filasB;
int columnasB;
int filasC;
int columnasC;
//contadores para a y b
//int *contadorA;
//int *contadorB;
int *contadorC;

/*void* CrearMA(void *i){
	int *lim = (int*) i;
	int a,b;
	a = contadorA[(int)*lim];
	b = contadorA[(int)*lim+1];
	for(int i=a; i<b;i++){
		for(int j=0; j<columnasA; j++){
			matrizA[(columnasA*i)+j] = (rand() % 20);
		}
	}
	pthread_exit(0);
	return (NULL);
}
void* CrearMB(void *i){
	int *lim = (int*) i;
	int a,b;
	a = contadorB[(int)*lim];
	b = contadorB[(int)*lim+1];
	for(int i=a; i<b;i++){
		for(int j=0; j<columnasB; j++){
			matrizB[(columnasB*i)+j] = (rand() % 20);
		}
	}
	pthread_exit(0);
	return (NULL);
}*/
void* SumaAB(void *i){
	int *lim = (int*) i;
	int a,b;
	a = contadorC[(int)*lim];
	b = contadorC[(int)*lim+1];
	for(int i=a; i<b;i++){
		for(int j=0; j<columnasC; j++){
			matrizC[(columnasC*i)+j] = matrizA[(columnasC*i)+j] + matrizB[(columnasC*i)+j];
		}
	}
	pthread_exit(0);
	return (NULL);
}
void* RestaAB(void *i){
	int *lim = (int*) i;
	int a,b;
	a = contadorC[(int)*lim];
	b = contadorC[(int)*lim+1];
	for(int i=a; i<b;i++){
		for(int j=0; j<columnasC; j++){
			matrizC[(columnasC*i)+j] = matrizA[(columnasC*i)+j] - matrizB[(columnasC*i)+j];
		}
	}
	pthread_exit(0);
	return (NULL);
}
void* TranspuestaA(void *i){
	int *lim = (int*) i;
	int a,b;
	a = contadorC[(int)*lim];
	b = contadorC[(int)*lim+1];
	for(int i=a; i<b;i++){
		for(int j=0; j<columnasC; j++){
			matrizC[(columnasC*i)+j] = matrizA[(filasC*j)+i];
		}
	}
	pthread_exit(0);
	return (NULL);
}
void* MultAB(void *i){
	int *lim = (int*) i;
	int a,b;
	int aux = 0;
	a = contadorC[(int)*lim];
	b = contadorC[(int)*lim+1];
	for(int i=a; i<b; i++){
		for(int j=0; j<columnasB; j++){
			for(int k=0; k<columnasA; k++){
				aux = matrizA[(columnasA*i)+k]*matrizB[(columnasB*k)+j] + aux;
			}
		matrizC[(columnasC*i)+j] = aux;
		aux = 0;
		}
	}
	pthread_exit(0);
	return (NULL);
}
//Programa Principal
int main(int argc, char *argv[]){
	//relojes
	clock_t inicio;
	double tiempo;
	int dim;
	dim = strtol(argv[1], nullptr, 0);;
	filasA = dim;
	columnasA = dim;
	filasB = dim;
	columnasB = dim;
	int a , b, auxint;
	//Semilla para los numeros aleatorios
	srand(time(NULL));
	//Asigmnacion de memoria a los contadores
	//contadorA = new int[n_threads+1];
	//contadorB = new int[n_threads+1];
	contadorC = new int[n_threads+1];
	//se crean los hilos
	pthread_t *thd = new pthread_t[n_threads];
	int *ids = new int[n_threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//Asigacion de memoria a las matrices A y B
	matrizA = new int[(filasA*columnasA)];
	matrizB = new int[(filasB*columnasB)];
	//se paralelizara por filas
	//auxint = round(filasA/n_threads);
	//contadorA[0] = 0;
	//creacion de limites
	/*for(int k=0; k<n_threads;k++){
		contadorA[k+1] = k*auxint + auxint;
		if(k == n_threads-1){
			contadorA[k+1] = contadorA[k+1] + (filasA%n_threads);
		}
	}*/
	//Generacion de valores de A
	/*for(int k = 0; k<n_threads; k++){
		ids[k] = k;
		pthread_create(&thd[k], &attr, *CrearMA, &ids[k]);
	}
	for(int k = 0; k<n_threads; k++){
		pthread_join(thd[k], NULL);
	}*/
	for(int i = 0;i<filasA; i++){
		for(int j=0; j<columnasA; j++){
			matrizA[(columnasA*i)+j] = (rand() % 10+1);
		}
	}
	//Impresion de la matriz A
	/*cout << "Matriz A" << endl;
	for(int i=0;i<filasA;i++){
		for(int j=0;j<columnasA;j++){
			cout << matrizA[(columnasA*i) +j] << "\t";
		}
		cout << endl;
	}*/
	//MATRIZ B
	/*auxint = round(filasB/n_threads);
	contadorB[0] = 0;
	//creacion de limites
	for(int k=0; k<n_threads;k++){
		contadorB[k+1] = k*auxint + auxint;
		if(k == n_threads-1){
			contadorB[k+1] = contadorB[k+1] + (filasB%n_threads);
		}
	}*/
	//Generacion de valores de B
	/*for(int k = 0; k<n_threads; k++){
		ids[k] = k;
		pthread_create(&thd[k], &attr, *CrearMB, &ids[k]);
	}
	for(int k = 0; k<n_threads; k++){
		pthread_join(thd[k], NULL);
	}*/
	for(int i = 0;i<filasB; i++){
		for(int j=0; j<columnasB; j++){
			matrizB[(columnasB*i)+j] = (rand() % 10+1);
		}
	}
	//Impresion de la matriz B
	/*cout << "Matriz B" << endl;
	for(int i=0;i<filasB;i++){
		for(int j=0;j<columnasB;j++){
			cout << matrizB[(columnasB*i) +j] << "\t";
		}
		cout << endl;
	}*/
	//Suma de matrices
	if(filasA == filasB && columnasA == columnasB){
		//inicio para el conteo de la suma
		inicio = clock();
		//Asigacion de memoria a la matriz C
		filasC = filasA;
		columnasC = columnasA;
		matrizC = new int[filasC*columnasC];
		//se paralelizara por filas
		auxint = round(filasC/n_threads);
		contadorC[0] = 0;
		//creacion de limites
		for(int k=0; k<n_threads;k++){
			contadorC[k+1] = k*auxint + auxint;
			if(k == n_threads-1){
				contadorC[k+1] = contadorC[k+1] + (filasC%n_threads);
			}
		}
		//Suma A con B
		for(int k = 0; k<n_threads; k++){
			ids[k] = k;
			pthread_create(&thd[k], &attr, *SumaAB, &ids[k]);
		}
		for(int k = 0; k<n_threads; k++){
			pthread_join(thd[k], NULL);
		}
		//Impresion de la suma de A con B
		/*cout << "La Suma de A con B es:" << endl;
		for(int i=0;i<filasC;i++){
			for(int j=0;j<columnasC;j++){
				cout << matrizC[(columnasC*i) +j] << "\t";
			}
			cout << endl;
		}*/
		delete[] matrizC;	
		tiempo = ((clock()-inicio)/(double)CLOCKS_PER_SEC)/n_threads;
		cout << "El tiempo de ejecución de la suma es: " << tiempo << endl;
	} else {
		cout << "No se puede realizar la suma por incompatibilidad de dimensiones" << endl;
	}
	//Resta de matrices
	if(filasA == filasB && columnasA == columnasB){
		//inicio para el conteo de la resta
		inicio = clock();
		//Asigacion de memoria a la matriz C
		filasC = filasA;
		columnasC = columnasA;
		matrizC = new int[filasC*columnasC];
		//se paralelizara por filas
		auxint = round(filasC/n_threads);
		contadorC[0] = 0;
		//creacion de limites
		for(int k=0; k<n_threads;k++){
			contadorC[k+1] = k*auxint + auxint;
			if(k == n_threads-1){
				contadorC[k+1] = contadorC[k+1] + (filasC%n_threads);
			}
		}
		//Resta A con B
		for(int k = 0; k<n_threads; k++){
			ids[k] = k;
			pthread_create(&thd[k], &attr, *RestaAB, &ids[k]);
		}
		for(int k = 0; k<n_threads; k++){
			pthread_join(thd[k], NULL);
		}
		//Impresion de la resta de A con B
		/*cout << "La Resta de A con B es:" << endl;
		for(int i=0;i<filasC;i++){
			for(int j=0;j<columnasC;j++){
				cout << matrizC[(columnasC*i) +j] << "\t";
			}
			cout << endl;
		}*/
		delete[] matrizC;
		tiempo = ((clock()-inicio)/(double)CLOCKS_PER_SEC)/n_threads;
		cout << "El tiempo de ejecución de la resta es: " << tiempo << endl;
		
	} else {
		cout << "No se puede realizar la resta por incompatibilidad de dimensiones" << endl;
	}
	//Transpuesta de la matriz A
	//inicio para el conteo de la transpuesta
	inicio = clock();
	//Asignacion de memoria a la matriz C
	filasC = columnasA;
	columnasC = filasA;
	matrizC = new int[filasC*columnasC];
	//se paralelizara por filas
	auxint = round(filasC/n_threads);
	contadorC[0] = 0;
	//creacion de limites
	for(int k=0; k<n_threads;k++){
		contadorC[k+1] = k*auxint + auxint;
		if(k == n_threads-1){
			contadorC[k+1] = contadorC[k+1] + (filasC%n_threads);
		}
	}
	for(int k = 0; k<n_threads; k++){
		ids[k] = k;
		pthread_create(&thd[k], &attr, *TranspuestaA, &ids[k]);
	}
	for(int k = 0; k<n_threads; k++){
		pthread_join(thd[k], NULL);
	}
	//Transpuesta de A
	/*cout << "La Transpuesta de A es:" << endl;
	for(int i=0;i<filasC;i++){
		for(int j=0;j<columnasC;j++){
			cout << matrizC[(columnasC*i) +j] << "\t";
		}
		cout << endl;
	}*/	
	delete[] matrizC;
	tiempo = ((clock()-inicio)/(double)CLOCKS_PER_SEC)/n_threads;
	cout << "El tiempo de ejecución de la transpuesta es: " << tiempo << endl;
	//Multiplicacion de Matrices A por B
	if(columnasA == filasB){
		//inicio para el conteo de la multiplicacion
		inicio = clock();
		//Asignacion de memoria a la matriz C
		filasC = filasA;
		columnasC = columnasB;
		matrizC = new int[filasC*columnasC];
		//se paralelizara por filas
		auxint = round(filasC/n_threads);
		contadorC[0] = 0;
		//creacion de limites
		for(int k=0; k<n_threads;k++){
			contadorC[k+1] = k*auxint + auxint;
			if(k == n_threads-1){
				contadorC[k+1] = contadorC[k+1] + (filasC%n_threads);
			}
		}
		//Multiplicacion A por B
		for(int k = 0; k<n_threads; k++){
			ids[k] = k;
			pthread_create(&thd[k], &attr, *MultAB, &ids[k]);
		}
		for(int k = 0; k<n_threads; k++){
			pthread_join(thd[k], NULL);
		}
		//Impresion de la Multiplicacion de A con B
		/*cout << "Multiplicacion A por B" << endl;
		for(int i=0;i<filasC;i++){
			for(int j=0;j<columnasC;j++){
				cout << matrizC[(columnasC*i) +j] << "\t";
			}
			cout << endl;
		}*/
		delete[] matrizC;
		tiempo = ((clock()-inicio)/(double)CLOCKS_PER_SEC)/n_threads;
		cout << "El tiempo de ejecución de la multiplicacion es: " << tiempo << endl;
	} else {
		cout << "No se puede realizar la multiplicacion por incompatibilidad de dimensiones" << endl;
	}	
	//Se eliminan los elementos generados con memoria dinamica
	//delete[] contadorA;
	delete[] contadorC;
	//delete[] contadorB;
	delete[] thd;
	delete[] ids;
	delete[] matrizA;
	delete[] matrizB;
	return 0;
}