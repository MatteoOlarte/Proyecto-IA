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

string TrEntity(const int value);
string TrFeeling(const int feeling0, const int feeling1, const int feeling2);

int RandomInteger();
void PlacePlayer();
void PlaceEntity(int value);
void AddPerception(int row, int col, int perception);
void MovePlayerTo(int newRow, int newCol);
int CheckGameStatus();
string GetAgentWarning();

const bool DEBUG = true;

const int ENTITY_PLAYER = 1;
const int ENTITY_WUMPUS = 2;
const int ENTITY_PIT = 3;
const int ENTITY_GOLD = 4;

const int STENCH = 5;
const int BREEZE = 6;
const int GLITTER = 7;
const int SCREAM = 8;

// GAME STATUS CONSTANTS
const int GAME_CONTINUE = 0;
const int GAME_LOST     = 1;
const int GAME_WON      = 2;
const int GAME_QUIT     = 3;

// moved to global scope for easier access in all functions
int world[10][10][5] = { { {0} } };
int agentRow = 9;
int agentCol = 0;

int main()
{   
	srand(static_cast<unsigned>(time(nullptr)));

	char input = ' ';

	bool running = true;

	PlacePlayer();

	PlaceEntity(ENTITY_GOLD);

	for (int i = 0; i < 2; i++) {
		PlaceEntity(ENTITY_WUMPUS);
	}

	for (int i = 0; i < 2; i++) {
		PlaceEntity(ENTITY_PIT);
	}

	while (running) {
		int status = CheckGameStatus();
		string warning = GetAgentWarning();

		WriteLine("Mundo actual (10x10):");

		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				int player = world[i][j][0];
				int entity = world[i][j][1];   
				int feeling0 = world[i][j][2];
				int feeling1 = world[i][j][3];
				int feeling2 = world[i][j][4];
				
				if (player != 0) {
					Write("[");
					Write(TrEntity(player));
					Write("]");
				}
				else if (entity != 0) {
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

		if (status == GAME_LOST) {
			WriteLine("*** GAME OVER - You died! ***");
			running = false;
			continue;
		}
		else if (status == GAME_WON) {
			WriteLine("*** YOU WIN! You found the gold! ***");
			running = false;
			continue;
		}
		
		WriteLine();
		Write("Agent at: row 9, column 0");
		WriteLine();
        if (warning != "") {
            WriteLine(warning);
        }

		WriteLine();
		Write("Enter command (W/A/S/D/Q): ");

		std::cin >> input;
		input = toupper(input);

		if (input == 'Q') {
			WriteLine("¡Gracias por jugar! Saliendo...");
			running = false;
		} else if (input == 'W') {
			MovePlayerTo(agentRow - 1, agentCol);
		} else if (input == 'S') {
			MovePlayerTo(agentRow + 1, agentCol);
		} else if (input == 'A') {
			MovePlayerTo(agentRow, agentCol - 1);
		} else if (input == 'D') {
			MovePlayerTo(agentRow, agentCol + 1);
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
	if (!DEBUG) {
		switch (value)
		{
			case ENTITY_PLAYER:    return "🐧";
			default:        return "⬛";
		}
	}

	switch (value)
	{
		case ENTITY_PLAYER:    return "🐧";
		case ENTITY_WUMPUS:    return "👾";
		case ENTITY_PIT:       return "🕳️ ";
		case ENTITY_GOLD:      return "🪙 ";
		default:        return "⬛";
	}
}

string TrFeeling(const int feeling0, const int feeling1, const int feeling2)
{
	if (!DEBUG) {
		return "⬛";
	}

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

string GetAgentWarning()
{
    // Layer 1 = Entity (Wumpus, Pit, Gold)
    int entity = world[agentRow][agentCol][1];

    // If player is on Gold → special win feeling (even before CheckGameStatus)
    if (entity == ENTITY_GOLD) {
        return "You see a bright GLITTER! The gold must be here!";
    }

    // Check feelings in layers 2, 3 and 4
    int f2 = world[agentRow][agentCol][2];
    int f3 = world[agentRow][agentCol][3];
    int f4 = world[agentRow][agentCol][4];

    // Multiple feelings at once
    if ((f2 != 0 && f3 != 0) || (f2 != 0 && f4 != 0) || (f3 != 0 && f4 != 0)) {
        return "You feel a strong mix of danger... something is very wrong here!";
    }

    // Single feelings
    if (f2 == STENCH || f3 == STENCH || f4 == STENCH) {
        return "You smell a terrible STENCH... the Wumpus is nearby!";
    }

    if (f2 == BREEZE || f3 == BREEZE || f4 == BREEZE) {
        return "You feel a cold BREEZE... there must be a pit close by!";
    }

    // No special feeling
    return "";
}

int CheckGameStatus()
{
	int current = world[agentRow][agentCol][1];

	if (current == ENTITY_WUMPUS || current == ENTITY_PIT) {
		return GAME_LOST;
	}

	if (current == ENTITY_GOLD) {
		return GAME_WON;
	}

	return GAME_CONTINUE;
}

void MovePlayerTo(int newRow, int newCol) {
	if (newRow < 0 || newRow > 9 || newCol < 0 || newCol > 9) {
		WriteLine("BUMP! You hit the wall.");
		return;
	}

	world[agentRow][agentCol][0] = 0;
	agentRow = newRow;
	agentCol = newCol;
	world[agentRow][agentCol][0] = ENTITY_PLAYER;
	Write("Moved to row ");
	Write(agentRow);
	Write(", column ");
	WriteLine(agentCol);
}

void PlacePlayer()
{
	world[9][0][0] = ENTITY_PLAYER;
}

void PlaceEntity(int value)
{
	int row, col;

	do {
		row = RandomInteger();
		col = RandomInteger();
	} while (world[row][col][0] != 0 || world[row][col][1] != 0);   // Only avoid other ENTITIES (layer 1 and 2)

	world[row][col][1] = value;          // Place entity in layer 1

	// Add corresponding perceptions
	AddPerception(row, col, value);
}

void AddPerception(int row, int col, int value)
{
	if (value == ENTITY_WUMPUS) {
		// Add STENCH (try to put in layers 3 or 4)
		if (row > 0)   world[row-1][col][3] = STENCH;   // or find free slot
		if (row < 9)   world[row+1][col][3] = STENCH;
		if (col > 0)   world[row][col-1][3] = STENCH;
		if (col < 9)   world[row][col+1][3] = STENCH;
	}
	else if (value == ENTITY_PIT) {
		// Add BREEZE
		if (row > 0)   world[row-1][col][4] = BREEZE;
		if (row < 9)   world[row+1][col][4] = BREEZE;
		if (col > 0)   world[row][col-1][4] = BREEZE;
		if (col < 9)   world[row][col+1][4] = BREEZE;
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