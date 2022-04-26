#include "UserProfile.h"

#pragma warning(disable:4996)
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

const string UserProfile::getUsername() {
	return this->username;
}
void UserProfile::setName(string name) {
	this->name = name;
}

void UserProfile::setUsername(string user) {
	this->username = user;
}

void UserProfile::delete_dynamic_profile(UserProfile* prof) {
	delete prof;

}

UserProfile* UserProfile::create_dynamic_profile(string username,string name) {
	UserProfile* result = new UserProfile(name, username);
	return result;
}

void UserProfile::clearFilesRead() {
	this->FilesAlreadyRead.clear();

}

void UserProfile::clearTweets() {
	this->Tweets.clear();
}


void UserProfile::update_profile() {
	//this->clean_tweets();
	if (this->Tweets.back().getAuthorFollowers() != this->followerCount) {
		cout << "WARNING: Profile follower count did not match most recent tweet follower count, was updated to most recent tweet follower count.\n";
		this->followerCount = this->Tweets.back().getAuthorFollowers();
	}

	if(this->Tweets.back().getAuthorFollowing() != this->followingCount){
		cout << "WARNING: Profile following count did not match most recent tweet following count, was updated to most recent tweet following count.\n";
		this->followingCount = this->Tweets.back().getAuthorFollowing();
	}

	this->calc_summary_stats();



}

// want to refactor this function: lot's of reused code that artificially increases the code length.
// there's got to be a better way to parse the profile file.
UserProfile UserProfile::load_profile(string username) {
	ifstream instance{ username + "_profile.txt" };
	if (instance.fail()) {
		cout << "WARNING: Profile associated with username: " << username << " was NOT found. A default profile empty profile was returned.\n";
		UserProfile empty;
		return empty;
	}
	else {
		UserProfile result;
		string buffer;
		stringstream intermediateBuffer;
		instance.seekg(7, ios_base::beg);
		char inp;

		while (instance >> noskipws >> inp) {
			if (inp == 39) {
				break;
			}

			intermediateBuffer << inp;
		}
		result.name = intermediateBuffer.str();
		intermediateBuffer.str("");

		instance.seekg(0,ios_base::beg);
		getline(instance, buffer);
		getline(instance, buffer);

		for (int i = 10; i < buffer.length() && buffer[i] != '\n' && buffer[i] != 39; ++i) {
			intermediateBuffer << buffer[i];
		}

		result.username = intermediateBuffer.str();
		intermediateBuffer.str("");

		getline(instance, buffer);
		for (int i = 15; i < buffer.length() && buffer[i] != '\n' && buffer[i] != 39; ++i) {
			intermediateBuffer << buffer[i];
		}
		result.followerCount = stoi(intermediateBuffer.str());
		intermediateBuffer.str("");

		getline(instance, buffer);
		for (int i = 16; i < buffer.length() && buffer[i] != '\n' && buffer[i] != 39; ++i) {
			intermediateBuffer << buffer[i];
		}

		result.followingCount = stoi(intermediateBuffer.str());
		intermediateBuffer.str("");

		getline(instance, buffer);
		for (int i = 22; i < buffer.length() && buffer[i] != '\n' && buffer[i] != 39; ++i) {
			intermediateBuffer << buffer[i];
		}
		result.TotalTweets = stoi(intermediateBuffer.str());
		intermediateBuffer.str("");

		getline(instance, buffer);
		for (int i = 33; i < buffer.length() && buffer[i] != '\n' && buffer[i] != 39; ++i) {
			intermediateBuffer << buffer[i];
		}

		result.TotalReplies = stoi(intermediateBuffer.str());
		intermediateBuffer.str("");

		getline(instance, buffer);
		for (int i = 34; i < buffer.length() && buffer[i] != '\n' && buffer[i] != 39; ++i) {
			intermediateBuffer << buffer[i];
		}
		result.TotalRetweets = stoi(intermediateBuffer.str());
		intermediateBuffer.str("");

		getline(instance, buffer);
		getline(instance, buffer);
		getline(instance, buffer);
		while (getline(instance, buffer)) {
			for (char c : buffer) {
				if (c == 39) {
					break;
				}
				else {
					intermediateBuffer << c;
				}
			}
			result.FilesAlreadyRead.push_back(intermediateBuffer.str());
			intermediateBuffer.str("");


		}

		for (int i = 0; i < result.FilesAlreadyRead.size(); ++i) {
			cout << "Data from file: " << result.FilesAlreadyRead[i] << " was automatically loaded onto profile.\n";
			result.load_and_package_tdata_csv(result.FilesAlreadyRead[i]);
		}
		return result;
	}

}


void UserProfile::store_profile() {
	string filename = this->username + "_profile.txt";
	auto date = chrono::system_clock::now();
	time_t dt = chrono::system_clock::to_time_t(date);
			ofstream instance{ this->username + "_profile.txt", ios_base::trunc};
			//instance.seekp(0,ios_base::beg);
			instance << "Name: " << "'" + this->name + "'" << '\n';
			instance << "Username: " << this->username << '\n';
			instance << "Follower count: " << this->followerCount << '\n';
			instance << "Following count: " << this->followingCount << '\n';
			instance << "Total tweets analyzed: " << this->TotalTweets << '\n';
			instance << "Total replies across all tweets: " << this->TotalReplies << '\n';
			instance << "Total retweets across all tweets: " << this->TotalRetweets << '\n';
			instance << "Created: " << ctime(&dt) << '\n';
			instance << "Profile created using following files: " << '\n';
			//instance.seekp(ios_base::end);
			for (string file : this->FilesAlreadyRead) {
				instance << file << '\n';
			}
			// instance << personality_summary(this->userPersonality);

}

void UserProfile::delete_profile(string username) {
	string filename = username + "_profile.txt";
	ifstream fileInstance{ filename };
	if (fileInstance.fail()) {
		throw error("Failed to find fileinstance with name: " + filename, -1);
		return;
	}
	fileInstance.close();
	remove(filename.c_str());



}


void UserProfile::calc_summary_stats() {
	for (int i = 0; i < this->Tweets.size(); ++i) {
		if (this->Tweets[i].isValidTweetPackage() == false || this->Tweets[i].getAuthorUsername() != this->username) {
			continue;
		}
		else {
			this->TotalLikes += this->Tweets[i].getLikes();
			this->TotalReplies += this->Tweets[i].getReplies();
			this->TotalRetweets += this->Tweets[i].getRetweets();
			this->TotalTweets += 1;
		}
	}

}


void UserProfile::clean_tweets() {
	for (int i = 0; i < this->Tweets.size(); ++i) {
		if (this->Tweets[i].isValidTweetPackage() == false) {
			 cout << "WARNING: Tweet " << i << " with content: " << this->Tweets[i].getTweet() << " was removed.\n";
			 swap(this->Tweets[i],this->Tweets.back());
			 this->Tweets.pop_back();
		} else if (this->Tweets[i].getAuthorUsername() != this->username) {
			 cout << "WARNING: Tweet " << i << " with content: " << this->Tweets[i].getTweet() << " was removed, due to differing author usernames.\n";
			 swap(this->Tweets[i], this->Tweets.back());
			 this->Tweets.pop_back();
	
		} 
	}

}



// read_and_package_tdata_csv(filename) is a member function to the UserProfile class that when fed in a filename with the associated
//	data, will append all data in the form of packaged tweets, to the UserProfile's associated vector<tweetPackage>tweets vector.

// requires: 
//	assumes that inputted csv file only contains data corresponding to tweets for the UserProfile implictly calling the function.
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
				//cout << input[i] << '\n';
				//++commaCount;
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

				if (((commaCount - 9) % 10 == 0) && input[i] == ',') { // num following
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

	for (int i = 0; i < packagedTweets.size(); ++i) {
		if (packagedTweets[i].getAuthorName() != this->name && packagedTweets[i].getAuthorUsername() != this->username) {
			cout << "WARNING: author display name and username for tweet: " << i << " do not match the associated profile for: " << this->username << ".\n";
			cout << "consider discarding, or seriously reviewing the offending tweet.\n";
		}

		this->Tweets.push_back(packagedTweets[i]);
	}




}

void UserProfile::tweets_file_summary(string filename) {
	if (filename == "NULL") {
		filename = this->username + "_tweet_summary.txt";
	}

	if (fileExists(filename) == true){
		ofstream instance{ filename , ios_base::app};
		for (int i = 0; i < this->Tweets.size(); ++i) {
			instance << i << "------\n";
			instance << Tweets[i].getTweet() << '\n';
			instance << "likes: " << Tweets[i].getLikes() << '\n';
			instance << "retweets: " << Tweets[i].getRetweets() << '\n';
			instance << "quotes: " << Tweets[i].getQuotes() << '\n';
			instance << "replies: " << Tweets[i].getReplies() << '\n'; 
			if (i == this->Tweets.size() - 1) {
				instance << "------\n";
				instance << "total tweets calculated for sample batch: " << this->Tweets.size() << '\n';
				instance << "total likes across all tweets for sample batch: " << this->TotalLikes << '\n';
				instance << "total replies across all tweets for sample batch: " << this->TotalReplies << '\n';
				instance << "total retweets across all tweets for sample batch: " << this->TotalRetweets << '\n';
			}
		}

	}
	else {
		ofstream instance{ filename };
		for (int i = 0; i < this->Tweets.size(); ++i) {
			instance << i << "------\n";
			instance << Tweets[i].getTweet() << '\n';
			instance << "likes: " << Tweets[i].getLikes() << '\n';
			instance << "retweets: " << Tweets[i].getRetweets() << '\n';
			instance << "quotes: " << Tweets[i].getQuotes() << '\n';
			instance << "replies: " << Tweets[i].getReplies() << '\n';
			instance << "following: " << Tweets[i].getAuthorFollowing() << '\n';
			if (i == this->Tweets.size() - 1) {
				instance << "------\n";
				instance << "total tweets calculated for sample batch: " << this->Tweets.size() << '\n';
				instance << "total likes across all tweets for sample batch: " << this->TotalLikes << '\n';
				instance << "total replies across all tweets for sample batch: " << this->TotalReplies << '\n';
				instance << "total retweets across all tweets for sample batch: " << this->TotalRetweets << '\n';
			}
		}
	}



}

// altered version of read_and_package_tdata_csv specifically for loading a profile.
void UserProfile::load_and_package_tdata_csv(string filename) {
	ifstream fileInstance{ filename };
	if (fileInstance.fail()) {
		throw error("Failed to find fileinstance with name: " + filename, -1);
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
				//cout << input[i] << '\n';
				//++commaCount;
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

				if (((commaCount - 9) % 10 == 0) && input[i] == ',') { // num following
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

	for (int i = 0; i < packagedTweets.size(); ++i) {
		if (packagedTweets[i].getAuthorName() != this->name && packagedTweets[i].getAuthorUsername() != this->username) {
			cout << "WARNING: author display name and username for tweet: " << i << " do not match the associated profile for: " << this->username << ".\n";
			cout << "consider discarding, or seriously reviewing the offending tweet.\n";
		}

		this->Tweets.push_back(packagedTweets[i]);
	}

}



