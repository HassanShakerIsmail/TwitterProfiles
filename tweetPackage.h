#pragma once
#include <vector>
#include <sstream>
#include "personality.cpp"
#include <iostream>

#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <string>

class TweetPackage {
	std::string tweet;
	int likes;
	int replies;
	int retweets;
	int quotes;
	std::string authorName;
	std::string authorUsername;
	int authorFollowers;
	int authorFollowing;

public:
	TweetPackage();
	TweetPackage(std::string tweet, int likes, int replies, int retweets, int quotes, std::string authorName, std::string authorUsername, int authorFollowers, int authorFollowing);
	std::string getTweet();
	int getLikes();
	int getReplies();
	int getRetweets();
	int getQuotes();
	std::string getAuthorName();
	std::string getAuthorUsername();
	int getAuthorFollowers();
	int getAuthorFollowing();
	void setTweet(std::string Tweet);
	void setLikes(int Likes);
	void setReplies(int Replies);
	void setRetweets(int Retweets);
	void setQuotes(int Quotes);
	void setAuthorName(std::string authorName);
	void setAuthorUsername(std::string authorUsername);
	void setAuthorFollowers(int authorFollowers);
	void setAuthorFollowing(int authorFollowing);
	bool isValidTweetPackage();
};


#endif 


