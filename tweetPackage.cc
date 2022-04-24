#include "tweetPackage.h"

TweetPackage::TweetPackage(std::string tweet, int likes, int replies, 
    int retweets, int quotes, std::string authorName, std::string authorUsername, 
    int authorFollowers, int authorFollowing) {
        this->tweet = tweet;
        this->likes = likes; 
        this->replies = replies; 
        this->retweets = retweets;
        this->quotes = quotes;
        this->authorName = authorName;
        this->authorUsername = authorUsername;
        this->authorFollowers = authorFollowers;
        this->authorFollowing = authorFollowing;
}

TweetPackage::TweetPackage() {
    TweetPackage("", 0, 0, 0, 0, "", "", 0, 0);
}

void TweetPackage::setTweet(std::string Tweet) {
    this->tweet = Tweet;
}

std::string TweetPackage::getTweet() {
    return this->tweet;
}

void TweetPackage::setLikes(int Likes) {
    this->likes = Likes;
}

int TweetPackage::getLikes() {
    return this->likes;
}

void TweetPackage::setReplies(int Replies) {
    this->replies = Replies;
}

int TweetPackage::getReplies() {
    return this->replies;
}

void TweetPackage::setRetweets(int Retweets) {
    this->retweets = Retweets;
}

int TweetPackage::getRetweets() {
    return this->retweets;
}

void TweetPackage::setQuotes(int Quotes) {
    this->quotes = Quotes;
}

int TweetPackage::getQuotes() {
    return this->quotes;
}

void TweetPackage::setAuthorName(std::string authorName) {
    this->authorName = authorName;
}

std::string TweetPackage::getAuthorName() {
    return this->authorName;
}

void TweetPackage::setAuthorUsername(std::string authorUsername) {
    this->authorUsername = authorUsername;
}

std::string TweetPackage::getAuthorUsername() {
    return this->authorUsername;
}

void TweetPackage::setAuthorFollowers(int authorFollowers) {
    this->authorFollowers = authorFollowers;
}

int TweetPackage::getAuthorFollowers() {
    return this->authorFollowers;
}

void TweetPackage::setAuthorFollowing(int authorFollowing) {
    this->authorFollowing = authorFollowing;
}

int TweetPackage::getAuthorFollowing() {
    return this->authorFollowing;
}
