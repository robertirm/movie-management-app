#include "console.h"



void Console::printMovies( const std::vector<Movie>& listOfMovies) const
{	
	if (listOfMovies.size() == 0) {
		std::cout << "No movies!\n";
		return;
	}

	for (const Movie& myMovie : listOfMovies) {
		std::cout << "#INDEX : " << myMovie.getIndex() << " | ";
		std::cout << "#TITLE : " << myMovie.getTitle() << " | ";
		std::cout << "#GENRE : " << myMovie.getGenre() << " | ";
		std::cout << "#YEAR : " << myMovie.getYearOfRelease() << " | ";
		std::cout << "#LEADING ACTOR : " << myMovie.getLeadingActor();
		std::cout << std::endl;
	}
}

void Console::printMenu()
{
	std::cout << "\n-------MOVIE RENTAL---------\n";
	std::cout << "1 - print the list of movies\n";
	std::cout << "2 - add a movie\n";
	std::cout << "3 - update a movie\n";
	std::cout << "4 - delete a movie\n";
	std::cout << "5 - search for a movie\n";
	std::cout << "6 - filter the list of movies\n";
	std::cout << "7 - sort the list of movies\n";
	std::cout << "8 - add a movie to the cart\n";
	std::cout << "9 - clear the cart\n";
	std::cout << "10 - randomize a cart\n";
	std::cout << "11 - print the cart\n";
	std::cout << "12 - export the cart in a .csv file\n";
	std::cout << "13 - report of the number of movies by year\n";
	std::cout << "14 - undo\n";
	std::cout << "0 - exit\n";
}

void Console::run()
{
	Validator val;
	printMenu();
	int cmd = 0;
	while (true) {
		std::cout << "\n--------------------------------------------\n";
		std::cout << "\nYOU HAVE " << ctrl.getAllCart().size() << " MOVIES IN THE CART!\n";
		std::cout << ">>>>> ";
		std::cin >> cmd;
		std::cout << std::endl;

		if (cmd == 0)
			break;
		else if (cmd == 1) {
			std::cout << "------STORED MOVIES------" << std::endl;

			try
			{
				printMovies(ctrl.getAll());
			}
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}
		}
		else if (cmd == 2) {
			std::string title, genre, year, leadingActor;
			std::string given_index;
			int index;
			std::cout << "ENTER INDEX: "; std::cin >> given_index;
			try {
				val.validateNumber(given_index);
				index = stoi(given_index);

				std::cout << "ENTER TITLE: "; std::cin >> title;
				std::cout << "ENTER GENRE: "; std::cin >> genre;
				std::cout << "ENTER YEAR: "; std::cin >> year;
				val.validateNumber(year);
				std::cout << "ENTER LEADING ACTOR: "; std::cin >> leadingActor;

				ctrl.addMovie(Movie(index, title, genre, year, leadingActor));
				std::cout << "The movie was added!\n";
			}
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}
			
		}
		else if (cmd == 3) {
			std::string title, genre, year, leadingActor;
			std::string given_index;
			int index;
			std::cout << "ENTER INDEX: "; std::cin >> given_index;
			try {
				val.validateNumber(given_index);
				index = stoi(given_index);
				std::cout << "ENTER NEW TITLE: "; std::cin >> title;
				std::cout << "ENTER NEW GENRE: "; std::cin >> genre;
				std::cout << "ENTER NEW YEAR: "; std::cin >> year;
				val.validateNumber(year);
				std::cout << "ENTER NEW LEADING ACTOR: "; std::cin >> leadingActor;
				ctrl.updateMovie(index, title, genre, year, leadingActor);
				std::cout << "The movie was updated!\n";
			}
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}

		}
		else if (cmd == 4) {
			std::string given_index;
			int index;
			std::cout << "INDEX OF THE MOVIE TO BE DELETED: "; std::cin >> given_index;
			try {
				val.validateNumber(given_index);
				index = stoi(given_index);
				ctrl.deleteMovie(index);
				std::cout << "The movie was deleted!\n";
			}
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}

		} 
		else if (cmd == 5) {
			std::string given_index;
			int index;
			std::cout << "INDEX OF THE MOVIE TO BE SEARCHED: "; std::cin >> given_index;
			try {
				val.validateNumber(given_index);
				index = stoi(given_index);
				val.validateOccurrence(index, ctrl.getAll());
				//const int i = ctrl.searchMovie(index);
				//Movie myMovie = ctrl.searchByIndex(index);
				std::cout << "#INDEX : " << ctrl.searchByIndex(index).getIndex() << " | ";
				std::cout << "#TITLE : " << ctrl.searchByIndex(index).getTitle() << " | ";
				std::cout << "#GENRE : " << ctrl.searchByIndex(index).getGenre() << " | ";
				std::cout << "#YEAR : " << ctrl.searchByIndex(index).getYearOfRelease() << " | ";
				std::cout << "#LEADING ACTOR : " << ctrl.searchByIndex(index).getLeadingActor();
				std::cout << std::endl;

			}
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}
		}
		else if (cmd == 6) {
			std::cout << "1 - by title \n";
			std::cout << "2 - by year of release \n";
			std::string given_mode;
			int mode;
			std::cout << "MODE : "; std::cin >> given_mode;
			try {
				val.validateNumber(given_mode);
				mode = stoi(given_mode);
				if (mode == 1){
					std::string title;
					std::cout << "ENTER TITLE: "; std::cin >> title;
					std::vector<Movie> filteredList = ctrl.filterByTitle(title);
					printMovies(filteredList);
				}
				else if (mode == 2) {
					std::string year;
					std::cout << "ENTER YEAR: "; std::cin >> year;
					val.validateNumber(year);
					std::vector<Movie> filteredList = ctrl.filterByYear(year);
					printMovies(filteredList);
				}

			} 
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}

		}
		else if (cmd == 7) {
			std::cout << "1 - by title \n";
			std::cout << "2 - by leading actor \n";
			std::cout << "3 - by year of release and genre \n";
			std::string given_mode;
			int mode;
			std::cout << "MODE : "; std::cin >> given_mode;
			try {
				val.validateNumber(given_mode);
				mode = stoi(given_mode);
				if (mode == 1) {
					std::vector<Movie> sortedList = ctrl.sortByTitle();
					printMovies(sortedList);
				}
				else if (mode == 2) {
					std::vector<Movie> sortedList = ctrl.sortByLeadingActor();
					printMovies(sortedList);
				}
				else if (mode == 3) {
					std::vector<Movie> sortedList = ctrl.sortByYearAndGenre();
					printMovies(sortedList);
				}
			}
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}

		}
		else if (cmd == 8) {
			std::string title;
			std::cout << "The title to be added: "; std::cin >> title;
			try {
				ctrl.addToCart(title);
				std::cout << "The movie was added to the cart!" << std::endl;
			}
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}
		}
		else if (cmd == 9) {
			std::cout << "The cart is now empty!" << std::endl;
			ctrl.clearCart();
		}
		else if (cmd == 10) {
			std::string number;
			std::cout << "The size of the cart : "; std::cin >> number;
			int nr;
			try {
				val.validateNumber(number);
				nr = stoi(number);
				ctrl.randomizeCart(nr);
				std::cout << "The cart was generated!" << std::endl;
			} 
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}
			
		}
		else if (cmd == 11) {
			std::cout << "------CART------" << std::endl;
			printMovies(ctrl.getAllCart());
		}
		else if (cmd == 12) {
			std::string fileName;
			std::cout << "Enter the name of the file to be stored(no need to include '.csv') :"; std::cin >> fileName;
			ctrl.exportCartAsCSV(fileName);
			std::cout << fileName << " .csv was created and the cart was written in it!" << std::endl;
		}
		else if (cmd == 13) {
			for (auto& p : ctrl.movieCounterByYear()) {
					std::cout << "#YEAR: " << p.first << " #NR OF MOVIES: " << p.second.getCount() << std::endl;
				}
		}
		else if (cmd == 14) {
			try
			{
				ctrl.undo();
				std::cout << "Undo has been done!\n";
			}
			catch (const ValidationException& e) {
				std::cout << e << std::endl;
			}
		}
	}
	
}
