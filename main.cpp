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

int RandomInteger();
void PlacePlayer(int world[10][10]);
void PlaceEntity(int world[10][10], int value);
void AddPerceptions(int world[10][10], int row, int col, int value);
string Tr(const int value);

const int PLAYER = 1;

const int WUMPUS = 20;
const int PIT = 30;
const int GOLD = 40;

const int STENCH = 200;
const int BREEZE = 300;
const int GLITTER = 400;
const int SCREAM = 1000;

int main()
{   
    srand(static_cast<unsigned>(time(nullptr)));

    int world[10][10] = { 0 };

    char input = ' ';

    bool running = true;

    PlacePlayer(world);

    PlaceEntity(world, GOLD);

    for (int i = 0; i < 2; i++) {
        PlaceEntity(world, WUMPUS);
    }

    for (int i = 0; i < 2; i++) {
        PlaceEntity(world, PIT);
    }

    while (running) {
        WriteLine("Mundo actual (10x10):");

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                const int value = world[i][j];
                Write("[");
                Write(Tr(value));
                Write("] ");
            }

            WriteLine();
        }

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                const int value = world[i][j];
                Write("[");
                Write(value);
                Write("] ");
            }

            WriteLine();
        }
        

        WriteLine();
        Write("Agente en: fila ");
        Write(9);
        Write(", columna ");
        WriteLine(0);

        WriteLine();
        Write("Ingrese comando (W/A/S/D/Q): ");

        std::cin >> input;
        input = toupper(input);

        if (input == 'Q') {
            WriteLine("¡Gracias por jugar! Saliendo...");
            running = false;
        } else if (input == 'W') {
            WriteLine("Moviendo hacia ARRIBA...");
        } else if (input == 'S') {
            WriteLine("Moviendo hacia ABAJO...");
        } else if (input == 'A') {
            WriteLine("Moviendo hacia IZQUIERDA...");
        } else if (input == 'D') {
            WriteLine("Moviendo hacia DERECHA...");
        } else {
            WriteLine("Comando inválido. Usa W/A/S/D o Q para salir.");
        }

        WriteLine("========================================");
        WriteLine();
    }

    return 0;
}

string Tr(const int value)
{
    switch (value)
    {
    case PLAYER:
        return "🐧";
    case WUMPUS:
        return "👾";
    case PIT:
        return "🕳️ ";
    case GOLD:
        return "🪙 ";
    case STENCH:
        return "🤢";
    case BREEZE:
        return "💀";
    case GLITTER:
        return "🪙 ";
    case GLITTER + GOLD:
        return "🪙 ";
    case SCREAM:
        return "⬛";
    default:
        return "⬛";
    }
}

void PlacePlayer(int world[10][10])
{
    world[9][0] = PLAYER;
}

void PlaceEntity(int world[10][10], int value)
{
    int row, col;

    do {
        row = RandomInteger();
        col = RandomInteger();
    } while (
        world[row][col] != 0 && 
        world[row][col] != STENCH && 
        world[row][col] != BREEZE && 
        world[row][col] != GLITTER
    );

    world[row][col] = value;

    AddPerceptions(world, row, col, value);
}

void AddPerceptions(int world[10][10], int row, int col, int value)
{
    if (value == WUMPUS) {
        if (row > 0)   world[row-1][col] += STENCH;
        if (row < 9)   world[row+1][col] += STENCH;
        if (col > 0)   world[row][col-1] += STENCH;
        if (col < 9)   world[row][col+1] += STENCH;
    }
    else if (value == PIT) {
        if (row > 0)   world[row-1][col] += BREEZE;
        if (row < 9)   world[row+1][col] += BREEZE;
        if (col > 0)   world[row][col-1] += BREEZE;
        if (col < 9)   world[row][col+1] += BREEZE;
    }
    else if (value == GOLD) {
        world[row][col] += GLITTER;
    }
}

int RandomInteger()
{
    return rand() % 10;
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