#include <iostream>
using namespace std;

struct Canciones {
    int ID;
    string titulo;
    int duracion;
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
    string titulo;
    int anno;
    int N_canciones;
};

struct Playlist {
    int ID;
    string nombre;
    string creador;
    string fecha;
};

struct Generos_Musicales
