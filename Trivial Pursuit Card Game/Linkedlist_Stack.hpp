#ifndef QUESTION_H
#define QUESTION_H
#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Array.hpp"

#include <string>
using namespace std;

// Declaration of the Question struct
struct Question
{
    string type;
    string question;
    string answer;
    Question* next;
};

// Forward declaration
class Quiz;

class Leaderboard;

void displayQuestion(Question* question, Quiz& quiz, int& current_score, const string& studentName, Leaderboard& leaderboard);

// Declaration of the Quiz class
class Quiz
{
private:
    Question* head;
    Question* tail;
    Question* answeredHead;
    Question* answeredTail;
    Question* discardedHead;
    Question* discardedTail;

    // Custom stack implemented using a singly linked list
    struct StackNode
    {
        Question* question;
        StackNode* next;
    } *stackHead;

public:
    Quiz();
    ~Quiz();
    void loadQuestions(const string& filename);
    Question* getRandomQuestion();
    bool checkAnswer(Question* question, const string& userAnswer);
    void discardQuestion(Question* question);
    void displayAnsweredQuestions(Quiz& quiz) const;
    bool displayDiscardedQuestions(Quiz& quiz, int& current_score, const string& studentName, Leaderboard& leaderboard);

    void pushToStack(Question* question);
    Question* popFromStack();
    bool isStackEmpty();
    friend void displayQuestion(Question* question, Quiz& quiz); // Declare displayQuestion as a friend function

};

#endif // QUESTION_H
