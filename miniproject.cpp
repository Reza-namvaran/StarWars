/*
 This game is developed by Mahdi Sadeghi => 40212358026 & Reza Namvaran => 40212358042
*/
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// functions declaration
void runGame();
void generateMap(string (&)[10][10], int (&)[2], int (&)[2], int, int);
void receiveInput(string (&)[10][10], int[], int (&)[2], int &, int &);
bool validateInput(char, string);
void gameOver(int, int);
void move(char, string (&)[10][10], int[], int (&)[2], int &);
void shot(char, string (&)[10][10], int (&)[2], int &);
void damage(int &);
string HealthBar(int &healthStatus);
bool isFilled(string[][10], int);

int main()
{
    runGame();
    return 0;
}

// runGame function is the root function of the game
void runGame()
{
    // map of game is defined here to be available in all of the program
    string map[10][10];
    // spaceshipPosition saves the first position of spaceship and currentPosition does the same but for the current moment
    int spaceshipPosition[2] = {-1, -1}, currentPosition[2] = {-1, 1}, score = 0, healthStatus = 3;
    // while enemy spaceships exist or health remains, game is running
    while (true)
    {
        generateMap(map, spaceshipPosition, currentPosition, score, healthStatus);
        // receive user inputs
        receiveInput(map, spaceshipPosition, currentPosition, healthStatus, score);
        // check the conditions of end game
        if (score == 10 || healthStatus == 0)
        {
            break;
        }
    }
    // show the result of game
    gameOver(score, healthStatus);
}

// generateMap creates map for the first time and generates random positions for spaceships and also updates game situation with any moves or shots
void generateMap(string (&map)[10][10], int (&spaceshipPosition)[2], int (&currentPosition)[2], int score, int healthStatus)
{
    string enemy = "*", spaceship = "^";
    // checking for generate new map or update map
    if (spaceshipPosition[0] == -1)
    {
        // generating random position for enemy spaceships
        srand(time(NULL));
        int random_x_position;
        int random_y_position;
        for (int i = 0; i < 10; i++)
        {
            // handling overwriting enemy spaceships and also checking for being empty at least one of spaces in each row
            do
            {
                random_x_position = rand() % 10;
                random_y_position = rand() % 10;
            } while (map[random_x_position][random_y_position] == enemy || isFilled(map, random_x_position));
            map[random_x_position][random_y_position] = enemy;
        }

        // generate position of user spaceship and checking for overwriting spaceships
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

    // show the map with spaceships,score and health bar
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

// receiveInput receives user inputs and checks them to be valid. At the end it calls move or shot function
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

// validateInput checks the user choices with the predefined options
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
            cout << "Your choice is invalid. You have to choose between `m` or `s` : ";
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
            cout << "Your choice is invalid. You have to choose between `w` or `s` or `a` or `d` : ";
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
            cout << "Your choice is invalid. You have to choose between `a` or `d` : ";
            return false;
        }
    }
}

// this functions show the result of game
void gameOver(int score, int healthStatus)
{
    if (score == 10)
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

/*
move function handles user spaceship moves
for each direction this function checks for existence and ability to do user choice
if user spaceship goes on any enemy spaceship positions it will be damaged
*/
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

/*
this function handles user spaceship shots
for each correct shot score will be increased
*/
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

// damage function decreases the health of user spaceship
void damage(int &healthStatus)
{
    healthStatus--;
}

// this function returns the health bar for print in console
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

// isFilled function checks a row of the map,if it has more than one empty space then it will returns true, else it will returns false
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