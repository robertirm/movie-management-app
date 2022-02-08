#pragma once
#include <string>
#include <iostream>

class Movie {

private:
	int index = 0;
	std::string title;
	std::string genre;
	std::string yearOfRelease;
	std::string leadingActor;


public:	
	Movie() = default;
	/*
		Creates a movie
		@param title : the name of the movie
		@param genre : the genre of the movie
		@param yearOfRelease : the year of release for the movie
		@param leadingActor : the main actor of the movie
		@return : a movie object
	*/
	Movie(const int& index,
		const std::string& title,
		const std::string& genre,
		const std::string& yearOfRelease,
		const std::string& leadingActor) :
		index{ index },
		title{ title },
		genre{ genre },
		yearOfRelease{ yearOfRelease },
		leadingActor{ leadingActor }
	{};

	int getIndex() const noexcept;

	/*
		Copies a movies
		@param myMovie : the movie to be copied
		@return : a movie object
	*/
	Movie(const Movie& myMovie);

	/*
		Gets the title of the movie
		@return the name of the movie
	*/
	std::string getTitle() const;

	/*
		Gets the genre of the movie
		@return the genre of the movie
	*/
	std::string getGenre() const;

	/*
		Gets the year of release of the movie
		@return the year of release of the movie
	*/
	std::string getYearOfRelease() const;

	/*
		Gets the leading actor of the movie
		@return the name of the leading actor of the movie
	*/
	std::string getLeadingActor() const;

	/*
		Sets the title for a movie
		@param newTitle : the new title
		@return : the title of the movie will be changed
	*/
	void setTitle(std::string newTitle);

	/*
		Sets the genre for a movie
		@param newGenre : the hew genre
		@return : the genre of the movie will be changed
	*/
	void setGenre(std::string newGenre);

	/*
		Sets the year for a movie
		@param newYear : the new year
		@return : the year of the movie will be changed
	*/
	void setYearOfRelease(std::string newYear);

	/*
		Sets the leading actor for a movie
		@param newActor: the new leadin actor
		@return : the leading actor of the movie will be changed
	*/
	void setLeadingActor(std::string newActor);
};