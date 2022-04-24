#include "userProfile.h"

void UserProfile::setName(string name) {
	this->name = name;
}

void UserProfile::setUsername(string user) {
	this->username = user;
}

void UserProfile::calc_summary_stats() {
	for (int i = 0; i < this->tweets.size(); ++i) {
		if (this->tweets[i].isValidTweetPackage() == false || this->tweets[i].getAuthorUsername() != this->username) {
			continue;
		}
		else {
			this->totalLikes += this->tweets[i].getLikes();
			this->totalReplies += this->tweets[i].getReplies();
			this->totalRetweets += this->tweets[i].getRetweets();
			this->totalTweets += 1;
		}
	}
}


void UserProfile::clean_tweets() {
	for (int i = 0; i < this->tweets.size(); ++i) {
		if (this->tweets[i].isValidTweetPackage() == false) {
			 cout << "WARNING: Tweet " << i << " with content: " << this->tweets[i].getTweet() << " was removed.\n";
			 swap(this->tweets[i],this->tweets.back());
			 this->tweets.pop_back();
		} else if (this->tweets[i].getAuthorUsername() != this->username) {
			 cout << "WARNING: Tweet " << i << " with content: " << this->tweets[i].getTweet() << " was removed, due to differing author usernames.\n";
			 swap(this->tweets[i], this->tweets.back());
			 this->tweets.pop_back();
	
		} 
	}

}



// read_and_package_tdata_csv(filename) is a member function to the userprofile class that when fed in a filename with the associated
//	data, will append all data in the form of packaged tweets, to the userProfile's associated vector<tweetPackage>tweets vector.

// requires: 
//	assumes that inputted csv file only contains data corresponding to tweets for the userProfile implictly calling the function.
//  data must be in csv format: i,tweet,rt_count,rply_count,like_count,quote_count,name,user_name,follower_count,following_count,total_num_tweets
void UserProfile::read_and_package_tdata_csv(string filename) {
	ifstream fileInstance{ filename };
	if (fileInstance.fail()) {
		throw error("Failed to find fileinstance with name: " + filename, -1);
	}

	// Check if this data has already been read [PROBLEMATIC CODE - REQUIRES REVISION, CONSIDER CHANGING FUNCTION CONTRACT]
	if (find(FilesAlreadyRead.begin(), FilesAlreadyRead.end(), filename) != FilesAlreadyRead.end()) {
		throw error("The file titled: " + filename + " has already been read.", -2);
	}
	else {
		this->FilesAlreadyRead.push_back(filename);
	}

	string input;
	vector<string>results{};
	vector<TweetPackage>packagedTweets;
	bool ignore_commas{ false };
	int commaCount{ -1 }; 

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

			if ((input[i] == ',' && ignore_commas == false) || i == input.length()) { // comma, or new line - push result in
				if (input[i] == ',') { ++commaCount; }
				results.push_back(intermediateBuffer.str());

				if ((commaCount - 1) % 10 == 0) { // tweet
					buffer.setTweet(intermediateBuffer.str());
				}

				if ((commaCount - 2) % 10 == 0) { // retweet count
					buffer.setRetweets(stoi(intermediateBuffer.str()));
				}

				if ((commaCount - 3) % 10 == 0) { // reply count
					buffer.setReplies(stoi(intermediateBuffer.str()));
				}

				if ((commaCount - 4) % 10 == 0) { // like count
					buffer.setLikes(stoi(intermediateBuffer.str()));
				}

				if ((commaCount - 5) % 10 == 0) { // quote count
					buffer.setQuotes(stoi(intermediateBuffer.str()));
				}

				if ((commaCount - 6) % 10 == 0) { // Name
					buffer.setAuthorName(intermediateBuffer.str());
				}

				if ((commaCount - 7) % 10 == 0) { // username
					buffer.setAuthorUsername(intermediateBuffer.str());
				}

				if ((commaCount - 8) % 10 == 0) { // num followers
					buffer.setAuthorFollowers(stoi(intermediateBuffer.str()));
				}

				if ((commaCount - 9) % 10 == 0) { // num following
					buffer.setAuthorFollowing(stoi(intermediateBuffer.str()));
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
		this->FilesAlreadyRead.pop_back(); 
		return;
	}


	// Simplified console output -> keep?
	/*
	for (int i = 0; i < packagedTweets.size(); ++i) {
		cout << i << "------\n";
		cout << packagedTweets[i].getTweet() << '\n';
		cout << "likes: " << packagedTweets[i].getLikes() << '\n';
		cout << "retweets: " << packagedTweets[i].getRetweets() << '\n';
		cout << "quotes: " << packagedTweets[i].getQuotes() << '\n';
		cout << "replies: " << packagedTweets[i].getReplies() << '\n';
	} */

	for (int i = 0; i < packagedTweets.size(); ++i) {
		if (packagedTweets[i].getAuthorName() != this->name && packagedTweets[i].getAuthorUsername() != this->username) {
			cout << "WARNING: author display name and username for tweet: " << i << " do not match the associated profile for: " << this->username << ".\n";
			cout << "consider discarding, or seriously reviewing the offending tweet.\n";
		}

		this->tweets.push_back(packagedTweets[i]);
	}


}

void UserProfile::tweets_file_summary(string filename) {
	if (filename == "NULL") {
		filename = this->username + "_tweet_summary.txt";
	}

	if (fileExists(filename) == true){
		ofstream instance{ filename , ios_base::app};
		for (int i = 0; i < this->tweets.size(); ++i) {
			instance << i << "------\n";
			instance << tweets[i].getTweet() << '\n';
			instance << "likes: " << tweets[i].getLikes() << '\n';
			instance << "retweets: " << tweets[i].getRetweets() << '\n';
			instance << "quotes: " << tweets[i].getQuotes() << '\n';
			instance << "replies: " << tweets[i].getReplies() << '\n';
			if (i == this->tweets.size() - 1) {
				instance << "------\n";
				instance << "total tweets calculated for sample batch: " << this->tweets.size() << '\n';
				instance << "total likes across all tweets for sample batch: " << this->totalLikes << '\n';
				instance << "total replies across all tweets for sample batch: " << this->totalReplies << '\n';
				instance << "total retweets across all tweets for sample batch: " << this->totalRetweets << '\n';
			}
		}

	}
	else {
		ofstream instance{ filename };
		for (int i = 0; i < this->tweets.size(); ++i) {
			instance << i << "------\n";
			instance << tweets[i].getTweet() << '\n';
			instance << "likes: " << tweets[i].getLikes() << '\n';
			instance << "retweets: " << tweets[i].getRetweets() << '\n';
			instance << "quotes: " << tweets[i].getQuotes() << '\n';
			instance << "replies: " << tweets[i].getReplies() << '\n';
			if (i == this->tweets.size() - 1) {
				instance << "------\n";
				instance << "total tweets calculated for sample batch: " << this->tweets.size() << '\n';
				instance << "total likes across all tweets for sample batch: " << this->totalLikes << '\n';
				instance << "total replies across all tweets for sample batch: " << this->totalReplies << '\n';
				instance << "total retweets across all tweets for sample batch: " << this->totalRetweets << '\n';
			}
		}
	}
}

std::vector<TweetPackage> UserProfile::getTweets() {
	return this->tweets;
}

int UserProfile::getTotalLikes() {
	return this->totalLikes;
}

int UserProfile::getTotalReplies() {
	return this->totalReplies;
}

int UserProfile::getTotalRetweets() {
	return this->totalRetweets;
}

int UserProfile::getFollowerCount() {
	return this->followerCount; 
}

// write_twitter_data_csv() is a member function to userProfile that for a called userProfile,
//  will output it's collected twitter data to the userProfile's data file 
//  (or append the new data onto it, assuming the profile already has a storage file)
//  NOTE: that this does NOT print the userProfiles personality profile - something write_personality_profile_csv() handles.
/*void userProfile::write_twitter_data_csv() {
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

} */

