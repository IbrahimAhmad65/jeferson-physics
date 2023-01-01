cmake_minimum_required(VERSION 3.24)
project(phys2)

set(CMAKE_CXX_STANDARD 17)
add_executable(phys2 main.cpp RigidBody.cpp RigidBody.h Math/Vector2D.cpp Math/Vector2D.h Math/Vector3D.cpp Math/Vector3D.h Math/Mesh.cpp Math/Mesh.h Math/Polygon.cpp Math/Polygon.h Tests/VectorPerformanceTest.cpp Tests/VectorPerformanceTest.h Tests/Test.cpp Tests/Test.h Math/Matrix.cpp Math/Matrix.h Math/NewMatrix.cpp Math/NewMatrix.h)
