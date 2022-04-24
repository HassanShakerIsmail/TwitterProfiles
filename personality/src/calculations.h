#ifndef PERSONALITY_RESULTS_H
#define PERSONALITY_RESULTS_H

#include <vector>
#include "tweetPackage.h"

class PersonalityResults {
    double agreeableness; 
    double openness; 
	double creativity; 
	double selfCenteredness; 
	double empathy; 
	double socialFactor;
	double neuroticism;

    std::vector<TweetPackage> tweetPackages; 

 public: 
    PersonalityResults(std::vector<TweetPackage> tweetPackages); 

 private:
    double calculate_agreeableness();
    double calculate_openness();
    double calculate_creativity();
    double calculate_self_centeredness();
    double calculate_empathy();
    double calculate_social_factor();
    double calculate_neuroticism();
}; 

#endif 