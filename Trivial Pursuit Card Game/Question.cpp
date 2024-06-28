#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Linkedlist_Stack.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <iomanip>
#include <cctype> // For tolower() and toupper() functions
#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_BinaryTree.hpp"
#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Array.hpp"

using namespace std;

Quiz::Quiz() : head(nullptr), tail(nullptr), answeredHead(nullptr), answeredTail(nullptr), discardedHead(nullptr), discardedTail(nullptr), stackHead(nullptr)
{
    srand(static_cast<unsigned>(time(nullptr)));
}

Quiz::~Quiz()
{
    // Destructor to clean up the linked lists
    Question* current = head;
    while (current != nullptr)
    {
        Question* next = current->next;
        delete current;
        current = next;
    }

    current = answeredHead;
    while (current != nullptr)
    {
        Question* next = current->next;
        delete current;
        current = next;
    }

    current = discardedHead;
    while (current != nullptr)
    {
        Question* next = current->next;
        delete current;
        current = next;
    }

    // Clean up the custom stack
    while (stackHead != nullptr) {
        StackNode* temp = stackHead;
        stackHead = stackHead->next;
        delete temp;
    }
}


void Quiz::loadQuestions(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "\nError: Unable to open file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string type, question, answer;

        getline(ss, type, ',');
        if (!type.empty() && type[0] == '\"' && type.back() == '\"')
        {
            type = type.substr(1, type.length() - 2); // Remove quotes
        }

        getline(ss, question, ',');
        if (!question.empty() && question[0] == '\"' && question.back() == '\"')
        {
            question = question.substr(1, question.length() - 2); // Remove quotes
        }

        getline(ss, answer, ',');
        if (!answer.empty() && answer[0] == '\"' && answer.back() == '\"')
        {
            answer = answer.substr(1, answer.length() - 2); // Remove quotes
        }

        if (!type.empty() && !question.empty() && !answer.empty())
        {
            Question* newQuestion = new Question{ type, question, answer, nullptr };
            if (!head)
            {
                head = newQuestion;
                tail = newQuestion;
            }
            else
            {
                tail->next = newQuestion;
                tail = newQuestion;
            }
        }
    }
    file.close();
}

bool Quiz::checkAnswer(Question* question, const string& userAnswer)
{
    // Trim the correct answer and remove spaces
    string correctAnswer = question->answer;
    correctAnswer.erase(remove_if(correctAnswer.begin(), correctAnswer.end(), ::isspace), correctAnswer.end());
    if (!correctAnswer.empty() && correctAnswer.front() == '\"' && correctAnswer.back() == '\"')
    {
        correctAnswer = correctAnswer.substr(1, correctAnswer.length() - 2);
    }

    // Remove spaces from the user's answer
    string trimmedUserAnswer = userAnswer;
    trimmedUserAnswer.erase(remove_if(trimmedUserAnswer.begin(), trimmedUserAnswer.end(), ::isspace), trimmedUserAnswer.end());

    // Convert both answers to uppercase for case-insensitive comparison
    string upperUserAnswer = trimmedUserAnswer;
    string upperCorrectAnswer = correctAnswer;
    transform(upperUserAnswer.begin(), upperUserAnswer.end(), upperUserAnswer.begin(), ::toupper);
    transform(upperCorrectAnswer.begin(), upperCorrectAnswer.end(), upperCorrectAnswer.begin(), ::toupper);

    bool isCorrect = (upperUserAnswer == upperCorrectAnswer);

    // Add to answered questions
    if (!answeredHead)
    {
        answeredHead = question;
        answeredTail = question;
    }
    else
    {
        answeredTail->next = question;
        answeredTail = question;
    }
    question->next = nullptr; // Ensure this question doesn't link to others in the answered list

    return isCorrect;
}

Question* Quiz::getRandomQuestion()
{
    if (!head)
    {
        cout << "\nAll questions have been displayed or answered.\n";
        //handleGameOptions(*this); // Return to the game menu
        return nullptr;
    }

    // If the custom stack is empty, refill it with questions from the linked list
    if (isStackEmpty())
    {
        // First, count the number of available questions
        int count = 0;
        Question* current = head;
        while (current)
        {
            count++;
            current = current->next;
        }

        // Create an array to hold pointers to all questions
        Question** questionArray = new Question * [count];
        current = head;
        for (int i = 0; i < count; i++)
        {
            questionArray[i] = current;
            current = current->next;
        }

        // Shuffle the array
        for (int i = count - 1; i > 0; --i)
        {
            int j = rand() % (i + 1);
            swap(questionArray[i], questionArray[j]);
        }

        // Push all questions onto the custom stack
        for (int i = 0; i < count; i++)
        {
            pushToStack(questionArray[i]);
        }

        delete[] questionArray; // Clean up the array
    }

    // Pop a question from the custom stack
    Question* randomQuestion = popFromStack();

    // Remove the chosen question from the linked list
    if (head == randomQuestion)
    {
        head = randomQuestion->next;
    }
    else
    {
        Question* prev = head;
        while (prev->next != randomQuestion)
        {
            prev = prev->next;
        }
        prev->next = randomQuestion->next;
    }

    if (tail == randomQuestion)
    {
        tail = nullptr;
    }

    randomQuestion->next = nullptr; // Isolate the random question
    return randomQuestion;
}

void Quiz::discardQuestion(Question* question)
{
    if (!discardedHead)
    {
        discardedHead = question;
        discardedTail = question;
    }
    else
    {
        discardedTail->next = question;
        discardedTail = question;
    }
}

void Quiz::displayAnsweredQuestions(Quiz& quiz) const
{
    if (!answeredHead)
    {
        cout << "\nNo answered questions.\n";
    }
    else
    {
        cout << "\n***********************\n";
        cout << "*  ANSWERED QUESTIONS *\n";
        cout << "***********************\n";
        Question* current = answeredHead;
        while (current != nullptr)
        {
            cout << "\nType: " << current->type << "\n";
            cout << "\nQuestion: " << current->question << "\n";
            cout << "\nAnswer: " << current->answer << "\n";
            cout << "------------------------------------------------------------------------------------------------------------------------------------------\n"; // Separation line
            current = current->next;
        }
    }
    cout << "\nPress 1 to return to the game menu: ";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        return;
    }
    else (choice != 1); // Ensure the loop only ends when 1 is pressed
    {
        cout << "\nInvalid choice, please enter 1 to return to the game menu: ";
        cin >> choice;
    }
}

bool Quiz::displayDiscardedQuestions(Quiz& quiz, int& current_score, const string& studentName, Leaderboard& leaderboard)
{
    if (!discardedHead)
    {
        cout << "\nNo discarded questions.\n";
        return false;
    }

    cout << "\n***********************\n";
    cout << "*   DISCARDED CARDS   *\n";
    cout << "***********************\n";

    int index = 1;
    Question* current = discardedHead;
    current_score = 0;
    while (current != nullptr)
    {
        cout << "\n" << index << ". Type: " << current->type << "\n";
        cout << "\nQuestion: " << current->question << "\n";
        cout << "-----------------------\n"; // Separation line

        current = current->next;
        index++;
    }

    // Allow the user to select a discarded question
    cout << "\nEnter the number of the discarded question you want to answer (or enter 'back' to return to the game menu): ";
    string choice;
    getline(cin, choice);

    if (choice == "back")
    {
        return false;
    }

    try
    {
        int selectedQuestionIndex = stoi(choice); // stoi - turn string to integer

        if (selectedQuestionIndex < 1 || selectedQuestionIndex >= index)
        {
            cout << "\nInvalid choice. Please enter a valid question number.\n";
            return false;
        }

        // Find the selected question
        current = discardedHead;
        Question* prev = nullptr;
        for (int i = 1; i < selectedQuestionIndex; ++i)
        {
            prev = current;
            current = current->next;
        }

        // Display the selected question
        cout << "\n***********************\n";
        cout << "*  SELECTED QUESTION  *\n";
        cout << "***********************\n";
        cout << "\nType: " << current->type << "\n";
        cout << "\nQuestion: " << current->question << "\n";

        // Proceed to answer the selected question
        string answer;
        cout << "\nEnter your answer: ";
        getline(cin, answer);

        // Check the user's answer
        if (checkAnswer(current, answer))
        {
            cout << "\nCorrect! The question has been added to the answered questions.\n\n";
            current_score = 8;
            // Move the question from discarded list to answered list
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                discardedHead = current->next;
            }

            if (!answeredHead)
            {
                answeredHead = current;
                answeredTail = current;
            }
            else
            {
                answeredTail->next = current;
                answeredTail = current;
            }
            current->next = nullptr;
        }
        else
        {
            cout << "\nIncorrect! The correct answer is: " << current->answer << "\n\n";
        }
        leaderboard.addToLeaderboard(studentName, current->question, current_score, 0);
        return true;
    }
    catch (const invalid_argument& e)
    {
        cout << "\nInvalid input. Please enter a valid question number.\n";
        return false;
    }
}

void displayQuestion(Question* question, Quiz& quiz, int& current_score, const string& studentName, Leaderboard& leaderboard)
{
    cout << "\n***********************\n";
    cout << "*      QUESTION       *\n";
    cout << "***********************\n";
    cout << "\nType: " << question->type << "\n";
    cout << "\nQuestion: " << question->question << "\n";
    cout << "\nSelect a choice!\n";
    cout << "1. Accept\n";
    cout << "2. Decline\n";
    cout << "\nEnter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore(); // Ignore the newline character in the buffer
    current_score = 0;
    switch (choice)
    {
    case 1:
    {
        string answer;
        cout << "\nEnter your answer: ";
        getline(cin, answer);

        if (quiz.checkAnswer(question, answer))
        {
            current_score = 10;
            cout << "\nCorrect! The question has been added to the answered questions.\n\n";

        }
        else
        {
            cout << "\nIncorrect! The correct answer is: " << question->answer << "\n\n";
        }
        leaderboard.addToLeaderboard(studentName, question->question, current_score, 0);
        break;
    }
    case 2:
        quiz.discardQuestion(question);
        cout << "\nQuestion discarded.\n\n";
        break; // Add break statement here
    default:
        cout << "\nInvalid choice, please enter again!\n\n";
        break;
    }
}

void Quiz::pushToStack(Question* question)
{
    StackNode* newNode = new StackNode{ question, stackHead };
    stackHead = newNode;
}

Question* Quiz::popFromStack()
{
    if (isStackEmpty())
    {
        return nullptr;
    }
    StackNode* temp = stackHead;
    Question* question = temp->question;
    stackHead = stackHead->next;
    delete temp;
    return question;
}

bool Quiz::isStackEmpty()
{
    return stackHead == nullptr;
}