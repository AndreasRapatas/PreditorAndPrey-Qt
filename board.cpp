#include "board.h"

#include <QTimer>
#include <iostream>

Board::Board(size_t x, size_t y, QWidget *parent)
	: QLabel(parent)
	, img(new QImage(x, y, QImage::Format_RGB32))
	, size_x(x)
	, size_y(y)
	, running(false)
	, x_range(0, size_x - 1)
	, y_range(0, size_y - 1)
{

	img->fill(qRgb(0,0,0));

	matrix = new Cell*[size_y];
	for (size_t y = 0; y < size_y; ++y) {
		matrix[y] = new Cell[size_x];
	}

	this->clear();
	this->fill_random();
	// this->fill_other();
	this->update();
}

Board::~Board() {

	for (size_t y = 0; y < size_y; ++y) {
		delete[] matrix[y];
	}
	delete[] matrix;
}

Board::Cell Board::random_cell() {

	static std::uniform_int_distribution<int> state_range(0, 2);

	switch (state_range(generator)) {
	case 0:
		return Cell(Cell::State::PREDITOR);
	case 1:
		return Cell(Cell::State::PREY);
	default:
		return Cell(Cell::State::NOTHING);
	}
}

void Board::update() {

	for (size_t y = 0; y < size_y; ++y) {
		for (size_t x = 0; x < size_x; ++x) {

			img->setPixel(x, y, matrix[y][x].state);
		}
	}

	this->setPixmap(QPixmap::fromImage(*img));
}

void Board::fill_random() {

	for (size_t y = 0; y < size_y; ++y) {
		for (size_t x = 0; x < size_x; ++x) {
			matrix[y][x] = this->random_cell();
		}
	}
}
void Board::fill_other() {

	for (size_t y = 0; y < size_y; ++y) {
		for (size_t x = 0; x < size_x; ++x) {
			if (y < size_y / 2) {
				matrix[y][x] = Cell(Cell::State::PREY);
			} else {
				matrix[y][x] = Cell(Cell::State::PREDITOR);
			}
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

std::pair<unsigned, unsigned> Board::valid_move(unsigned x, unsigned y) {

	static std::uniform_int_distribution<int> move(-1, 1);
	int new_x = 0;
	int new_y = 0;

	while (true) {

		new_x = x + move(generator);
		new_y = y + move(generator);

		if (new_x < 0 || static_cast<unsigned>(new_x) >= size_x) { continue; }
		if (new_y < 0 || static_cast<unsigned>(new_y) >= size_y) { continue; }

		return {new_x, new_y};
	}
}

void Board::run() {

	running = true;
	this->step();
}

void Board::pause() {

	running = false;
}

void Board::step() {

	for (size_t y = 0; y < size_y; ++y) {
		for (size_t x = 0; x < size_x; ++x) {

			auto new_pos = this->valid_move(x, y);

			// It didn't move
			if (new_pos.first == x && new_pos.second == y) { continue; }

			Cell &cur_cell = matrix[y][x];
			Cell &other_cell = matrix[new_pos.second][new_pos.first];

			if (cur_cell.state == Cell::State::PREDITOR) {

				cur_cell.health--;

				// Check if it is dead
				if (cur_cell.health == 0) {
					cur_cell = Cell(Cell::State::NOTHING);
					continue;
				}

				switch (other_cell.state) {
				case Cell::State::PREDITOR:
					continue;
				case Cell::State::PREY:
					cur_cell.health += other_cell.health;
					other_cell = Cell(Cell::State::PREDITOR);
					break;
				default:
					std::swap(cur_cell, other_cell);
					break;
				}

			} else if (cur_cell.state == Cell::State::PREY) {

				switch (other_cell.state) {
				case Cell::State::PREDITOR:
					continue;
				case Cell::State::PREY:
					continue;
				default:
					other_cell = Cell(Cell::State::PREY);
					cur_cell = Cell(Cell::State::PREY);
				}
			}
		}
	}

	this->update();

	// Pause to check for user input
	if (running) {
		QTimer::singleShot(10, this, &Board::step);
	}
}

