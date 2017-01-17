#include "IOManager.hh"
#include "LevelSelect.h"
#include "ID.hh"
#include <string>
#include "LevelSelect.h"
#include "SceneManager.hh"
#include "RankingScene.h"

std::vector<Sprite> IOManager::LoadLevelXML(std::string && filename)
{
	xml_document<> doc;    // character type defaults to char
	std::ifstream file(RESOURCE_FILE(filename));
	std::stringstream buffer;

	std::vector<Sprite> lvlData;
	Sprite temp;
	std::string name;
	std::string value;

	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	//std::cout << "Nombre raiz: " << doc.first_node()->name() << '\n';
	xml_node<> *pRoot = doc.first_node();
	if (LevelSelect::_diff == "Easy") {
		for (xml_node<> *pNode = pRoot->first_node("Easy"); pNode < pRoot->first_node("Medium"); pNode = pNode->next_sibling()) {
				//std::cout << pNode->name() << ':' << '\n';
			for (xml_node<> *pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {
						//std::cout << "  " << pNodeI->name() << "-" << pNodeI->value() << '\n';
				for (xml_node<> *pNode2 = pNodeI->first_node(); pNode2; pNode2 = pNode2->next_sibling()) {
								//std::cout << "    " << pNode2->name() << "-" << pNode2->value() << '\n';
					for (xml_node<> *pNode3 = pNode2->first_node(); pNode3; pNode3 = pNode3->next_sibling()) {
						//std::cout << "      " << pNode3->name() << "-" << pNode3->value() << '\n';
						name = pNode3->name();
						value = pNode3->value();
						//std::cout << "name" << name << std::endl;
						//std::cout << "value" << value << std::endl;
						if (name == "ID") {
							temp.objectID = SwitchTextrue(atoi(pNode3->value()));
						}
						else if (name == "x") {
							temp.transform.x = atoi(pNode3->value());
							//std::cout << "temp x" << temp.transform.x << std::endl;
						}
						else if (name == "y") {
							temp.transform.y = atoi(pNode3->value());
							//std::cout << "temp y" << temp.transform.y << std::endl;
						}
					}
					lvlData.push_back(temp);
				}
			}
		}
	}
	else if (LevelSelect::_diff == "Medium") {
		for (xml_node<> *pNode = pRoot->first_node("Medium"); pNode < pRoot->first_node("Hard"); pNode = pNode->next_sibling()) {
			//std::cout << pNode->name() << ':' << '\n';
			for (xml_node<> *pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {
				//std::cout << "  " << pNodeI->name() << "-" << pNodeI->value() << '\n';
				for (xml_node<> *pNode2 = pNodeI->first_node(); pNode2; pNode2 = pNode2->next_sibling()) {
					//std::cout << "    " << pNode2->name() << "-" << pNode2->value() << '\n';
					for (xml_node<> *pNode3 = pNode2->first_node(); pNode3; pNode3 = pNode3->next_sibling()) {
						//std::cout << "      " << pNode3->name() << "-" << pNode3->value() << '\n';
						name = pNode3->name();
						value = pNode3->value();
						//std::cout << "name" << name << std::endl;
						//std::cout << "value" << value << std::endl;
						if (name == "ID") {
							temp.objectID = SwitchTextrue(atoi(pNode3->value()));
						}
						else if (name == "x") {
							temp.transform.x = atoi(pNode3->value());
							//std::cout << "temp x" << temp.transform.x << std::endl;
						}
						else if (name == "y") {
							temp.transform.y = atoi(pNode3->value());
							//std::cout << "temp y" << temp.transform.y << std::endl;
						}
					}
					lvlData.push_back(temp);
				}
			}
		}
	}
	else if (LevelSelect::_diff == "Hard") {
		for (xml_node<> *pNode = pRoot->first_node("Hard"); pNode; pNode = pNode->next_sibling()) {
			//std::cout << pNode->name() << ':' << '\n';
			for (xml_node<> *pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling()) {
				//std::cout << "  " << pNodeI->name() << "-" << pNodeI->value() << '\n';
				for (xml_node<> *pNode2 = pNodeI->first_node(); pNode2; pNode2 = pNode2->next_sibling()) {
					//std::cout << "    " << pNode2->name() << "-" << pNode2->value() << '\n';
					for (xml_node<> *pNode3 = pNode2->first_node(); pNode3; pNode3 = pNode3->next_sibling()) {
						//std::cout << "      " << pNode3->name() << "-" << pNode3->value() << '\n';
						name = pNode3->name();
						value = pNode3->value();
						//std::cout << "name" << name << std::endl;
						//std::cout << "value" << value << std::endl;
						if (name == "ID") {
							temp.objectID = SwitchTextrue(atoi(pNode3->value()));
						}
						else if (name == "x") {
							temp.transform.x = atoi(pNode3->value());
							//std::cout << "temp x" << temp.transform.x << std::endl;
						}
						else if (name == "y") {
							temp.transform.y = atoi(pNode3->value());
							//std::cout << "temp y" << temp.transform.y << std::endl;
						}
					}
					lvlData.push_back(temp);
				}
			}
		}
	}
	else {
		std::cout << "Difficulty not found" << std::endl;
	}
	return lvlData;
}

ObjectID IOManager::SwitchTextrue(int index)
{
	switch (index) {
	case 1:
		return ObjectID::COCHE;
		break;
	case 2:
		return ObjectID::EXCAVADORA;
		break;
	case 3:
		return ObjectID::RALLY1;
		break;
	case 4:
		return ObjectID::RALLY2;
		break;
	case 5:
		return ObjectID::CAMION;
		break;
	case 6:
		return ObjectID::TRONCO_CORTO;
		break;
	case 7:
		return ObjectID::TRONCO_LARGO;
		break;
	case 8:
		return ObjectID::TRONCO_MEDIANO;
		break;
	case 9:
		return ObjectID::COCODRILO_CERRADO;
		break;
	case 10:
		return ObjectID::NUTRIA;
		break;
	case 11:
		return ObjectID::SERPIENTE;
		break;
	case 12:
		return ObjectID::TORTUGA;
		break;
	case 13:
		return ObjectID::TRITUGA1;
		break;
	case 14:
		return ObjectID::NUTRIA2;
		break;
	default:
		std::cout << "No ID found" << std::endl;
		break;
	}
}

std::vector<Score> IOManager::SaveRanking(Score score)
{
	std::ofstream filesalida;
	Score s;
	std::vector<Score> ListOfScore;
	
	ListOfScore = LoadRanking();

	int scoreSize = sizeof(Score);

	ListOfScore.push_back(score);

	filesalida.open(RESOURCE_FILE(std::string("cfg/Ranking.dat")), std::ios::out | std::ios::binary);
	if (!filesalida.is_open()) {
		throw std::exception("System was not able to open the rankings file");
	}
	for (int i = 0; i < ListOfScore.size(); i++) {
		filesalida.write(reinterpret_cast<char *>(&s), scoreSize);
	}
	
	filesalida.close();
	return ListOfScore;
}

std::vector<Score> IOManager::LoadRanking()
{
	std::ifstream fileentrada;
	std::streampos fileSize;
	std::vector<Score> ListOfScore;
	Score score;
	int scoreSize = sizeof(Score);
		

	fileentrada.open(RESOURCE_FILE(std::string("cfg/Ranking.dat")), std::ios::in | std::ios::binary);
	if (!fileentrada.is_open()) {
		throw std::exception("System was not able to open the rankings file");
	}

	//Compute the filesize
	fileentrada.seekg(0, std::ios::end);
	fileSize = fileentrada.tellg();
	fileentrada.seekg(0, std::ios::beg);

	int numElements = (int)fileSize / sizeof(score);

	for (int i = 0; i < numElements; i++) {
		fileentrada.read(reinterpret_cast<char *>(&score), scoreSize);
		ListOfScore.push_back(score);
	}

	if (numElements == 0) {
		score.name = "Adri";
		score.score = 10;
		std::ofstream filesalida(RESOURCE_FILE(std::string("cfg/Ranking.dat")), std::ios::out | std::ios::binary | std::ios::ate);
		for (int i = 0; i < 10; i++) {
			filesalida.write(reinterpret_cast<char *>(&score), scoreSize);
			//std::cout << score.name << score.score << std::endl;
			ListOfScore.push_back(score);
		}
		filesalida.close();
	}
	fileentrada.close();
	return ListOfScore;
}
