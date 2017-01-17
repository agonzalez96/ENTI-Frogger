/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include <iostream>
#include <map>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : int {
	BARRO, CAMION, COCHE,COCODRILO_CERRADO, COCODRILO_ABIERTO,EXCAVADORA,META,MOSCA,NUTRIA, NUTRIA2, RALLY1,RALLY2, RANA,RANA_FEMENINA,SERPIENTE,TITULO,TORTUGA,
	TRONCO_CORTO, TRONCO_LARGO, TRONCO_MEDIANO,
	BG_00, BG_GAME, RANA2, TORTUGA2, TORTUGA3, TORTUGA4, TORTUGA5, TORTUGA6, TRITUGA1, TRITUGA2, TRITUGA3, TRITUGA4, TRITUGA5, BG_RANKING,  // Background IDs
	TIMER
};



inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering
enum class FontID : int { 
	ARIAL,
	CANDY,
	FACTORY, 
	MAX 
};