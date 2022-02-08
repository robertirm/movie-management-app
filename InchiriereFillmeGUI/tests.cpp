#include "tests.h"

void testDomain()
{
	Movie myMovie = Movie(1111, "Spectre", "Action/Adventure", "2015", "Daniel Craig");
	assert(myMovie.getTitle() == "Spectre");
	assert(myMovie.getGenre() == "Action/Adventure");
	assert(myMovie.getYearOfRelease() == "2015");
	assert(myMovie.getLeadingActor() == "Daniel Craig");

}

void testValidator() {
	Validator myVal;
	Movie myMovie = Movie(1234, "", "", "w", "");
	try {
		myVal.validateMovie(myMovie);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	std::string myNumber = "123";
	try {
		myVal.validateNumber(myNumber);
		assert(true);
	}
	catch (ValidationException) {
		assert(false);
	}

	myNumber = "abc";
	try {
		myVal.validateNumber(myNumber);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}


}

void testRepoLabWithExceptions() {
	RepoLab myRepo(1);
	try {
		assert(myRepo.getAll().size() == 0);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		myRepo.addMovie(Movie(1111, "Spectre", "Action/Adventure", "2015", "Daniel Craig"));
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try
	{

		myRepo.updateMovie(1111, "Skyfall", "Action/Adventure", "2012", "Daniel Craig");
		assert(false);
	}
	catch (ValidationException)
	{
		assert(true);

	}

	try
	{
		myRepo.deleteMovie(1111);
		assert(false);
	}
	catch (ValidationException)
	{
		assert(true);
	}
}

void testRepoLab() {
	RepoLab myRepo(0);
	try {
		assert(myRepo.getAll().size() == 0);
		assert(true);
	}
	catch (ValidationException) {
		assert(false);
	}

	try {
		myRepo.addMovie(Movie(1111, "Spectre", "Action/Adventure", "2015", "Daniel Craig"));
		assert(true);
	}
	catch (ValidationException) {
		assert(false);
	}

	try
	{

		myRepo.updateMovie(1111, "Skyfall", "Action/Adventure", "2012", "Daniel Craig");
		assert(true);
	}
	catch (ValidationException)
	{
		assert(false);

	}

	try
	{
		myRepo.deleteMovie(1111);
		assert(true);
	}
	catch (ValidationException)
	{
		assert(false);
	}
}

void testRepoInMemory() {
	RepoInMemory myRepo;
	assert(myRepo.getAll().size() == 0);

	// test add movie
	myRepo.addMovie(Movie(1111, "Spectre", "Action/Adventure", "2015", "Daniel Craig"));
	assert(myRepo.getAll().size() == 1);
	assert(myRepo.getAll().at(0).getTitle() == "Spectre");
	assert(myRepo.getAll().at(0).getGenre() == "Action/Adventure");
	assert(myRepo.getAll().at(0).getYearOfRelease() == "2015");
	assert(myRepo.getAll().at(0).getLeadingActor() == "Daniel Craig");


	myRepo.addMovie(Movie(2222, "Man of Steel", "Action/Adventure/Sci-FI", "2013", "Henry Cavill"));
	myRepo.addMovie(Movie(3333, "Jurassic World", "Action/Adventure/Sci-FI", "2015", "Chris Pratt"));
	assert(myRepo.getAll().size() == 3);

	// test update movie
	myRepo.updateMovie(1111, "Skyfall", "Action/Adventure", "2012", "Daniel Craig");
	assert(myRepo.getAll().at(0).getTitle() == "Skyfall");
	assert(myRepo.getAll().at(0).getGenre() == "Action/Adventure");
	assert(myRepo.getAll().at(0).getYearOfRelease() == "2012");
	assert(myRepo.getAll().at(0).getLeadingActor() == "Daniel Craig");

	// test delete movie
	myRepo.deleteMovie(1111);
	assert(myRepo.getAll().size() == 2);
	assert(myRepo.getAll().size() == 2);
}


void testRepoFile()
{
	std::string fileName = "test.txt";
	RepoFile myRepo(fileName);
	assert(myRepo.getAll().size() == 0);

	// test add movie
	myRepo.addMovie(Movie(1111, "Spectre", "Action/Adventure", "2015", "Daniel Craig"));
	assert(myRepo.getAll().size() == 1);
	assert(myRepo.getAll().at(0).getTitle() == "Spectre");
	assert(myRepo.getAll().at(0).getGenre() == "Action/Adventure");
	assert(myRepo.getAll().at(0).getYearOfRelease() == "2015");
	assert(myRepo.getAll().at(0).getLeadingActor() == "Daniel Craig");


	myRepo.addMovie(Movie(2222, "Man of Steel", "Action/Adventure/Sci-FI", "2013", "Henry Cavill"));
	myRepo.addMovie(Movie(3333, "Jurassic World", "Action/Adventure/Sci-FI", "2015", "Chris Pratt"));
	assert(myRepo.getAll().size() == 3);

	// test update movie
	myRepo.updateMovie(1111, "Skyfall", "Action/Adventure", "2012", "Daniel Craig");
	assert(myRepo.getAll().at(0).getTitle() == "Skyfall");
	assert(myRepo.getAll().at(0).getGenre() == "Action/Adventure");
	assert(myRepo.getAll().at(0).getYearOfRelease() == "2012");
	assert(myRepo.getAll().at(0).getLeadingActor() == "Daniel Craig");

	// test delete movie
	myRepo.deleteMovie(1111);
	assert(myRepo.getAll().size() == 2);
	assert(myRepo.getAll().size() == 2);

	std::ofstream file("test.txt");
	file.close();
}

void testController()
{
	Validator val;
	std::string fileName = "test.txt";
	RepoFile repo(fileName);
	Controller ctrl{ repo, val };
	assert(ctrl.getAll().size() == 0);

	// test add movie
	ctrl.addMovie(Movie(1111, "Spectre", "Action/Adventure", "2015", "Daniel Craig"));
	assert(ctrl.getAll().size() == 1);
	assert(ctrl.getAll().at(0).getTitle() == "Spectre");
	assert(ctrl.getAll().at(0).getGenre() == "Action/Adventure");
	assert(ctrl.getAll().at(0).getYearOfRelease() == "2015");
	assert(ctrl.getAll().at(0).getLeadingActor() == "Daniel Craig");
	try {
		ctrl.addMovie(Movie(1111, "Spectre", "Action/Adventure", "2015", "Daniel Craig"));
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	ctrl.addMovie(Movie(2222, "Man of Steel", "Action/Adventure/Sci-FI", "2013", "Henry Cavill"));
	ctrl.addMovie(Movie(3333, "Jurassic World", "Action/Adventure/Sci-FI", "2015", "Chris Pratt"));
	assert(ctrl.getAll().size() == 3);

	// test update movie
	try {
		ctrl.updateMovie(1535, "a", "a", "1", "a");
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	ctrl.updateMovie(1111, "Skyfall", "Action/Adventure", "2012", "Daniel Craig");
	assert(ctrl.getAll().at(0).getTitle() == "Skyfall");
	assert(ctrl.getAll().at(0).getGenre() == "Action/Adventure");
	assert(ctrl.getAll().at(0).getYearOfRelease() == "2012");
	assert(ctrl.getAll().at(0).getLeadingActor() == "Daniel Craig");

	// test delete movie
	ctrl.deleteMovie(1111);
	assert(ctrl.getAll().size() == 2);
	try {
		ctrl.deleteMovie(33);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	assert(ctrl.getAll().size() == 2);

	std::ofstream file("test.txt");
	file.close();
}

void testSearchSortFilter() {
	Validator val;
	std::string fileName = "test.txt";
	RepoFile repo(fileName);
	Controller ctrl{ repo,val };
	ctrl.addMovie(Movie(1111, "BBB", "Action/Adventure", "2015", "bbb"));
	ctrl.addMovie(Movie(2222, "CCC", "Action/Adventure/Sci-FI", "2013", "aaa"));
	ctrl.addMovie(Movie(3333, "AAA", "Action/Adventure/Sci-FI", "2015", "ccc"));

	std::map<std::string, DTO> dict = ctrl.movieCounterByYear();
	assert(dict.size() == 2);

	assert(dict.at("2015").getYear() == "2015");
	assert(dict.at("2015").getCount() == 2);

	try {
		const Movie foundMovie = ctrl.searchByIndex(124);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	try {
		const Movie foundMovie = ctrl.searchByIndex(2222);
		assert(true);
	}
	catch (ValidationException) {
		assert(false);
	}

	int found = ctrl.searchMovie(2222);
	assert(found == 1);
	found = ctrl.searchMovie(124);
	assert(found == -1);

	std::vector<Movie> list;
	list = ctrl.filterByTitle("A");
	assert(list.size() == 1);
	list = ctrl.filterByYear("2015");
	assert(list.size() == 2);

	list = ctrl.sortByTitle();
	assert(list.at(0).getTitle() == "AAA");
	list = ctrl.sortByYearAndGenre();
	assert(list.at(0).getTitle() == "CCC");
	ctrl.updateMovie(3333, "AAA", "Action/Adventure", "2015", "ccc");
	list = ctrl.sortByYearAndGenre();
	list = ctrl.sortByLeadingActor();
	assert(list.at(0).getLeadingActor() == "aaa");


	std::ofstream file("test.txt");
	file.close();
}

void testCart() {
	Validator val;
	std::string fileName = "test.txt";
	RepoFile repo(fileName);
	Controller ctrl{ repo,val };
	ctrl.addMovie(Movie(1111, "BBB", "Action/Adventure", "2015", "bbb"));
	ctrl.addMovie(Movie(2222, "CCC", "Action/Adventure/Sci-FI", "2013", "aaa"));
	ctrl.addMovie(Movie(3333, "AAA", "Action/Adventure/Sci-FI", "2015", "ccc"));
	
	
	assert(ctrl.getAllCart().size() == 0);
	try {
		ctrl.addToCart("QWERTY");
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}
	ctrl.addToCart("BBB");
	ctrl.addToCart("AAA");
	assert(ctrl.getAllCart().size() == 2);
	ctrl.exportCartAsCSV("testCartFile");
	int number_of_lines = 0;
	std::string line;
	std::ifstream testFile("testCartFile.csv");
	while (std::getline(testFile, line))
		++number_of_lines;
	assert(number_of_lines == 2);

	ctrl.clearCart();
	assert(ctrl.getAllCart().size() == 0);

	
	try {
		ctrl.randomizeCart(10);
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	ctrl.randomizeCart(2);
	assert(ctrl.getAllCart().size() == 2);

	ctrl.clearCart();

	ctrl.randomizeCart(1);
	assert(ctrl.getAllCart().size() == 1);
	std::ofstream file("test.txt");
	file.close();
}

void testUndo() {
	Validator val;
	std::string fileName = "test.txt";
	RepoFile repo(fileName);
	Controller ctrl{ repo, val };
	ctrl.addMovie(Movie(1111, "BBB", "Action/Adventure", "2015", "bbb"));
	ctrl.addMovie(Movie(2222, "CCC", "Action/Adventure/Sci-FI", "2013", "aaa"));
	ctrl.addMovie(Movie(3333, "AAA", "Action/Adventure/Sci-FI", "2015", "ccc"));
	ctrl.updateMovie(1111, "Skyfall", "Action/Adventure", "2012", "Daniel Craig");
	ctrl.deleteMovie(1111);

	ctrl.undo();
	assert(ctrl.getAll().size() == 3);
	ctrl.undo();
	assert(ctrl.searchByIndex(1111).getYearOfRelease() == "2015");
	ctrl.undo();
	ctrl.undo();
	ctrl.undo();
	assert(ctrl.getAll().size() == 0);
	try {
		ctrl.undo();
		assert(false);
	}
	catch (ValidationException) {
		assert(true);
	}

	std::ofstream file("test.txt");
	file.close();
}