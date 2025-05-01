#ifndef FILE_H_
#define FILE_H_
#include<vector>
#include<string>
#include<iostream>
#include<memory>
#include<algorithm>
enum command{null,cd,ls,pwd,mkdir,rm,mv,nano,rmdir,quit,help};

class File{
    public:
    File(const std::string& name) : file_name(name) {
    }
      std::string file_name;
      std::string file_type;
      std::string content;
};

struct directory{
    directory();
    std::string directory_path;
    std::string directory_name;
    std::vector<std::unique_ptr<File>> elems;
    std::vector<std::unique_ptr<directory>> subdire;
    directory* parent = nullptr;
    directory* cd(std::string name);
    void ls(std::string name,std::string username);
    void mkdir(std::string name);
    void pwd();
    void rm(std::string name);
    void rmdir(std::string name);
    void move(std::string name, std::string dest);
    void nano(std::string name);

};

void helpp();
extern directory root;

command command_handler(std::string x);
#endif
