#ifndef PREDATOR_AND_PREY_H
#define PREDATOR_AND_PREY_H

#include <random>

#include <QLabel>
#include <QLabel>
#include <flat_matrix/flat_matrix.h>

class PredatorAndPrey : public QLabel {

	Q_OBJECT

private:

	enum class Type {
		Predator,
		Prey,
		Nothing
	};

	struct Cell {

		Type type;
		unsigned health;

		Cell() :
			type(Type::Nothing),
			health(0)
		{}

		Cell(const Type &type) :
			type(type),
			health(type == Type::Predator ? 10 : 0)
		{}

		void age() {

			if (--health == 0) {
				type = Type::Nothing;
			}
		}
	};

	bool running = false;

	unsigned width;
	unsigned height;
	unsigned cell_number;
	flat_matrix<Cell> state;
	QImage *img;

	// Predator - Prey - Nothing
	std::uniform_int_distribution<unsigned> type;
	// +1 or -1
	std::uniform_int_distribution<int> move;
	std::default_random_engine generator;

	void next_step();

public slots:

	void run();
	void pause();
	void reset();
	void step();

public:

	PredatorAndPrey(unsigned width, unsigned height, QWidget *parent = 0);

	void fill_random();

	unsigned calc_index(unsigned x, unsigned y);

	unsigned calc_x(unsigned index);

	unsigned calc_y(unsigned index);

	void update();
};

#endif // PREDATOR_AND_PREY_H
