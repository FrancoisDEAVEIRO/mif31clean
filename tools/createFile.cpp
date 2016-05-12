#include "../include/createFile.hpp"


void CreateFilePointRandom(int N, int max, int nbPoints){
    std::ofstream objetfichier;
    srand(time(NULL));
    objetfichier.open("data/pointRandom2D.txt", std::ios::out); //on ouvrre le fichier en ecriture
    if (objetfichier.bad()) //permet de tester si le fichier s'est ouvert sans probleme
        return;

    // Remplissage fichier
	for(int i=0; i<nbPoints; i++){
        for(int j=0; j<N; j++){
            objetfichier << rand()%max << ";" ;
        }
        objetfichier <<  std::endl;
	}
    objetfichier.close(); //on ferme le fichier pour liberer la mémoire
}
