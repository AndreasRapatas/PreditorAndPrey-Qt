#ifndef BOARD_H_
#define BOARD_H_

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QColor>
#include <random>

class Board : public QLabel {
	Q_OBJECT
private:
	struct Cell {
		enum State : unsigned {
			PREDITOR = qRgb(255, 0, 0),
			PREY = qRgb(0, 255, 0),
			NOTHING = qRgb(0, 0, 0),
		};
		State state;
		unsigned health;
		Cell() : state(State::NOTHING) {}
	};

	size_t size_x;
	size_t size_y;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> x_range;
	std::uniform_int_distribution<int> y_range;
	Cell::State **matrix;
	QImage *img;
	bool running;
	Board::Cell::State random_state();
	void update();
	void fill_random();
	void clear();
	unsigned valid_move_x(unsigned x);
	unsigned valid_move_y(unsigned y);
public slots:
	void start();
	void stop();
	void next();
public:
	Board(size_t x, size_t y, QWidget *parent = 0);
	~Board();
};

#endif // BOARD_H_
