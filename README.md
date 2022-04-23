# TwitterProfiles

This is a pet project I've created after being inspired by R tweet package, which allows you to analyze stats of tweets from various users, such as tweet length, like, retweets, etc.

The idea of the project is as follows:
Using the tweepy python library, and Twitter's API - I created a python program that would (with manual tweaking unfortunately, I've yet to automate this part) retrieve and store certain information about a users most recent 100 (configurable to whatever) tweets. The information I chose to store were things like retweets, likes, tweet counts, followers, and a few others you can find in the python file. Note, these data are stored in CSV format.

Continuing on, based on these statistics, users would have personality profiles made that would be dynamically adjusted with inputted tweets after said tweets were analysed, and have an ad-hoc personality assigned to them, and stored.

For example, after analyzing Kanye West's 100 most recent tweets, a profile would be created for Kanye, in which traits like narcissism, aggression, empathy, etc would be documented and compared against an average baseline (Which for now, is arbitrarly set)

Please note that the python code wont work, because this API uses twitter accounts bearer token; and I've for obvious reasons not made that public.

As of April 23rd 2022, my good friend @rbangre has joined me on this project.
