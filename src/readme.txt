Prerequisites:
- GCC
- CMake
- Boost
- TCMalloc
- libgoogle-perftools-dev
- libunwind-0.99-beta


Run:
- test_taumng_index.cpp: it is the main file to construct a tauMNG
- test_taumng_search.cpp: it is the main file to perform ANN search on tauMNG


Zeyu:
Build as NSG.
To run tau, prepare a KNN-graph first. I use efanna2e.
The entry code is in test_taumng_index.cpp and test_taumng_search.cpp.
Change the file path inside these 2 files to match the positions in your server.

The example of parameters are in .vscode/launch.json.
The commented lines are for building index, and the rest are for searching index.
The "0"s in the parameters mean nothing in our case. Don't care about them but don't delete them.
NOTE: IP and L2 distance should be hard-coded in the two entry files. Don't confuse them.