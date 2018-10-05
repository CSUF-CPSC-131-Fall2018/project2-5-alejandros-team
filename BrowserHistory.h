#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include <iterator>
#include "Webpage.h"
using namespace std;


class BrowserHistory {
public:
	//def ctor
	BrowserHistory();

	void visitSite(Webpage newSite);
	string back();
	string forward();

	void readHistory(string fileName);

	string getUrl();
	size_t getNavSize();
	list<Webpage> getSitesVisited();
	string ex;//error string
	void chop();
private:
	list<Webpage> navHistory;
	list<Webpage>::iterator navPos;
	list<Webpage> sitesVisited;
	int numSites;

};

void BrowserHistory::readHistory(string fileName) {
	string temp;
	int newTime;
	Webpage newSite;
	ifstream inFile(fileName.c_str());

	while (inFile >> temp) {
		if (temp == "new") {
			inFile >> temp >> newTime;
			newSite = Webpage(temp, time_t(newTime));
			visitSite(newSite);
		}
		else if (temp == "back") {
			back();
		}
		else if (temp == "forward") {
			forward();
		}
		else {
			throw logic_error("invalid command");
		}
	}
}
BrowserHistory::BrowserHistory() {
	//both lists have a def blank webpage in their list
	navHistory.push_front(Webpage());
	navPos = navHistory.begin();
	sitesVisited.push_front(Webpage());
	numSites = 0;
	
}
void BrowserHistory::visitSite(Webpage page) {
	list<Webpage>::iterator temp;
	temp = navPos;
	temp++;
	//checking to see if we need to delete the "foward" websites saved in browser history
	if (temp != navHistory.end()) {
		chop();
	}
	
	//adding the website too both lists
	sitesVisited.push_back(page);
	navHistory.push_back(page);
	//making the iterator point to the newest visited websitre
	navPos = navHistory.end();
	navPos--;
	numSites++;
}
string BrowserHistory::back() {
	//going back 1 in the browserhistory
	//checking to see if possible
	if (navPos == navHistory.begin()) {
		ex = "error";
		return ex;
	}
	navPos--;
	return navPos->getUrl();

}
string BrowserHistory::forward() {
	//going forward 1 in the navHistory

	list<Webpage>::iterator temp;
	temp = navHistory.end();
	temp--;//temp is pointing to last webpage
	//checking to see is iterator is at last webpage
	if (navPos == temp) {
		
		ex = "error";
		return ex;
	}
	navPos++;
	return navPos->getUrl();
	//navPos++;
	
}
string BrowserHistory::getUrl() {
	//return url from webpage iterator pointer
	//if statement to make sure navPos isnt pointing to nullptr
	
	if (navPos != navHistory.end()) {
		string def;
		def = navPos->getUrl();
		//For default blank webpage
		if (def == "blank") {
			ex = "error";
			return ex;
		}
		else return navPos->getUrl();
	}
	
	ex = "error";
	return ex;
}
size_t BrowserHistory::getNavSize() {
	//-1 because list has a default of 1 webpage
	return navHistory.size() - 1;
	//return numSites;
}
list<Webpage> BrowserHistory::getSitesVisited() {
	//popping front becuase of default webpage in front of list
	sitesVisited.pop_front();
	return sitesVisited;
}

void BrowserHistory::chop() {
	//making a temp iterator, so I dont change the navPos
	list<Webpage>::iterator temp;
	temp = navPos;
	//erasing from iterator + 1 to end of list
	navHistory.erase(++temp, navHistory.end());
}
