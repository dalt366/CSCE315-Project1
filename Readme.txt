
	Once the files are compiled and the application is running, it will bring up a menu. This menu will have multiple options:
	ENTER 1 to print information about specific customers,
	ENTER 2 to print information about a specific restaurant,
	ENTER 3 to print ratings for a specific restaurant,
	ENTER 4 to print out a breakdown of a certain customer attribute,
	ENTER 5 to print ratings for a specific customer,
	ENTER 6 to print a breakdown of cuisine types offered by restaurants,
	ENTER 7 to look up restaurants by cuisine type.
	
	entering -1 and -2 was there for printing a list of tables, or printing a record in a table, respectively both used in debugging.
	
	This menu will continue, until the number 0 is entered to exit.
	
	Many of the different paths in the menu will ask for other information to be entered before information will be returned.
	
	How we used the database functionality is that we pulled the information is large files to a Database of Table full of Records, and then we used many of the 
	functions provided to pull information out of the Databases, and print them onto the screen. 
	
	Our main use of the Database function is using the query function to look into different tables for specific attributes, and used them for different uses. 
	
	The only function we did not fully get into our application Combine information from more than one table, we did use within the printRestaurantRatings function
	a pull place ID from the table and then used that information to pull from another table.
