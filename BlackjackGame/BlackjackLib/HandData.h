#pragma once
#include <vector>
#include "CardData.h"

struct HandData {
	std::vector<CardData> cards;
	int value;
};