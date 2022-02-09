//Proyecto final en cuda
//Alumno: Angel Adrian Castañeda Flores
//El codigo se encuentra mejor explicado en el reporte
//Librerias a utilizar
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <cuda.h>
#include <iostream>
#include <time.h>
//Suma de matrices
__global__ void Suma(int* a, int* b, int* c, int m, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    if (i < m && j < n) {
        c[(n * i) + j] = a[(n * i) + j] + b[(n * i) + j];
    }
}
//Resta de matrices
__global__ void Resta(int* a, int* b, int* c, int m, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    if (i < m && j < n) {
        c[(n * i) + j] = a[(n * i) + j] - b[(n * i) + j];
    }
}
//Tranpuesta de Matriz
__global__ void Transpuesta(int* a, int* c, int m, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    if (i < m && j < n) {
        c[(n * i) + j] = a[(m * j) + i];
    }
}
//Mutliplicacion de Matrices
__global__ void Matmul(int* a, int* b, int* c, int m, int n, int ca, int cb) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    int aux = 0;
    if (i < m && j < n) {
        for (int k = 0; k < ca; k++) {
            aux = (a[(ca * i) + k] * b[(cb * k) + j]) + aux;
        }
        c[(n * i) + j] = aux;
    }
}
using namespace std;
int main() {
    //Semilla para los numeros aleatorios
    srand(time(NULL));
    //matrices y propiedades
    int *matrizA, *matrizB, *matrizC;
    int *cudaA, *cudaB, *cudaC;
    int filasA, filasB, filasC;
    int columnasA, columnasB, columnasC;
    int aux;
    //variables para medir tiempo
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    float milliseconds = 0;
    filasA = 10;
    columnasA = 10;
    filasB = 10;
    columnasB = 10;
    //Asigacion de memoria a la matriz A
    matrizA = new int[filasA * columnasA];
    matrizB = new int[filasB * columnasB];
    //Generacion de matriz A
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasA; j++) {
            matrizA[(columnasA * i) + j] = (rand() % 10+1);
        }
    }
    //Impresion de matriz A
    cout << "Matriz A" << endl;
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasA; j++) {
            cout << matrizA[(columnasA * i) + j] << "\t";
        }
        cout << endl;
    }
    //Generacion de matriz B
    for (int i = 0; i < filasB; i++) {
        for (int j = 0; j < columnasB; j++) {
            matrizB[(columnasB * i) + j] = (rand() % 10+1);
        }
    }
    //Impresion de matriz B
    cout << "Matriz B" << endl;
    for (int i = 0; i < filasB; i++) {
        for (int j = 0; j < columnasB; j++) {
            cout << matrizB[(columnasB * i) + j] << "\t";
        }
        cout << endl;
    }
    //Asignacion de memoria en el GPU para las matrices A y B
    cudaMalloc((void**)&cudaA, filasA * columnasA * sizeof(int));
    cudaMemcpy(cudaA, matrizA, filasA * columnasA * sizeof(int), cudaMemcpyHostToDevice);
    cudaMalloc((void**)&cudaB, filasB * columnasB * sizeof(int));
    cudaMemcpy(cudaB, matrizB, filasB * columnasB * sizeof(int), cudaMemcpyHostToDevice);
    //Suma de Matrices A con B
    if (filasA == filasB && columnasA == columnasB){
        cudaEventRecord(start);
        //Se inicializa C
        filasC = filasA;
        columnasC = columnasA;
        matrizC = new int[filasC * columnasC];
        //Se asigna memoria a la GPU para C
        cudaMalloc((void**)&cudaC, filasC * columnasC * sizeof(int));
        //Generacion de la malla
        dim3 threadsPerBlock(8,8);
        dim3 numBlocks(ceil(float(filasC) / float(threadsPerBlock.x)), ceil(float(columnasC) / float(threadsPerBlock.y)));
        //Se ejecuta la suma en el GPU
        Suma <<<numBlocks, threadsPerBlock>>> (cudaA, cudaB, cudaC, filasC, columnasC);
        //Esperar a que el GPU termine
        cudaDeviceSynchronize();
        //Se copia el resultado del GPU al CPU
        cudaMemcpy(matrizC, cudaC, filasC * columnasC * sizeof(int), cudaMemcpyDeviceToHost);
        //Impresion de la suma
        cout << "La suma de A con B es: " << endl;
        for (int i = 0; i < filasC; i++) {
            for (int j = 0; j < columnasC; j++) {
                cout << matrizC[(columnasC * i) + j] << "\t";
            }
            cout << endl;
        }
        //Liberacion de Memoria de C
        cudaFree(cudaC);
        delete[] matrizC;
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        milliseconds = 0;
        cudaEventElapsedTime(&milliseconds, start, stop);
        cout << "el tiempo de ejecución de la suma es de: " << milliseconds/1000 << endl;
    } 
    else {
        cout << "No se puede hacer la suma de matrices por incompatibilidad de dimensiones" << endl;
    }   
    //Resta de Matrices A con B
    if (filasA == filasB && columnasA == columnasB) {
        cudaEventRecord(start);
        //Se inicializa C
        filasC = filasA;
        columnasC = columnasA;
        matrizC = new int[filasC * columnasC];
        //Se asigna memoria a la GPU para C
        cudaMalloc((void**)&cudaC, filasC * columnasC * sizeof(int));
        cudaMemcpy(cudaC, matrizC, filasC * columnasC * sizeof(int), cudaMemcpyHostToDevice);
        //Generacion de la malla
        dim3 threadsPerBlock(8, 8);
        dim3 numBlocks(ceil(float(filasC) / float(threadsPerBlock.x)), ceil(float(columnasC) / float(threadsPerBlock.y)));
        //Se ejecuta la suma en el GPU
        Resta <<<numBlocks, threadsPerBlock>>> (cudaA, cudaB, cudaC,filasC, columnasC);
        //Se copia el resultado del GPU al CPU
        cudaMemcpy(matrizC, cudaC, filasC * columnasC * sizeof(int), cudaMemcpyDeviceToHost);
        //Impresion de la resta de A con B
        cout << "La resta de A con B es: " << endl;
        for (int i = 0; i < filasC; i++) {
            for (int j = 0; j < columnasC; j++) {
                cout << matrizC[(columnasC * i) + j] << "\t";
            }
            cout << endl;
        }
        //Liberacion de Memoria de C
        cudaFree(cudaC);
        delete[] matrizC;
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        milliseconds = 0;
        cudaEventElapsedTime(&milliseconds, start, stop);
        cout << "el tiempo de ejecución de la resta es de: " << milliseconds / 1000 << endl;
    }
    else {
        cout << "No se puede hacer la resta de matrices por incompatibilidad de dimensiones" << endl;
    }
    //Transpuesta de A
    //Se inicializa C
    cudaEventRecord(start);
    filasC = columnasA;
    columnasC = filasA;
    matrizC = new int[filasC * columnasC];
    //Se asigna memoria a la GPU para C
    cudaMalloc((void**)&cudaC, filasC * columnasC * sizeof(int));
    cudaMemcpy(cudaC, matrizC, filasC * columnasC * sizeof(int), cudaMemcpyHostToDevice);
    //Generacion de la malla
    dim3 threadsPerBlock(8, 8);
    dim3 numBlocks(ceil(float(filasC) / float(threadsPerBlock.x)), ceil(float(columnasC) / float(threadsPerBlock.y)));
    //Se ejecuta la transpuesta en el GPU
    Transpuesta <<<numBlocks, threadsPerBlock >>> (cudaA, cudaC, filasC, columnasC);
    //Se copia el resultado del GPU al CPU
    cudaMemcpy(matrizC, cudaC, filasC * columnasC * sizeof(int), cudaMemcpyDeviceToHost);
    //Impresion de transpuesta de A con B
    cout << "La transpuesta de A: " << endl;
    for (int i = 0; i < filasC; i++) {
        for (int j = 0; j < columnasC; j++) {
            cout << matrizC[(columnasC * i) + j] << "\t";
        }
        cout << endl;
    }
    //Liberacion de Memoria de C
    cudaFree(cudaC);
    delete[] matrizC;
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    cout << "el tiempo de ejecución de la transpuesta es de: " << milliseconds / 1000 << endl;
    //Multiplicacion de Matrices A con B
    if (columnasA == filasB) {
        cudaEventRecord(start);
        //Se inicializa C
        filasC = filasA;
        columnasC = columnasB;
        matrizC = new int[filasC * columnasC];
        //Se asigna memoria a la GPU para C
        cudaMalloc((void**)&cudaC, filasC * columnasC * sizeof(int));
        cudaMemcpy(cudaC, matrizC, filasC * columnasC * sizeof(int), cudaMemcpyHostToDevice);
        //Generacion de la malla
        dim3 threadsPerBlock(8, 8);
        dim3 numBlocks(ceil(float(filasC) / float(threadsPerBlock.x)), ceil(float(columnasC) / float(threadsPerBlock.y)));
        //Se ejecuta la suma en el GPU
        Matmul <<<numBlocks, threadsPerBlock>>> (cudaA, cudaB, cudaC, filasC, columnasC, columnasA, columnasB);
        //Se copia el resultado del GPU al CPU
        cudaMemcpy(matrizC, cudaC, filasC * columnasC * sizeof(int), cudaMemcpyDeviceToHost);
        //Impresion de la resta de A con B
        cout << "La multiplicacion de A con B es: " << endl;
        for (int i = 0; i < filasC; i++) {
            for (int j = 0; j < columnasC; j++) {
                cout << matrizC[(columnasC * i) + j] << "\t";
            }
           cout << endl;
        }
        //Liberacion de Memoria de C
        cudaFree(cudaC);
        delete[] matrizC;
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        milliseconds = 0;
        cudaEventElapsedTime(&milliseconds, start, stop);
        cout << "el tiempo de ejecución de la multiplicacion es de: " << milliseconds / 1000 << endl;
    }
    else {
        cout << "No se puede hacer la multiplicacion de matrices por incompatibilidad de dimensiones" << endl;
    }
    //liberacion de memoria
    cudaFree(cudaA);
    delete[] matrizA;
    cudaFree(cudaB);
    delete[] matrizB;
    return 0;  
}