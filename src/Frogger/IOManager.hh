/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"
#include <XML/rapidxml_utils.hpp>
#include"Sprite.hh"
#include "Score.hh"

using namespace Logger;
using namespace rapidxml;

namespace IOManager {

	std::vector<Sprite> LoadLevelXML(std::string &&filename);
	ObjectID SwitchTextrue(int index);
	std::vector<Score> SaveRanking(Score score);
	std::vector<Score> LoadRanking();
}
