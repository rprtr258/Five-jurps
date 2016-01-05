#ifndef SAVELOADER_H
#define SAVELOADER_H

#include <fstream>
#include <vector>
#include <string>

#include "Field.h"

class SaveLoader {
    public:
        SaveLoader(const std::string &path);
        ~SaveLoader();
        void resetPath(const std::string &path);

        void load(Field &field);
    private:
        std::ifstream inputFile;
        std::ofstream outputFile;
        std::string savePath;
};

#endif
