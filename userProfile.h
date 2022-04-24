#pragma once
#include <string>
#include <vector>
#include "personality.h"
#include "tweetPackage.h"
#include "error.h"
#include <fstream>

class userProfile {
	int followerCount{ 0 };
	int followingCount{ 0 };
	int TotalTweets{ 0 };
	int TotalLikes{ 0 };
	int TotalReplies{ 0 };
	int TotalRetweets{ 0 };
	string name;
	string username;
	string profileStorage = username;
	personality userPersonality;
	vector<TweetPackage> Tweets{};
	vector<string> FilesAlreadyRead{};
	
public:
	void setName(string name);
	void setUsername(string user);
	void read_and_package_tdata_csv(string filename);
	void tweets_file_summary(string filename = "NULL");
	void clean_tweets();
	void calc_summary_stats();
	//void write_twitter_data_csv();

};