#pragma once
#include "controller.h"
#include <iostream>


class Console {
private:
	Controller& ctrl;

public:
	Console(Controller& c) noexcept : ctrl{ c } {};

	/*
		Prints a list of movies
		@param listOfMovies: the list of movies to be printed
	*/
	void printMovies(const std::vector<Movie>& listOfMovies) const;

	/*
		Prints the menu of the application
	*/
	void printMenu();

	/*
		Run application
	*/
	void run();

};
