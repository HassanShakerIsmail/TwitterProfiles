#include <sstream>
#include <fstream>
#include "personality.h"
#pragma once

using namespace std;

struct personality { // was original class declaration better?

	// The following personality class is developed on a theory of personality I've come up with.
	//  This obviously means that this metric is well to be blunt - complete garbage

	// GUIDE:
	// agreeableness:
	//  -1 -> disagreeable, argumentative archtype
	//   0 -> neutral, average agreeableness 
	//   1 -> very agreeable, peacemaker archtype

	// openness: 
	// -1 -> unopen to change, closedmindedness
	//  0 -> average openness. 
	//  1 -> extremely open to conversation

	// creativity: [REQUIRES REVISION]
	// 0 -> complete uniformity, non-creative by the book
	// 50 -> average creativity
	// 100 -> more on creative spectrum

	// self-centeredness:
	// -1 -> selfish, self focus is priority 
	//  0 -> average 
	//  1 -> selfless

	// empathy:
	// -1 -> unempathetic, sociopathy - psychopathy, etc
	//  0 -> average empathy
	//  1 -> empathetic, selfless archtype - caretaker/giver

	// socialfactor:
	// -1 -> unsocialable, extreme introvert. perhaps disorders such as severe autism, depressive tendencies, etc
	//  0 -> average sociability, 
	//  1 -> extreme sociability, highly extroverts. Possible narcissists.

	// neuroticism:
	// -1 -> low neuroticism 
	//  0 -> standard neuroticism
	//  1 -> high neuroticism

	//------------------------------------------------------------------------------------------------

	// personalityStorage -> stores a file that compounds a user profile report based on each factor
	// ProfileValidity -> keeps track on whether or not profile is in broken state (false) or not (true)

	double agreeableness{ 0 };
	double openness{ 0 };
	double creativity{ 0 };
	double selfCenteredness{ 0 };
	double empathy{ 0 };
	double socialFactor{ 50 };
	double neuroticism{ 0 };

	string personalityStorage; 
	bool ProfileValidity = true;

public:
	personality(double agree = 0, double open = 0, double creativity = 0, double empathy = 0, 
		double socialFactor = 0, double selfCenteredness = 0):
		agreeableness{ agree }, openness{ open }, creativity{ creativity },
		selfCenteredness{ selfCenteredness }, empathy{ empathy }, socialFactor{ socialFactor } {};
	

	// addition to agreeable
	void alter_agreeable(double x) {
		agreeableness += x;

		if (agreeableness < -1 || agreeableness > 1) {
			ProfileValidity = false;
		}

	}

	void alter_openness(double x) {
		openness += x;

		if (openness < -1 || openness > 1) {
			ProfileValidity = false;
		}

	}

	// void processString(string str);

};


 /*void personality::processString(string tweet) {
	 return;


}  */
