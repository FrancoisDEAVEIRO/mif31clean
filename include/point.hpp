#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <vector>

template <typename T, int N> class Point;

template <typename T,int dimension>
std::ostream & operator << (std::ostream & os, Point<T,dimension> &);

template <typename T,int dimension>
std::istream & operator >> (std::istream & is, Point<T,dimension> &);

template <typename T, int N> class Point{
	public :
	    int id;
		Point();
		std::vector<T> tab;
		Point<T, N>(const int);
        Point<T, N>(const Point &);
        Point<T, N>(const std::vector<T>);
        virtual ~Point();
        Point<T, N>& operator=(const Point &);
        bool operator==(const Point<T, N> &) const;
        void ajout(const T &);
        T & operator[](int); //Acces en lecture
        const T & operator[](int) const; //Accès en écriture
        void affiche();
        std::string toString();

};

template<typename T, int N>
Point<T,N>::Point(const std::vector<T> t){
    tab = t;
    id = 0;
}

template<typename T, int N>
Point<T,N>::Point(const Point & p){
    tab = p.tab;
    id = p.id;
}

template<typename T, int N>
Point<T,N>&Point<T,N>::operator=(const Point & p){
    tab = p.tab;
    return *this;
}

template<typename T, int N>
Point<T,N>::Point(){
    id = 0;
}

template<typename T, int N>
void Point<T,N>:: ajout(const T & e){
    tab.push_back(e);
}

template<typename T, int N>
Point<T, N>::~Point(){
    //destructeur
}

template<typename T, int N>
void Point<T,N>::affiche(){
    std::cout << id << " : ";
    for(typename std::vector<T>::iterator i = tab.begin(); i != tab.end();i++)
        std::cout << *i << " ";
}

template<typename T, int N>
std::string Point<T,N>::toString(){
    std::string res = "";
    for(typename std::vector<T>::iterator i = tab.begin(); i != tab.end();i++)
        res+= std::to_string(*i) + " ";
    return res;
}

template <class T,int N>
std::ostream  & operator<< (std::ostream & os, Point<T,N> & p){
    os << p.id << " : ";
    for(typename std::vector<T>::iterator i = p.tab.begin(); i != p.tab.end();i++)
        os << *i << " ";
    return os ;
}

template <class T,int N>
T & Point<T,N>::operator[](int i){
    return tab[i];
}

template <class T,int N>
const T & Point<T,N>::operator[](int i) const{
    return tab[i];
}

template <class T,int N>
bool Point<T,N>::operator==(const Point<T, N> & p) const{
    for(unsigned int i=0; i<p.tab.size(); i++){
        if(tab[i]!=p.tab[i])
            return false;
    }
    return true;
}

#endif //POINT_HPP
