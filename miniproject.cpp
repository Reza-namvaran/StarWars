#include <iostream>

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
    } while (!validateInput(userInput));
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

bool validateInput(char userInput, string status = "firstChoice")
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

void createGame() {}

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