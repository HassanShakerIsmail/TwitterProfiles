#pragma once
#include <vector>
#include "personality.cpp"
#include <iostream>


struct userProfile {
	struct TweetPackage {
		string Tweet;
		int Likes;
		int Replies;
		int Retweets;
		int Quotes;
		string authorName;

	}; 
	int followerCount{ 0 };
	int followingCount{ 0 };
	int TotalTweets{ 0 };
	//int TotalLikes{ 0 };
	//int TotalReplies{ 0 };
	//int TotalRetweets{ 0 };
	string name;
	string username;
	string profileStorage = username;
	personality userPersonality;
	vector<TweetPackage> Tweets{};
	vector<string> FilesAlreadyRead{};
	// void access_profile(string username);
	void read_twitter_data_csv(string filename);
	void write_twitter_data_csv();

};

// Error struct
//  errorCode legend to be added here
struct error {
	string errorMessage;
	int errorCode{ 0 };

	error(string msg = "Unspecified Exception", int errorCode = -1) :
		errorMessage{ msg }, errorCode{ errorCode }{};

	void displayError() {
		cout << "Exception occured with message: " << errorMessage << '\n';
		cout << "Exception code: " << errorCode << '\n';
	}
};