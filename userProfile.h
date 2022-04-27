#pragma once
#include <string>
#include <vector>
#include "personality.h"
#include "tweetPackage.h"
#include "error.h"
#include <chrono>
#include <ctime>
#include <fstream>
 
class UserProfile {
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
	void load_and_package_tdata_csv(string filename);



public:

	UserProfile(string name = "NULL", string username = "NULL") :
	  name{ name },username{ username }, profileStorage{ "NULL" }, userPersonality{ 0 }{};


	const string getUsername();
	void clearFilesRead();
	void setName(string name);
	void setUsername(string user);
	void read_and_package_tdata_csv(string filename);
	void tweets_file_summary(string filename = "NULL");
	void clean_tweets();
	void store_profile();
	void update_profile();
	void clearTweets();
    static void delete_profile(string username);
	static UserProfile load_profile(string username);
	static UserProfile* create_dynamic_profile(string username, string name);
	static void delete_dynamic_profile(UserProfile* prof);
	//void write_twitter_data_csv();



	~UserProfile() {
	}

};