#include "FileManager.h"

using namespace std;

FileManager::FileManager(const string &rootDir, const string &outputFilename)
    : fileSystem(rootDir), outputFile(outputFilename) {
    indexFiles(fileSystem.getRoot(), rootDir);
}

FileManager::~FileManager() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

void FileManager::indexFiles(DirNode *currNode, const string &parentPath) {
    if (currNode == nullptr) {
        return;
    }

    string filePath = parentPath + "/" + currNode->getName();

    ifstream inFile(filePath);
    string line;
    int lineNum = 1;

    while (getline(inFile, line)) {
        istringstream iss(line);
        string word;

        while (iss >> word) {
            string sw = stripNonAlphaNum(word); // sw stands for stripped word
            ht.insert(sw, filePath + ":" + to_string(lineNum) + ": " + line);
        }
        ++lineNum;
    }

    inFile.close();

    for (int i = 0; i < currNode->numSubDirs(); ++i) {
        DirNode* subDir = currNode->getSubDir(i);
        indexFiles(subDir, filePath);
    }
}

void FileManager::processQueries() {
    string query;

    while (true) {
        cout << "Query? ";

        getline(cin, query);

        if (query == "@q") {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            exit(0);

        } else if (query == "@quit") {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            exit(0);

        } else if (query == "@f") {
            string newOutputFile;
            cin >> newOutputFile;
            if (outputFile.is_open()) {
                outputFile.close();
            }
            outputFile.open(newOutputFile);

        } else if (query.substr(0,2) == "@i") {
            query = removeCommand(query);
            performQuery(query, false);

        } else if (query.substr(0,11) == "@insensitive") {
            query = removeCommand(query);
            performQuery(query, false);

        } else {
            performQuery(query, true);
        }
    }
}

void FileManager::performQuery(const string &query, bool caseSensitive) {
    string strippedQuery = stripNonAlphaNum(query);

    if (not caseSensitive) {
        strippedQuery = toLowercase(strippedQuery);
    }

    int hashValue = ht.hashFunction(strippedQuery);
    
    string result = ht.search(strippedQuery);

    if (not result.empty()) {
        processResults(result);
    } else {
        outputFile << strippedQuery;
        queryNotFound(caseSensitive);
    }
}

void FileManager::processResults(const string &result) {
    istringstream iss(result);
    string filePath;
    int lineNum;
    string line;

    while (iss >> filePath >> lineNum >> line) {
        printResults(filePath, lineNum, line);
    }
}

void FileManager::printResults(const string &filePath, int lineNum,
                               const string &line) {
    outputFile << filePath << ":" << lineNum << ": " << line << endl;
}

void FileManager::queryNotFound(bool caseSensitive) {
    if (not caseSensitive) {
        outputFile << " Not Found." << endl;
    } else {
        outputFile << " Not Found. Try with @insensitive or @i." << endl;
    }
}

string FileManager::toLowercase(const string &input) {
    string result = input;
    for (char &c : result) {
        c = std::tolower(c);
    }
    return result;
}

string FileManager::removeCommand(const string &query) {
    string strippedQuery;
    if (query.substr(0,2) == "@i") {
        strippedQuery = query.substr(2);
    } else if (query.substr(0,11) == "@insensitive") {
        strippedQuery = query.substr(11);
    }
    return strippedQuery;
}