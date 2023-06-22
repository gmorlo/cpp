#include <iostream>
#include <cstdlib>

int main() {
    const char array[][10] = {"placek", "kokos", "poziomka", "arbuz"};

    int array_size = sizeof(array) / sizeof(array[0]);
    
    int randomIndex = rand() % array_size;
    
    const char* variable = array[randomIndex];

    std::cout << variable;
    return 0;
}
