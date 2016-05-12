#ifndef READER_HPP
#define READER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "point.hpp"

template <typename T, int N>
std::vector<Point<T,N> > lecture(const char* file){
    std::ifstream fichier(file);
    std::vector<Point<T,N> > nuageDePoint;
    if(fichier){
        //L'ouverture s'est bien passée, on peut donc lire
        std::string ligne;
        std::string delimiter = ";";
        size_t pos = 0;
        std::string token;
        int id = 0;
        while(getline(fichier, ligne)){ //Tant qu'on n'est pas à la fin, on lit
            std::vector<T> v;
            while ((pos = ligne.find(delimiter)) != std::string::npos) {
                token = ligne.substr(0, pos);
                v.push_back(std::stoi(token));
                ligne.erase(0, pos + delimiter.length());
            }
            Point<T,N> p(v);
            p.id = id;
            nuageDePoint.push_back(p);
            id++;
        }
   }else{
      std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
   }
   return nuageDePoint;
}


#endif // READER_HPP
