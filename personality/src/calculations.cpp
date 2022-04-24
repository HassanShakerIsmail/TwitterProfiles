#include "calculations.h"

PersonalityResults::PersonalityResults(std::vector<TweetPackage> tweetPackages) {
    this->tweetPackages = tweetPackages;

    this->agreeableness = calculate_agreeableness();
    this->openness = calculate_openness();
    this->creativity = calculate_creativity();
    this->selfCenteredness = calculate_self_centeredness();
    this->empathy = calculate_empathy();
    this->socialFactor = calculate_social_factor();
    this->neuroticism = calculate_neuroticism();
}

double PersonalityResults::calculate_agreeableness() {
    // Calculate agreeableness
}

double PersonalityResults::calculate_openness() {
    // Calculate openness
}

double PersonalityResults::calculate_creativity() {
    // Calculate creativity
}

double PersonalityResults::calculate_self_centeredness() {
    // Calculate self centeredness
}

double PersonalityResults::calculate_empathy() {
    // Calculate empathy
}

double PersonalityResults::calculate_social_factor() {
    // Calculate social factor
}

double PersonalityResults::calculate_neuroticism() {
    // Calculate neuroticism
}

