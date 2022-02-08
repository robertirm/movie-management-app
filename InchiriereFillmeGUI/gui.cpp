#include "gui.h"


// create the gui
void GUI::initGUI()
{
	setLayout(appLayout);

	QVBoxLayout* listLayout = new QVBoxLayout;
	listLayout->addWidget(listOfMovies);
	listLayout->addWidget(refreshButton);


	QHBoxLayout* sortLayout = new QHBoxLayout;
	sortLayout->addWidget(sortByTitleButton);
	sortLayout->addWidget(sortByLeadingActorButton);
	sortLayout->addWidget(sortByYearAndGenreButton);
	listLayout->addLayout(sortLayout);
	appLayout->addLayout(listLayout);

	QVBoxLayout* funcionsLayout = new QVBoxLayout;
	appLayout->addLayout(funcionsLayout);

	QFormLayout* movieLayout = new QFormLayout;
	QLabel* idLabel = new QLabel("ID");
	QLabel* titleLabel = new QLabel("Title");
	QLabel* genreLabel = new QLabel("Genre");
	QLabel* yearLabel = new QLabel("Year");
	QLabel* actorLabel = new QLabel("Leading Actor");
	QLabel* header = new QLabel("Selected Movie : ");
	movieLayout->addRow(header);
	movieLayout->addRow(idLabel, idTextBox);
	movieLayout->addRow(titleLabel, titleTextBox);
	movieLayout->addRow(genreLabel, genreTextBox);
	movieLayout->addRow(yearLabel, yearTextBox);
	
	

	movieLayout->addRow(actorLabel, actorTextBox);
	funcionsLayout->addLayout(movieLayout);

	QHBoxLayout* crudLayout = new QHBoxLayout;
	crudLayout->addWidget(addButton);
	crudLayout->addWidget(deleteButton);
	crudLayout->addWidget(updateButton);
	crudLayout->addWidget(undoButton);
	funcionsLayout->addLayout(crudLayout);

	QHBoxLayout* searchLayout = new QHBoxLayout;
	searchTextBox->setPlaceholderText("Enter the id of the movie to be searched");
	searchLayout->addWidget(searchTextBox);
	searchLayout->addWidget(searchButton);
	funcionsLayout->addLayout(searchLayout);

	QHBoxLayout* filterLayout = new QHBoxLayout;
	filterTextBox->setPlaceholderText("Enter a title or year");
	filterLayout->addWidget(filterTextBox);
	filterLayout->addWidget(filterByTitleButton);
	filterLayout->addWidget(filterByYearButton);
	funcionsLayout->addLayout(filterLayout);

	// windows for add
	addWindow->setLayout(addWindowLayout);
	addWindowLayout->addLayout(addForm);
	QHBoxLayout* addButtons = new QHBoxLayout;
	addButtons->addWidget(addWindowButton);
	addButtons->addWidget(addCancelWindowButton);
	addWindowLayout->addLayout(addButtons);
	QLabel* addIdLabel = new QLabel("ID");
	QLabel* addTitleLabel = new QLabel("Title");
	QLabel* addGenreLabel = new QLabel("Genre");
	QLabel* addYearLabel = new QLabel("Year");
	QLabel* addActorLabel = new QLabel("Leading Actor");
	addForm->addRow(addIdLabel, addIdTextBox);
	addForm->addRow(addTitleLabel, addTitleTextBox);
	addForm->addRow(addGenreLabel, addGenreTextBox);
	addForm->addRow(addYearLabel, addYearTextBox);
	addForm->addRow(addActorLabel, addActorTextBox);

	// window for update
	updateWindow->setLayout(updateWindowLayout);
	updateWindowLayout->addLayout(updateForm);
	QHBoxLayout* updateButtons = new QHBoxLayout;
	updateButtons->addWidget(updateWindowButton);
	updateButtons->addWidget(updateCancelWindowButton);
	updateWindowLayout->addLayout(updateButtons);
	QLabel* updateTitleLabel = new QLabel("Title");
	QLabel* updateGenreLabel = new QLabel("Genre");
	QLabel* updateYearLabel = new QLabel("Year");
	QLabel* updateActorLabel = new QLabel("Leading Actor");
	updateForm->addRow(updateTitleLabel, updateTitleTextBox);
	updateForm->addRow(updateGenreLabel, updateGenreTextBox);
	updateForm->addRow(updateYearLabel, updateYearTextBox);
	updateForm->addRow(updateActorLabel, updateActorTextBox);

	QHBoxLayout* cartBar = new QHBoxLayout;
	funcionsLayout->addLayout(cartBar);

	QHBoxLayout* reportAndExit = new QHBoxLayout;
	reportAndExit->addWidget(reportButton);
	reportAndExit->addWidget(exitButton);
	funcionsLayout->addLayout(reportAndExit);
	
	//window for report
	reportWindow->setLayout(reportWindowLayout);
	reportTable->setHorizontalHeaderLabels(QStringList() << "Year" << "Nr of Movies");
	reportWindowLayout->addWidget(reportTable);


	QVBoxLayout* cartLayout = new QVBoxLayout;
	appLayout->addLayout(cartLayout);
	cartLayout->addWidget(cart);
	cartLayout->addLayout(firstLine);
	cartLayout->addLayout(secondLine);
	cartLayout->addLayout(thirdLine);
	cartLayout->addLayout(forthLine);
	cartLayout->addLayout(fifthLine);
	firstLine->addWidget(addToCart);
	firstLine->addWidget(addSearch);
	addSearch->setPlaceholderText("Enter the name of the movie");
	secondLine->addWidget(randomizeCart);
	secondLine->addWidget(randomSize);
	randomSize->setPlaceholderText("Nr. of movies to be added");
	thirdLine->addWidget(exportCart);
	thirdLine->addWidget(exportName);
	exportName->setPlaceholderText("File name (no need for .csv)");
	forthLine->addWidget(refreshCart);
	forthLine->addWidget(clearCart);
	fifthLine->addWidget(open1);
	fifthLine->addWidget(open2);
}

// create connection between signals and slots
void GUI::connectSignalsSlots()
{
	// refresh button
	QObject::connect(refreshButton, &QPushButton::clicked, [&]() {
		reloadList(ctrl.getAll());
		});

	// sort by title button
	QObject::connect(sortByTitleButton, &QPushButton::clicked, [&]() {
		reloadList(ctrl.sortByTitle());
		});

	// sort by actor button
	QObject::connect(sortByLeadingActorButton, &QPushButton::clicked, [&]() {
		reloadList(ctrl.sortByLeadingActor());
		});

	// sort by year and genre button
	QObject::connect(sortByYearAndGenreButton, &QPushButton::clicked, [&]() {
		reloadList(ctrl.sortByYearAndGenre());
		});

	// show the selected item details
	QObject::connect(listOfMovies, &QListWidget::itemSelectionChanged, [&]() {
		if (listOfMovies->selectedItems().size() == 0) {
			idTextBox->setText("");
			titleTextBox->setText("");
			genreTextBox->setText("");
			yearTextBox->setText("");
			actorTextBox->setText("");
		}
		else {
			const Movie& movie = ctrl.searchByIndex(listOfMovies->selectedItems().at(0)->data(Qt::UserRole).toInt());
			idTextBox->setText(QString::number(movie.getIndex()));
			titleTextBox->setText(QString::fromStdString(movie.getTitle()));
			genreTextBox->setText(QString::fromStdString(movie.getGenre()));
			yearTextBox->setText(QString::fromStdString(movie.getYearOfRelease()));
			actorTextBox->setText(QString::fromStdString(movie.getLeadingActor()));
		}
		});

	// button to open window for add
	QObject::connect(addButton, &QPushButton::clicked, [&]() {
		addWindow->setModal(true);
		addWindow->show();
		});

	// add button from the adding window
	QObject::connect(addWindowButton, &QPushButton::clicked, [&]() {
		Validator val;
		
		try {
			val.validateNumber(addYearTextBox->text().toStdString());
			val.validateNumber(addIdTextBox->text().toStdString());
			int id = addIdTextBox->text().toInt();
			std::string title = addTitleTextBox->text().toStdString();
			std::string genre = addGenreTextBox->text().toStdString();
			std::string year = addYearTextBox->text().toStdString();
			std::string actor = addActorTextBox->text().toStdString();
			Movie myMovie(id, title, genre, year, actor);
			val.validateMovie(myMovie);
			ctrl.addMovie(myMovie);
		}
		catch (const ValidationException& e) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getAll().at(0)));
		}
		reloadList(ctrl.getAll());
		//loadButtons();
		addWindow->close();
		});

	// cancel button from the adding window
	QObject::connect(addCancelWindowButton, &QPushButton::clicked, [&]() {
		addWindow->close();
		});

	// delete button
	QObject::connect(deleteButton, &QPushButton::clicked, [&]() {
		if (listOfMovies->selectedItems().size() == 0) {
			QMessageBox::warning(nullptr, "Warning", "Please select a movie!");
		}
		else
		{
			ctrl.deleteMovie(idTextBox->text().toInt());
			reloadList(ctrl.getAll());
			//loadButtons();

		}
		
		});

	// update button to open th window for updating
	QObject::connect(updateButton, &QPushButton::clicked, [&]() {
		if (listOfMovies->selectedItems().size() == 0) {
			QMessageBox::warning(nullptr, "Warning", "Please select a movie!");
		}
		else {
			updateTitleTextBox->setText(titleTextBox->text());
			updateGenreTextBox->setText(genreTextBox->text());
			updateYearTextBox->setText(yearTextBox->text());
			updateActorTextBox->setText(actorTextBox->text());
			updateWindow->setModal(true);
			updateWindow->show();
		}
		});

	// update button from the updating window
	QObject::connect(updateWindowButton, &QPushButton::clicked, [&]() {
		Validator val;
		try
		{
			val.validateNumber(updateYearTextBox->text().toStdString());
			std::string title = updateTitleTextBox->text().toStdString();
			std::string genre = updateGenreTextBox->text().toStdString();
			std::string year = updateYearTextBox->text().toStdString();
			std::string actor = updateActorTextBox->text().toStdString();
			int id = idTextBox->text().toInt();
			ctrl.updateMovie(id, title, genre, year, actor);
			reloadList(ctrl.getAll());
		}
		catch (const ValidationException& e)
		{
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getAll().at(0)));
		}
		updateWindow->close();
		});

	// cancel button from the updating window
	QObject::connect(updateCancelWindowButton, &QPushButton::clicked, [&]() {
		updateWindow->close();
		});

	// undo button
	QObject::connect(undoButton, &QPushButton::clicked, [&]() {
		try
		{
			ctrl.undo();
			reloadList(ctrl.getAll());
			//loadButtons();
		}
		catch (const ValidationException& e)
		{
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getAll().at(0)));
		}
		});

	// search button
	QObject::connect(searchButton, &QPushButton::clicked, [&]() {
		Validator val;
		if (searchTextBox->text() == "") {
			QMessageBox::warning(nullptr, "Warning", "Please enter an id!");
		}
		try
		{
			val.validateNumber(searchTextBox->text().toStdString());
			int index = searchTextBox->text().toInt();
			val.validateOccurrence(index, ctrl.getAll());
			Movie foundMovie = ctrl.searchByIndex(index);
			idTextBox->setText(QString::number(foundMovie.getIndex()));
			titleTextBox->setText(QString::fromStdString(foundMovie.getTitle()));
			genreTextBox->setText(QString::fromStdString(foundMovie.getGenre()));
			yearTextBox->setText(QString::fromStdString(foundMovie.getYearOfRelease()));
			actorTextBox->setText(QString::fromStdString(foundMovie.getLeadingActor()));
			QMessageBox::information(nullptr, "Succes!", "The movie has been found!");
		}
		catch (const ValidationException& e)
		{
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getAll().at(0)));
		}
		});

	// filter by title button
	QObject::connect(filterByTitleButton, &QPushButton::clicked, [&]() {
		if (filterTextBox->text() == "") {
			QMessageBox::warning(nullptr, "Warning", "Please enter some text!");
		}
		else {
			auto filteredMovies = ctrl.filterByTitle(filterTextBox->text().toStdString());
			if (filteredMovies.empty())
				QMessageBox::warning(nullptr, "Warning", "Nothing found!");
			else {
				QString size = QString::number(filteredMovies.size());
				QMessageBox::information(nullptr, "Succes!", size + " movies found!");
				//reloadList(filteredMovies);
				reloadListWithColor(ctrl.getAll(), filteredMovies);
			}
		}
		});

	QObject::connect(filterTextBox, &QLineEdit::textChanged, [&]() {
		if (filterTextBox->text() == "") {
		reloadList(ctrl.getAll()); 
		return;
		}
		auto filteredMovies = ctrl.filterByTitle(filterTextBox->text().toStdString());		
		reloadListWithColor(ctrl.getAll(), filteredMovies);		
		});

	// filter by year button
	QObject::connect(filterByYearButton, &QPushButton::clicked, [&]() {

		if (filterTextBox->text() == "") {
			QMessageBox::warning(nullptr, "Warning", "Please enter some text!");
		}
		else {
			try
			{
				Validator val;
				val.validateNumber(filterTextBox->text().toStdString());
				auto filteredMovies = ctrl.filterByYear(filterTextBox->text().toStdString());
				if (filteredMovies.empty())
					QMessageBox::warning(nullptr, "Warning", "Nothing found!");
				else {
					QString size = QString::number(filteredMovies.size());
					QMessageBox::information(nullptr, "Succes!", size + " movies found!");
					//reloadList(filteredMovies);
					reloadListWithColor(ctrl.getAll(), filteredMovies);
				}
			}
			catch (const ValidationException& e)
			{
				QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getAll().at(0)));
			}
		}
		});

	// exit button 
	QObject::connect(exitButton, &QPushButton::clicked, [&]() {
		close();
		});

	// report button
	QObject::connect(reportButton, &QPushButton::clicked, [&]() {
		std::map<std::string, DTO> dict = ctrl.movieCounterByYear();
		reportTable->setRowCount((int)dict.size());
		int i = 0;
		for (auto& thing : dict){
			reportTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(thing.first)));
			reportTable->setItem(i, 1, new QTableWidgetItem(QString::number(thing.second.getCount())));
			i++;
		}

		reportWindow->setModal(true);
		reportWindow->show();
		});


	// open cart button


	/*
		Cart 
	*/

	// refresh
	QObject::connect(refreshCart, &QPushButton::clicked, [&]() {
		reloadCart(ctrl.getAllCart());
	});

	// clear cart
	QObject::connect(clearCart, &QPushButton::clicked, [&]() {
		ctrl.clearCart();
		notifyObservers();
		reloadCart(ctrl.getAllCart());

		});

	// add to cart
	QObject::connect(addToCart, &QPushButton::clicked, [&]() {
		std::string title = addSearch->text().toStdString();
		try
		{
			ctrl.addToCart(title);
			addSearch->setText("");
			notifyObservers();
			reloadCart(ctrl.getAllCart());

		}
		catch (const ValidationException& e)
		{
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getAll().at(0)));
		}
		});

	// randomize cart
	QObject::connect(randomizeCart, &QPushButton::clicked, [&]() {
		Validator val;
		try
		{
			val.validateNumber(randomSize->text().toStdString());
			int nr = randomSize->text().toInt();
			ctrl.randomizeCart(nr);
			randomSize->setText("");
			reloadCart(ctrl.getAllCart());
			notifyObservers();
		}
		catch (const ValidationException& e)
		{
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getAll().at(0)));
		}
		});
	
	// export cart
	QObject::connect(exportCart, &QPushButton::clicked, [&]() {
		try
		{
			ctrl.exportCartAsCSV(exportName->text().toStdString());
			exportName->setText("");
			QMessageBox::information(nullptr, "Succes!","The file was created.");
		}
		catch (const ValidationException& e)
		{
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(e.getAll().at(0)));
		}
		});

	// open 1
	QObject::connect(open1, &QPushButton::clicked, [&]() {
		addObserver(new CartCRUDGUI(ctrl, observers));
		});

	// open 2
	QObject::connect(open2, &QPushButton::clicked, [&]() {
		addObserver(new CartReadOnlyGUI(ctrl, observers));
		});

}


// load all movies to the list widget
void GUI::reloadList(const std::vector<Movie> list)
{
	listOfMovies->clear();
	for (auto& movie : list)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(movie.getTitle()) + " | " + QString::fromStdString(movie.getYearOfRelease()));
		item->setData(Qt::UserRole, movie.getIndex());
		listOfMovies->addItem(item);
	}
}

// load cart
void GUI::reloadCart(const std::vector<Movie> list)
{
	cart->clear();
	for (auto& movie : list)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(movie.getTitle()));
		item->setData(Qt::UserRole, movie.getIndex());
		cart->addItem(item);
	}
}

void GUI::reloadListWithColor(const std::vector<Movie> list, const std::vector<Movie> list2) {
	listOfMovies->clear();
	for (auto& movie : list)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(movie.getTitle()));
		item->setData(Qt::UserRole, movie.getIndex());
		bool ok = false;
		for(auto& movie2: list2)
			if (movie.getIndex() == movie2.getIndex()) {
				ok = true;
				break;
			}
		if (ok) {
			item->setBackground(Qt::green);
		}
		listOfMovies->addItem(item);
	}
}

void GUI::loadButtons()
{
	appLayout->addLayout(butoaneDinamice);
	std::map<std::string, DTO> dict = ctrl.movieCounterByYear();
	


	for (auto& x : dict){
		bool ok = true;
		for (auto& ss : currentButtons) {
			if (ss == x.first)
			{
				ok = false;
				break;
			}
		}

		if (ok == true)
		{

			QString s = QString::fromStdString(x.first);
			QPushButton* btn = new QPushButton(s);
			currentButtons.push_back(x.first);

			QObject::connect(btn, &QPushButton::clicked, [=]() {
				std::string txt = btn->text().toStdString();

				auto all = ctrl.getAll();
				for (auto& m : all) {
					if (m.getYearOfRelease() == txt)
						ctrl.deleteMovie(m.getIndex());
				}

				unsigned int i = 0;
				for (auto& ss : currentButtons) {
					if (ss == txt) {
						std::vector<std::string> ::iterator it{ currentButtons.erase(currentButtons.begin() + i) };
					}
					i++;
				}

				reloadList(ctrl.getAll());
				delete btn;

				});

			butoaneDinamice->addWidget(btn);
			
		}
	}

}

