#pragma once
#include <vector>
#include "Edge.h"
class GameStatus
{
public:
	int stage, score, cont_stage;
	int ini_score;
	bool isPlay;
	 int max_Edges;
	 std::vector<Edge*> edges;
	GameStatus();
	
};

