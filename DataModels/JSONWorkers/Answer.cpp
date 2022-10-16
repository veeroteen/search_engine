#include "Answer.h"


void Answer::saveData()
{
    fillDict();
    saveDict(fileName);
}
void Answer::setFileName(std::string fileName)
{
    this->fileName = fileName;
}