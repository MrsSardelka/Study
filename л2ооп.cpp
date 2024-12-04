#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Game {
    string title;
    string genre;
    string platform;
    int year;
    string developer;
    int players;
    int min_cpu;
    int min_ram;
    int min_hdd;
};

void addGame(vector<Game*>& games) {
    Game* game = new Game;
    cout << "Enter game title: ";
    cin.ignore();
    getline(cin, game->title);
    cout << "Enter game genre: ";
    getline(cin, game->genre);
    cout << "Enter game platform: ";
    getline(cin, game->platform);
    cout << "Enter game release year: ";
    cin >> game->year;
    cout << "Enter game developer: ";
    cin.ignore();
    getline(cin, game->developer);
    cout << "Enter number of players: ";
    cin >> game->players;
    cout << "Enter minimum CPU frequency (in MHz): ";
    cin >> game->min_cpu;
    cout << "Enter minimum RAM (in MB): ";
    cin >> game->min_ram;
    cout << "Enter minimum HDD space (in MB): ";
    cin >> game->min_hdd;
    games.push_back(game);
}

void displayGames(const vector<Game*>& games) {
    for (const auto& game : games) {
        cout << "Title: " << game->title << "\n";
        cout << "Genre: " << game->genre << "\n";
        cout << "Platform: " << game->platform << "\n";
        cout << "Year: " << game->year << "\n";
        cout << "Developer: " << game->developer << "\n";
        cout << "Players: " << game->players << "\n";
        cout << "Min CPU: " << game->min_cpu << " MHz\n";
        cout << "Min RAM: " << game->min_ram << " MB\n";
        cout << "Min HDD: " << game->min_hdd << " MB\n";
        cout << "------------------------\n";
    }
}

void findGameByGenre(const vector<Game*>& games) {
    string genre;
    cout << "Enter genre to search: ";
    cin.ignore();
    getline(cin, genre);
    Game* selected_game = nullptr;
    for (const auto& game : games) {
        if (game->genre == genre) {
            if (selected_game == nullptr || game->min_ram < selected_game->min_ram) {
                selected_game = game;
            }
        }
    }
    if (selected_game) {
        cout << "The game with the lowest RAM requirement in the genre " << genre << " is " << selected_game->title << "\n";
    }
    else {
        cout << "No games found for the genre " << genre << "\n";
    }
}

void gamesForComputer(const vector<Game*>& games) {
    int cpu, ram, hdd;
    cout << "Enter CPU frequency (in MHz): ";
    cin >> cpu;
    cout << "Enter RAM size (in MB): ";
    cin >> ram;
    cout << "Enter HDD space (in MB): ";
    cin >> hdd;
    bool found = false;
    for (const auto& game : games) {
        if ((game->min_cpu <= cpu) && (game->min_ram <= ram) && (game->min_hdd <= hdd)) {
            cout << game->title << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No games can be installed on the computer with the given specifications\n";
    }
}

void findGameByGenreFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << "\n";
        return;
    }

    string genre;
    cout << "Enter genre to search: ";
    cin.ignore();
    getline(cin, genre);

    int num_games;
    file >> num_games;
    file.ignore();

    Game* selected_game = nullptr;
    for (int i = 0; i < num_games; ++i) {
        Game game;
        getline(file, game.title);
        getline(file, game.genre);
        getline(file, game.platform);
        file >> game.year;
        file.ignore();
        getline(file, game.developer);
        file >> game.players;
        file >> game.min_cpu;
        file >> game.min_ram;
        file >> game.min_hdd;
        file.ignore();

        if (game.genre == genre) {
            if (selected_game == nullptr || game.min_ram < selected_game->min_ram) {
                if (selected_game == nullptr) {
                    selected_game = new Game;
                }
                *selected_game = game;
            }
        }
    }

    if (selected_game) {
        cout << "The game with the lowest RAM requirement in the genre " << genre << " is " << selected_game->title << "\n";
        delete selected_game;
    }
    else {
        cout << "No games found for the genre " << genre << "\n";
    }

    file.close();
}

void saveGamesToFile(const vector<Game*>& games, const string& filename) {
    // Открыть файл в режиме добавления
    ofstream outFile(filename, std::ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (const Game* game : games) {
        outFile << game->title << endl;
        outFile << game->genre << endl;
        outFile << game->platform << endl;
        outFile << game->year << endl;
        outFile << game->developer << endl;
        outFile << game->players << endl;
        outFile << game->min_cpu << endl;
        outFile << game->min_ram << endl;
        outFile << game->min_hdd << endl;
    }

    outFile.close();
    cout << "Games saved to " << filename << " successfully." << endl;
}


void readGamesFromFile(const string& filename, vector<Game*>& games) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << "\n";
        return;
    }
    int num_games;
    file >> num_games;
    file.ignore();
    for (int i = 0; i < num_games; ++i) {
        Game* game = new Game;
        getline(file, game->title);
        getline(file, game->genre);
        getline(file, game->platform);
        file >> game->year;
        file.ignore();
        getline(file, game->developer);
        file >> game->players;
        file >> game->min_cpu;
        file >> game->min_ram;
        file >> game->min_hdd;
        file.ignore();
        games.push_back(game);
    }
    file.close();
}

void displayGamesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file " << filename << "\n";
        return;
    }

    int num_games;
    file >> num_games;
    file.ignore();
    for (int i = 0; i < num_games; ++i) {
        Game game;
        getline(file, game.title);
        getline(file, game.genre);
        getline(file, game.platform);
        file >> game.year;
        file.ignore();
        getline(file, game.developer);
        file >> game.players;
        file >> game.min_cpu;
        file >> game.min_ram;
        file >> game.min_hdd;
        file.ignore();

        cout << "Title: " << game.title << "\n";
        cout << "Genre: " << game.genre << "\n";
        cout << "Platform: " << game.platform << "\n";
        cout << "Year: " << game.year << "\n";
        cout << "Developer: " << game.developer << "\n";
        cout << "Players: " << game.players << "\n";
        cout << "Min CPU: " << game.min_cpu << " MHz\n";
        cout << "Min RAM: " << game.min_ram << " MB\n";
        cout << "Min HDD: " << game.min_hdd << " MB\n";
        cout << "------------------------\n";
    }
    file.close();
}


int main() {
    vector<Game*> games;
    int choice;
    string filename = "games.txt";

    while (true) {
        cout << "1. Add game\n";
        cout << "2. Display games\n";
        cout << "3. Find game by genre with lowest RAM\n";
        cout << "4. Find games for a computer\n";
        cout << "5. Read games from file\n";
        cout << "6. Save games to file\n";
        cout << "7. Find game by genre in file\n";
        cout << "8. Display all games from file\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addGame(games);
            break;
        case 2:
            displayGames(games);
            break;
        case 3:
            findGameByGenre(games);
            break;
        case 4:
            gamesForComputer(games);
            break;
        case 5:
            readGamesFromFile(filename, games);
            break;
        case 6:
            saveGamesToFile(games, filename);
            break;
        case 7:
            findGameByGenreFromFile(filename);
            break;
        case 8:
            displayGamesFromFile(filename);
            break;
        case 9:
            for (auto game : games) {
                delete game;
            }
            return 0;
        default:
            cout << "Invalid choice\n";
        }
    }
    return 0;
}

//2 задание
//#include <iostream>
//#include <iomanip> // Для std::setprecision
//
//int main() {
//    double x = 123.456789;
//    std::cout << std::fixed << std::setprecision(2) << x << std::endl; // Вывод: 123.46
//    std::cout << std::scientific << x << std::endl; // Вывод: 1.234568e+02
//    return 0;
//}



//3 задание
//#include <iostream>
//#include <fstream>
//
//int main() {
//    std::ofstream outfile("example.txt");
//    outfile << "Hello, World!" << std::endl;
//    outfile.close();
//
//    std::ifstream infile("example.txt");
//    std::string line;
//    while (std::getline(infile, line)) {
//        std::cout << line << std::endl;
//    }
//    infile.close();
//    return 0;
//}


//4 задание
//#include <iostream>
//struct Point {
//    int x;
//    int y;
//};
//Point createPoint(int x, int y) {
//    Point p;
//    p.x = x;
//    p.y = y;
//    return p;
//}
//void printPoint(const Point& p) {
//    std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
//}
//int main() {
//    Point p1 = createPoint(10, 20);
//    printPoint(p1); // Вывод: (10, 20)
//    return 0;
//}

//8 задание
//#include <iostream>
//int main() {
//    int* arr = new int[5]; // Выделение динамического массива из 5 элементов
//    for (int i = 0; i < 5; ++i) {
//        arr[i] = i + 1; // Заполнение массива
//    }
//
//    for (int i = 0; i < 5; ++i) {
//        std::cout << arr[i] << " "; // Вывод элементов
//    }
//    std::cout << std::endl;
//
//    delete[] arr; // Освобождение памяти
//    return 0;
//}



