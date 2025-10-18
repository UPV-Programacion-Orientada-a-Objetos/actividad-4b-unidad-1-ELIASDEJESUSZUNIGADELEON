#include <iostream>
#include <iomanip>
#include "Simulador2D.h"

using namespace std;

void mostrarMenu() {
    cout << "\n=== SIMULADOR GENERICO DE FLUIDOS 2D ===" << endl;
    cout << "1. Simular 1 paso" << endl;
    cout << "2. Simular N pasos" << endl;
    cout << "3. Mostrar grid actual" << endl;
    cout << "4. Agregar fuente" << endl;
    cout << "5. Establecer valor en posicion" << endl;
    cout << "6. Redimensionar grid" << endl;
    cout << "7. Mostrar fuentes" << endl;
    cout << "8. Cambiar a simulador INT" << endl;
    cout << "9. Cambiar a simulador FLOAT" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
}

template<typename T>
void demostrarSimulador(Simulador2D<T>& sim, const string& tipo) {
    cout << "\n>> Inicializando Sistema (Tipo " << tipo << ") <<" << endl;
    cout << "Creando Grid (" << tipo << ") de " << sim.obtenerFilas() << "x" << sim.obtenerColumnas() << "..." << endl;
    
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                cout << "\nSimulando 1 paso..." << endl;
                sim.simularPaso();
                cout << "--- Grid Después del Paso ---" << endl;
                sim.mostrarGrid();
                break;
            }
            case 2: {
                int pasos;
                cout << "Numero de pasos a simular: ";
                cin >> pasos;
                cout << "\nSimulando " << pasos << " pasos..." << endl;
                for(int i = 0; i < pasos; i++) {
                    sim.simularPaso();
                }
                cout << "--- Grid Después de " << pasos << " Pasos ---" << endl;
                sim.mostrarGrid();
                break;
            }
            case 3: {
                cout << "\n--- Grid Actual ---" << endl;
                sim.mostrarGrid();
                break;
            }
            case 4: {
                T valor;
                cout << "Valor de la fuente: ";
                cin >> valor;
                sim.agregarFuente(valor);
                cout << "Fuente agregada: " << valor << endl;
                break;
            }
            case 5: {
                int fila, col;
                T valor;
                cout << "Fila: ";
                cin >> fila;
                cout << "Columna: ";
                cin >> col;
                cout << "Valor: ";
                cin >> valor;
                sim.establecerValor(fila, col, valor);
                cout << "Valor establecido en [" << fila << "," << col << "] = " << valor << endl;
                break;
            }
            case 6: {
                int nuevaF, nuevaC;
                cout << "Nuevas filas: ";
                cin >> nuevaF;
                cout << "Nuevas columnas: ";
                cin >> nuevaC;
                sim.redimensionarGrid(nuevaF, nuevaC);
                cout << "Grid redimensionado a " << nuevaF << "x" << nuevaC << ". Datos copiados." << endl;
                break;
            }
            case 7: {
                sim.mostrarFuentes();
                break;
            }
            case 8:
            case 9: {
                cout << "Cambiando tipo de simulador..." << endl;
                return;
            }
            case 0: {
                cout << "Liberando memoria del Grid y Fuentes... Sistema cerrado." << endl;
                break;
            }
            default: {
                cout << "Opcion no valida." << endl;
                break;
            }
        }
    } while(opcion != 0 && opcion != 8 && opcion != 9);
}

void ejecutarEjemploCompleto() {
    cout << "\n--- EJEMPLO COMPLETO DE DIFUSION ---" << endl;
    
    // Crear simulador float 5x5
    Simulador2D<float> simFloat(5, 5);
    
    cout << "\n>> Agregando Fuentes de Concentracion <<" << endl;
    simFloat.agregarFuente(100.0f);
    cout << "Agregar Fuente 1 (Valor 100.0): Éxito." << endl;
    simFloat.agregarFuente(50.0f);
    cout << "Agregar Fuente 2 (Valor 50.0): Éxito." << endl;
    
    cout << "\n>> Aplicando Valores Iniciales <<" << endl;
    simFloat.establecerValor(2, 2, 100.0f);
    cout << "Grid[2,2] = 100.0 (Fuente 1)" << endl;
    simFloat.establecerValor(4, 0, 50.0f);
    cout << "Grid[4,0] = 50.0 (Fuente 2)" << endl;
    
    cout << "\n--- Grid Inicial (Paso 0) ---" << endl;
    simFloat.mostrarGrid();
    
    cout << "\nOpcion: Simular 1 Paso" << endl;
    cout << "Simulando Propagacion..." << endl;
    simFloat.simularPaso();
    
    cout << "\n--- Grid Después del Paso 1 ---" << endl;
    simFloat.mostrarGrid();
    
    cout << "\nOpcion: Redimensionar" << endl;
    simFloat.redimensionarGrid(6, 6);
    cout << "Redimensionando Grid a 6x6. Datos copiados." << endl;
    
    cout << "\n--- Grid Redimensionado ---" << endl;
    simFloat.mostrarGrid();
}

void probarAmbostipos() {
    cout << "\n--- PRUEBA CON DIFERENTES TIPOS ---" << endl;
    
    // Simulador con enteros
    cout << "\n>> Simulador con ENTEROS <<" << endl;
    Simulador2D<int> simInt(3, 3);
    simInt.establecerValor(1, 1, 100);
    simInt.agregarFuente(100);
    simInt.agregarFuente(50);
    cout << "Grid inicial (INT):" << endl;
    simInt.mostrarGrid();
    simInt.simularPaso();
    cout << "Después de 1 paso:" << endl;
    simInt.mostrarGrid();
    
    // Simulador con flotantes
    cout << "\n>> Simulador con FLOTANTES <<" << endl;
    Simulador2D<float> simFloat(3, 3);
    simFloat.establecerValor(1, 1, 100.5f);
    simFloat.agregarFuente(100.5f);
    simFloat.agregarFuente(50.25f);
    cout << "Grid inicial (FLOAT):" << endl;
    simFloat.mostrarGrid();
    simFloat.simularPaso();
    cout << "Después de 1 paso:" << endl;
    simFloat.mostrarGrid();
}

int main() {
    cout << "=== SIMULADOR GENERICO DE FLUIDOS 2D (MODELADO FISICO) ===" << endl;
    
    int opcionPrincipal;
    
    do {
        cout << "\n=== MENU PRINCIPAL ===" << endl;
        cout << "1. Ejecutar ejemplo completo" << endl;
        cout << "2. Probar ambos tipos (INT y FLOAT)" << endl;
        cout << "3. Modo interactivo - Simulador FLOAT" << endl;
        cout << "4. Modo interactivo - Simulador INT" << endl;
        cout << "5. Probar constructor de copia" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcionPrincipal;
        
        switch(opcionPrincipal) {
            case 1: {
                ejecutarEjemploCompleto();
                break;
            }
            case 2: {
                probarAmbostipos();
                break;
            }
            case 3: {
                Simulador2D<float> simFloat(5, 5);
                demostrarSimulador(simFloat, "FLOAT");
                break;
            }
            case 4: {
                Simulador2D<int> simInt(5, 5);
                demostrarSimulador(simInt, "INT");
                break;
            }
            case 5: {
                cout << "\n--- PRUEBA DE CONSTRUCTOR DE COPIA ---" << endl;
                Simulador2D<float> original(3, 3);
                original.establecerValor(1, 1, 42.5f);
                original.agregarFuente(42.5f);
                
                cout << "Simulador original:" << endl;
                original.mostrarGrid();
                
                Simulador2D<float> copia(original);
                cout << "Simulador copiado:" << endl;
                copia.mostrarGrid();
                
                cout << "Modificando original..." << endl;
                original.establecerValor(0, 0, 99.9f);
                
                cout << "Original modificado:" << endl;
                original.mostrarGrid();
                cout << "Copia (debe mantenerse igual):" << endl;
                copia.mostrarGrid();
                break;
            }
            case 0: {
                cout << "Gracias por usar el Simulador 2D!" << endl;
                break;
            }
            default: {
                cout << "Opcion no valida." << endl;
                break;
            }
        }
    } while(opcionPrincipal != 0);
    
    return 0;
}