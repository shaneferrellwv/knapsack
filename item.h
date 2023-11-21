#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// class to represent item choices
class item
{
public:
    string name;
    int w; // weight
    int v; // value

    // item constructor
    item(string name, int weight, int value)
    {
        this->name = name;
        this->w = weight;
        this->v = value;
    }

    // utlility function to create list of items from input file
    // file must be whitespace-separated values within input/ directory
    // in the form: name weight value
    static vector<item> createItemsList(const string& filePath)
    {
        vector<item> items;
        ifstream itemsFile("input/" + filePath);

        // check if file exists
        if (!itemsFile)
            throw invalid_argument("File input/" + filePath + " does not exist");

        string line;
        while (getline(itemsFile, line))
        {
            istringstream stream(line);
            string name;
            int w;
            double v;

            // check if file is in correct format (string int double)
            if (!(stream >> name >> w >> v) || !(stream.eof()))
                throw invalid_argument("File " + filePath + " in invalid format");
            
            items.push_back(item(name, w, v));
        }

        return items;
    }
};