#include <iostream>
#include "Kopiec.hpp"

int main() {
    int choice;
    int value;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add Elements\n";
        std::cout << "2. Pop Min\n";
        std::cout << "3. Delete Element\n";
        std::cout << "4. Size\n";
        std::cout << "5. Decrease Key\n";
        std::cout << "6. Top\n";
        std::cout << "7. Wizualizacja\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;


        switch (choice) {
            case 1:
                int input;
                int n;
                std::cout << "Podaj liczbe wezlow do dodania: ";
                cin>>n;
                std::cout << "Podaj wartosci kluczy dla wezlow: ";
                for(int i=0;i<n;i++){
                    cin>>input;
                    push(input);
                }
                cout<<endl;

                break;

            case 2:
                std::cout << "Popped Min: " << pop_min() << std::endl;
                break;

            case 3:
                std::cout << "Podaj wartosc klucza do usuniecia: ";
                std::cin >> value;
                del(value);
                std::cout << "Element zostal usuniety.\n";
                cout<<endl;
                break;

            case 4:
                std::cout << "Size of the heap: " << size() << std::endl;
                cout<<endl;

                break;

            case 5: {
                int keyToDecrease;
                int newValue;
                std::cout << "Podaj wartosc klucza do zmniejszenia: ";
                std::cin >> keyToDecrease;
                std::cout << "Podaj nowa wartosc klucza: ";
                std::cin >> newValue;

                Node *nodeToDecrease = find(keyToDecrease, minimum);

                if (nodeToDecrease != nullptr) {
                    decrease_key(nodeToDecrease, newValue);
                    std::cout << "Klucz zostal zmniejszony.\n";
                } else {
                    std::cout << "Nie znaleziono wezla o podanym kluczu.\n";
                }

                std::cout << std::endl;
                break;
            }

            case 6:
                std::cout << "Top element: " << top() << std::endl;
                cout<<endl;

                break;

            case 7:
                std::cout << "Visualisation" << std::endl;
                visualisation();

                cout<<endl;

                break;

            case 8:
                std::cout << "Exiting program.\n";
                break;
        }

    } while (choice != 8);

    return 0;
}
