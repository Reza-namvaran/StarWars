#include <iostream>
#include <ctime>

using namespace std;

void runGame();
void receiveInput();
bool validateInput(char, string);
void createGame();
void updateGame(bool *, string *);
void showGame();
void gameOver(string);
void move(char);
void shot(char);
void throwError(string);

int main()
{
    runGame();
    return 0;
}

void runGame()
{
    createGame();
    string winner;
    bool isGameRunning = true;
    while (isGameRunning)
    {
        receiveInput();
        updateGame(&isGameRunning, &winner);
    }
    gameOver(winner);
}

void receiveInput()
{
    char userInput;

    cout << "What would you like to do? ( m => move, s => shot ) : ";
    do
    {
        cin >> userInput;
    } while (!validateInput(userInput, "firstChoice"));
    userInput = tolower(userInput);

    if (userInput == 'm')
    {
        cout << "Choose your move ( w => Go up, s => Go down , a => Go left , d => Go right ) : ";
        do
        {
            cin >> userInput;
        } while (!validateInput(userInput, "move"));
        move(userInput);
    }
    else
    {
        cout << "Choose your move ( a => Go left , d => Go right ) : ";
        do
        {
            cin >> userInput;
        } while (!validateInput(userInput, "shot"));
        shot(userInput);
    }
}

bool validateInput(char userInput, string status)
{
    //  status value can be : "firstChoice" or "move" or "shot"
    userInput = tolower(userInput);
    if (status == "firstChoice")
    {
        if (userInput == 'm' || userInput == 's')
        {
            return true;
        }
        else
        {
            throwError("Your choice is invalid. You have to choose between `m` or `s` : ");
            return false;
        }
    }
    else if (status == "move")
    {
        if (userInput == 'w' || userInput == 's' || userInput == 'a' || userInput == 'd')
        {
            return true;
        }
        else
        {
            throwError("Your choice is invalid. You have to choose between `w` or `s` or `a` or `d` : ");
            return false;
        }
    }
    else
    {
        if (userInput == 'a' || userInput == 'd')
        {
            return true;
        }
        else
        {
            throwError("Your choice is invalid. You have to choose between `a` or `d` : ");
            return false;
        }
    }
}

void createGame() {
    string map[10][10], enemy = "*", spaceship = "^";
    
    srand(time(NULL));
    int random_x_position;
    int random_y_position;
    for (int i = 0; i < 10; i++){
        random_x_position = rand() % 10;
        random_y_position = rand() % 10;
        map[random_x_position][random_y_position] = enemy;
    }

    random_x_position = rand() % 10;
    random_y_position = rand() % 10;

    if (map[random_x_position][random_y_position] != enemy)
    {
        map[random_x_position][random_y_position] = spaceship;
    }

    for (int i = 0; i < 11; i++) {
        for ( int j = 0; j < 10; j++) {
            cout << " ---";
        }
        
        cout << endl;

        if (i == 10) continue;

        for (int k = 0; k < 10; k++) {
            if (map[i][k] == enemy || map[i][k] == spaceship) {
                cout << "| " << map[i][k] << " ";
            
            }
            else {
                cout << "|   ";
            }
            if (k == 9) {
                cout << "|";
            }

        }

        cout << endl;
    }

}

void updateGame(bool *isGameRunningPtr, string *winnerPtr)
{
    system("cls");
}

void showGame() {}

void gameOver(string winner) {}

void move(char direction) {}

void shot(char direction) {}

void throwError(string errorMessage)
{
    cout << errorMessage << endl;
}