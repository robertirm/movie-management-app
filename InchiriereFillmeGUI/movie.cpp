#include "movie.h"



Movie::Movie(const Movie& myMovie)
{
	//std::cout << "Copy!\n";
	index = myMovie.index;
	title = myMovie.title;
	genre = myMovie.genre;
	yearOfRelease = myMovie.yearOfRelease;
	leadingActor = myMovie.leadingActor;
}

int Movie::getIndex() const noexcept
{
	return index;
}

std::string Movie::getTitle() const
{
	return title;
}

std::string Movie::getGenre() const
{
	return genre;
}

std::string Movie::getYearOfRelease() const
{
	return yearOfRelease;
}

std::string Movie::getLeadingActor() const
{
	return leadingActor;
}

void Movie::setTitle(std::string newTitle)
{
	title = newTitle;
}

void Movie::setGenre(std::string newGenre)
{
	genre = newGenre;
}

void Movie::setYearOfRelease(std::string newYear)
{
	yearOfRelease = newYear;
}

void Movie::setLeadingActor(std::string newActor)
{
	leadingActor = newActor;
}
