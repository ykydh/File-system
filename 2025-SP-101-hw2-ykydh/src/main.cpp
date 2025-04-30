#include "File.h"
#include <string>
#include <iostream>
#include <sstream>
//null,cd,ls,pwd,mkdir,rm,mv
std::string uername;
int main(){
    enum command input;
    std::string inp,name,extra;
    directory* current;
    std::string command;
    std::vector<char> input_v;
    //int j;

    std::cout<<"Type a user name: ";
    std::cin>>uername;
    current = &root;
    std::cin.clear();              // Clear error flags
    std::cin.ignore();
    while(true)
    {
      std::cout<<uername<<"@Filesystem-emulator "<<current->directory_path<<" % "; 
      name="";
      command="";
      std::getline(std::cin, inp);  // Read full line
      std::istringstream iss(inp);  // Use string stream to parse

        iss >> command >> name >> extra;


      input=command_handler(command);
      //std::cout<<input<<std::endl;
      switch(input)
      {
        case 0:
        {
          std::cout<<"Invalid input"<<std::endl;
          break;
        }
        case 1:
        {
          directory* next = current->cd(name); // make sure cd returns a pointer
          if (next != nullptr){
            current = next;
          } 
          break;
        }
        case 2:
        {
          current->ls(name,uername);
          break;
        }
        case 3:
        {
          current->pwd();
          break;
        }
        case 4:
        {
          current->mkdir(name);
          break;
        }  
        case 5:
          current->rm(name);
          break;
        case 6:
          current->move(name,extra);
          break;
        case 7:
          current->nano(name);
          break;
        case 8:
          current->rmdir(name);
          break;
        case 9:
          return 1;
          break;
        case 10:
          helpp();
          break;
      }
    }
      return 0;
}