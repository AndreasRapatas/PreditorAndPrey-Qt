#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "predator_and_prey.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	PredatorAndPrey *board = new PredatorAndPrey(600, 300);
	QPushButton *step  = new QPushButton("Step");
	QPushButton *run   = new QPushButton("Run");
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
		board, &PredatorAndPrey::step
	);
	QObject::connect(
		run, &QPushButton::clicked,
		board, &PredatorAndPrey::run
	);
	QObject::connect(
		reset, &QPushButton::clicked,
		board, &PredatorAndPrey::reset
	);
	QObject::connect(
		pause, &QPushButton::clicked,
		board, &PredatorAndPrey::pause
	);

	return app.exec();
}
