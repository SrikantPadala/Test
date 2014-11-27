/*Lab 8*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

int min(int a,int b,int c) { return (a < b ? (a < c ? a : c) : (b < c ? b : c)); }
typedef std::unordered_multimap<char,string> Dictionary;

struct element
{
	string word;
	int priority;

	element(string w, int p)
	{
		word = w;
		priority = p;
	}
};

struct compare
{
	bool operator()(const element &e1, const element &e2) const
	{
		return e1.priority > e2.priority;
	}
};

int getEditDistance(string input, string second);

int main(int argc, char *argv[])
{
    Dictionary dictionary;
    vector<string> inputData;
    ifstream in,dict;
    ofstream out;
    if(argc != 7)
	{
		cerr << "Invalid number of arguments" << endl;
		return 0;
	}
	//Parsing the command line options
    char ch, *inputfile, *dictionaryfile, *outputfile;
    int iFlag = 0, dFlag = 0, oFlag = 0;
    while ((ch=getopt(argc, argv, "d:i:o:"))!=EOF) {
        switch(ch) {
        case 'i':
            inputfile = optarg;
            iFlag = 1;
            break;

        case 'd':
            dictionaryfile = optarg;
            dFlag = 1;
            break;

		case 'o':
            outputfile = optarg;
            oFlag = 1;
            break;

        default:
            printf ("Sorry!! Invalid option came into processing\n");
            break;
        }
    }

    argc -= optind;
    argv += optind;
    //End of processing the command line options

    if(iFlag == 1)
	{
		in.open(inputfile);
        if (in.fail()) {
            cerr << "Input file cannot be opened" << endl;
            return 0;
        }
        string temp;
        while(true)
        {
            in >> temp;
			if(in.eof()) break;
            inputData.push_back(temp);
        }
		/*for(auto it = inputData.begin(); it != inputData.end(); it++)
        {
			cerr << *it << endl;
		}*/
	}

	if(oFlag == 1)
	{
		out.open(outputfile);
		if (out.fail()) {
	        cerr << "Output file cannot be opened" << endl;
	        return 0;
	    }
	}

	if(dFlag == 1)
	{
        dict.open(dictionaryfile);
        if (dict.fail()) {
            cerr << "Dictionary file cannot be opened" << endl;
            return 0;
        }
        string temp;
        while(true)
        {
            dict >> temp;
            if(dict.eof()) break;
            dictionary.insert(Dictionary::value_type(temp[0],temp));
        }

        /*for(auto it = dictionary.begin(); it != dictionary.end(); it++) {
            cerr << it->first << '\t';
            cerr << it->second << endl;
        }*/

		priority_queue<element, vector<element>, compare> pq;

        for(auto it = inputData.begin(); it != inputData.end(); it++)
        {
            string input = *it;
            out << input << ": ";

            //cerr << "First : " << input;

			auto words = dictionary.equal_range(input[0]);

            for(auto d = words.first; d != words.second; d++) {
                //cerr << " Second : " << d->second << endl;
                string second = d->second;
                int editDistance = getEditDistance(input,second);
				//cerr << "Edit distance : " << table[input.size()][second.size()] << endl;
                if(editDistance <= 3 && editDistance > 0)
                    pq.push(element(second,editDistance));
            }
			while(!pq.empty())
			{
				element min = pq.top();
				out << min.word << " ";
				pq.pop();
			}
            out << endl;
        }
    }
    return 0;
}

int getEditDistance(string input, string second)
{
	int table[input.size()+1][second.size()+1];

    for(int i=0; i < input.size()+1; i++)
        table[i][0] = i;
    for(int j=0; j < second.size()+1; j++)
        table[0][j] = j;
    for(int i=1; i < input.size()+1; i++)
    {
        for(int j=1; j < second.size()+1; j++)
        {
            table[i][j] = min(table[i-1][j]+1,table[i][j-1]+1,table[i-1][j-1] + (input[i-1] == second[j-1] ? 0 : 1));
        }
    }
	/*cerr << endl;
	for(int i=0; i < input.size()+1; i++)
    {
        for(int j=0; j < second.size()+1; j++)
        {
			cerr << table[i][j] << " ";
		}
		cerr << endl;
	}*/
	//cerr << "Edit distance : " << table[input.size()][second.size()] << endl;
    return table[input.size()][second.size()];
}
