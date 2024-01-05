#include <iostream>
#include <ctime>

using namespace std;

void runGame();
void generateMap(string (&)[10][10], int (&)[2], bool &, int, int);
void receiveInput(string (&)[10][10], int[], int &, int &);
bool validateInput(char, string);
void gameOver(int, int);
void move(char, string (&)[10][10], int[], int &);
void shot(char, string (&)[10][10], int &);
void damage(int &);
string throwError(string);

int main()
{
    runGame();
    return 0;
}

void runGame()
{
    string map[10][10];
    int spaceshipPosition[2] = {-1, -1}, winnerStatus = 10, healthStatus = 3;
    bool isGameRunning = true;
    while (isGameRunning)
    {
        generateMap(map, spaceshipPosition, isGameRunning, winnerStatus, healthStatus);
        receiveInput(map, spaceshipPosition, healthStatus, winnerStatus);
    }
    gameOver(winnerStatus, healthStatus);
}

void generateMap(string (&map)[10][10], int (&spaceshipPosition)[2], bool &isGameRunning, int winnerStatus, int healthStatus)
{
    string enemy = "*", spaceship = "^";
    if (spaceshipPosition[0] == -1)
    {
        srand(time(NULL));
        int random_x_position;
        int random_y_position;
        for (int i = 0; i < 10; i++)
        {
            do
            {
                random_x_position = rand() % 10;
                random_y_position = rand() % 10;
            } while (map[random_x_position][random_y_position] == enemy);
            map[random_x_position][random_y_position] = enemy;
        }

        do
        {
            random_x_position = rand() % 10;
            random_y_position = rand() % 10;
            map[random_x_position][random_y_position] = spaceship;
            spaceshipPosition[0] = random_x_position;
            spaceshipPosition[1] = random_y_position;
        } while (map[random_x_position][random_y_position] == enemy);
    }
    else
    {
        system("cls");
        if (winnerStatus == 0 || healthStatus == 0)
        {
            isGameRunning = false;
            return;
        }
    }
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << " ---";
        }

        cout << endl;

        if (i == 10)
            continue;

        for (int k = 0; k < 10; k++)
        {
            if (map[i][k] == enemy || map[i][k] == spaceship)
            {
                cout << "| " << map[i][k] << " ";
            }
            else
            {
                cout << "|   ";
            }
            if (k == 9)
            {
                cout << "|";
            }
        }
        cout << endl;
    }
}

void receiveInput(string (&map)[10][10], int spaceshipPosition[], int &healthStatus, int &winnerStatus)
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
        move(userInput, map, spaceshipPosition, healthStatus);
    }
    else
    {
        cout << "Choose your move ( a => Go left , d => Go right ) : ";
        do
        {
            cin >> userInput;
        } while (!validateInput(userInput, "shot"));
        shot(userInput, map, winnerStatus);
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
            cout << throwError("Your choice is invalid. You have to choose between `m` or `s` : ");
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
            cout << throwError("Your choice is invalid. You have to choose between `w` or `s` or `a` or `d` : ");
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
            cout << throwError("Your choice is invalid. You have to choose between `a` or `d` : ");
            return false;
        }
    }
}

void gameOver(int winnerStatus, int healthStatus)
{
    if (winnerStatus == 0)
    {
        cout << "\n   \\\\      //\\\\      //  ||     //\\\\      // \n";
        cout << "    \\\\    //  \\\\    //   ||    //  \\\\    // \n";
        cout << "     \\\\  //    \\\\  //    ||   //    \\\\  // \n";
        cout << "      \\\\//      \\\\//     ||  //      \\\\// \n\n";
    }
    else if (healthStatus == 0)
    {
        cout << "\n   ||             //||||||\\\\       ///|||||\\\\\\    ||\\\\\\\\\\\\\\\\\\\\\n";
        cout << "   ||            ||        ||      \\\\       //    ||\n";
        cout << "   ||            ||        ||         \\\\          ||\\\\\\\\\\\\\\\\\\\\\n";
        cout << "   ||            ||        ||    //       \\\\      ||\n";
        cout << "   ||\\\\\\\\\\\\\\\\\\    \\\\||||||//     \\\\\\|||||///      ||\\\\\\\\\\\\\\\\\\\\\n\n";
    }
}

void move(char direction, string (&map)[10][10], int spaceshipPosition[], int &healthStatus)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == "^")
            {
                if (direction == 'w')
                {
                    if (i == 0)
                    {
                        return;
                    }
                    else if (map[i - 1][j] == "*")
                    {
                        map[i][j] = "";
                        map[spaceshipPosition[0]][spaceshipPosition[1]] = "^";
                        damage(healthStatus);
                        return;
                    }
                    map[i][j] = "";
                    map[i - 1][j] = "^";
                    return;
                }
                else if (direction == 's')
                {
                    if (i == 9)
                    {
                        return;
                    }
                    else if (map[i + 1][j] == "*")
                    {
                        map[i][j] = "";
                        map[spaceshipPosition[0]][spaceshipPosition[1]] = "^";
                        damage(healthStatus);
                        return;
                    }
                    map[i][j] = "";
                    map[i + 1][j] = "^";
                    return;
                }
                else if (direction == 'a')
                {
                    if (j == 0)
                    {
                        return;
                    }
                    else if (map[i][j - 1] == "*")
                    {
                        map[i][j] = "";
                        map[spaceshipPosition[0]][spaceshipPosition[1]] = "^";
                        damage(healthStatus);
                        return;
                    }
                    map[i][j] = "";
                    map[i][j - 1] = "^";
                    return;
                }
                else
                {
                    if (j == 9)
                    {
                        return;
                    }
                    else if (map[i][j + 1] == "*")
                    {
                        map[i][j] = "";
                        map[spaceshipPosition[0]][spaceshipPosition[1]] = "^";
                        damage(healthStatus);
                        return;
                    }
                    map[i][j] = "";
                    map[i][j + 1] = "^";
                    return;
                }
            }
        }
    }
}

void shot(char direction, string (&map)[10][10], int &winnerStatus) {}

void damage(int &healthStatus) {}

string throwError(string errorMessage)
{
    return errorMessage;
}