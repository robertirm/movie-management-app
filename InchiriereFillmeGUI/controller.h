#pragma once
#include "repository.h"
#include "validator.h"
#include <algorithm>
#include <functional>
#include <random>
#include <chrono>
#include <map>


class DTO {
private:
	std::string year;
	int count;
public:
	DTO() = default;

	DTO(const std::string yr) : year{ yr }, count {0}{};

	std::string getYear() const {
		return year;
	}

	int getCount() const noexcept {
		return count;
	}

	void incrementCount() noexcept {
		count++;
	}
};

class RentCart {
private:
	std::vector<Movie> rentedMovies;

public:
	RentCart() = default;

	/*
		Adds a movie to the cart
		@param mov: the movie to be added
	*/
	void addToCart(const Movie& mov) {
		rentedMovies.push_back(mov);
	}

	/*
		Empties the cart
	*/
	void freeCart() noexcept {
		rentedMovies.clear();
	}

	/*
		Gets the current list of movies from the cart
		@return a list of movies
	*/
	const std::vector<Movie>& getAll() const noexcept {
		return rentedMovies;
	}
};

class UndoAbstractClass {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAbstractClass() = default;
};


class UndoAdd : public UndoAbstractClass {
private:
	Movie addedMovie;
	Repo& repo;
public:
	UndoAdd(Repo& r, const Movie& m) : repo{ r }, addedMovie{ m }{};
	void doUndo() override {
		repo.deleteMovie(addedMovie.getIndex());
	}
};

class UndoDelete : public UndoAbstractClass {
private:
	Movie deletedMovie;
	Repo& repo;
public:
	UndoDelete(Repo& r, const Movie& m) : repo{ r }, deletedMovie{ m }{};
	void doUndo() override {
		repo.addMovie(deletedMovie);
	}
};

class UndoUpdate : public UndoAbstractClass {
private:
	Movie updatedMovie;
	Repo& repo;
public:
	UndoUpdate(Repo& r, const Movie& m) : repo{ r }, updatedMovie{ m }{};
	void doUndo() override {
		repo.updateMovie(updatedMovie.getIndex(), 
			updatedMovie.getTitle(), 
			updatedMovie.getGenre(), 
			updatedMovie.getYearOfRelease(), 
			updatedMovie.getLeadingActor()
		);
	}
};


class Controller {
	
private:
	Repo& repo;
	Validator& val;
	RentCart cart;
	std::vector<std::unique_ptr<UndoAbstractClass>> undoList;

public:
	Controller(Repo& r, Validator& v) noexcept : repo{ r }, val{ v } {};


	/*
		Gets the list of movies
		@return a list of movies
	*/
	const std::vector<Movie>& getAll() const ;

	/*
		Add a movie to the list of movies
		@param myMovie: the movie to pe added
		@return 0 if the movie was added, -1 otherwise
	*/
	void addMovie(const Movie& myMovie);

	/*
		Delete a movie based on his name
		@param titleToBeDeleted: the title of the movie to be deleted
		@return the position of the deleted movie or -1 if the movie doesn't exist
	*/
	void deleteMovie(const int index);


	/*
		Delete a movie based on his name
		@param title: the title of the movie to be updated
		@param newTitle : the new title
		@param newGenre : the new genre
		@param newYear : the new year
		@param newActor : the new actor
		@return the position of the updated movie or -1 if the movie doesn't exist
	*/
	void updateMovie(const int index, const std::string newTitle, const std::string newGenre, const std::string newYear, const std::string newActor);

	/*
		Filters the movies by a criterion
		@param funct: function of filtration
		@return a vector with the filtered movies
	*/
	std::vector<Movie> filter(std::function <bool(const Movie&)>funct);

	/*
		Filters the movies by title
		@param str: the title to be searched
		@return a vector with the filtered movies
	*/
	std::vector<Movie> filterByTitle(const std::string str);
	
	/*
		Filters the movies by year
		@param str: the year to be searched
		@return a vector with the filtered movies
	*/
	std::vector<Movie> filterByYear(const std::string str);

	/*
		Sorts the movies by some given criteria
		@param funct: function representing the criteria
		@return a vector with the sorted movies
	*/
	std::vector<Movie> sort(std::function <bool(const Movie&, const Movie&)>funct);

	/*
		Sorts the movies by title
		@return a vector with the sorted movies
	*/
	std::vector<Movie> sortByTitle();

	/*
		Sorts the movies by leading actor
		@return a vector with the sorted movies
	*/
	std::vector<Movie> sortByLeadingActor();

	/*
		Sorts the movies by year and genre
		@return a vector with the sorted movies
	*/
	std::vector<Movie> sortByYearAndGenre();

	/*
		Search for a movie with the given index
		@param index: the given index 
		@return the position int the list of the Movie with the given index 
			or -1 if it doesn't appear
	*/
	int searchMovie(int index) noexcept;

	/*
		Gets the list of movies that are currently in the rental cart
		@return a list of movies
	*/
	const std::vector<Movie>& getAllCart() const noexcept;

	/*
		Empties the cart 
	*/
	void clearCart() noexcept;

	/*
		Adds a movie to the cart based on a given title
		@param title: the title of the movie to be added
		@exception ValidationException: if the movie with the given name doesn't exist
	*/
	void addToCart(const std::string title);

	/*
		Populates the cart with random movies from the RepoFile
		@param numberOfMovies: the size of the generated cart
		@exception ValidationException: there are fewer movies stored in the RepoFile 
			than the wanted amount of them to be added to the cart 
	*/
	void randomizeCart(const int numberOfMovies);

	/*
		Store rent cart in a given .csv file
		@param filename: the name of the file where the movies should be stored
	*/
	void exportCartAsCSV(std::string filename);


	/*
		Gets a map with the keys being years and the values beeing DTOs who store the number of movies from that year
		@return std::map with the years and the numbers of movies for each year
	*/
	std::map<std::string, DTO> movieCounterByYear();

	/*
		Searches for a movie with the given index
		@param index: the id of the number
		@exception ValidationException : the movie with the given index doesn't exist
		@return the movie with the index
	*/
	const Movie& searchByIndex(const int index);

	/*
		Undo of the add, delete and update functionalities
	*/
	void undo();
};





