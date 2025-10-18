#ifndef SIMULADOR2D_H
#define SIMULADOR2D_H

#include <iostream>
#include <iomanip>

template <typename T>
class Simulador2D {
private:
    // Matriz de la cuadrícula (Dinámica y Genérica)
    T **_grid;
    int _filas;
    int _columnas;

    // Vector de Fuentes (Dinámico y Genérico)
    T *_fuentes;
    int _numFuentes;
    int _capacidadFuentes;

    // Vector de Constantes (Estático)
    float _constantes[3]; // [0] = Coeficiente de Difusión, [1] = DeltaX, [2] = DeltaT

    // Métodos privados auxiliares
    void inicializarGrid();
    void liberarGrid();
    T** crearMatriz(int filas, int columnas);

public:
    // MÉTODOS PÚBLICOS OBLIGATORIOS:
    Simulador2D(int f, int c); // Constructor
    ~Simulador2D(); // Destructor
    
    // Constructor de copia
    Simulador2D(const Simulador2D<T>& otro);
    
    // Operador de asignación
    Simulador2D<T>& operator=(const Simulador2D<T>& otro);
    
    void redimensionarGrid(int nuevaF, int nuevaC);
    void agregarFuente(T valor); // Expansión manual del vector dinámico si es necesario
    void simularPaso(); // Implementación del algoritmo
    
    // Métodos de acceso y visualización
    void mostrarGrid() const;
    void establecerValor(int fila, int col, T valor);
    T obtenerValor(int fila, int col) const;
    void establecerConstantes(float coefDifusion, float deltaX, float deltaT);
    void mostrarFuentes() const;
    int obtenerFilas() const { return _filas; }
    int obtenerColumnas() const { return _columnas; }
    int obtenerNumFuentes() const { return _numFuentes; }
};

// IMPLEMENTACIÓN DE LA CLASE TEMPLATE

// Constructor
template <typename T>
Simulador2D<T>::Simulador2D(int f, int c) : _filas(f), _columnas(c), _numFuentes(0), _capacidadFuentes(2) {
    // Crear matriz dinámica
    _grid = crearMatriz(_filas, _columnas);
    inicializarGrid();
    
    // Crear vector dinámico de fuentes
    _fuentes = new T[_capacidadFuentes];
    
    // Inicializar constantes por defecto
    _constantes[0] = 0.1f; // Coeficiente de Difusión
    _constantes[1] = 1.0f; // DeltaX
    _constantes[2] = 0.1f; // DeltaT
}

// Destructor
template <typename T>
Simulador2D<T>::~Simulador2D() {
    liberarGrid();
    delete[] _fuentes;
}

// Constructor de copia
template <typename T>
Simulador2D<T>::Simulador2D(const Simulador2D<T>& otro) 
    : _filas(otro._filas), _columnas(otro._columnas), 
      _numFuentes(otro._numFuentes), _capacidadFuentes(otro._capacidadFuentes) {
    
    // Copiar matriz
    _grid = crearMatriz(_filas, _columnas);
    for (int i = 0; i < _filas; i++) {
        for (int j = 0; j < _columnas; j++) {
            _grid[i][j] = otro._grid[i][j];
        }
    }
    
    // Copiar vector de fuentes
    _fuentes = new T[_capacidadFuentes];
    for (int i = 0; i < _numFuentes; i++) {
        _fuentes[i] = otro._fuentes[i];
    }
    
    // Copiar constantes
    for (int i = 0; i < 3; i++) {
        _constantes[i] = otro._constantes[i];
    }
}

// Operador de asignación
template <typename T>
Simulador2D<T>& Simulador2D<T>::operator=(const Simulador2D<T>& otro) {
    if (this != &otro) {
        // Liberar memoria actual
        liberarGrid();
        delete[] _fuentes;
        
        // Copiar dimensiones
        _filas = otro._filas;
        _columnas = otro._columnas;
        _numFuentes = otro._numFuentes;
        _capacidadFuentes = otro._capacidadFuentes;
        
        // Copiar matriz
        _grid = crearMatriz(_filas, _columnas);
        for (int i = 0; i < _filas; i++) {
            for (int j = 0; j < _columnas; j++) {
                _grid[i][j] = otro._grid[i][j];
            }
        }
        
        // Copiar vector de fuentes
        _fuentes = new T[_capacidadFuentes];
        for (int i = 0; i < _numFuentes; i++) {
            _fuentes[i] = otro._fuentes[i];
        }
        
        // Copiar constantes
        for (int i = 0; i < 3; i++) {
            _constantes[i] = otro._constantes[i];
        }
    }
    return *this;
}

// Crear matriz dinámica
template <typename T>
T** Simulador2D<T>::crearMatriz(int filas, int columnas) {
    T** matriz = new T*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new T[columnas];
    }
    return matriz;
}

// Inicializar grid con valores cero
template <typename T>
void Simulador2D<T>::inicializarGrid() {
    for (int i = 0; i < _filas; i++) {
        for (int j = 0; j < _columnas; j++) {
            _grid[i][j] = T(0);
        }
    }
}

// Liberar memoria de la matriz
template <typename T>
void Simulador2D<T>::liberarGrid() {
    if (_grid != nullptr) {
        for (int i = 0; i < _filas; i++) {
            delete[] _grid[i];
        }
        delete[] _grid;
        _grid = nullptr;
    }
}

// Redimensionar grid
template <typename T>
void Simulador2D<T>::redimensionarGrid(int nuevaF, int nuevaC) {
    // Crear nueva matriz
    T** nuevaMatriz = crearMatriz(nuevaF, nuevaC);
    
    // Inicializar con ceros
    for (int i = 0; i < nuevaF; i++) {
        for (int j = 0; j < nuevaC; j++) {
            nuevaMatriz[i][j] = T(0);
        }
    }
    
    // Copiar datos existentes
    int filasACopiar = (nuevaF < _filas) ? nuevaF : _filas;
    int columnasACopiar = (nuevaC < _columnas) ? nuevaC : _columnas;
    
    for (int i = 0; i < filasACopiar; i++) {
        for (int j = 0; j < columnasACopiar; j++) {
            nuevaMatriz[i][j] = _grid[i][j];
        }
    }
    
    // Liberar matriz antigua
    liberarGrid();
    
    // Actualizar referencias
    _grid = nuevaMatriz;
    _filas = nuevaF;
    _columnas = nuevaC;
}

// Agregar fuente con expansión automática
template <typename T>
void Simulador2D<T>::agregarFuente(T valor) {
    // Verificar si necesitamos expandir el vector
    if (_numFuentes >= _capacidadFuentes) {
        // Duplicar capacidad
        int nuevaCapacidad = _capacidadFuentes * 2;
        T* nuevoVector = new T[nuevaCapacidad];
        
        // Copiar datos existentes
        for (int i = 0; i < _numFuentes; i++) {
            nuevoVector[i] = _fuentes[i];
        }
        
        // Liberar vector antiguo
        delete[] _fuentes;
        
        // Actualizar referencias
        _fuentes = nuevoVector;
        _capacidadFuentes = nuevaCapacidad;
    }
    
    // Agregar nueva fuente
    _fuentes[_numFuentes] = valor;
    _numFuentes++;
}

// Simular un paso de difusión
template <typename T>
void Simulador2D<T>::simularPaso() {
    // Crear matriz temporal
    T** temp = crearMatriz(_filas, _columnas);
    
    // Inicializar matriz temporal copiando los valores actuales
    for (int i = 0; i < _filas; i++) {
        for (int j = 0; j < _columnas; j++) {
            temp[i][j] = _grid[i][j];
        }
    }
    
    // Aplicar algoritmo de difusión solo a celdas internas
    for (int i = 1; i < _filas - 1; i++) {
        for (int j = 1; j < _columnas - 1; j++) {
            // Promedio de los cuatro vecinos
            T suma = _grid[i-1][j] + _grid[i+1][j] + _grid[i][j-1] + _grid[i][j+1];
            temp[i][j] = suma / T(4);
        }
    }
    
    // Copiar resultados de vuelta a la matriz principal
    for (int i = 0; i < _filas; i++) {
        for (int j = 0; j < _columnas; j++) {
            _grid[i][j] = temp[i][j];
        }
    }
    
    // Liberar matriz temporal
    for (int i = 0; i < _filas; i++) {
        delete[] temp[i];
    }
    delete[] temp;
}

// Mostrar grid en consola
template <typename T>
void Simulador2D<T>::mostrarGrid() const {
    for (int i = 0; i < _filas; i++) {
        std::cout << "|";
        for (int j = 0; j < _columnas; j++) {
            std::cout << " " << std::setw(6) << std::fixed << std::setprecision(1) << _grid[i][j] << " |";
        }
        std::cout << std::endl;
    }
}

// Establecer valor en posición específica
template <typename T>
void Simulador2D<T>::establecerValor(int fila, int col, T valor) {
    if (fila >= 0 && fila < _filas && col >= 0 && col < _columnas) {
        _grid[fila][col] = valor;
    }
}

// Obtener valor de posición específica
template <typename T>
T Simulador2D<T>::obtenerValor(int fila, int col) const {
    if (fila >= 0 && fila < _filas && col >= 0 && col < _columnas) {
        return _grid[fila][col];
    }
    return T(0);
}

// Establecer constantes físicas
template <typename T>
void Simulador2D<T>::establecerConstantes(float coefDifusion, float deltaX, float deltaT) {
    _constantes[0] = coefDifusion;
    _constantes[1] = deltaX;
    _constantes[2] = deltaT;
}

// Mostrar fuentes
template <typename T>
void Simulador2D<T>::mostrarFuentes() const {
    std::cout << "Fuentes registradas (" << _numFuentes << "): ";
    for (int i = 0; i < _numFuentes; i++) {
        std::cout << _fuentes[i] << " ";
    }
    std::cout << std::endl;
}

#endif // SIMULADOR2D_H