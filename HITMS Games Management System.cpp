#include <iostream>
#include <string>

using namespace std;

struct Player {
    string name;
    int id;
    int score;
    

    Player(int playerId, string playerName) {
        id = playerId;
        name = playerName;
        score = 0;
    }
};

struct Match {
    int matchID;
    Player* player1;
    Player* player2;
    int score1;
    int score2;

    
    Match(int id, Player* p1, Player* p2) {
        matchID = id;
        player1 = p1;
        player2 = p2;
        score1 = 0;
        score2 = 0;
    }
};

class GameManagementSystem {
private:
    Player** players;
    Match** matches;
    int playerCount = 0;
    int matchCount = 0;

public:
    GameManagementSystem() {
        players = NULL;
        matches = NULL;
    }

    
    void registerPlayer() {
        int id;
        string name;

        cout << "Enter Player ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Player Name: ";
        getline(cin, name);

       
        Player* newPlayer = new Player(id, name);

        
        Player** temp = new Player*[playerCount + 1];
        for (int i = 0; i < playerCount; ++i) {
            temp[i] = players[i];
        }
        temp[playerCount++] = newPlayer;

        delete[] players;
        players = temp;

        cout << "Player registered: " << newPlayer->name << endl;
    }

    
    void scheduleMatch() {
        if (playerCount < 2) {
            cout << "At least 2 players needed to schedule a match.\n";
            return;
        }

        int matchID, p1ID, p2ID;
        cout << "Enter Match ID: ";
        cin >> matchID;
        cout << "Enter Player 1 ID: ";
        cin >> p1ID;
        cout << "Enter Player 2 ID: ";
        cin >> p2ID;

        Player* p1 = NULL;
        Player* p2 = NULL;
        for (int i = 0; i < playerCount; ++i) {
            if (players[i]->id == p1ID) p1 = players[i];
            if (players[i]->id == p2ID) p2 = players[i];
        }

        if (!p1 || !p2) {
            cout << "Invalid Player IDs.\n";
            return;
        }

        Match* newMatch = new Match(matchID, p1, p2);

        
        Match** temp = new Match*[matchCount + 1];
        for (int i = 0; i < matchCount; ++i) {
            temp[i] = matches[i];
        }
        temp[matchCount++] = newMatch;

        delete[] matches;
        matches = temp;

        cout << "Match scheduled between " << p1->name << " and " << p2->name << endl;
    }

   
    void updateScore() {
        int matchID;
        cout << "Enter Match ID to update score: ";
        cin >> matchID;

        Match* match = NULL;
        for (int i = 0; i < matchCount; ++i) {
            if (matches[i]->matchID == matchID) {
                match = matches[i];
                break;
            }
        }

        if (!match) {
            cout << "Match not found!\n";
            return;
        }

        cout << "Enter Score for " << match->player1->name << ": ";
        cin >> match->score1;
        cout << "Enter Score for " << match->player2->name << ": ";
        cin >> match->score2;

        match->player1->score += match->score1;
        match->player2->score += match->score2;

        cout << "Scores updated.\n";
    }

    
    void displayLeaderboard() {
        cout << "\nLeaderboard:\n";
        for (int i = 0; i < playerCount; ++i) {
            for (int j = i + 1; j < playerCount; ++j) {
                if (players[i]->score < players[j]->score) {
                    swap(players[i], players[j]);
                }
            }
        }

        for (int i = 0; i < playerCount; ++i) {
            cout << "ID: " << players[i]->id << " | " << players[i]->name
                 << " | Score: " << players[i]->score << endl;
        }
    }

    
    void generateReport() {
        cout << "\nPerformance Report:\n";
        for (int i = 0; i < matchCount; ++i) {
            cout << "Match " << matches[i]->matchID << ": "
                 << matches[i]->player1->name << " (" << matches[i]->score1 << ") vs "
                 << matches[i]->player2->name << " (" << matches[i]->score2 << ")\n";
        }
    }

   
    ~GameManagementSystem() {
        for (int i = 0; i < playerCount; ++i) delete players[i];
        delete[] players;
        for (int i = 0; i < matchCount; ++i) delete matches[i];
        delete[] matches;
    }
};

int main() {
    GameManagementSystem system;
    int choice;

    do {
        cout << "\nHITMS Games Management System\n";
        cout << "1. Register Player\n";
        cout << "2. Schedule Match\n";
        cout << "3. Update Match Score\n";
        cout << "4. Display Leaderboard\n";
        cout << "5. Generate Report\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.registerPlayer(); break;
            case 2: system.scheduleMatch(); break;
            case 3: system.updateScore(); break;
            case 4: system.displayLeaderboard(); break;
            case 5: system.generateReport(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n"; break;
        }
    } while (choice != 6);

    return 0;
}

