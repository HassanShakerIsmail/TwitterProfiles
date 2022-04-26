#include "tweetPackage.h"
#include "UserProfile.h"
#include <string>
int main() {
	try {
		cout << "Please enter command from available list: (case sensitive)\n";
		cout << "'LOAD' will prompt you for a username to load a profile from file.\n";
		cout << "'DELETE' will delete your current profile.\n";
		cout << "'CLOSE' will store, and close the current profile.\n";
		cout << "'END' will end this program.\n";
		string input;
		bool flagstatus{ false };
		UserProfile* x = new UserProfile;
		while (input != "END") {
			cin >> input;
			if (input == "LOAD") {
				string username;
				cout << "Please enter username of profile you wish to load.\n";
				cin >> username;
				*x = UserProfile::load_profile(username);
				flagstatus = true;
			}

			if (input == "CREATE") { // add more here
				if (flagstatus != true) {
					cout << "Please enter the name, and username respectively; of the profile you're creating.\n";
					string name;
					string username;
					cin >> name >> username;
					x->setName(name);
					x->setUsername(username);
					cout << "Please enter csv filenames to aggregrate data from. When you are done, simply enter 'X'\n";
					string fileNameInputs;
					char clean;
					while (fileNameInputs != "X") {
						cin >> fileNameInputs;
						if (fileNameInputs != "X") {
							x->read_and_package_tdata_csv(fileNameInputs);

							cout << "Would you like to clean tweets? (y/n)\n";
							cin >> clean;
							if (clean == 'y') {
								x->clean_tweets();
							}
							else if (clean == 'n') {
								continue;
							}
						}
	
					}
					
				}
				else {
					cout << "Unable to create a profile as you already have one initialized.\n";
				}
			}

			if (input == "CLOSE") {
				char clean;
				cout << "would you like to clean profile before summary? (y/n)\n";
				cin >> clean;
				if (clean == 'y') {
					x->clean_tweets();
				}
				x->update_profile();
				x->tweets_file_summary();
				x->store_profile();
				flagstatus = false;
			}

			if (input == "DELETE") {
				if (flagstatus == false) {
					cout << "No profile to delete. Please try again.\n";
				}
				else {
					char tweetSumBool;
					cout << "Delete associated tweet summary?(y/n)\n";
					cin >> tweetSumBool;
					if (tweetSumBool == 'y') {
						string filename = x->getUsername() + "_tweet_summary.txt";
						remove(filename.c_str());
					}
					UserProfile::delete_profile(x->getUsername());
					flagstatus = false;
					x->clearTweets();
					x->clearFilesRead();
				}

			}

			cout << "Please enter command from available list: (case sensitive)\n";
			cout << "'LOAD' will prompt you for a username to load a profile from file.\n";
			cout << "'DELETE' will delete your current profile.\n";
			cout << "'CLOSE' will store, and close the current profile.\n";
			cout << "'END' will end this program.\n";
			
		}
		delete x;
	}
	catch (error x) {
		 x.displayError();
	}
}

// MANUAL TESTING

/*
			UserProfile* x = UserProfile::create_dynamic_profile("kanyewest", "ye");
			x->read_and_package_tdata_csv("twitterdata.csv");
			x->clean_tweets();
			x->update_profile();
			x->tweets_file_summary();
			x->store_profile();
			UserProfile::delete_dynamic_profile(x); */

			//UserProfile z = UserProfile::load_profile("JustinTrudeau");
			/*cout << z.name << '\n';
			cout << z.username << '\n';
			cout << z.followerCount << '\n';
			cout << z.followingCount << '\n';
			cout << z.TotalTweets << '\n';
			cout << z.TotalReplies << '\n';
			cout << z.TotalRetweets << '\n'; */


			/*
			UserProfile x;
			x.setUsername("kanyewest");
			x.setName("ye");
			x.read_and_package_tdata_csv("twitterdata.csv");
			x.clean_tweets();
			x.calc_summary_stats();
			x.update_profile();
			x.tweets_file_summary();
			x.store_profile();


			UserProfile y;
			y.setUsername("JustinTrudeau");
			y.setName("Justin Trudeau");
			//x.read_twitter_data_csv("JustinTrudeau_twitterdata.csv");
			y.read_and_package_tdata_csv("JustinTrudeau_twitterdata.csv");
			y.clean_tweets();
			y.tweets_file_summary();
			y.update_profile();
			y.store_profile(); */