#include "board.h"

#include <QTimer>

Board::Board(size_t x, size_t y, QWidget *parent)
	: QLabel(parent)
	, size_x(x)
	, size_y(y)
	, x_range(0, size_x - 1)
	, y_range(0, size_y - 1)
	, img(new QImage(x, y, QImage::Format_RGB32))
	, running(false)
{

	img->fill(qRgb(0,0,0));

	matrix = new Cell::State*[size_y];
	for (size_t y = 0; y < size_y; ++y) {
		matrix[y] = new Cell::State[size_x];
	}
	this->clear();
	this->fill_random();
	this->update();
}

Board::~Board() {
	for (size_t y = 0; y < size_y; ++y) {
		delete[] matrix[y];
	}
	delete[] matrix;
}

Board::Cell::State Board::random_state() {

	static std::uniform_int_distribution<int> c_range(0, 2);

	switch (c_range(generator)) {
		case 0:
			return Cell::State::PREDITOR;
		case 1:
			return Cell::State::PREY;
		default:
			return Cell::State::NOTHING;
	}
}

void Board::update() {

	for (size_t y = 0; y < size_y; ++y) {
		for (size_t x = 0; x < size_x; ++x) {

			img->setPixel(x, y, matrix[y][x]);
		}
	}

	this->setPixmap(QPixmap::fromImage(*img));
}

void Board::fill_random() {

	for (size_t y = 0; y < size_y; ++y) {
		for (size_t x = 0; x < size_x; ++x) {
			matrix[y][x] = random_state();
		}
	}
}

void Board::clear() {

	for (size_t y = 0; y < size_y; ++y) {
		for (size_t x = 0; x < size_x; ++x) {
			matrix[y][x] = Cell::State::NOTHING;
		}
	}
}

unsigned valid_move_x(unsigned x) {

	// TODO: all of this

	static std::uniform_int_distribution<unsigned> x_space(0, 2);

	for (bool is_valid = true; !is_valid; ) {

		if (false) {
			is_valid = false;
		}
	}
}

void Board::start() {

	running = true;
	this->next();
}

void Board::stop() {

	running = false;
}

void Board::next() {

	for (size_t y = 0; y < size_y; ++y) {
		for (size_t x = 0; x < size_x; ++x) {

		}
	}

	this->update();

	if (running) {
		QTimer::singleShot(1, this, &Board::next);
	}
}

