#include "calculations.h"

PersonalityResults::PersonalityResults(UserProfile profile) {
    this->profile = profile;
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
    /* 
    Here we aim to calculate the social factor of a twitter user. We will do this by determining if their engagements are high or low. 
    We use the scale provided by https://scrunch.com/blog/what-is-a-good-engagement-rate-on-twitter. An engagement is defined by a like
    or retweet. 
    */
   
   double engagement_factor = (profile.getTotalLikes() + profile.getTotalRetweets() + profile.getTotalReplies()) / profile.getTotalTweets();
   return engagement_factor; 
}

double PersonalityResults::calculate_neuroticism() {
    // Calculate neuroticism
}

