#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

struct Vertex {
	float x;
	float y;
	float z;
};

int main() {
	std::string filename{ "france" }; 	// Insert filename here
	std::ifstream inn(filename + ".txt");
	if (!inn.is_open()) {
		std::cout << "Cant open file!" << std::endl;
		return 0;
	}

	std::string line;
	std::vector<Vertex> lasData;
	while (std::getline(inn, line)) {
		std::stringstream ss(line);
		Vertex v;
		ss >> v.x;
		ss >> v.y;
		ss >> v.z;
		lasData.push_back(v);
	}

	inn.close();

	std::ofstream out(filename + ".lasbin", std::ios::binary);
	out.write((const char*)lasData.data(), lasData.size() * sizeof(Vertex));
	std::cout << "Wrote las text file to binary" << std::endl;

	/*
		Read example :D

		std::ifstream is("BIGLAS.lasbin", std::ios::binary | std::ios::ate);
		auto size = is.tellg();
		std::vector<glm::vec3> lasDataPoints(size / sizeof(glm::vec3));
		is.seekg(0);
		is.read(reinterpret_cast<char *>lasDataPoints.data(), size))
	*/
}