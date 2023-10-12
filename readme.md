# MeshSimplifier
A mesh simplifier implemented using vcglib and Meshlab.
* Supports non-manifold mesh
* Wrapper for libigl
* No manual installation of dependencies required
## Usage
This project build with xmake. Install xmake from the official website: https://xmake.io/#/getting_started

Clone
```
git clone https://github.com/hytracen/MeshSimplifier.git
```
Modify
```c++
std::string input_model_path{R"()"};  // Path to the model to be reduced
std::string output_model_path{R"()"}; // Output path for the reduced model
int target_faces_count{1000};         // Number of faces in the simplified model
```
Run
```
xmake
xmake run
```
## Reference
https://github.com/LiMingci/MeshSimplifier

http://vcglib.net/platonic_8h_source.html
