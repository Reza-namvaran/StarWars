#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void runGame();
void generateMap(string (&)[10][10], int (&)[2], int (&)[2], int, int, int);
void receiveInput(string (&)[10][10], int[], int (&)[2], int &, int &);
bool validateInput(char, string);
void gameOver(int, int, int);
void move(char, string (&)[10][10], int[], int (&)[2], int &);
void shot(char, string (&)[10][10], int (&)[2], int &);
void damage(int &);
string HealthBar(int &healthStatus);
string throwError(string);
bool isFilled(string[][10], int);
int generateCountOfEnemy();

int main()
{
    runGame();
    return 0;
}

void runGame()
{
    string map[10][10];
    int spaceshipPosition[2] = {-1, -1}, currentPosition[2] = {-1, 1}, enemyCounter = generateCountOfEnemy(), score = 0, healthStatus = 3;
    while (true)
    {
        generateMap(map, spaceshipPosition, currentPosition, enemyCounter, score, healthStatus);
        receiveInput(map, spaceshipPosition, currentPosition, healthStatus, score);
        if (score == enemyCounter || healthStatus == 0)
        {
            break;
        }
    }
    gameOver(score, healthStatus, enemyCounter);
}

void generateMap(string (&map)[10][10], int (&spaceshipPosition)[2], int (&currentPosition)[2], int enemyCounter, int score, int healthStatus)
{
    string enemy = "*", spaceship = "^";
    if (spaceshipPosition[0] == -1)
    {
        srand(time(NULL));
        int random_x_position;
        int random_y_position;
        for (int i = 0; i < enemyCounter; i++)
        {
            do
            {
                random_x_position = rand() % 10;
                random_y_position = rand() % 10;
            } while (map[random_x_position][random_y_position] == enemy || isFilled(map, random_x_position));
            map[random_x_position][random_y_position] = enemy;
        }

        do
        {
            random_x_position = rand() % 10;
            random_y_position = rand() % 10;
            map[random_x_position][random_y_position] = spaceship;
            spaceshipPosition[0] = random_x_position;
            spaceshipPosition[1] = random_y_position;
            currentPosition[0] = spaceshipPosition[0];
            currentPosition[1] = spaceshipPosition[1];
        } while (map[random_x_position][random_y_position] == enemy);
    }
    else
    {
        system("cls");
    }

    cout << "Score: " << score << endl;
    cout << HealthBar(healthStatus) << endl;

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

void receiveInput(string (&map)[10][10], int spaceshipPosition[], int (&currentPosition)[2], int &healthStatus, int &score)
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
        move(userInput, map, spaceshipPosition, currentPosition, healthStatus);
    }
    else
    {
        cout << "Choose your move ( a => Shot left , d => Shot right ) : ";
        do
        {
            cin >> userInput;
        } while (!validateInput(userInput, "shot"));
        shot(userInput, map, currentPosition, score);
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

void gameOver(int score, int healthStatus, int enemyCounter)
{
    if (score == enemyCounter)
    {
        cout << "\n   \\\\      //\\\\      //  ||    ||\\\\      || \n";
        cout << "    \\\\    //  \\\\    //   ||    ||  \\\\    || \n";
        cout << "     \\\\  //    \\\\  //    ||    ||    \\\\  || \n";
        cout << "      \\\\//      \\\\//     ||    ||      \\\\|| \n\n";
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

void move(char direction, string (&map)[10][10], int spaceshipPosition[], int (&currentPosition)[2], int &healthStatus)
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
                    currentPosition[0] = i - 1;
                    currentPosition[1] = j;
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
                    currentPosition[0] = i + 1;
                    currentPosition[1] = j;
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
                    currentPosition[0] = i;
                    currentPosition[1] = j - 1;
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
                    currentPosition[0] = i;
                    currentPosition[1] = j + 1;
                    return;
                }
            }
        }
    }
}

void shot(char direction, string (&map)[10][10], int (&currentPosition)[2], int &score)
{
    switch (direction)
    {
    case 'a':
        for (int j = currentPosition[1]; j >= 0; j--)
        {
            if (map[currentPosition[0]][j] == "*")
            {
                map[currentPosition[0]][j] = " ";
                score++;
                return;
            }
        }
        break;
    case 'd':
        for (int j = currentPosition[1]; j <= 9; j++)
        {
            if (map[currentPosition[0]][j] == "*")
            {
                map[currentPosition[0]][j] = " ";
                score++;
                return;
            }
        }
        break;
    }
}

void damage(int &healthStatus)
{
    healthStatus--;
}

string HealthBar(int &healthStatus)
{
    string health = "Health: [   ";
    for (int i = 9; i <= healthStatus + 8; i++)
    {
        health.replace(i, healthStatus + 8, "*");
    }

    health += "]";
    return health;
}

string throwError(string errorMessage)
{
    return errorMessage;
}

bool isFilled(string map[][10], int row)
{
    int counter = 0;
    for (int j = 0; j < 10; j++)
    {
        if (map[row][j] == "*")
        {
            counter++;
        }
    }
    if (counter == 9)
    {
        return true;
    }
    return false;
}

int generateCountOfEnemy()
{
    int count = (rand() % 81) + 10;
    return count;
}