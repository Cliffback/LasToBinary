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

int main(int argc, char* argv[]) {

	if (argc != 3) {
		std::cout << "argc: " << argc << std::endl;
		for (uint32_t i = 0; i < argc; i++)
			std::cout << argv[i] << std::endl;
		std::cout << "Needs filename and out filename." << std::endl;
		return 0;
	}

	std::string filename(argv[1]);

	std::ifstream inn(filename);
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

	std::ofstream out(argv[2], std::ios::binary);
	out.write((const char*)lasData.data(), lasData.size() * sizeof(Vertex));
	out.close();

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