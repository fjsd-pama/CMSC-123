#include <iostream>
#include "list.cpp"
#include <fstream>
#include <bitset>

/**
* Created by Arniel Pama, Oct. 2016
**/

using namespace std;

//SIZE OF BITS THEY HOLD
int SOURCEADD_SIZE = 32;
int DESTADD_SIZE = 32;
int SEQNUM_SIZE = 16;
int CHECKSUM_SIZE = 16;
int LENGTHOFDATA_SIZE = 16;
//int DATA_SIZE = variable
//int PADDING_SIZE = variable

class packet{
  public:
    string srcAddr, destAddr, checkSum, data, padding;
    int sequenceNum, lengthOfData;
    bool isNotCorrupt;
    packet();
    packet(string, string, int, string, bool, int, string, string);
};

packet::packet(){
  //do nothing
}

packet::packet(string srcAddr, string destAddr, int sequenceNum, string checkSum, bool isNotCorrupt, int lengthOfData, string data, string padding){
  this->srcAddr = srcAddr;
  this->destAddr = destAddr;
  this->sequenceNum = sequenceNum;
  this->checkSum = checkSum;
  this->isNotCorrupt = isNotCorrupt;
  this->lengthOfData = lengthOfData;
  this->data = data;
  this->padding = padding;
}

int binToDecimal(string given){
  bitset<32> bits1(given);
  return (int)(bits1.to_ulong());
}

//convert IP addresses to dotted form (e.g. 172.105.89.23)
string convertToDottedForm(string given){
  int one, two, three, four;
  one = binToDecimal(given.substr(0, 8));
  two = binToDecimal(given.substr(8, 8));
  three = binToDecimal(given.substr(16, 8));
  four = binToDecimal(given.substr(24, 8));

  return to_string(one) + "." + to_string(two) + "." + to_string(three) + "." + to_string(four);
}

string onesComplement(string bit){
  for (size_t i = 0; i < bit.size(); i++){
    if ( bit[i] == '1'){
      bit[i] = '0';
    } else{
      bit[i] = '1';
    }
  }

  return bit;
}

string computeCheckSum(string given){
  int result = 0;
  string current;
  string copy = given;
  copy.replace(80, CHECKSUM_SIZE, "0000000000000000"); //replaces checkSum temporarily
  for (size_t x = 0; x <= copy.size(); x += 16){
    current = copy.substr(x, 16);
    result = result + binToDecimal(current);
    bitset<17> answer(result);

    if ((answer.to_string())[0] == '1'){
      result = binToDecimal((answer.to_string().substr(1, 16))) + 1;
    }
  }

  bitset<17> finalresult(result);
  return onesComplement(finalresult.to_string().substr(1, 16));
}

//convert a string of bits into words
string binToChars(string givenBits){
  string result;
  char current;
  for (size_t i = 0; i <= givenBits.size(); i += 8){
    current = binToDecimal(givenBits.substr(i, 8));
    result += current;
  }

  return result;
}

//arrange the poem in order
void reconstructPoem(list<packet>& poem){
  for(int i = 0; i < poem.getSize() - 1; i++){
    int smallest = i;

    for ( int j = i + 1; j < poem.getSize(); j++){
      if ( (poem.get(j).sequenceNum < poem.get(smallest).sequenceNum) ){
        smallest = j;
      }
    }

    packet temp = poem.get(i);
    poem.set(poem.get(smallest), i);
    poem.set(temp, smallest);
  }

  //put the line with the negative sequenceNum is at the end of the poem
  packet temp = poem.get(0);
  if (temp.sequenceNum < 0){
    poem.remove(0);
    poem.insert(temp, poem.getSize() - 1);
  }
}


void writeOutputPoems(list< list<packet> > given, string ofName ){
  ofstream file(ofName);
  list<packet> poem; //a list of packet is a poem
  packet currentPacket;
  packet firstPacketInAPoem;

  //traversing the whole list of list of packets
  for ( int i = 0; i < given.getSize(); i++ ){
    poem = given.get(i);
    reconstructPoem(poem); //dapat passed as a reference ni (??)

    firstPacketInAPoem = poem.get(0);
    //display(firstPacketInAPoem);

    //prints the title
    if( firstPacketInAPoem.sequenceNum == 0 ){
      file<<firstPacketInAPoem.data<<endl;
    } else{
      file<<"[title missing]"<<endl;
    }

    //prints IP address
    file<<firstPacketInAPoem.srcAddr<<"/"<<firstPacketInAPoem.destAddr<<endl;

    //printing the rest of the lines of the current poem
    for(int j = 1; j < poem.getSize(); j++){
      currentPacket = poem.get(j);


      if (currentPacket.lengthOfData == 0){
          //do nothing
      } else {
          if( currentPacket.isNotCorrupt ){
            file<<currentPacket.data<<endl;
          } else{
              file<<"[line corrupted]"<<endl;
          }
      }
    } //end inner for

    file<<"\n------------------------------------------------------------\n"<<endl; //end of a poem
  } //end outer for

  file.close();

}

bool isWithUniqueIPAddress(packet line, list< list<packet> > setOfPoems){
  for (int i = 0; i < setOfPoems.getSize(); i++){
    if ( (setOfPoems.get(i).get(0).srcAddr == line.srcAddr) && (setOfPoems.get(i).get(0).destAddr == line.destAddr) ){
      return false;
    }
  }

  return true;
}

bool isWithUniqueSeqNum(packet line, list<packet> poem){
  for (int i = 0; i < poem.getSize(); i++){
    if ( (poem.get(i).sequenceNum == line.sequenceNum) ){
      return false;
    }
  }

  return true;
}

void decodeInputFile(string fileName){
  //declare variables
  list<packet> poem;
  list< list<packet> > poemSS;
  int paddingNumStart = 0;
  string srcAddr, destAddr, checkSum, data, padding;
  short sequenceNum;
  int lengthOfData;
  bool isNotCorrupt;
  string currentLine;

  //file manipulation
  ifstream file(fileName);
  if(file.is_open()){
		while(!file.eof()){
      file>>currentLine;

      //converting the currentLine into a packet
      srcAddr = convertToDottedForm(currentLine.substr(0, SOURCEADD_SIZE));
      destAddr = convertToDottedForm(currentLine.substr(32, DESTADD_SIZE));
      sequenceNum = (short)binToDecimal(currentLine.substr(64, SEQNUM_SIZE));
      checkSum = currentLine.substr(80, CHECKSUM_SIZE);

      if ( checkSum.compare(computeCheckSum(currentLine)) == 0 ){
        isNotCorrupt = true;
      } else{
        isNotCorrupt = false;
      }

      lengthOfData = binToDecimal(currentLine.substr(96, LENGTHOFDATA_SIZE));
      data = binToChars(currentLine.substr(112, lengthOfData));
      paddingNumStart = 102 + lengthOfData;
      padding = currentLine.substr(paddingNumStart, currentLine.size() - paddingNumStart);
      packet currentPacket = packet(srcAddr, destAddr, sequenceNum, checkSum,isNotCorrupt, lengthOfData, data, padding);

      //if-else statement here adds currentPacket to poemSS
      if ( isWithUniqueIPAddress(currentPacket, poemSS) ){
        if (poemSS.getSize() == 0){
            poem = poemSS.get(0);
            poem.insert(currentPacket, 0);
            poemSS.insert(poem, 0);
        } else{
            poem = poemSS.get(poemSS.getSize());
            poem.insert( currentPacket, poem.getSize() );
            poemSS.insert( poem, poemSS.getSize() );
        }

      } else{
        for( int i = 0; i < poemSS.getSize(); i++){
          poem = poemSS.get(i);
          if ( (poem.get(0).srcAddr == currentPacket.srcAddr) && (poem.get(0).destAddr == currentPacket.destAddr)
              && isWithUniqueSeqNum(currentPacket, poem) ){
              poem = poemSS.get(i);
              poem.insert(currentPacket, poem.getSize());
              poemSS.set(poem, i);
              break;
          }
        }
      }
    } //end while

    writeOutputPoems(poemSS, "poems.in");
	  file.close();
	} //end outer if
}


int main(){
  //decodeInputFile("cases_in_order.in");
  decodeInputFile("cases_random.in");
  return 0;
}
