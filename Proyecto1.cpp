#include <iostream>
using namespace std;

struct Canciones {
    int ID;
    string Titulo;
    int Duracion;
    int ID_Album;
    int ID_Artista;
};

struct Artistas {
    int ID;
    string Nombre_Artistico;
    string Nombre_Real;
    string Pais;
    string Sello_Discografico;
};

struct Albumes {
    int ID;
    string Titulo;
    int Anno;
    int N_canciones;
};

struct Playlist {
    int ID;
    string Nombre;
    string Creador;
    string Fecha;
};

struct Generos_Musicales {
    int ID;
    string Nombre;
    string Descripcion;
};

struct Sellos_Discograficos {
    int ID;
    string Nombre;
    string Pais;
    int Anno_fundacion;
};
