
	Once the files are compiled and the application is running, it will bring up a menu. This menu will have multiple options:
	ENTER 1 to print information about specific customers,
	ENTER 2 to print information about a specific restaurant,
	ENTER 3 to print ratings for a specific restaurant,
	ENTER 4 to print out a breakdown of a certain customer attribute,
	ENTER 5 to print ratings for a specific customer,
	ENTER 6 to print a breakdown of cuisine types offered by restaurants,
	ENTER 7 to look up restaurants by cuisine type.
	ENTER 8 to print a breakdown of payment types accepted
	ENTER 9 to print a list of tables
	ENTER 10 to print a record in a table
	
	This menu will continue, until the number 0 is entered to exit.
	
	Some reports/queries will ask for an argument before running. Type the argument and hit ENTER
	
	The database functionality was used to load large tables (from CSV input data) and query them to generate various reports. The query function was the most widely used database feature because it allowed us to extract the particular information. Our database application never made use of the delete function. Once our tables were constructed, there was no need to delete any items from them and therefore the delete function was unnecessary for us.
	
	Some parts of our database application make use of more than one table. Menu option 3 allows the user to enter the name of a restaurant which must be converted to a 'placeID' through the 'Restaurants' table and then queried against the 'Ratings' table for the appropriate information. We also made extensive use of libraries 'AttributeList' class which essentailly represented a column within a table. This class allowed for simpler loop constructs.
