#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Game.hpp"
#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_BinaryTree.hpp"
#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Array.hpp"
#include <conio.h>

void Game::displayMenu()
{
    cout << "\n***********************\n";
    cout << "*         MENU        *\n";
    cout << "***********************\n";
    cout << "\nSelect a choice!\n";
    cout << "1. Start Game\n";
    cout << "2. View Scoreboard\n";
    cout << "3. View Leaderboard\n";
    cout << "4. Logout\n";
    cout << "\nEnter your choice: ";
}

void Game::displayQuestionMenu()
{
    cout << "\n***********************\n";
    cout << "*    Question MENU    *\n";
    cout << "***********************\n";
    cout << "\nSelect a choice!\n";
    cout << "1. Unanswered Question Cards\n";
    cout << "2. Answered Question Cards\n";
    cout << "3. Discarded Cards\n";
    //cout << "4. Back to Main Menu\n";
    cout << "\nEnter your choice: ";
}

int Game::answerQuestion()
{
    int choice = -1;
    int quesScore = 0; //diisi dengan nilai yang seharusnya
    StudentBio* curr = studq.Peek();
    bool alreadyAns = false;
    while (alreadyAns == false) {
        displayQuestionMenu();
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1: {
            Question* q = quiz.getRandomQuestion();
            if (!q)
            {
                cout << "\nError: No questions available." << endl;
                return false;
            }
            //cout << "Testing Only: " << curr->studentName << endl;
            displayQuestion(q, quiz, quesScore, curr->studentName, leaderboard);
            alreadyAns = true;
            break;
        }break;
        case 2: {
            cout << "\nViewing answered question cards...\n";
            quiz.displayAnsweredQuestions(quiz);
            break;
        }break;
        case 3: {
            cout << "\nViewing discarded cards...\n";
            alreadyAns = quiz.displayDiscardedQuestions(quiz, quesScore, curr->studentName, leaderboard);
            break;
        }break;
        case 4: {
            cout << "\nReturning to the main menu.\n";
            //quiz.displayMenu(quiz);
            break;
        }

        }
    }
    return quesScore;
}

void Game::doQuiz()
{
    StudentQ alreadyAnsSesi1;
    while (!studq.isEmpty()) {
        StudentBio* curr = studq.Peek();
        cout << "...............ROUND ONE................\n";
        cout << "Nomor : " << curr->studentNo << endl;
        cout << "Name  : " << curr->studentName << endl;
        cout << "Score : " << curr->score << endl;
        cout << "........................................\n";
        int currentScore = answerQuestion();
        curr->score += currentScore;
        alreadyAnsSesi1.Enqueue(curr);
        studq.Dequeue();
    }

    // Enqueue the students back into studq for the next rounds
    while (!alreadyAnsSesi1.isEmpty()) {
        StudentBio* curr = alreadyAnsSesi1.Peek();
        studq.Enqueue(curr);
        alreadyAnsSesi1.Dequeue();
    }

    // Round 2
    StudentQ alreadyAnsSesi2;
    while (!studq.isEmpty()) {
        StudentBio* curr = studq.Peek();
        cout << "...............ROUND TWO................\n";
        cout << "Nomor : " << curr->studentNo << endl;
        cout << "Name  : " << curr->studentName << endl;
        cout << "Score : " << curr->score << endl;
        cout << "........................................\n";
        int currentScore = answerQuestion();
        curr->score += currentScore;
        alreadyAnsSesi2.Enqueue(curr);
        studq.Dequeue();
    }

    // Enqueue the students back into studq for the next round
    while (!alreadyAnsSesi2.isEmpty()) {
        StudentBio* curr = alreadyAnsSesi2.Peek();
        studq.Enqueue(curr);
        alreadyAnsSesi2.Dequeue();
    }

    // Round 3
    while (!studq.isEmpty()) {
        StudentBio* curr = studq.Peek();
        cout << "...............ROUND THREE..............\n";
        cout << "Nomor : " << curr->studentNo << endl;
        cout << "Name  : " << curr->studentName << endl;
        cout << "Score : " << curr->score << endl;
        cout << "........................................\n";
        int currentScore = answerQuestion();
        curr->score += currentScore;
        // No need to enqueue into another queue after the last round
        studq.Dequeue();
    }
}

void Game::leaderboardMenu() {
    int choice = -1;
    while (choice != 4) {
        cout << "\n***********************\n";
        cout << "*     LEADERBOARD     *\n";
        cout << "***********************\n";
        cout << "\n1. Search student by name\n";
        cout << "2. Search topics by keyword\n";
        cout << "3. Sort leaderboard\n";
        cout << "4. Return to main menu\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            searchStudentByName();
            break;
        case 2:
            searchTopicsByKeyword();
            break;
        case 3:
            sortLeaderboardByTotalScore();
            break;
        case 4:
            cout << "\nReturning to the main menu.\n";
            break;
        default:
            cout << "\nInvalid choice, please enter again!\n";
            break;
        }
    }
}

void Game::searchStudentByName() {
    string name;
    cout << "\nEnter the name of the student to search: ";
    getline(cin, name);

    // Search for the student by name
    LeaderboardEntry student = leaderboard.searchStudentByName(name, leaderboard.getLeaderboard(), leaderboard.getLeaderboardSize());

    if (student.name.empty()) {
        cout << "\nStudent not found in the leaderboard.\n";
    }
    else {
        cout << "\nStudent found in the leaderboard:\n";
        cout << "\nName: " << student.name << endl;
        cout << "Score: " << student.totalScore << endl;
        // Display other details of the student
    }
}

void Game::searchTopicsByKeyword() {
    string keyword;
    cout << "\nEnter the keyword to search: ";
    getline(cin, keyword);
    leaderboard.searchTopicsByKeyword(keyword, leaderboard.getLeaderboard(), leaderboard.getLeaderboardSize());
}

void Game::sortLeaderboardByTotalScore() {
    leaderboard.sortLeaderboardByTotalScore(leaderboard.getLeaderboard(), leaderboard.getLeaderboardSize());
    leaderboard.displaySortedLeaderboard();
    cout << "\nLeaderboard sorted by total score.\n";
}


void Game::displayTop30HierarchicalChart() const {
    BinaryTree top30Tree;
    const auto* leaderboardArray = leaderboard.getLeaderboard();
    int leaderboardSize = leaderboard.getLeaderboardSize();
    for (int i = 0; i < std::min(30, leaderboardSize); ++i) {
        top30Tree.addNode(leaderboardArray[i].name, leaderboardArray[i].totalScore);
    }
    top30Tree.buildTree();
    top30Tree.displayHierarchical();
}

void Game::play()
{
    quiz.loadQuestions("Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_quiz_questions.csv");
    studq.loadStudent();
    //studq.Show();

    int choice = -1;
    while (choice != 4) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            cout << "\nStarting the game...\n\n";
            doQuiz();
            break;
        case 2:
            cout << "\nViewing scoreboard...\n\n";
            displayTop30HierarchicalChart();
            // Implement scoreboard viewing logic here
            break;
        case 3:
            system("cls"); //Clear the screen
            cout << "\nViewing leaderboard...\n";
            system("color E0"); 
            leaderboard.displayLeaderboard();
            leaderboardMenu();
            break;
        case 4:
            cout << "\nExiting the program.\n";
            break;
        default:
            cout << "\nInvalid choice, please enter again!\n";
            break;
        }
    }
}


