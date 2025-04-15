#include <iostream>
using namespace std;

//Lista simple Ins al inicio
struct Canciones {
    int ID;
    string Titulo;
    int Duracion;
    int ID_Album;
    int ID_Artista;

    Canciones * sig;

}*primeroC;

//Lista doble ordenada alfabeticamente
struct Artistas {
    int ID;
    string Nombre_Artistico;
    string Nombre_Real;
    string Pais;
    string Sello_Discografico;

    Artistas * sig;
    Artistas * ant;

}*primeroArt;

//Lista simple Ins al final
struct Albumes {
    int ID;
    string Titulo;
    int Anno;
    int N_canciones;

    Albumes * sig;

}*primeroAlb;

//Lista circular Ins al final
struct Generos_Musicales {
    int ID;
    string Nombre;
    string Descripcion;

    Generos_Musicales * sig;

}*primeroG;

//Lista simple Ins al inicio
struct Playlist {
    int ID;
    string Nombre;
    string Creador;
    string Fecha;

    Playlist * sig;

}*primeroP;


//Lista doble y circular ins al final
struct Sellos_Discograficos {
    int ID;
    string Nombre;
    string Pais;
    int Anno_fundacion;

    Sellos_Discograficos * sig;
    Sellos_Discograficos * ant;

}*primeroSD;
