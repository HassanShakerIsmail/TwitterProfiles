#include "tweetPackage.h"
#include "userProfile.h"
int main() {
	try {
		userProfile x;
		x.setUsername("kanyewest");
		x.setName("ye");
		userProfile y;
		y.setUsername("JustinTrudeau");
		y.setName("Justin Trudeau");
		//x.read_twitter_data_csv("JustinTrudeau_twitterdata.csv");
		y.read_and_package_tdata_csv("JustinTrudeau_twitterdata.csv");
		y.clean_tweets();
		y.calc_summary_stats();
		y.tweets_file_summary();
	}
	catch (error x) {
		 x.displayError();
	}
}