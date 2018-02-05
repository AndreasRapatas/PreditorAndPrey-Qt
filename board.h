#ifndef BOARD_H_
#define BOARD_H_

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QColor>
#include <random>
#include <utility>

class Board : public QLabel {

	Q_OBJECT

private:

	struct Cell {

		enum State : unsigned {
			PREDITOR = qRgb(255, 0, 0),
			PREY     = qRgb(0, 255, 0),
			NOTHING  = qRgb(0, 0, 0),
		};

		State state;
		unsigned health;

		Cell() : state(State::NOTHING) {}
		Cell(State state)
			: state(state)
			, health((state == State::PREDITOR) ? 10 : 0)
		{}
	};

	Cell **matrix;
	QImage *img;

	size_t size_x;
	size_t size_y;
	bool running;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> x_range;
	std::uniform_int_distribution<int> y_range;

	Board::Cell random_cell();
	std::pair<unsigned, unsigned> valid_move(unsigned x, unsigned y);

	void fill_random();
	void fill_other();
	void clear();
	void update();

public slots:

	void run();
	void pause();
	void step();

public:

	Board(size_t x, size_t y, QWidget *parent = 0);
	~Board();
};

#endif // BOARD_H_
