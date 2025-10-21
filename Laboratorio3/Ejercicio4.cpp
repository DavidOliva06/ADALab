/*
 * Programa de Comparación de Algoritmos de Ordenamiento
 * Ordena elementos aleatorios y compara tiempos de ejecución de:
 * - Insertion Sort (O(n²))
 * - Selection Sort (O(n²))
 * - Merge Sort (O(n log n))
 * - Quick Sort (O(n log n) promedio)
 */

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <ctime> 
using namespace std;
using namespace std::chrono;

// Insertion Sort: eficiente para listas pequeñas o casi ordenadas
vector<int> Insertion_Sort(vector<int> lista){
    for(int i = 1; i < lista.size(); i++){
        // Insertar elemento en su posición correcta en la parte ordenada
        for(int j = i; j > 0 && lista[j] < lista[j-1]; j--){
            swap(lista[j], lista[j-1]);
        }
    }
    return lista;
}

// Selection Sort: selecciona el mínimo en cada iteración
vector<int> Selection_Sort(vector<int> lista){
    for(int i = 0, menor; i < lista.size()-1; i++){
        menor = i;
        // Buscar el elemento más pequeño en la parte no ordenada
        for(int j = i; j < lista.size(); j++){
            if(lista[j] < lista[menor]){
                menor = j;
            }
        }
        swap(lista[menor], lista[i]);
    }
    return lista;
}

// Merge Sort: divide y conquista, siempre O(n log n)
vector<int> Merge_Sort(vector<int> lista){
    // Caso base: lista de 0 o 1 elemento ya está ordenada
    if (lista.size() <= 1) 
        return lista;
    
    // Dividir la lista en dos mitades
    int medio = lista.size() / 2;
    vector<int> izquierda(lista.begin(), lista.begin() + medio);
    vector<int> derecha(lista.begin() + medio, lista.end());

    // Ordenar recursivamente cada mitad
    izquierda = Merge_Sort(izquierda);
    derecha = Merge_Sort(derecha);

    // Mezclar las dos mitades ordenadas
    vector<int> merged;
    int i = 0, j = 0;
    while (i < izquierda.size() && j < derecha.size()) {
        if (izquierda[i] < derecha[j]) {
            merged.push_back(izquierda[i]);
            i++;
        } else {
            merged.push_back(derecha[j]);
            j++;
        }
    }
    // Agregar elementos restantes
    while (i < izquierda.size()) {
        merged.push_back(izquierda[i]);
        i++;
    }
    while (j < derecha.size()) {
        merged.push_back(derecha[j]);
        j++;
    }
    return merged;
}

// Función auxiliar para particionar el array en Quick Sort
int particion(vector<int>& lista, int inicio, int fin){
    int pivote = lista[fin];  // Elegir el último elemento como pivote
    int i = inicio - 1;  // Índice del elemento más pequeño
    
    // Reorganizar elementos: menores a la izquierda, mayores a la derecha
    for(int j = inicio; j < fin; j++){
        if(lista[j] <= pivote){
            i++;
            swap(lista[i], lista[j]);
        }
    }
    swap(lista[i + 1], lista[fin]);  // Colocar pivote en su posición final
    return i + 1;
}

// Quick Sort recursivo: muy eficiente en promedio
void Quick_Sort_Recursivo(vector<int>& lista, int inicio, int fin){
    if(inicio < fin){
        // Particionar y obtener índice del pivote
        int indice_pivote = particion(lista, inicio, fin);
        
        // Ordenar recursivamente las dos particiones
        Quick_Sort_Recursivo(lista, inicio, indice_pivote - 1);
        Quick_Sort_Recursivo(lista, indice_pivote + 1, fin);
    }
}

// Función envolvente para Quick Sort
vector<int> Quick_Sort(vector<int> lista){
    if(lista.size() <= 1) return lista;
    Quick_Sort_Recursivo(lista, 0, lista.size() - 1);
    return lista;
}

// Función para ejecutar el ordenamiento seleccionado y medir tiempo
vector<int> tipo(vector<int> lista, string ordenamiento){
    vector<int> lista2;
    
    if(ordenamiento == "insertion"){
        auto inicio = high_resolution_clock::now(); 
        lista2 = Insertion_Sort(lista);
        auto final = high_resolution_clock::now();
        duration<double, milli> tiempo = final - inicio;
        cout << "Insertion Sort - Tiempo: " << tiempo.count() << " ms" << endl;
    }
    else if(ordenamiento == "selection"){
        auto inicio = high_resolution_clock::now(); 
        lista2 = Selection_Sort(lista);
        auto final = high_resolution_clock::now();
        duration<double, milli> tiempo = final - inicio;
        cout << "Selection Sort - Tiempo: " << tiempo.count() << " ms" << endl;
    }
    else if(ordenamiento == "merge"){
        auto inicio = high_resolution_clock::now(); 
        lista2 = Merge_Sort(lista);
        auto final = high_resolution_clock::now();
        duration<double, milli> tiempo = final - inicio;
        cout << "Merge Sort - Tiempo: " << tiempo.count() << " ms" << endl;
    }
    else if(ordenamiento == "quick"){
        auto inicio = high_resolution_clock::now(); 
        lista2 = Quick_Sort(lista);
        auto final = high_resolution_clock::now();
        duration<double, milli> tiempo = final - inicio;
        cout << "Quick Sort - Tiempo: " << tiempo.count() << " ms" << endl;
    }
    else {
        cout << "Ordenamiento no válido. Opciones: insertion, selection, merge, quick" << endl;
        return lista;
    }
    
    return lista2;
}

// Función para imprimir la lista (útil para verificar con listas pequeñas)
void imprimir(vector<int> lista){
    cout << "Lista ordenada: [";
    for(int i = 0; i < lista.size(); i++){
        cout << " " << lista[i];
    }
    cout << " ]" << endl;
}

int main(){
    vector<int> lista, lista_ordenada;
    int n;
    string ordenamiento;
    
    cout << "=== Comparador de Algoritmos de Ordenamiento ===" << endl;
    cout << "Ingrese el numero de elementos: ";
    cin >> n;
    cout << "Ingrese el tipo de ordenamiento (insertion/selection/merge/quick): ";
    cin >> ordenamiento;
    
    // Inicializar generador de números aleatorios
    srand(time(nullptr));

    // Generar lista con números aleatorios
    for (int i = 0; i < n; i++) {
        int num = rand() % (n * 5);  
        lista.push_back(num);
    }
    
    cout << "\nOrdenando " << n << " elementos..." << endl;
    lista_ordenada = tipo(lista, ordenamiento);
    
    // Imprimir solo si hay pocos elementos (para no saturar la consola)
    if(n <= 100){
        imprimir(lista_ordenada);
    }
    
    return 0;
}