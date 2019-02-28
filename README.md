# Predator & Prey
This project implements the [cellular automaton](https://en.wikipedia.org/wiki/Cellular_automaton) Predator & Prey using C++ and displays it using [Qt5](https://www.qt.io/). Predator & Prey is simulating an environment where a predator (red) and a prey (green) exist in a harmonic balance using the following set of rules:
* If a prey moves, it multiplies in the previous position
* If a predator lands on a prey, it turns it into a predator
* Predators die after 10 rounds

# Usage
```bash
predator_and_prey_qt
```

![Preview](https://i.imgur.com/ssM9G0v.png "Window Preview")

# Installation

## Dependencies
Follow the project's installation instructions.
* [Qt5](https://www.qt.io/) (For Ubuntu simply ```apt install qtbase5-dev```)
* [Rapatas/flat_matrix](https://github.com/Rapatas/flat_matrix)

## Predator & Prey
```bash
git clone https://github.com/Rapatas/predator_and_prey_qt
mkdir predator_and_prey_qt/build
cd predator_and_prey_qt/build
cmake ..
make install # As root
```
