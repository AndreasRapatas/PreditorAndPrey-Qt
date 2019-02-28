#include "predator_and_prey.h"
#include <QTimer>

PredatorAndPrey::PredatorAndPrey(
	unsigned width,
	unsigned height,
	QWidget *parent
) :
	QLabel(parent),
	width(width),
	height(height),
	cell_number(width * height),
	state(width, height),
	img(new QImage(width, height, QImage::Format_RGB32)),
	type(0, 2),
	move(-1, 1)
{
	fill_random();
	update();
}

void PredatorAndPrey::fill_random() {

	for (unsigned i = 0; i < cell_number; ++i) {
		switch (type(generator)) {
		case 0:
			state[i] = Cell();
			break;
		case 1:
			state[i] = Cell(Type::Prey);
			break;
		case 2:
			state[i] = Cell(Type::Predator);
			break;
		}
	}
}

unsigned PredatorAndPrey::calc_index(unsigned x, unsigned y) {
	return (x + y * width);
}

unsigned PredatorAndPrey::calc_x(unsigned index) {
	return index % width;
}

unsigned PredatorAndPrey::calc_y(unsigned index) {
	return index / width;
}

void PredatorAndPrey::step() {

	if (!running) {
		next_step();
	}
}

void PredatorAndPrey::next_step() {

	int x = 0;
	int y = 0;
	int new_x = 0;
	int new_y = 0;

	for (unsigned i = 0; i < cell_number; ++i) {

		state[i].age();

		if (state[i].type == Type::Nothing) { continue; }

		x = calc_x(i);
		y = calc_y(i);

		new_x = move(generator) + x;
		new_y = move(generator) + y;

		// The random generator said it will not move
		if (new_x == x && new_y == y) { continue; }

		// Wrap on the edges
		if (new_x < 0) { new_x = width - 1; }
		if ((unsigned) new_x == width) { new_x = 0; }
		if (new_y < 0) { new_y = height - 1; }
		if ((unsigned) new_y == height) { new_y = 0; }

		Cell &other_cell = state(new_x, new_y);
		Cell &this_cell = state[i];

		if (this_cell.type == Type::Predator) {

			if (other_cell.type == Type::Prey) {
				other_cell = Cell(Type::Predator);
			}

		} else {

			if (other_cell.type == Type::Nothing) {
				other_cell = Cell(Type::Prey);
			}
		}
	}

	update();

	// Pause to check for user input
	if (running) {
		QTimer::singleShot(10, this, &PredatorAndPrey::next_step);
	}
}

void PredatorAndPrey::reset() {

	fill_random();
	update();
}

void PredatorAndPrey::pause() {

	running = false;
}

void PredatorAndPrey::run() {

	if (running) { return; }

	running = true;
	next_step();
}

void PredatorAndPrey::update() {

	for (size_t i = 0; i != cell_number; ++i) {

		QColor color;

		switch (state[i].type) {
		case Type::Nothing:
			color = qRgb(0, 0, 0);
			break;
		case Type::Predator:
			color = qRgb(255, 0, 0);
			break;
		case Type::Prey:
			color = qRgb(0, 255, 0);
			break;
		}

		img->setPixel(calc_x(i), calc_y(i), color.rgb());
	}

	setPixmap(QPixmap::fromImage(*img));
}
