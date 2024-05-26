#include <iostream>
#include <list>
#include <vector>

class MiClase {
public:
    std::vector<int*> listaPrueba;  // Vector para almacenar punteros a elementos

    void add(int& num) {
        listaPrueba.push_back(&num);  // Almacenar la dirección de num
    }

    void incrementarElementos() {
        for (auto elem : listaPrueba) {
            (*elem) += 1;  // Incrementar el valor apuntado por elem
        }
    }
};

int main() {
    std::list<int> miLista = {1, 2, 3, 4, 5};

    MiClase obj;

    for (auto& elem : miLista) {
        if (elem % 2 == 0) {
            obj.add(elem);
        }
    }

    obj.incrementarElementos();

    for (auto& elem : miLista) {
        std::cout << elem << " ";
    }

    return 0;
} ;[0y]
