#ifndef ASSET_H
#define ASSET_H

#pragma once

#include <bgfx/bgfx.h>
#include <fstream>
#include <sstream>
#include "../../../Libraries/cpplocate/source/cpplocate/include/cpplocate/cpplocate.h"

template <typename AssetObj>
class Asset{
public:
    Asset(){	
        
    }

    ~Asset(){
        
    };

    void create(){}

    std::string get_file_contents(std::string path){
        std::ifstream file(path);
        std::stringstream data;
        data << file.rdbuf();
        return data.str();
    }

    std::string get_asset_path(std::string path){
	    return cpplocate::getModulePath() + path;
    }
};

#endif