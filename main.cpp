#include <iostream>
#include <string>

using std::string;

void Write(const string& texto);
void Write(const char* texto);
void Write(int numero);
void Write(char caracter);

void WriteLine();
void WriteLine(const string& texto);
void WriteLine(const char* texto);
void WriteLine(int numero);
void WriteLine(char caracter);

int main()
{
    const int mundo[10][10] = { 0 };

    WriteLine("Matriz del Mundo de Wumpus creada (10x10)");
    WriteLine();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            Write(mundo[i][j]);
            Write(" ");
        }

        WriteLine();
    }

    return 0;
}

void Write(const string& texto)
{
    std::cout << texto;
}

void Write(const char* texto)
{
    std::cout << texto;
}

void Write(int numero)
{
    std::cout << numero;
}

void Write(char caracter)
{
    std::cout << caracter;
}

void WriteLine()
{
    std::cout << "\n";
}

void WriteLine(const string& texto)
{
    std::cout << texto << "\n";
}

void WriteLine(const char* texto)
{
    std::cout << texto << "\n";
}

void WriteLine(int numero)
{
    std::cout << numero << "\n";
}

void WriteLine(char caracter)
{
    std::cout << caracter << "\n";
}