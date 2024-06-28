#pragma once
#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Linkedlist_Stack.hpp"
#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Queue.hpp"
#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Array.hpp"
#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_BinaryTree.hpp"

class Game
{
	Quiz quiz;
	StudentQ studq;
	Leaderboard leaderboard;

public:
	void play();
	void displayMenu();
	void displayQuestionMenu();
	void doQuiz();
	int answerQuestion();
	void leaderboardMenu();
	void searchStudentByName();
	void searchTopicsByKeyword();
	void sortLeaderboardByTotalScore();
	void displayTop30HierarchicalChart() const;
};

