<h1><img src="https://www.codexus.fr/img/hexagones/logo_hexagones.png" height="96" alt="Hexagones Logo" /></h1>

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Astropilot/Hexagones/blob/master/LICENSE)
[![Version](https://img.shields.io/github/release/Astropilot/Hexagones.svg)](https://github.com/Astropilot/Hexagones/releases/latest)
![Made with love](https://img.shields.io/badge/Made%20with-%E2%9D%A4%EF%B8%8F-yellow.svg)

Rewriting in C of a pedagogical program allowing to understand the functioning of path-finding algorithms in graphs.

![Screencast](https://www.codexus.fr/img/hexagones/demo.gif)

## How to use it

Hexagons allows you to test path-finding algorithms on a 2D hexagonal map.

Algorithms should try to find a path from the starting point (the magenta-colored hexagon) to the ending point (the red colored hexagon). <br>
You can complicate their task by adding impassable or difficult to cross obstacles, you have walls (black), water (blue), grass (green) and sand (yellow).

The walls are totally impassable, but the others only slow down by having a higher cost to move from one neighbour to the other. The costs are as follows:

| Type of tile | Cost       |
| :----------- | :--------: |
| Wall         | impassable |
| Nothing      | 1          |
| Water        | 10         |
| Grass        | 5          |
| Sand         | 2          |

Here is the list of algorithms that have been implemented:

* [x] Depth-first search
* [x] Breadth-first search
* [x] Connected components (This algorithm is an exception, it only displays the connected components.)
* [x] Bellman-Ford
* [x] Dijkstra
* [x] A*

## Download & Install

### Prerequisites

To be able to compile the project, you must first have the GTK 3 graphics library.

On Debian/Unbuntu distributions you can install it via the command
```bash
$ sudo apt-get install libgtk-3-dev
```

### How to compile

First of all you have to recover the sources. To do this you can either download a release [from the release page](https://github.com/Astropilot/Hexagones/releases), or clone the repository via the command
```bash
$ git clone https://github.com/Astropilot/Hexagones.git
```

Once the sources are recovered, you can compile the project under UNIX with the make command:
```bash
$ cd Hexagones
$ make
```

Finally, all you have to do is launch Hexagons!
```bash
$ ./hexagones
```

## Credits

This project is a rewrite of an already existing project originally written in Python by [Mr. David Auger](https://www.david.uvsq.fr/?profile=auger-david), professor-researcher at the University Institute of Technology in Vélizy, France.
