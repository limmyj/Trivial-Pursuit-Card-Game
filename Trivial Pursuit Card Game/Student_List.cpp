#include "Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_Queue.hpp"
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

void StudentQ::Enqueue(int nomor, string name, int score)
{
	StudentBio* studbio = new StudentBio(nomor, name, score);
	if (front == nullptr) {
		front = studbio;
		rear = studbio;
	}
	else {
		rear->next = studbio;
		rear = studbio;
	}
}

void StudentQ::Enqueue(StudentBio* studbio) //queue temporary
{
	StudentBio* backup = new StudentBio(studbio->studentNo, studbio->studentName, studbio->score);
	if (front == nullptr) {
		front = backup;
		rear = backup;
	}
	else {
		rear->next = backup;
		rear = backup;
	}
}

void StudentQ::Dequeue() { //queue process, execute the front queue
	if (!isEmpty()) {
		StudentBio* temp = front;
		front = front->next;
		delete temp;
		if (front == nullptr) {
			rear = nullptr;
		}
	}
}

void StudentQ::loadStudent() {
    ifstream file("Group WDSTR2309_TP066286_TP064806_TP068712_TP068440_TP069074_studentlist.csv");
    if (!file.is_open())
    {
        cout << "\nError: Unable to open file student." << endl;
        return;
    }
    string line;  //read per line
    while (getline(file, line))
    {
        stringstream ss(line); //to read
        string sno, sname, sscore;

        getline(ss, sno, ',');
        getline(ss, sname, ',');
        getline(ss, sscore, ',');
		Enqueue(stoi(sno), sname, stoi(sscore));
    }
    file.close();
}

void StudentQ::Show() {
	StudentBio* temp = front;
	while (temp != nullptr) {
		cout << "number[" << temp->studentNo <<"-"<<temp->studentName << "=" << temp->score << "]" << endl;
		temp = temp->next;
	}
}
bool StudentQ::isEmpty() {
	if (front == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

StudentBio* StudentQ::Peek() { //only read from top
	if (!isEmpty()) {
		return front;
	}
	else {
		return nullptr;
	}
}

