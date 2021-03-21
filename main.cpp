#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

void printDecoding(string result, ofstream &outputFile, int choice)
{
    if(choice == 1)
    {
         outputFile << "Decodificacao em arquivo txt: " << endl;
         outputFile << result;
         outputFile << endl;
         outputFile << endl;
    }

    else
    {
        cout << "Decodificacao em console" << endl;
        cout << result;
    }
    
    cout << endl;
}

string decoding(vector<string> &dictionary, vector<int> &codified)
{
    int index;
    string aux, result;

    for (int i = 0; i < codified.size(); i++)
    {
        index = codified[i];
        aux = dictionary[index];
        result += aux;
    }
    return result;
}

bool chooseDecoding()
{
    int choice = -1;

    while (choice != 1 && choice != 0)
    {
        cout << "Deseja decodificar o arquivo?" << endl;
        cout << "Digite [1] para sim" << endl;
        cout << "Digite [0] para nao" << endl;
        cin >> choice;
    }

    return choice;
}

void printLZWCodified(vector<int> &codified, ofstream &outputFile, int choice)
{
    if (choice == 1)
    {
        outputFile << "Imprimindo a codificacao em arquivo txt " << endl;

        for (int i = 0; i < codified.size(); i++)
        {
            outputFile << " " << codified[i];
        }

        outputFile << endl;
        outputFile << endl;
    }

    else
    {
        cout << "Imprimindo a codificacao no console " << endl;

        for (int i = 0; i < codified.size(); i++)
        {
            cout << " " << codified[i];
        }
    }

    cout << endl;
}

void printCharInDictionary(vector<string> &dictionary, ofstream &outputFile, int choice)
{

    if (choice == 1)
    {
        outputFile << "Imprimindo caracteres iniciais do dicionario em txt!" << endl;

        for (int i = 0; i < dictionary.size(); i++)
        {
            outputFile << " " << dictionary[i];
        }

        outputFile << endl;
        outputFile << endl;
    }

    else
    {
        cout << "Imprimindo caracteres iniciais do dicionario no console!" << endl;

        for (int i = 0; i < dictionary.size(); i++)
        {
            cout << " " << dictionary[i];
        }
    }

    cout << endl;
}

int selectOutput()
{
    int choice = -1;

    while (choice != 1 && choice != 2)
    {
        cout << "Digite [1] para saida em arquivo;" << endl;
        cout << "Digite [2] para saida em console;" << endl;
        cin >> choice;
    }

    if (choice == 1)
    {
        cout << "A saida em arquivo estara salva em exit.txt!" << endl;
    }

    return choice;
}

void lzwCompression(vector<string> &dictionary, vector<int> &codified, string &aux)
{
    char aux2 = aux[0];
    int index;
    string c, p(1, aux2);    

    for (int i = 1; i < aux.size(); i++)
    {
        c = aux[i];
        vector<string>::iterator iterator = find(dictionary.begin(), dictionary.end(), p + c);

        if (iterator != dictionary.end())
        {
            p += c;
        }
        
        else
        {
            vector<string>::iterator iteratorP = find(dictionary.begin(), dictionary.end(), p);
            index = distance(dictionary.begin(), iteratorP);
            dictionary.push_back(p + c);
            codified.push_back(index);
            p = c;
        }
    }

    vector<string>::iterator iteratorP = find(dictionary.begin(), dictionary.end(), p);
    index = distance(dictionary.begin(), iteratorP);
    codified.push_back(index);
}

void addCharInDictionary(vector<string> &dictionary, string aux)
{
    char c;

    for (int i = 0; i <= aux.size(); i++)
    {
        c = aux[i];
        string aux(1, c);
        dictionary.push_back(aux);
    }

    sort(dictionary.begin(), dictionary.end());
    dictionary.erase(unique(dictionary.begin(), dictionary.end()), dictionary.end());
}

string readTxt(ifstream &inputFile, string &aux, ofstream &outputFile, int choice)
{
    string line;

    if (inputFile.is_open())
    {
        getline(inputFile, line);
        aux += line;
    }

    if(choice == 1)
    {
        outputFile << "Entrada: " << aux << endl;
        outputFile << endl;
    }

    else
    {
        cout << "Entrada: " << aux << endl;
    }

}

int main()
{
    string line, aux;
    ifstream inputFile;
    ofstream outputFile("exit.txt");
    vector<string> dictionary;
    vector<int> codified;

    cout << "Iniciando o programa" << endl;
    int choice = selectOutput();

    inputFile.open("entry.txt");
    readTxt(inputFile, aux, outputFile, choice);


    addCharInDictionary(dictionary, aux);
    printCharInDictionary(dictionary, outputFile, choice);

    lzwCompression(dictionary, codified, aux);
    printLZWCodified(codified, outputFile, choice);

    bool selectDecodified = chooseDecoding();

    if (selectDecodified == true)
    {
        string decodified = decoding(dictionary, codified);
        printDecoding(decodified, outputFile, choice);
    }

    return 0;
}
