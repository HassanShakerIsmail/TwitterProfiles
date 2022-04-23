#include "twitterProfiles.h"
int main() {
	try {
		userProfile x;
		x.username = "kanyewest";
		x.name = "ye";
		//x.read_twitter_data_csv("JustinTrudeau_twitterdata.csv");
		x.read_and_package_tdata_csv("twitterdata.csv");
	}
	catch (error x) {
		 x.displayError();
	}
}