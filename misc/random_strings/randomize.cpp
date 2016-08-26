#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <my_timer.h>
#include <random>
#include <string>


using namespace std;

const int MAX_CHAR=26;


void generate_substring(string input_string)
{

}

struct Node
{
    int   value;
    Node* children[MAX_CHAR];
};

class Tree
{

    public:

    Tree();
    ~Tree();

    void insert (string  );
    bool search (const string);

    private:
        Node *root;
        int   node_count;
};

Tree::Tree()
{
    root  = new Node;
    node_count = 0;

    if (root)
    {
        for (int i=0;i<MAX_CHAR; i++)
        {
            root->children[i] = NULL;
        }
    }
}

Tree::~Tree()
{

    if (root == NULL)
        return;

    for (int i=0;i<MAX_CHAR; i++)
    {
        if (root->children[i] != NULL)
        {
            delete root->children[i];
        }
    }
}

//only lower case supported for now
static int
charToInt(char character)
{
    return ((int)character - 'a');
}

void
Tree::insert(string key)
{
    Node *pWalker = root;

    node_count++;

    for(int level = 0; level < key.size(); level++)
    {
        int index = charToInt(key[level]);
        if (pWalker->children[index] == NULL)
        {
           pWalker->children[index] = new Node;
           cout << "inserting "<<key[level]<< " at index "<<index<<endl;
        }
        pWalker = pWalker->children[index];
    }

    pWalker->value = node_count;
    cout << "node count: "<<node_count <<endl;
}

bool
Tree::search(string key)
{
    Node *pWalker = root;
    for(int level = 0; level < key.size(); level++)
    {
        int index = charToInt(key[level]);
        if (pWalker->children[index] == NULL)
        {
            return false;
        }
        pWalker = pWalker->children[index];
    }
    return((pWalker!=NULL) && (pWalker->value != 0));
}

int main(int argc, const char *argv[])
{
#if 0
    vector<string> input_list;
    string         tmpStr;
    ifstream       ifs(argv[1]);
    ofstream       ofs(argv[2], ofstream::out);
    my_timer       my_clock;
    random_device  rd;
    mt19937        rand_gen(rd());



    if (argc < 3)
    {
        cout << "usage: "<< endl;
        cout << "randomize input_text_file output_text_file"<< endl;
        return -1;
    }

    if (ifs.is_open() && ofs.is_open())
    {
        while (ifs >> tmpStr)
        {
            input_list.push_back(tmpStr);
        }
    }
    else
    {
        cout << "failed to open files " << argv[1] << " "<<argv[2] <<endl;
        return -1;
    }


    my_clock.start();

    shuffle(input_list.begin(), input_list.end(), rand_gen);

    for (auto& i : input_list)
    {
        ofs << i << endl;
        cout <<i<<endl;
    }

    my_clock.finish();

    cout << "elapsed time "<< my_clock.get_mseconds() <<endl;

    ofs.close();
    ifs.close();

#endif
    string keys[8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};

    string output[32] = {"Not present in trie", "Present in trie"};

    Tree myTree;

    for(int i = 0; i < 8; i++)
    {
        myTree.insert(keys[i]);
    }


    // Search for different keys
    cout << "the   is  " << output[myTree.search( "the")]   << endl;
    cout << "these is  " << output[myTree.search( "these")] << endl;
    cout << "their is  " << output[myTree.search( "their")] << endl;
    cout << "thaw  is  " << output[myTree.search("thaw")]   << endl;
    cout << "ther  is  " << output[myTree.search("thes")]   << endl;
    return 0;
}
