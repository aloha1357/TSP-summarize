#include <bits/stdc++.h>


using namespace std;
///////////////////map{
class Map {
public:
	int numVertex;
	double** coordinate;
	Map(string file);
	double getDistance(int, int);
	string file;
	void free();
};

std::string DIMESION_PROPERTY = "DIMENSION";
std::string BEST_PROPERTY = "BEST";
std::string START_VERTEX_PAGE = "NODE_COORD_SECTION";

double sqr(double x) {
	return x * x;
}

double Map::getDistance(int vertexA, int vertexB) {
	double distance = sqrt(
		sqr(this->coordinate[vertexA][0] - this->coordinate[vertexB][0])
		+ sqr(this->coordinate[vertexA][1] - this->coordinate[vertexB][1])
	);
	return distance;
}

Map::Map(string filePath) {
	string line;
	cout << endl;
	cout << "file: " << filePath << endl;
	ifstream dataFile;
	dataFile.open(filePath.c_str());
	if (dataFile.is_open()) {
		bool vertexDataRegion = false;
		while (dataFile.good()) {
			getline(dataFile, line);

			if (vertexDataRegion) {
				int vertexId;
				double posX;
				double posY;
				sscanf(line.c_str(), "%d %lf %lf", &vertexId, &posX, &posY);
				vertexId--; // we store vertex from 0

				this->coordinate[vertexId][0] = posX;
				this->coordinate[vertexId][1] = posY;
			}

			if (line.find(DIMESION_PROPERTY) == 0) {
				unsigned int index = 0;
				for (; index < line.size(); index++) {
					if (line[index] >= '0' && line[index] <= '9') break;
				}
				this->numVertex = atoi(line.substr(index, 100).c_str());
				cout << "So din : " << this->numVertex << endl;

				this->coordinate = new double* [this->numVertex];
				for (int i = 0; i < this->numVertex; i++) {
					this->coordinate[i] = new double[2];
				}
			}

			if (line.find(BEST_PROPERTY) == 0) {
				int bestValue;
				unsigned int index = 0;
				for (; index < line.size(); index++) {
					if (line[index] >= '0' && line[index] <= '9') break;
				}
				bestValue = atoi(line.substr(index, 100).c_str());
				cout << "best value : " << bestValue << endl;
			}

			if (line.find(START_VERTEX_PAGE) == 0) {
				vertexDataRegion = true;
			}
		}
		dataFile.close();
	}
}

void Map::free() {
	for (int i = 0; i < this->numVertex; i++) {
		delete[] this->coordinate[i];
	}
	delete[] this->coordinate;
}
/////////////////////}

////////solution{
class Solution {
private:
	double score;
	Map* map;
	int* v;
public:
	void computeScore();
	void swapSolve(int i, int j);
	Solution(Map* map);
	void initSolution();
	int getV(int key);
	double getScore();
	void set(int key, int value);
	void free();
	void printPath();
};

Solution::Solution(Map* map) {
	this->map = map;
	v = new int[map->numVertex];
	score = 0;
	initSolution();
}

void Solution::initSolution() {
	for (int i = 0; i < map->numVertex; i++) {
		this->v[i] = i;
	}
	srand(time(NULL));
	for (int i = (map->numVertex - 1); i >= 0; i--) {
		int j = rand() % map->numVertex;
		swap(this->v[i], this->v[j]);
	}
	computeScore();
}

void Solution::computeScore() {
	score = 0;
	for (int i = 0; i < (map->numVertex - 1); i++) {
		score += map->getDistance(this->v[i], this->v[i + 1]);
	}
	score += map->getDistance(this->v[map->numVertex - 1], this->v[0]);
}

void Solution::printPath() {
	cout << "Duong di : ";
	for (int i = 0; i < map->numVertex; i++) {
		cout << this->v[i] << " ";
	}
	cout << endl;
}

int Solution::getV(int key) {
	return this->v[key];
}
void Solution::set(int key, int value) {
	this->v[key] = value;
}

void Solution::swapSolve(int i, int j) {
	swap(this->v[i], this->v[j]);
}

double Solution::getScore() {
	computeScore();
	return score;
}

void Solution::free() {
	delete[] this->v;
}

////////////////}

///////////////tabu search TSP{
class TSPTabuSolver {
public:
	TSPTabuSolver(string filePath);
	void solve(int);
	Solution* getBestNearbySolution(int);
	void resetTabuList();
private:
	double bestSolverScore;
	int** tabu_list;
	int** tabu_f_list;
	Map* map;
	Solution* s;
};
#define TABU_LENGTH 30
#define NUM_INTERATION 3000
#define PENAL_LONG_TERM 10
#define LONG_TERM_LENGTH 100
#define TIME_TRY 500

TSPTabuSolver::TSPTabuSolver(string filePath) {
	map = new Map(filePath);
	s = new Solution(map);
	bestSolverScore = std::numeric_limits<double>::max();

	tabu_list = new int* [map->numVertex];
	tabu_f_list = new int* [map->numVertex];
	for (int i = 0; i < map->numVertex; i++) {
		tabu_f_list[i] = new int[map->numVertex];
		tabu_list[i] = new int[map->numVertex];
	}

	resetTabuList();
}

void TSPTabuSolver::resetTabuList() {
	for (int i = 0; i < map->numVertex; i++) {
		for (int j = 0; j < map->numVertex; j++) {
			tabu_list[i][j] = 0;
			tabu_f_list[i][j] = 0;
		}
	}
}

/*
	numCandidate : times that solver run to get the best score
*/
void TSPTabuSolver::solve(int numCandidate) {
	Solution bestSolution(map);
	double bestSolutionScore = bestSolution.getScore();

	for (int loopCount = 0; loopCount < numCandidate; loopCount++) {
		s->initSolution();
		resetTabuList();
		//cout << "Init Score : " << s->getScore() << endl;
		int countTime = 0;
		bestSolverScore = std::numeric_limits<double>::max();
		for (int i = 0; i < NUM_INTERATION; i++) {
			s = this->getBestNearbySolution(i);
			double score = s->getScore();
			if (score < bestSolverScore) {
				bestSolverScore = score;
				countTime = 0;

				if (bestSolverScore < bestSolutionScore) {
					for (int j = 0; j < map->numVertex; j++) {
						bestSolution.set(j, s->getV(j));
					}
					bestSolutionScore = bestSolverScore;
				}
			}
			else {
				countTime++;
				if (countTime > TIME_TRY) {
					break;
				}
			}
		}

	}
	cout << "Best score : " << bestSolutionScore << endl;
	bestSolution.printPath();
}
Solution* TSPTabuSolver::getBestNearbySolution(int it) {
	double bestScore = std::numeric_limits<double>::max();;
	int vertexA = 0;
	int vertexB = 1;
	for (int i = 0; i < map->numVertex; i++) {
		for (int j = (i + 1); j < map->numVertex; j++) {
			//swap for new solution
			s->swapSolve(i, j);
			double currentScore = s->getScore();
			double penalScore = currentScore + PENAL_LONG_TERM * tabu_f_list[i][j];
			if ((bestScore > penalScore && this->tabu_list[i][j] <= it) || currentScore < bestSolverScore) {
				vertexA = i;
				vertexB = j;
				bestScore = penalScore;
				this->tabu_list[i][j] = (it + TABU_LENGTH);
				this->tabu_list[j][i] = (it + TABU_LENGTH);
			}
			// back to orginal solution
			s->swapSolve(j, i);
			if (tabu_f_list[i][j] > 0 && it > LONG_TERM_LENGTH) tabu_f_list[i][j] -= 1;
		}
	}
	tabu_f_list[vertexA][vertexB] += 2;
	s->swapSolve(vertexA, vertexB);
	return s;
}
int main(int argc, char* argv[]) {
  auto start = std::chrono::system_clock::now();
	TSPTabuSolver solver2("cities.txt");
	solver2.solve(6);
  auto end = std::chrono::system_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout << "Spent"
		<< double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den
		<< "seconds" << endl;
	return 0;
}

//////////////////////////////}
