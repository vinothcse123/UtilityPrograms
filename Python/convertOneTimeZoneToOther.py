import datetime
import pytz
my_timestamp=datetime.datetime.now()

old_timezone = pytz.timezone("US/Eastern")
new_timezone = pytz.timezone("Asia/Kolkata")


new_timezone_timestamp = old_timezone.localize(my_timestamp).astimezone(new_timezone)

print (new_timezone_timestamp.strftime("%Y-%m-%d %H:%M:%S"))
print(datetime.datetime.now(datetime.timezone.utc).astimezone().tzinfo)


#https://en.wikipedia.org/wiki/List_of_tz_database_time_zones

#https://stackoverflow.com/questions/31977563/how-do-you-convert-a-datetime-timestamp-from-one-timezone-to-another-timezone
