#include "validator.h"

std::ostream& operator<<(std::ostream& out, const ValidationException& errors)
{
	for (const auto& err : errors.messages)out << err << std::endl;
	return out;
}

void Validator::validateMovie(const Movie& myMovie)
{
	std::vector<std::string> errors;
	if( myMovie.getIndex() == 0)errors.push_back("The id can't be null!");
	if (myMovie.getTitle().size() == 0)errors.push_back("The title can't be null!");
	if (myMovie.getGenre().size() == 0)errors.push_back("The genre can't be null!");
	if (myMovie.getYearOfRelease().size() == 0)errors.push_back("The year can't be null!");
		try {
			validateNumber(myMovie.getYearOfRelease());
		}
		catch (ValidationException) {
			errors.push_back("The year must be a natural number!");
		}
	if (myMovie.getLeadingActor().size() == 0)errors.push_back("The leading actor can't be null!");
	if (errors.size() > 0)
		throw ValidationException(errors);

}

void Validator::validateOccurrence(const int index, const std::vector<Movie>& list)
{
	for (auto& myMovie : list) {
		if (myMovie.getIndex() == index)
			return;
	}
	std::vector<std::string> errors;
	errors.push_back("The movie doesn't exist!");
	throw ValidationException(errors);
}

void Validator::validateAdd(const int index, const std::vector<Movie>& list)
{
	std::vector<std::string> errors;
	for (auto& myMovie : list) {
		if (myMovie.getIndex() == index)
			errors.push_back("The movie already exists!");
			
	}
	if (errors.size() > 0)
		throw ValidationException(errors);
}

void Validator::validateNumber(const std::string& number)
{
	std::string::const_iterator it = number.begin();
	while (it != number.end() && std::isdigit(*it)) ++it;
	std::vector<std::string> errors;
	if (!number.empty() && it == number.end() == false)
		errors.push_back("Input needs to be a natural number!");
	if (errors.size() > 0)
		throw ValidationException(errors);
}

void Validator::validateExistingTitle(const std::string& title, const std::vector<Movie>& list)
{
	for (auto& myMovie : list) {
		if (myMovie.getTitle() == title)
			return;
	}
	std::vector<std::string> errors;
	errors.push_back("The movie can't be added to the cart because it doesn't exist!");
	throw ValidationException(errors);
}

