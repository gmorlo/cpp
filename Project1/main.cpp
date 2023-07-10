#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    int x = 0;
    std::cout << "Podaj rozmiar tablicy: ";
    std::cin >> x;
    char array[x] = {}; // Zakładam maksymalną długość łańcucha jako 100
    char b;
    
    for (int i = 0; i < x; i++) {
        std::cout << "Podaj " << i + 1 << " element: ";
        std::cin >> array[i];
    }
    
    int array_size = sizeof(array) / sizeof(array[0]);
    
    srand(time(0));  // Inicjalizacja generatora liczb losowych na podstawie aktualnego czasu
    
    int randomIndex = rand() % array_size;
    
    char variable = array[randomIndex];

    std::cout << variable;
    return 0;
}
