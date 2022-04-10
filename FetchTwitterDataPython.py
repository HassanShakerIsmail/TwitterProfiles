import tweepy
import configparser
import pandas as pd
import os

# read configuartions
# rawConfigParser used instead of ConfigParser due to clash with bearer_token value
config = configparser.RawConfigParser()
ini_path = os.path.join(os.getcwd(),'twitterKeys.txt')
config.read(ini_path)

print(config)
api_key = config.get('twitter', 'api_key')
api_key_secret = config['twitter']['api_key_secret']

access_token = config['twitter']['access_token']
access_token_secret = config['twitter']['access_token_secret']

bearer_token = config.get('twitter','bearer_token')

# authentication
auth = tweepy.OAuthHandler(api_key, api_key_secret)
auth.set_access_token(access_token,access_token_secret)
api = tweepy.API(auth)

# fetch tweets from home-timeline REQUIRES ELEVATED ACCESS
# public_tweets = api.home_timeline()

#fetch tweets from specified user REQUIRES ELEVATED ACCESS
#response = api.user_timeline(screen_name = "kanyewest",count=200, include_rts = False, tweet_mode = 'extended')

client = tweepy.Client(bearer_token)


# fetch tweet information from specified ID profile (previous 100)
response = client.get_users_tweets(169686021,tweet_fields="created_at,public_metrics,author_id",user_fields="location,id,name,username",
                                 expansions=['author_id'],max_results=100)
user_information_response = client.get_user(id=169686021,user_fields="public_metrics")
print(user_information_response.data["public_metrics"])

cols = ['Tweet', 'Retweet Count','Reply count','like count', 'quote count', 'Name', 'Username', 'number of Followers'
        , 'number of Following', 'total number of tweets']
tweetData = []

# fetch user information from specified ID profile 
followersCount = user_information_response.data["public_metrics"]["followers_count"]
followingCount = user_information_response.data["public_metrics"]["following_count"]
tweetCount = user_information_response.data["public_metrics"]["tweet_count"]



# aggregrate tweet and user information
for tweet in response.data:
    username = ""
    name = ""

    # match names and usernames with tweet author
    for user in response.includes['users']:
        if user.id == tweet.author_id:
            username = user.username
            name = user.name
            break

    tweetData.append([tweet.text, tweet.public_metrics['retweet_count'],
                        tweet.public_metrics['reply_count'], tweet.public_metrics['like_count'],
                        tweet.public_metrics['quote_count'], name, username, followersCount, followingCount, tweetCount])


data = pd.DataFrame(tweetData, columns=cols)
print(data)
data.to_csv(os.path.join(os.getcwd(),'twitterdata.csv'))
