#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "board.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	Board *board = new Board(600, 300);
	QPushButton *step = new QPushButton("Step");
	QPushButton *run = new QPushButton("Run");
	QPushButton *reset = new QPushButton("Reset");
	QPushButton *pause = new QPushButton("Pause");

	QHBoxLayout *buttons = new QHBoxLayout;
	buttons->addWidget(step);
	buttons->addWidget(run);
	buttons->addWidget(reset);
	buttons->addWidget(pause);

	QVBoxLayout *lay = new QVBoxLayout;
	lay->addWidget(board);
	lay->addLayout(buttons);

	QWidget window;
	window.setLayout(lay);
	window.show();


	QObject::connect(
		step, &QPushButton::clicked,
		board, &Board::step
	);
	QObject::connect(
		run, &QPushButton::clicked,
		board, &Board::run
	);
	QObject::connect(
		reset, &QPushButton::clicked,
		board, &Board::reset
	);
	QObject::connect(
		pause, &QPushButton::clicked,
		board, &Board::pause
	);

	return app.exec();
}
