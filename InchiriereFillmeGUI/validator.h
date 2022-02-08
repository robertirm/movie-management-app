#include "repository.h"

class ValidationException {
private:
	std::vector<std::string> messages;
public:
	friend std::ostream& operator<<(std::ostream& out, const ValidationException& errors);

	ValidationException(const std::vector<std::string> errors) :
		messages{ errors } {};

	const std::vector<std::string>& getAll() const noexcept {
		return messages;
	}
};

/*
	Output representation of the ValidationException
*/	
std::ostream& operator<<(std::ostream& out, const ValidationException& errors);


class Validator {

public:
	/*
		Validates a movie
		@param mov: the given movie
		@exception ValidatorException if the movie is not valid
	*/
	void validateMovie(const Movie& mov);

	/*
		Checks if the index already exists in the list of movies
		@param index: the index to be checked
		@param list: list of movies
		@exception ValidatorException if the index is not present among the list movies
	*/
	void validateOccurrence(const int index, const std::vector<Movie>& list);

	/*
		Checks if the index doesn't exist in the list of movies
		@param index: the index to be checked
		@param list: list of movies
		@exception ValidatorException if the index is present among the list movies
	*/
	void validateAdd(const int index, const std::vector<Movie>& list);

	/*
		Checks if a string represent a natural number
		@param number: the index to be checked
		@exception ValidatorException if the index is not present among the list movies
	*/
	void validateNumber(const std::string& number);

	/*
		Checks if the title exists in the list of movies
		@param title: the title to be checked
		@param list: list of movies
		@exception ValidatorException if the title is not present among the list movies
	*/
	void validateExistingTitle(const std::string& title, const std::vector<Movie>& list);
};