#pragma once
#include<iostream>
#include<string>
using namespace std;
class StudentBio
{
public:
	int studentNo;
	std::string studentName;
	int score;
	StudentBio* next;

	StudentBio(int nomor, string name, int score) :studentNo(nomor), studentName(name), score(score), next(nullptr) {}
};

class StudentQ
{
private:
	StudentBio* front;
	StudentBio* rear;

public:
	StudentQ() :front(nullptr), rear(nullptr) {
	}
	bool isEmpty();
	void Enqueue(int nomor, string name, int score);
	void Enqueue(StudentBio* studbio);
	void Dequeue();
	void loadStudent();
	StudentBio* Peek();
	void Show();
};