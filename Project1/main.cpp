#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

class RandomArray {
private:
    int size;
    std::string* array;

public:
    RandomArray(int size) {
        this->size = size;
        this->array = new std::string[size];
    }

    ~RandomArray() {
        delete[] array;
    }

    void readElements() {
        std::string input;
        for (int i = 0; i < size; i++) {
            std::cout << "Podaj " << i + 1 << " element: ";
            std::cin >> input;
            array[i] = input;
        }
    }

    void printRandomElement() {
        srand(time(0));
        int randomIndex = rand() % size;
        std::string variable = array[randomIndex];
        std::cout << "Losowy element: " << variable << std::endl;
    }

    void printAllElements() {
        std::cout << "Wszystkie elementy: ";
        for (int i = 0; i < size; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int x = 0;
    std::cout << "Podaj rozmiar tablicy: ";
    std::cin >> x;

    RandomArray randomArray(x);
    randomArray.readElements();
    randomArray.printRandomElement();
    randomArray.printAllElements();

    return 0;
}
