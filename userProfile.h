#pragma once
#include <string>
#include <vector>
#include "personality.h"
#include "tweetPackage.h"
#include "error.h"
#include <fstream>

class UserProfile {
	int followerCount{ 0 };
	int followingCount{ 0 };
	int totalTweets{ 0 };
	int totalLikes{ 0 };
	int totalReplies{ 0 };
	int totalRetweets{ 0 };
	string name;
	string username;
	string profileStorage = username;
	personality userPersonality;
	vector<TweetPackage> tweets{};
	vector<string> FilesAlreadyRead{};
	
public:
	void setName(string name);
	void setUsername(string user);
	void read_and_package_tdata_csv(string filename);
	void tweets_file_summary(string filename = "NULL");
	void clean_tweets();
	void calc_summary_stats();

	vector<TweetPackage> getTweets();
	int getTotalTweets(); 
	int getTotalLikes();
	int getTotalReplies();
	int getTotalRetweets();
	int getFollowerCount(); 
	//void write_twitter_data_csv();
};