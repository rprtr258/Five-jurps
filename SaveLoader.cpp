#include "SaveLoader.h"

SaveLoader::SaveLoader(const std::string &path):savePath(path) {
}

SaveLoader::~SaveLoader() {
}

void SaveLoader::resetPath(const std::string &path) {
    savePath = path;
}

void SaveLoader::load(Field &field) {
    int size, t;
    std::vector<std::vector<int> > newField, newGoal;
    inputFile.open(savePath);
    inputFile >> size;
    for(int i = 0;i<size;i++) {
        std::vector<int> columnField(size), columnGoal(size);
        newField.push_back(columnField);
        newGoal.push_back(columnGoal);
    }
    for(int i = 0;i<size;i++) {
        for(int j = 0;j<size;j++) {
            inputFile >> t;
            newField[j][i] = t;
        }
    }
    for(int i = 0;i<size;i++) {
        for(int j = 0;j<size;j++) {
            inputFile >> t;
            newGoal[j][i] = t;
        }
    }
    field.set(newField, newGoal);
    inputFile.close();
}
