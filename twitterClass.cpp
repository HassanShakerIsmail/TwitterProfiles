#pragma once
#include "twitterClass.h"
#include <iostream>
#include <sstream>
#include <sys/stat.h> // functionality required for testing file existence

// TO DO:
// TRY TO FIX read_twitter_data_csv() AS TWEETS WITH QUOTES IN THEM CAUSE MISREADS AND THUS INPUT OF 
// EMPTY STRINGS TO TWEETPACKAGE DATA IN FUNCTION!

using namespace std;

inline bool fileExists(string& name) { // Mostly non-directly related function that checks file for existence
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}


// write_twitter_data_csv() is a member function to userProfile that for a called userProfile,
//  will output it's collected twitter data to the userProfile's data file 
//  (or append the new data onto it, assuming the profile already has a storage file)
//  NOTE: that this does NOT print the userProfiles personality profile - something write_personality_profile_csv() handles.
void userProfile::write_twitter_data_csv() {
	string fileName = username + "_twitter_data.txt";
	bool fileExistence = fileExists(fileName);
	ofstream outputInstance{ fileName };

	if (fileExistence == false) { // Output header -> MAY NEED TO BE UPDATED WITH MOST CURRENT VALUES!
		outputInstance << "USERPROFILE FOR USERNAME: " << username << " NAME: " << name << "\n";
		outputInstance << "FOLLOWER COUNT: " << followerCount << " FOLLOWING COUNT: " << followingCount << '\n';
		outputInstance << "TOTAL TWEETS: " << TotalTweets << '\n';
	}

	for (int i = 0; i < Tweets.size(); ++i) {
		outputInstance << "TWEET: \n" << Tweets[i].Tweet << '\n' << "LIKES:" << Tweets[i].Likes << '\n';
		outputInstance << "RETWEETS: " << Tweets[i].Retweets << "\n" << "REPLIES: " << Tweets[i].Replies << '\n';
		outputInstance << "QUOTES: " << Tweets[i].Quotes << '\n';
	}

}


/* void userProfile::access_profile(string username) {


} */


// csv_file is assumed to be in:
//  i,Tweet,Retweet Count,Reply count,like count,quote count,Name,Username,number of Followers,number of Following,total number of tweets
//   where i denotes the ith most recent retrieved tweet. Moreover, you'll notice that number of followers, and number of following
//   will remain constant. This is an inefficiency that will be solved further down the line, when I'm able to tweak the API
//   into retrieving data real time.



// REQUIRES: 
//  twitter data of said file only contains the tweets of ONE PROFILE/PERSON!
//   implementation for reading multiple profiles will be added later, via a seperate function

//  inputted CSV files MUST contain date of aggregration of data, i.e if we fetched the tweets of say
//   Kanye West on 1:54pm Feb 25th 2022, our file would be titled "KanyeWestTwitterData_0154:25:02:2022"
//   This helps avoid reading duplicate data, which can muck up our profiles. 
void userProfile::read_twitter_data_csv(string filename) {
	ifstream fileInstance{ filename };
	if (fileInstance.fail()) {
		throw error("Failed to find fileinstance with name: " + filename, -1);
	}

	// Check if this data has already been read [PROBLEMATIC CODE - REQUIRES REVISION, CONSIDER CHANGING FUNCTION CONTRACT]
	/* if (find(FilesAlreadyRead.begin(), FilesAlreadyRead.end(), filename) != FilesAlreadyRead.end()){
		throw error("The file titled: " + filename + " has already been read.", -2);
	}
	else {
		FilesAlreadyRead.push_back(filename);
	} */  

	string input;
	vector<string>results{};
	vector<TweetPackage>packagedTweets;
	bool ignore_commas{ false };
	int commaCount{ -1 }; // shifted by factor 1 to left (required)

	getline(fileInstance, input); // skip first line of CSV (assumed to be legend)
	while (getline(fileInstance, input)) {
		stringstream intermediateBuffer;
		TweetPackage buffer;
		for (int i = 0; i <= input.length(); ++i) {
			if (input[i] == '"' && ignore_commas == false) {
				ignore_commas = true;
			}
			else if (input[i] == '"' && ignore_commas == true) {
				ignore_commas = false;
			}

			if ((input[i] == ',' && ignore_commas == false) || i == input.length() ) { // comma, or new line - push result in
				if (input[i] == ',') { ++commaCount; }
				results.push_back(intermediateBuffer.str());

				// cout << commaCount << "--\n";
				// cout << results.back() << '\n';

				// cases for data to be pushed into tweetPackage buffer
				 if ((commaCount - 1) % 10 == 0) { // tweet
					buffer.Tweet = intermediateBuffer.str();
				}

				if ((commaCount - 2) % 10 == 0){ // retweet count
					buffer.Retweets = stoi(intermediateBuffer.str());
				}

				if ((commaCount - 3) % 10 == 0){ // reply count
					buffer.Replies = stoi(intermediateBuffer.str());
				}

				if ((commaCount - 4) % 10 == 0) { // like count
					buffer.Likes = stoi(intermediateBuffer.str());
				}

				if ((commaCount - 5) % 10 == 0) { // quote count
					buffer.Quotes = stoi(intermediateBuffer.str());

				} 

				if (i == input.length()) {
					packagedTweets.push_back(buffer);
				}
				intermediateBuffer.str("");
				intermediateBuffer.clear();
			}
			else {
				intermediateBuffer << input[i];
			}
		}
	}

	if (results.size() == 0) { // Empty CSV file
		return;
	}

	  /* for (int i = 0; i < results.size(); ++i) {
		cout << results[i] << '\n';
	}  */


	  for (int i = 0; i < packagedTweets.size(); ++i) {
		  cout << i << "--\n";
		  cout << packagedTweets[i].Tweet << " ";
		  cout << packagedTweets[i].Likes << '\n';
	  }  


	userProfile finalRes;
	// Subroutine to prepare/process the data, with the key idea being as follows:
	//  We know that data will be of format:
	//  #,Tweet,Retweet Count,Reply count,like count,quote count,Name,Username,number of Followers,number of Following,total number of tweets
	// Hence, in the vector results, we expect the 1st entry to be tweet, second retweet, third reply count, etc.

	// We only need to set these values once as they're the same throughout the CSV file [VALID ASSUMPTION?]
	finalRes.name = results[6];
	finalRes.username = results[7];
	finalRes.followerCount = stoi(results[8]);
	finalRes.followingCount = stoi(results[9]);
	finalRes.TotalTweets = stoi(results[10]);

	/*for (int i = 0; i < results.size(); i += 11) {
		TweetPackage tweetData;
		tweetData.Tweet = results[i+1];
		tweetData.Retweets = stoi(results[i + 2]);
		tweetData.Replies = stoi(results[i + 3]);
		tweetData.Likes = stoi(results[i + 4]);
		tweetData.Quotes = stoi(results[i + 5]);
		finalRes.Tweets.push_back(tweetData);

		// finalRes.userPersonality.processString(results[i]); // Process tweet for user profiling
	} */

	// this->write_profile_data_csv();
	this->write_twitter_data_csv();
	// finalRes.write_twitter_data_csv();
	// finalRes.write_profile_data_csv();

}