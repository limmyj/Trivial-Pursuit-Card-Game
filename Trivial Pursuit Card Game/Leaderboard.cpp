#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Array.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

Leaderboard::Leaderboard() : leaderboardSize(0) 
{}


void Leaderboard::addToLeaderboard(const string& name, const string& question, int score, int totalScore) {
    // debugging cout << "addToLeaderboard called with name: " << name  << endl;
    // Search for an existing entry with the same name
    for (int i = 0; i < leaderboardSize; ++i) {
        if (leaderboard[i].name == name) {
            // Update the existing entry
            for (int j = 0; j < MAX_ROUNDS; ++j) {
                if (leaderboard[i].questions[j].empty()) {
                    leaderboard[i].questions[j] = question;
                    leaderboard[i].scores[j] = score;
                    leaderboard[i].totalScore += score;
                    cout << "Updated entry for " << name << " in the leaderboard." << endl;
                    return;
                }
            }
            // Handle the case where all rounds are filled
            cout << "All rounds are filled for " << name << ". Cannot add more questions." << endl;
            return;
        }
    }

    // If no existing entry is found, create a new entry
    if (leaderboardSize < LEADERBOARD_CAPACITY) { // Ensure there is space in the leaderboard
        LeaderboardEntry newEntry;
        newEntry.name = name;
        newEntry.questions[0] = question;
        newEntry.scores[0] = score;
        newEntry.totalScore = score;
        leaderboard[leaderboardSize++] = newEntry;
        cout << "Entry added to the leaderboard." << leaderboardSize  << endl;
    }
    else {
        cout << "Leaderboard is full. Cannot add more entries." << endl;
    }
}


// Function to truncate long questions and add ellipses
string truncateQuestion(const string& question, size_t maxLength) {
    if (question.length() > maxLength) {
        return question.substr(0, maxLength - 3) + "...";
    }
    return question;
}

// Function to display the leaderboard
void Leaderboard::displayLeaderboard() const {
    const size_t maxQuestionLength = 50; // Set the maximum length for a displayed question

    std::wcout << R"(
                                                                        _                    _           _                         _ 
                                                                       | |                  | |         | |                       | |
                                                                       | |     ___  __ _  __| | ___ _ __| |__   ___   __ _ _ __ __| |
                                                                       | |    / _ \/ _` |/ _` |/ _ \ '__| '_ \ / _ \ / _` | '__/ _` |
                                                                       | |___|  __/ (_| | (_| |  __/ |  | |_) | (_) | (_| | | | (_| |
                                                                       |______\___|\__,_|\__,_|\___|_|  |_.__/ \___/ \__,_|_|  \__,_|                                                    
)" << '\n';

    cout << "***************************************************************************************************************************************************************************************************************\n";
    cout << "Rank" << setw(10) << "Name"
        << setw(50) << "Round 1" << setw(50) << "Round 2"
        << setw(50) << "Round 3" << setw(40) << "Overall Score" << endl;
    cout << "***************************************************************************************************************************************************************************************************************\n";
    for (int i = 0; i < leaderboardSize; ++i) {
        cout << (i + 1) << "\t"; // Rank
        cout << setw(10) << left << leaderboard[i].name << "\t";

        for (int j = 0; j < MAX_ROUNDS; ++j) {
            string truncatedQuestion = truncateQuestion(leaderboard[i].questions[j], maxQuestionLength);
            cout << setw(55) << left << (truncatedQuestion + ": " + to_string(leaderboard[i].scores[j])) << "\t";
        }

        cout << setw(5) << left << "  " << leaderboard[i].totalScore << "\n";
    }
}

// Function to search for a specific student by name
LeaderboardEntry Leaderboard::searchStudentByName(const string& name, const LeaderboardEntry leaderboard[], int leaderboardSize) {
    for (int i = 0; i < leaderboardSize; ++i) {
        if (leaderboard[i].name == name) {
            return leaderboard[i]; // Return the LeaderboardEntry object
        }
    }
    // If the student is not found, return an empty LeaderboardEntry object
    return LeaderboardEntry();
}

// Function to search for topics or questions by keywords
void Leaderboard::searchTopicsByKeyword(const string& keyword, const LeaderboardEntry leaderboard[], int leaderboardSize) {
    for (int i = 0; i < leaderboardSize; ++i) {
        for (int j = 0; j < MAX_ROUNDS; ++j) {
            if (leaderboard[i].questions[j].find(keyword) != string::npos) {
                // Display relevant information (e.g., student name, question, score)
                cout << "Student: " << leaderboard[i].name << endl;
                cout << "Question: " << leaderboard[i].questions[j] << endl;
                cout << "Score: " << leaderboard[i].scores[j] << endl;
                cout << endl;
            }
        }
    }
}

// Comparison function to compare two leaderboard entries based on total score
bool compareByTotalScore(const LeaderboardEntry& a, const LeaderboardEntry& b) {
    return a.totalScore > b.totalScore; // Sort in descending order of total score
}

// Quicksort partition function
int partition(LeaderboardEntry leaderboard[], int low, int high) {
    LeaderboardEntry pivot = leaderboard[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (compareByTotalScore(leaderboard[j], pivot)) {
            ++i;
            swap(leaderboard[i], leaderboard[j]);
        }
    }
    swap(leaderboard[i + 1], leaderboard[high]);
    return i + 1;
}

// Quicksort recursive function
void quickSort(LeaderboardEntry leaderboard[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(leaderboard, low, high);
        quickSort(leaderboard, low, pivotIndex - 1);
        quickSort(leaderboard, pivotIndex + 1, high);
    }
}

// Function to sort the leaderboard based on total scores
void Leaderboard::sortLeaderboardByTotalScore(LeaderboardEntry leaderboard[], int leaderboardSize) {
    // Use quicksort to sort the leaderboard based on total scores
    quickSort(leaderboard, 0, leaderboardSize - 1);
}

// Function to display the sorted leaderboard based on total scores
void Leaderboard::displaySortedLeaderboard() const {
    cout << "Leaderboard sorted by total score:" << endl;
    for (int i = 0; i < leaderboardSize; ++i) {
        cout << "Rank " << i + 1 << ": ";
        cout << "Name: " << leaderboard[i].name << ", ";
        cout << "Total Score: " << leaderboard[i].totalScore << endl;
    }
}
