#ifndef PERSONALITY_RESULTS_H
#define PERSONALITY_RESULTS_H

#include <vector>
#include "tweetPackage.h"
#include "userProfile.h"

class PersonalityResults {
    UserProfile profile; 
 public: 
    PersonalityResults(UserProfile profile); 
    double calculate_agreeableness();
    double calculate_openness();
    double calculate_creativity();
    double calculate_self_centeredness();
    double calculate_empathy();
    double calculate_social_factor();
    double calculate_neuroticism();
}; 

#endif 