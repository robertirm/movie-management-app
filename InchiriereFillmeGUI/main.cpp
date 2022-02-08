#include "gui.h"
#include "tests.h"

void testEverything()
{
	testDomain();
	testRepoFile();
	testRepoInMemory();
	testRepoLab();
	testRepoLabWithExceptions();
	testController();
	testValidator();
	testSearchSortFilter();
	testCart();
	testUndo();
}


//int main() {
//	testEverything();
//}

	
int main(int argc, char *argv[])
{
	testEverything();
	{
		QApplication a(argc, argv);
		
		std::string fileName = "movies.txt";
		RepoFile repo(fileName);
		//RepoInMemory repo;
		//RepoLab repo(0.5);
		Validator val;
		Controller ctrl{ repo, val };

		GUI ui(ctrl);
		ui.show();
		a.exec();
	}
}
