#include "File.h"
#include <string>
#include <iostream>
#include <sstream>
directory root;

directory::directory()
{
  directory_name = "Root";
  directory_path = "/Root";
}

directory* directory::cd(std::string name)
{
    for (auto& subdir : subdire)
    {
        if (subdir->directory_name == name)
        {
          return subdir.get();
        }
    }

    if(name == "../")
        {
          return this->parent;
        }
    std::cout << "Directory not found.\n";
    return nullptr;
}

void directory::ls(std::string name,std::string username)
{
  if(name == "-l")
  {
    for (auto& subdir : subdire)
    {
      std::cout<<"d "<<username<<" staff "<< subdir->directory_name <<std::endl;
    }
      
    for (auto& elem : elems)
    {
      std::cout <<"- "<<username<<" staff "<< elem->file_name <<std::endl;
    }
  
      std::cout << std::endl;
    return;
  }
   
  for (auto& subdir : subdire)
  {
    std::cout << subdir->directory_name << "   ";
  }
    
  for (auto& elem : elems)
  {
    std::cout << elem->file_name << "   ";
  }

    std::cout << std::endl;
}

command command_handler(std::string x)
{

    if(x=="cd")
      return command::cd;
    if(x=="ls")
      return command::ls;
    if(x=="pwd")
      return command::pwd;
    if(x=="mkdir")
      return command::mkdir;
    if(x=="rm")
      return command::rm;
    if(x=="mv")
      return command::mv;
    if(x=="nano")
      return command::nano;
    if(x=="rmdir")
      return command::rmdir;
    if(x=="quit")
      return command::quit;
    if(x=="help")
      return command::help;
    return command::null;
}

void directory::mkdir(std::string name)
{

  std::unique_ptr<directory> new_dir = std::make_unique<directory>();

  // Set the directory name
  new_dir->directory_name = name;
  new_dir->parent=this;
  new_dir->directory_path=directory_path+"/"+name;
  // Move the pointer into the subdirectory list
  subdire.push_back(std::move(new_dir));
}

void directory::pwd()
{
  std::cout<<directory_path<<std::endl;
}

void directory::rmdir(std::string name)
{
    for (auto it = subdire.begin(); it != subdire.end(); ++it)
    {
        if ((*it)->directory_name == name)
        {
            it->reset();           
            subdire.erase(it); 
            return;
        }
    }
    std::cout << "Directory not found!" << std::endl;
}

void directory::rm(std::string name)
{
    for (auto it = elems.begin(); it != elems.end(); ++it)
    {
        if ((*it)->file_name == name)
        {
            it->reset();             // optional: clear the unique_ptr
            elems.erase(it);       // erase the element at iterator it
            return;
        }
    }
    std::cout << "File not found! Need help? type help" << std::endl;
}

void directory::nano(std::string name)
{
    File* temp = nullptr;
    bool found = false;

    // Search for existing file
    for (auto& file : elems)
    {
        if (file->file_name == name)
        {
            temp = file.get(); 
            found = true;
            break;
        }
    }

  
    if (!found)
    {
        elems.push_back(std::make_unique<File>(name));
        temp = elems.back().get();
    }

    std::cout << "Enter file contents (end with a single line containing only \"EOF\"):\n";
    std::string line;
    std::string content;
    while (std::getline(std::cin, line))
    {
        if (line == "EOF") break;
        content += line + "\n";
    }

    temp->content = content;
}

void directory::move(std::string name, std::string dest)
{
  std::vector<std::string> path;
  std::unique_ptr<File>* temp_F = nullptr;
  std::unique_ptr<directory>* temp_D = nullptr;
  directory* path_D = &root;

  std::stringstream ss(dest);
  std::string temp, token;

  while (std::getline(ss, token, '/')) {
    path.push_back(token);
  }

  // Find File or directory by name
  for (auto &file : elems)
  {
    if (file->file_name == name)
    {
      temp_F = &file;
      break;
    }
  }

  for (auto &subd : subdire)
  {
    if (subd->directory_name == name)
    {
      temp_D = &subd;
      break;
    }
  }

  // Traverse path
  for (const auto& part : path)
  {
    bool found = false;
    for (auto& subd : path_D->subdire)
    {
      if (subd->directory_name == part)
      {
        path_D = subd.get();
        found = true;
        break;
      }
    }
    if (!found)
    {
      std::cout << "Invalid path: " << part << std::endl;
      return;
    }
  }

  // Move file or directory
  if (temp_F)
  {
    path_D->elems.push_back(std::move(*temp_F));
    elems.erase(std::remove_if(elems.begin(), elems.end(),
      [&](const std::unique_ptr<File>& f) { return f.get() == temp_F->get(); }),
      elems.end());
  }
  else if (temp_D)
  {
    path_D->subdire.push_back(std::move(*temp_D));
    subdire.erase(std::remove_if(subdire.begin(), subdire.end(),
      [&](const std::unique_ptr<directory>& d) { return d.get() == temp_D->get(); }),
      subdire.end());
  }
  else
  {
    std::cout << "File or directory not found! Need help? type help" << std::endl;
  }
}

void helpp()
{
  std::cout<<"Available functions and parameters"<<std::endl;
  std::cout<<"\ncd: cd <subdirectory or ../>\n\nls: ls for normal listing or ls -l for details\n\npwd: pwd for displaying current directory's path\n\nmkdir: mkdir <name> to make a new directory\n\nrm: rm <filename> to remove a file\n\nmv: mv <path from the root> to move a file or directory\nEx:Move main.cpp from Root/User/Downloads to Root/User/Docs mv main.cpp User/Docs\n\nnano: nano <filename> to create or edit a file\n\nrmdir: rmdir <directoryname> to remove a directory\n\nexit: exit to stop running this program\n\n";
  return;
}
