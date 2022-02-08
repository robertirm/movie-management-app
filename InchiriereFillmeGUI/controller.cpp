#include "controller.h"



const std::vector<Movie>& Controller::getAll() const 
{
	return repo.getAll(); 
}

void Controller::addMovie(const Movie& myMovie)
{
	//val.validateMovie(myMovie);
	val.validateAdd(myMovie.getIndex(), repo.getAll());
	repo.addMovie(myMovie);
	undoList.push_back(std::make_unique<UndoAdd>(repo, myMovie));
}

void Controller::deleteMovie(const int index)
{
	val.validateOccurrence(index, repo.getAll());
	undoList.push_back(std::make_unique<UndoDelete>(repo, searchByIndex(index)));
	repo.deleteMovie(index);
}

void Controller::updateMovie(const int index, const std::string newTitle, const std::string newGenre, const std::string newYear, const std::string newActor)
{
	val.validateMovie(Movie(index, newTitle, newGenre, newYear, newActor));
	val.validateOccurrence(index, repo.getAll());
	undoList.push_back(std::make_unique<UndoUpdate>(repo, searchByIndex(index)));
	repo.updateMovie(index, newTitle, newGenre, newYear, newActor);

}

void Controller::undo()
{
	if (undoList.empty()) {
		std::vector<std::string> errors;
		errors.push_back("Undo can't be done!");
		throw ValidationException(errors);
	}
	undoList.back()->doUndo();
	undoList.pop_back();
}

int Controller::searchMovie(int index) noexcept
{
	int i = 0;
	for (const Movie& myMovie : repo.getAll()) {
		if (myMovie.getIndex() == index) {
			return i;
		}
		i++;
	}
	return -1;
}

const Movie& Controller::searchByIndex(const int index)
{
	auto it = std::find_if(repo.getAll().begin(), repo.getAll().end(),
		[&index](const Movie& crtMovie) noexcept {
			return crtMovie.getIndex() == index;
		}
	);

	if (it == repo.getAll().end())
	{
		std::vector<std::string> errors;
		errors.push_back("The movie doesn't exist!");
		throw ValidationException(errors);
	}
	else 
		return *it;
}

const std::vector<Movie>& Controller::getAllCart() const noexcept
{
	return cart.getAll();	
}

void Controller::clearCart() noexcept
{
	cart.freeCart();
}

void Controller::addToCart(const std::string title)
{
	val.validateExistingTitle(title, repo.getAll());
	for (const Movie& myMovie : repo.getAll()) {
		if (myMovie.getTitle() == title) {
			cart.addToCart(myMovie);
			return;
		}
	}
}

void Controller::exportCartAsCSV(std::string filename)
{

	std::ofstream fout(filename+".csv");

	if (!fout.is_open()) {
		std::vector<std::string> errors;
		errors.push_back("Error open file");
		throw ValidationException(errors);
	}

	for (auto& movie : cart.getAll())
	{
		fout << movie.getIndex() << ",";
		fout << movie.getTitle() << ",";
		fout << movie.getGenre() << ",";
		fout << movie.getYearOfRelease() << ",";
		fout << movie.getLeadingActor();
		fout << std::endl;
	}
	fout.close();
}

void Controller::randomizeCart(const int numberOfMovies)
{
	if (numberOfMovies > repo.getAll().size())
	{
		std::vector<std::string> errors;
		errors.push_back("That many movies are not stored!");
		throw ValidationException(errors);
	}
	std::vector<Movie> shuffledMovies = repo.getAll();
	//unsigned int seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::shuffle(shuffledMovies.begin(), shuffledMovies.end(), std::default_random_engine(std::random_device{}()));
	
	int counter = numberOfMovies;
	while (counter > 0) {
		cart.addToCart(shuffledMovies.back());
		shuffledMovies.pop_back();
		counter--;
	}

}

std::map<std::string, DTO> Controller::movieCounterByYear()
{
	std::map<std::string, DTO> dictionary;
	for (const Movie& myMovie : repo.getAll()) {
		bool found = false;
		for (auto& pair : dictionary) {
			if (myMovie.getYearOfRelease() == pair.first) {
				pair.second.incrementCount();
				found = true;
				break;
			}
		}
		if (!found) {
			std::pair<std::string, DTO> pair (myMovie.getYearOfRelease(), DTO(myMovie.getYearOfRelease()));
			pair.second.incrementCount();
			dictionary.insert(pair);
		}
	}
	return dictionary;
}




std::vector<Movie> Controller::filter(std::function <bool(const Movie&)>funct) {
	std::vector<Movie> foundMovies(repo.getAll().size());
	auto it = std::copy_if(repo.getAll().begin(), repo.getAll().end(), foundMovies.begin(), funct);
	foundMovies.resize(std::distance(foundMovies.begin(), it));
	return foundMovies;
}

std::vector<Movie> Controller::filterByTitle(const std::string str)
{
	return filter([str](const Movie& mov) {
		return mov.getTitle().find(str) != std::string::npos;
		}
	);
}

std::vector<Movie> Controller::filterByYear(const std::string str)
{
	return filter([str](const Movie& mov) {
		return mov.getYearOfRelease().find(str) != std::string::npos;
		}
	);
}



std::vector<Movie> Controller::sort(std::function<bool(const Movie&, const Movie&)> funct)
{
	std::vector<Movie> sortedMovies{ repo.getAll() };
	std::sort(sortedMovies.begin(), sortedMovies.end(), funct);
	return sortedMovies;
}

std::vector<Movie> Controller::sortByTitle()
{
	return sort(
		[](const Movie& mov1, const Movie& mov2) {
			return mov1.getTitle() < mov2.getTitle();
		}
	);
}

std::vector<Movie> Controller::sortByLeadingActor()
{
	return sort(
		[](const Movie& mov1, const Movie& mov2) {
			return mov1.getLeadingActor() < mov2.getLeadingActor();
		}
	);
}

std::vector<Movie> Controller::sortByYearAndGenre()
{
	return sort(
		[](const Movie& mov1, const Movie& mov2) {
			if (mov1.getYearOfRelease() == mov2.getYearOfRelease())
				return mov1.getGenre() < mov2.getGenre();
			return mov1.getYearOfRelease() < mov2.getYearOfRelease();
		}
	);
}

