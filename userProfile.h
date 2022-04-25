#pragma once
#include <string>
#include <vector>
#include "personality.h"
#include "tweetPackage.h"
#include "error.h"
#include <chrono>
#include <ctime>
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
	void calc_summary_stats();


public:

	userProfile(string name = "NULL", string username = "NULL") :
	  name{ name },username{ username }, profileStorage{ "NULL" }, userPersonality{ 0 }{};



	void setName(string name);
	void setUsername(string user);
	void read_and_package_tdata_csv(string filename);
	void tweets_file_summary(string filename = "NULL");
	void clean_tweets();
	void store_profile();
	void update_profile();
	userProfile load_profile(string username);
	static userProfile* create_dynamic_profile(string username, string name);
	static void delete_dynamic_profile(userProfile* prof);
	//void write_twitter_data_csv();



	~userProfile() {
	}

};