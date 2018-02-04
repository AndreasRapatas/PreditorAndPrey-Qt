#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>


#include "board.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	Board *board = new Board(600, 300);
	QPushButton *start = new QPushButton("Begin");
	QPushButton *stop = new QPushButton("Stop");

	QHBoxLayout *buttons = new QHBoxLayout;
	buttons->addWidget(start);
	buttons->addWidget(stop);

	QVBoxLayout *lay = new QVBoxLayout;
	lay->addWidget(board);
	lay->addLayout(buttons);

	QWidget window;
	window.setLayout(lay);
	window.show();

	QObject::connect(
		start, &QPushButton::clicked,
		board, &Board::start
	);
	QObject::connect(
		stop, &QPushButton::clicked,
		board, &Board::stop
	);

	return app.exec();
}
