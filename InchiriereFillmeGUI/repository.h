#pragma once
#include "movie.h"
#include <vector>
#include <fstream>
#include <map>
#include <memory>


class Repo {
public:
	virtual const std::vector<Movie>& getAll() const  = 0;
	virtual void addMovie(const Movie& myMovie) = 0;
	virtual void deleteMovie(const int index) = 0;
	virtual void updateMovie(const int index, 
							const std::string newTitle, 
							const std::string newGenre, 
							const std::string newYear, 
							const std::string newActor) = 0;
	virtual ~Repo() = default;
};



class RepoLab :public Repo {
	
	
	std::map<int, Movie> dictOfMovies;
	double prob;
	std::vector<Movie> listOfMovies;
	
public:
	RepoLab() = default;
	
	RepoLab(double p): prob{ p } {};

	const std::vector<Movie>& getAll() const override;
	
	void addMovie(const Movie& myMovie) override;
	
	void deleteMovie(const int index) override;

	void updateMovie(const int index, 
		const std::string newTitle,
		const std::string newGenre, 
		const std::string newYear, 
		const std::string newActor) override;

};



class RepoFile:public Repo{
private:
	std::vector<Movie> listOfMovies;
	std::string fileName;
	void loadFromFile();
	void writeToFile();

public:
	RepoFile() = default;
	RepoFile(std::string& file) : fileName{ file } {
		loadFromFile();
	};

	/*
		Gets the list of movies
		@return a list of movies
	*/
	const std::vector<Movie>& getAll() const noexcept override;

	/*
		Add a movie to the list of movies
		@param myMovie: the movie to pe added
		@return 0 if the movie was added, -1 otherwise
	*/
	void addMovie(const Movie& myMovie) override;

	/*
		Delete a movie based on his name
		@param titleToBeDeleted: the title of the movie to be deleted
		@return the position of the deleted movie or -1 if the movie doesn't exist
	*/
	void deleteMovie(const int index) override;

	/*
		Delete a movie based on his name
		@param index: the index of the movie to be updated
		@param newTitle : the new title
		@param newGenre : the new genre
		@param newYear : the new year
		@param newActor : the new actor
		@return the position of the updated movie or -1 if the movie doesn't exist
	*/
	void updateMovie(const int index, const std::string newTitle, const std::string newGenre, const std::string newYear, const std::string newActor) override;

};


class RepoInMemory : public Repo{

	std::vector<Movie> listOfMovies;

public:
	/*
		Gets the list of movies
		@return a list of movies
	*/
	const std::vector<Movie>& getAll() const noexcept override;


	/*
		Add a movie to the list of movies
		@param myMovie: the movie to pe added
		@return 0 if the movie was added, -1 otherwise
	*/
	void addMovie(const Movie& myMovie) override ;


	/*
		Delete a movie based on his name
		@param titleToBeDeleted: the title of the movie to be deleted
		@return the position of the deleted movie or -1 if the movie doesn't exist
	*/
	void deleteMovie(const int index) override;


	/*
		Delete a movie based on his name
		@param index: the index of the movie to be updated
		@param newTitle : the new title
		@param newGenre : the new genre
		@param newYear : the new year
		@param newActor : the new actor
		@return the position of the updated movie or -1 if the movie doesn't exist
	*/
	void updateMovie(const int index, const std::string newTitle, const std::string newGenre, const std::string newYear, const std::string newActor) override;

};