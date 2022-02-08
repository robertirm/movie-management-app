#pragma once

#include "controller.h"

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QSpinBox>

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
protected:

	std::vector<Observer*> observers;
public:
	
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void notifyObservers() {
		for (auto& obs : observers) {
			obs->update();
		}
	}

	virtual void update() = 0;
};


class CartCRUDGUI : public QWidget, public Observer{

	Controller& ctrl; 

	//QWidget* cartWindow = new QWidget();
	QVBoxLayout* cartLayout = new QVBoxLayout;
	QPushButton* genBtn = new QPushButton("Generare");
	QPushButton* golBtn = new QPushButton("Golire");
	QListWidget* cartList = new QListWidget;

	std::vector<Observer*>& observers;

	void notify() {
		for (auto& obs : observers) {
			obs->update();
		}
	}

	void reloadLisit(const std::vector<Movie>& list) {
		cartList->clear();
		for (auto& m : list) {
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(m.getTitle()));
			cartList->addItem(item);
		}
	}

public:
	CartCRUDGUI(Controller& c, std::vector<Observer*>& obs) : ctrl{ c }, observers{obs} {
		setLayout(cartLayout);
		cartLayout->addWidget(cartList);
		cartLayout->addWidget(genBtn);
		cartLayout->addWidget(golBtn);
		update();
		show();
		observers.push_back(this);

		QObject::connect(genBtn, &QPushButton::clicked, [&]() {
			const int x = std::rand() % ctrl.getAll().size() + 1;
			ctrl.randomizeCart(x);
			reloadLisit(ctrl.getAllCart());
			notify();
			});

		QObject::connect(golBtn, &QPushButton::clicked, [&]() {
			ctrl.clearCart();
			reloadLisit(ctrl.getAllCart());
			notify();
			});

	};

	void update() override {
		reloadLisit(ctrl.getAllCart());
	}

};

class CartReadOnlyGUI : public QWidget, public Observer {
	
	Controller& ctrl;
	QVBoxLayout* layout = new QVBoxLayout;
	std::vector<Observer*> observers;

public:
	
	CartReadOnlyGUI(Controller& c, std::vector<Observer*>& v) :
		ctrl{ c }, observers{ v }{
		setLayout(layout);
		setFixedSize(600, 400);
		show();
	};

	void paintEvent(QPaintEvent* ev) override {
		ev->accept();
		QPainter p{ this };
		const size_t n = ctrl.getAllCart().size();
		const int x = rand() % 600;
		const int y = rand() % 400;
		
		for (size_t i = 0; i < n; i++)
		{
			const QRect* r = new QRect(rand() % 600, rand() % 400, rand() % 600 - x, rand() % 400 - y);
			p.drawEllipse(*r);
		}
	}
	
	void update() override {
		repaint();
	}


};



class GUI :public QWidget, public Observer, public Observable {
private:
	Controller& ctrl;
	QListWidget* listOfMovies = new QListWidget;
	void initGUI();
	void connectSignalsSlots();
	void reloadList(const std::vector<Movie> list);
	void reloadCart(const std::vector<Movie> list);
	void reloadListWithColor(const std::vector<Movie> list, const std::vector<Movie> list2);

	QPushButton* exitButton = new QPushButton("Exit");
	QPushButton* refreshButton = new QPushButton("Refresh");
	QPushButton* sortByTitleButton = new QPushButton("Sort by Title");
	QPushButton* sortByLeadingActorButton = new QPushButton("Sort by Actor");
	QPushButton* sortByYearAndGenreButton = new QPushButton("Sort by Year ");


	QLineEdit* idTextBox = new QLineEdit;
	QLineEdit* titleTextBox = new QLineEdit;
	QLineEdit* genreTextBox = new QLineEdit;
	QLineEdit* yearTextBox = new QLineEdit;
	QLineEdit* actorTextBox = new QLineEdit;

	QPushButton* addButton = new QPushButton("Add");
	QPushButton* deleteButton = new QPushButton("Delete");
	QPushButton* updateButton = new QPushButton("Update");
	QPushButton* undoButton = new QPushButton("Undo");

	QPushButton* searchButton = new QPushButton("Search");
	QLineEdit* searchTextBox = new QLineEdit;

	QLineEdit* filterTextBox = new QLineEdit;
	QPushButton* filterByTitleButton = new QPushButton("Filter by Title");
	QPushButton* filterByYearButton = new QPushButton("Filter by Year");

	QDialog* addWindow = new QDialog;
	QVBoxLayout* addWindowLayout = new QVBoxLayout;
	QFormLayout* addForm = new QFormLayout;
	QLineEdit* addIdTextBox = new QLineEdit;
	QLineEdit* addTitleTextBox = new QLineEdit;
	QLineEdit* addGenreTextBox = new QLineEdit;
	QLineEdit* addYearTextBox = new QLineEdit;
	QLineEdit* addActorTextBox = new QLineEdit;
	QPushButton* addWindowButton = new QPushButton("Add");
	QPushButton* addCancelWindowButton = new QPushButton("Cancel");

	QDialog* updateWindow = new QDialog;
	QFormLayout* updateForm = new QFormLayout;
	QVBoxLayout* updateWindowLayout = new QVBoxLayout;
	QLineEdit* updateTitleTextBox = new QLineEdit;
	QLineEdit* updateGenreTextBox = new QLineEdit;
	QLineEdit* updateYearTextBox = new QLineEdit;
	QLineEdit* updateActorTextBox = new QLineEdit;
	QPushButton* updateWindowButton = new QPushButton("Update");
	QPushButton* updateCancelWindowButton = new QPushButton("Cancel");

	QPushButton* reportButton = new QPushButton("Report");
	QDialog* reportWindow = new QDialog;
	QTableWidget* reportTable = new QTableWidget{2,2};
	QVBoxLayout* reportWindowLayout = new QVBoxLayout;



	QHBoxLayout* firstLine = new QHBoxLayout;
	QHBoxLayout* secondLine = new QHBoxLayout;
	QHBoxLayout* thirdLine = new QHBoxLayout;
	QHBoxLayout* forthLine = new QHBoxLayout;
	QHBoxLayout* fifthLine = new QHBoxLayout;
	QListWidget* cart = new QListWidget;
	QPushButton* addToCart = new QPushButton("Add to Cart");
	QLineEdit* addSearch = new QLineEdit;
	QPushButton* clearCart = new QPushButton("Clear Cart");
	QPushButton* randomizeCart = new QPushButton("Randomize");
	QLineEdit* randomSize = new QLineEdit;
	QPushButton* exportCart = new QPushButton("Export Cart");
	QLineEdit* exportName = new QLineEdit;
	QPushButton* exitCart = new QPushButton("Exit");
	QPushButton* refreshCart = new QPushButton("Refresh");


	QPushButton* open1 = new QPushButton("Open CartCRUDGUI");
	QPushButton* open2 = new QPushButton("Open CartReadOnlyGUI");

	QVBoxLayout* butoaneDinamice = new QVBoxLayout;
	void loadButtons();
	std::vector<std::string> currentButtons;

	QHBoxLayout* appLayout = new QHBoxLayout;

	
	void update() override {
		reloadCart(ctrl.getAllCart());
	}

public:

	GUI(Controller& c): ctrl {c} {
		initGUI();
		connectSignalsSlots();
		reloadList(ctrl.getAll());
		
		
		//loadButtons();


		addObserver(this);


	}

};