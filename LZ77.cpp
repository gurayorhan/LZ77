#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

unsigned short forwardBufferRange = 8;
unsigned short searchBufferRange = 8;

int insideToAgain(string forwardBuffer,int again){
    int i = 0,againBackup = 0;
    while(1){
        if((again+i) < forwardBuffer.size()){
            if(forwardBuffer.at(i) == forwardBuffer.at(again+i)){
                againBackup++;
            }else{
                break;
            }
        }else{
            break;
        }
        i++;
    }
    return againBackup;
}

//the position and number of repeated words are calculated
int * theNumberOfRepetitions(string searchBuffer,string forwardBuffer){
    int index= 0,againCount=1;
    int* again = new int[2]{1,1};//again[0] index ,again[1] again count
    for(int i = 0; i< searchBuffer.size()-1;i++){
        if((int)forwardBuffer.at(0) == (int)searchBuffer.at(i)){
            index=i;
            for(int j = 1;j<forwardBuffer.size();j++){
                if((int)forwardBuffer.at(againCount) == (int)searchBuffer.at(j+i) && (j+i)< searchBuffer.size()-1 && againCount < forwardBuffer.size()-1){
                    againCount++;
                }else{
                    break;
                }
            }
            if(againCount >= again[1]){
                again[1] = againCount;
                again[0] = index+1;
                againCount = 1;
            }
        }
    }
    if(again[1] > 1){
        again[1] += insideToAgain(forwardBuffer,again[1]);
    }
    return again;
}

//excess data in search buffer is deleted
string clearMyOver(string searchBuffer){
    for(int i = 0;i<searchBufferRange-searchBuffer.size();i++)
            searchBuffer.erase(searchBuffer.begin());
    return searchBuffer;
}

void LZ77(){
    char character;
    ostringstream craeteText;
    ifstream readFile("text.txt");
    string forwardBuffer,searchBuffer,compressedText,uncompressedText;
    bool close = true,definitiveTransition = false,firstCharacterAdd = true;
    if(readFile.is_open()){
        while(readFile.good() || forwardBuffer.size()> 1){
            if(!readFile.good()){
                close = false;
                definitiveTransition = true;
            }
            if(close){
                readFile.get(character);
                forwardBuffer.append(1,character);
                uncompressedText+=character;
            }
            if(forwardBuffer.size() == forwardBufferRange || definitiveTransition){
                if(searchBuffer.size() < 1){
                    cout<<"(0,0,"<<forwardBuffer[0]<<")";
                    searchBuffer.append(1,forwardBuffer[0]);
                    forwardBuffer.erase(forwardBuffer.begin());
                }else if(searchBuffer.size() <= searchBufferRange && searchBuffer.size() > 0){
                    if(searchBuffer.find(forwardBuffer[0]) != std::string::npos){
                        int *again = theNumberOfRepetitions(searchBuffer,forwardBuffer);
                        cout<<"("<<searchBuffer.size()-again[0]+1<<","<<again[1]<<","<<forwardBuffer[again[1]]<<")";
                        for(int j = 0; j< again[1]+1;j++){
                            searchBuffer.append(1,forwardBuffer[0]);
                            forwardBuffer.erase(forwardBuffer.begin());
                        }
                    }else{
                        cout<<"(0,0,"<<forwardBuffer[0]<<")";
                        searchBuffer.append(1,forwardBuffer[0]);
                        forwardBuffer.erase(forwardBuffer.begin());
                    }
                    if(searchBuffer.size() > searchBufferRange)
                        searchBuffer = clearMyOver(searchBuffer);
                }
            }
        }
    }
    readFile.close();
    uncompressedText.erase(uncompressedText.size()-1);
    cout<<endl<<endl<<uncompressedText<<endl<<endl;
}

int main()
{
    LZ77();
    return 0;
}
