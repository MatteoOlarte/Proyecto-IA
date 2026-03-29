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
void PlacePlayer(int world[10][10][4]);
void PlaceEntity(int world[10][10][4], int value);
void AddPerception(int world[10][10][4], int row, int col, int perception);

string TrEntity(const int value);
string TrFeeling(const int feeling0, const int feeling1, const int feeling2);

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
    // srand(static_cast<unsigned>(time(nullptr)));

    int world[10][10][4] = { { {0} } };

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
                int entity = world[i][j][0];   
                int feeling0 = world[i][j][1];
                int feeling1 = world[i][j][2];
                int feeling2 = world[i][j][3];
                
                if (entity != 0) {
                    Write("[");
                    Write(TrEntity(entity));
                    Write("]");
                } 
                else if (feeling0 != 0 || feeling1 != 0 || feeling2 != 0) {
                    Write("[");
                    Write(TrFeeling(feeling0, feeling1, feeling2));
                    Write("]");
                }
                else {
                    Write("[⬛]");
                }
                
            }
            WriteLine();
        }


        WriteLine();
        Write("Agent at: row 9, column 0");
        WriteLine();

        WriteLine();
        Write("Enter command (W/A/S/D/Q): ");

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

string TrEntity(const int value)
{
    switch (value)
    {
        case PLAYER:    return "🐧";
        case WUMPUS:    return "👾";
        case PIT:       return "🕳️ ";
        case GOLD:      return "🪙 ";
        default:        return "⬛";
    }
}

string TrFeeling(const int feeling0, const int feeling1, const int feeling2)
{
    if (feeling0 == SCREAM) {
        return "☠️";
    }

    if (feeling1 != 0 && feeling2 != 0) {
        return "😱";
    }
    else {
        if (feeling1 == STENCH) {
            return "🤢";
        }
        if (feeling2 == BREEZE) {
            return "😨";
        }
    }

    return "🙂";
}

void PlacePlayer(int world[10][10][4])
{
    world[9][0][0] = PLAYER;
}

void PlaceEntity(int world[10][10][4], int value)
{
    int row, col;

    do {
        row = RandomInteger();
        col = RandomInteger();
    } while (world[row][col][0] != 0);   // Only avoid other ENTITIES (layer 0)

    world[row][col][0] = value;          // Place entity in layer 0

    // Add corresponding perceptions
    AddPerception(world, row, col, value);
}

void AddPerception(int world[10][10][4], int row, int col, int value)
{
    if (value == WUMPUS) {
        // Add STENCH (try to put in layers 2 or 3)
        if (row > 0)   world[row-1][col][2] = STENCH;   // or find free slot
        if (row < 9)   world[row+1][col][2] = STENCH;
        if (col > 0)   world[row][col-1][2] = STENCH;
        if (col < 9)   world[row][col+1][2] = STENCH;
    }
    else if (value == PIT) {
        // Add BREEZE
        if (row > 0)   world[row-1][col][3] = BREEZE;
        if (row < 9)   world[row+1][col][3] = BREEZE;
        if (col > 0)   world[row][col-1][3] = BREEZE;
        if (col < 9)   world[row][col+1][3] = BREEZE;
    }
    else if (value == GOLD) {
        // Add GLITTER (we can use layer 2 for example)
        world[row][col][2] = GLITTER;
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