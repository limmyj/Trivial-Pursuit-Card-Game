#ifndef ARRAY_HEADER
#define ARRAY_HEADER

#include <string>
using namespace std;

const int MAX_ROUNDS = 3; // Maximum number of rounds
const int LEADERBOARD_CAPACITY = 10;

struct LeaderboardEntry {
    string name;
    string questions[MAX_ROUNDS]; // Array to store questions for each round
    int scores[MAX_ROUNDS]; // Array to store scores for each round
    int totalScore;

    // Constructor to initialize arrays
    LeaderboardEntry() : totalScore(0) {
        for (int i = 0; i < MAX_ROUNDS; ++i) {
            questions[i] = ""; // Initialize questions with empty strings
            scores[i] = 0; // Initialize scores with 0
        }
    }
};

// Forward declaration
class Leaderboard;

// Declaration of the Quiz class
class Leaderboard {
private:

    LeaderboardEntry leaderboard[LEADERBOARD_CAPACITY];
    int leaderboardSize;

public:
    Leaderboard();

    void addToLeaderboard(const string& name, const string& question, int score, int totalScore);
    // Function to display the leaderboard
    void displayLeaderboard() const;
    void searchTopicsByKeyword(const string& keyword, const LeaderboardEntry leaderboard[], int leaderboardSize);
    LeaderboardEntry searchStudentByName(const string& name, const LeaderboardEntry leaderboard[], int leaderboardSize);
    void sortLeaderboardByTotalScore(LeaderboardEntry leaderboard[], int leaderboardSize);
    void displaySortedLeaderboard() const;

    const LeaderboardEntry* getLeaderboard() const {
        return leaderboard;
    }
    int getLeaderboardSize() const {
        return leaderboardSize;
    }
    LeaderboardEntry* getLeaderboard() {
        return leaderboard;
    }
};

#endif // ARRAY_HEADER
