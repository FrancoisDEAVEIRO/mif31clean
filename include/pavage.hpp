#ifndef PAVAGE_HPP
#define PAVAGE_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include "point.hpp"
#include "simplexe.hpp"
#include <Grapic.h>

using namespace grapic;

template <typename T, int N> class Pavage;

template <class T,int N>
std::ostream & operator << (std::ostream & os, Simplexe<T,N>&);

template <typename T, int N> class Pavage{
	public :
	    Pavage();
	    void init(int winSize);
        virtual ~Pavage();
 		std::vector<Simplexe<T,N> > tab;
        Pavage<T, N>(std::vector<Point<T,N> >, int winSize);
        void ajout(const Simplexe<T,N>);
        void affiche();
        void addPoint(Point<T,N>&);
        void addPointSimplexe(Point<T,N>& p, Simplexe<T,N>& s,const typename std::vector<Simplexe<T,N> >::iterator it);
        void drawPavage(int dimW, int infoSize);
        void displayInfo(std::string texte1,std::string texte2,std::string texte3, int dimW, int infoSize);
        float distancePoint(Point<T,N> p1,Point<T,N> p2);
        bool existeDeja(Point<T,N>& p);
        bool estOppose(Point<T,N> p1, Point<T,N> p2);
        void dec2bin(int a, std::vector<int>&, int dim);
};

template<typename T, int N>
Pavage<T,N>::Pavage(){

}

template<typename T, int N>
Pavage<T, N>::~Pavage(){
    //destructeur
}

// Renvoie un tableau de int sous forme d'un binaire
template<typename T, int N>
void Pavage<T, N>::dec2bin(int a, std::vector<int>& tab, int dim) {
    if(a!=0 || dim!=0){
        dec2bin(a/2,tab, dim-1);
        tab.push_back(a%2);
    }
}


template <typename T, int N>
void Pavage<T, N>::init(int winSize){
    //Création du pavage
    // On englobe l'ensemble par 2 simplexes
    // On sait que pour une dimension N, in faut N² points pour l'englober
    // Cela revient à utiliser un binaire avec 0->0 et 1 -> winSize
    std::vector<Point<T,N> > nuageDePoints;
    // Chaque point
    for(int i=0; i<pow(2,N); i++){
        Point<T,N> p;
        std::vector<int> tab;
        dec2bin(i,tab,N);
        for(unsigned int j=0; j<tab.size(); j++){
            if(tab[j]==0)
                p.ajout(0);
            else
                p.ajout(winSize);
        }
        nuageDePoints.push_back(p);
    }
    // On ajoute ensuite N+1 points qui composeront le N-simplexe qui englobera avec les autres N-simplexes l'espace
    // Pour ce faire j'utilise le méthode suivantes : On prend 2 points diamètralement opposés P1 et P2 avec xp1 != xp2, yp1 != yp2 , ...
    // On peut donc prendre la 1ère et la dernière valeur puisque leur équivalent binaire est 00000... et 11111...
    // On forme ensuite le simplexe en ajoutant N-1 points n'étant pas diamètralement opposés
    Point<T,N> p1 = nuageDePoints[0];
    Point<T,N> p2 = nuageDePoints[nuageDePoints.size()-1];
    Simplexe<T,N> s;
    s.ajout(p1);
    s.ajout(p2);
    //Gestion du cas de N=1 où on ne rentre même pas dans la boucle
    if(N==1){
        ajout(s);
        return;
    }
    // Pour chaque autres points
    for(unsigned int i=1; i<nuageDePoints.size()-1; i++){
        // On init le simplexe avec les 2 points opposés
        Simplexe<T,N> tmp = s;
        tmp.ajout(nuageDePoints[i]);
        int pointsAjoutes = 0;
        // j est le prochain point testé en fonction de i
        unsigned int j = i+1;
        while(pointsAjoutes < N-2){
            if(pointsAjoutes < N-2){
                if( i!= j){
                    if(!estOppose(nuageDePoints[i], nuageDePoints[j])){
                        tmp.ajout(nuageDePoints[j]);
                        pointsAjoutes++;
                    }
                }
            }else{
                break;
            }
            j++;
            // Si on est arrivé au dernier point, on revient au deuxieme
            if(j==nuageDePoints.size())
                j = 2;
        }
        ajout(tmp);
    }
}

template <typename T, int N>
bool Pavage<T, N>::estOppose(Point<T,N> p1, Point<T,N> p2){
    for(int i=0; i<N; i++){
        if(p1[i] == p2[i])
            return false;
    }
    return true;
}


template <typename T, int N>
Pavage<T, N>::Pavage(std::vector<Point<T,N> > nuageDePoints, int winSize){
    init(winSize);
    for(typename std::vector<Point<T,N> >::iterator i = nuageDePoints.begin(); i != nuageDePoints.end();i++){
        color(255, 255, 255);
        point((*i)[0],(*i)[1]);
        //print((*i)[0],(*i)[1],(*i).id);
        addPoint(*i);
    }
}

template <typename T, int N>
void Pavage<T, N>::addPoint(Point<T,N>& p){
    // On vérifie que oe point n'existe pas déjà (sinon conflit de simplexe)
    if(existeDeja(p))
        return;
    for(typename std::vector<Simplexe<T,N> >::iterator i = tab.begin(); i != tab.end(); i++){
        Simplexe<T,N> tmp = (*i);
        std::vector<Simplexe<T,N> > tmp2;

        if(tmp.appartient(p)){
            // On split le simplexe en N+1 N-simplexes
            for(typename std::vector<Point<T,N> >::iterator j = tmp.tab.begin(); j != tmp.tab.end(); j++){
                Simplexe<T,N> s;
                s.ajout(p);
                s.ajout(*j);
                if((j+1) != tmp.tab.end()){
                    s.ajout(*(j+1));
                }else{
                    s.ajout(tmp.tab[0]);
                }

                // On retrace les sous simplexes
                Color c;
                c.r = 255;
                c.g = 255;
                c.b = 255;
                s.drawSimplexe(c);
                tmp2.push_back(s);
            }
            tab.erase(i);
            tab.insert(tab.end(),tmp2.begin(),tmp2.end());
            return;
        }
    }
}

template <typename T, int N>
bool Pavage<T, N>::existeDeja(Point<T,N>& p){
    for(typename std::vector<Simplexe<T,N> >::iterator i = tab.begin(); i != tab.end(); i++){
        for(typename std::vector<Point<T,N> >::iterator j = (*i).tab.begin(); j != (*i).tab.end(); j++){
            if((*j)==p)
                return true;
        }
    }
    return false;
}

template <typename T, int N>
void Pavage<T, N>::ajout(const Simplexe<T,N> s){
    tab.push_back(s);
}

// Affichage des groupes de simplexes
template <typename T, int N>
void Pavage<T, N>::affiche(){
    for(typename std::vector<Simplexe<T,N> >::iterator i = tab.begin(); i != tab.end();i++){
        std::cout << *i << std::endl ;
    }
}

//AFFICHAGE
template <typename T, int N>
void Pavage<T, N>::drawPavage(int dimW, int infoSize){
    if (isMousePressed(SDL_BUTTON_LEFT)){
		int x, y;
		mousePos(x, y);
        Point<T,N> p({x,y});
        for(typename std::vector<Simplexe<T,N> >::iterator i = tab.begin(); i != tab.end(); i++){
            if((*i).appartient(p)){
                Point<T,N> barycentre = (*i).barycentre();
                Color c;
                c.r = 0;
                c.g = 255;
                c.b = 0;
                (*i).drawSimplexe(c);
                (*i).hover = true;
                std::string info1 = "Coordonnées : X = "+ std::to_string(x) + ", Y = " + std::to_string(y);
                std::string info2 = "Simplexe : " + (*i).toString();
                std::string info3 = "Barycentre : " + barycentre.toString();
                displayInfo(info1, info2, info3, dimW,infoSize);
            }else{
                if((*i).hover){
                    Color c;
                    c.r = 255;
                    c.g = 255;
                    c.b = 255;
                    (*i).drawSimplexe(c);
                    (*i).hover = false;
                }
            }
        }

	}else if (isMousePressed(SDL_BUTTON_RIGHT)){
		int x, y;
		mousePos(x, y);
        Point<T,N> p({x,y});
        for(typename std::vector<Simplexe<T,N> >::iterator i = tab.begin(); i != tab.end(); i++){
            if((*i).appartient(p)){
                addPoint(p);
                Color c;
                c.r = 0;
                c.g = 0;
                c.b = 0;
                (*i).drawSimplexe(c);
                (*i).hover = true;
                //Pour éviter les erreur dues à la modification de tab
                break;
            }else{
                if((*i).hover){
                    Color c;
                    c.r = 255;
                    c.g = 255;
                    c.b = 255;
                    (*i).drawSimplexe(c);
                    (*i).hover = false;
                }
            }
        }
	}else{// MOUSE HOVER
        int x, y;
		mousePos(x, y);
        Point<T,N> p({x,y});
        for(typename std::vector<Simplexe<T,N> >::iterator i = tab.begin(); i != tab.end(); i++){
            if((*i).appartient(p)){
                if(!(*i).hover){
                    Point<T,N> barycentre = (*i).barycentre();
                    Color c;
                    c.r = 0;
                    c.g = 0;
                    c.b = 255;
                    (*i).drawSimplexe(c);
                    (*i).hover = true;
                    std::string info1 = "Coordonnées : X = "+ std::to_string(x) + ", Y = " + std::to_string(y);
                    std::string info2 = "Simplexe : " + (*i).toString();
                    std::string info3 = "Barycentre : " + barycentre.toString();
                    displayInfo(info1, info2, info3, dimW,infoSize);
                }
            }else{
                if((*i).hover){
                    Color c;
                    c.r = 255;
                    c.g = 255;
                    c.b = 255;
                    (*i).drawSimplexe(c);
                    (*i).hover = false;
                }
            }
        }
	}
}


template <typename T, int N>
void Pavage<T, N>::displayInfo(std::string texte1,std::string texte2,std::string texte3, int dimW, int infoSize){
    color(230,230,230);
    rectangleFill(0,dimW,dimW,dimW+infoSize);
    color(0,0,0);
    print(5,dimW+infoSize*3/4, texte1.c_str());
    print(5,dimW+infoSize/2, texte2.c_str());
    print(5,dimW+infoSize/4, texte3.c_str());
}

template<typename T, int N>
float Pavage<T, N>::distancePoint(Point<T,N> p1,Point<T,N> p2){
    T somme = 0;
    for(int i=0; i<N; i++){
        somme+=pow(p2[i]-p1[i],2);
    }
    return sqrt(somme);
}



#endif // PAVAGE_HPP
