#include "repository.h"
#include "validator.h"
#include <sstream>

void RepoFile::loadFromFile()
{
	std::ifstream fin(fileName);
	if (!fin.is_open()) {
		std::vector<std::string> errors;
		errors.push_back("Error open file");
		throw ValidationException(errors);
	}
	std::vector<Movie> list;
	char line [256] { '\0' };
	char* token = nullptr;
	while (fin.getline(line, 256)) {
		char* column = strtok_s(line, ",", &token);
		const int index = atoi(column);
		column = strtok_s(nullptr, ",", &token);
		std::string title = column;
		column = strtok_s(nullptr, ",", &token);
		std::string genre = column;
		column = strtok_s(nullptr, ",", &token);
		std::string year = column;
		column = strtok_s(nullptr, ",", &token);
		std::string actor = column;
		list.push_back(Movie(index, title, genre, year, actor));
	}
	listOfMovies = list;
	fin.close();

}

void RepoFile::writeToFile()
{
	std::ofstream fout(fileName);
	if (!fout.is_open()) {
		std::vector<std::string> errors;
		errors.push_back("Error open file");
		throw ValidationException(errors);
	}
	for (auto& movie : listOfMovies)
	{
		fout << movie.getIndex() << ",";
		fout << movie.getTitle() << ",";
		fout << movie.getGenre() << ",";
		fout << movie.getYearOfRelease() << ",";
		fout << movie.getLeadingActor() << std::endl;
	}
	fout.close();
}

const std::vector<Movie>& RepoFile::getAll() const noexcept
{
	return listOfMovies;
}

void RepoFile::addMovie(const Movie& myMovie)
{
	//loadFromFile()
	listOfMovies.push_back(myMovie);
	writeToFile();
}

void RepoFile::deleteMovie(const int index)
{
	loadFromFile();
	unsigned int i = 0;
	for (auto &myMovie : listOfMovies) {
		if (myMovie.getIndex() == index) {
			std::vector<Movie> ::iterator it{ listOfMovies.erase(listOfMovies.begin() + i) };
		}
		i++;
	}
	writeToFile();
}

void RepoFile::updateMovie(const int index, const std::string newTitle, const std::string newGenre, const std::string newYear, const std::string newActor)
{
	loadFromFile();
	for (Movie& myMovie : listOfMovies) {
		if (myMovie.getIndex() == index) {
			myMovie.setTitle(newTitle);
			myMovie.setGenre(newGenre);
			myMovie.setLeadingActor(newActor);
			myMovie.setYearOfRelease(newYear);

		}
	}
	writeToFile();
} 










const std::vector<Movie>& RepoInMemory::getAll() const noexcept
{
	
	return listOfMovies;
}

void RepoInMemory::addMovie(const Movie& myMovie)
{
	listOfMovies.push_back(myMovie);
}

void RepoInMemory::deleteMovie(const int index) 
{
	unsigned int i = 0;
	for (auto& myMovie : listOfMovies) {
		if (myMovie.getIndex() == index) {
			std::vector<Movie> ::iterator it{ listOfMovies.erase(listOfMovies.begin() + i) };
		}
		i++;
	}
}

void RepoInMemory::updateMovie(const int index, const std::string newTitle, const std::string newGenre, const std::string newYear, const std::string newActor)
{
	for (Movie& myMovie : listOfMovies) {
		if (myMovie.getIndex() == index) {
			myMovie.setTitle(newTitle);
			myMovie.setGenre(newGenre);
			myMovie.setLeadingActor(newActor);
			myMovie.setYearOfRelease(newYear);

		}
	}
}









const std::vector<Movie>& RepoLab::getAll() const
{
	const bool isTrue = (rand() % 100) < (prob * 100);
	if (isTrue)
	{
		std::vector<std::string> errors;
		errors.push_back(" !!! UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY!!!");
		throw ValidationException(errors);
	}
		
	return listOfMovies;
}

void RepoLab::addMovie(const Movie& myMovie)
{
	const bool isTrue = (rand() % 100) < (prob * 100);
	if (isTrue)
	{
		std::vector<std::string> errors;
		errors.push_back(" !!! UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY!!!");
		throw ValidationException(errors);
	}

	std::pair<int, Movie> pair(myMovie.getIndex(), myMovie);
	dictOfMovies.insert(pair);
	
	/////
	
	listOfMovies.push_back(myMovie);
}

void RepoLab::deleteMovie(const int index)
{
	const bool isTrue = (rand() % 100) < (prob * 100);
	if (isTrue)
	{
		std::vector<std::string> errors;
		errors.push_back(" !!! UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY!!!");
		throw ValidationException(errors);
	}

	dictOfMovies.erase(index);

	/////
	
	unsigned int i = 0;
	for (auto& myMovie : listOfMovies) {
		if (myMovie.getIndex() == index) {
			std::vector<Movie> ::iterator it{ listOfMovies.erase(listOfMovies.begin() + i) };
		}
		i++;
	}
}

void RepoLab::updateMovie(const int index, const std::string newTitle, const std::string newGenre, const std::string newYear, const std::string newActor)
{
	const bool isTrue = (rand() % 100) < (prob * 100);
	if (isTrue)
	{
		std::vector<std::string> errors;
		errors.push_back(" !!! UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY UNLUCKY!!!");
		throw ValidationException(errors);
	}

	auto it = dictOfMovies.find(index);
	(*it).second.setTitle(newTitle);
	(*it).second.setGenre(newGenre);
	(*it).second.setLeadingActor(newActor);
	(*it).second.setYearOfRelease(newYear);

	/////

	for (Movie& myMovie : listOfMovies) {
		if (myMovie.getIndex() == index) {
			myMovie.setTitle(newTitle);
			myMovie.setGenre(newGenre);
			myMovie.setLeadingActor(newActor);
			myMovie.setYearOfRelease(newYear);

		}
	}
}


