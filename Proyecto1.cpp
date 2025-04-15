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

    Canciones(int id,string t,int d,int id_al,int id_ar){
        ID = id;
        Titulo = t;
        Duracion = d;
        ID_Album = id_al;
        ID_Artista = id_ar;

        sig = nullptr;
    }

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

    Albumes * album;
    Canciones * cancion;

}*primeroArt;

//Lista simple Ins al final
struct Albumes {
    int ID;
    string Titulo;
    int Anno;
    int N_canciones;

    Albumes * sig;

    Canciones * cancion;

}*primeroAlb;


//Lista circular Ins al final
struct Generos_Musicales {
    int ID;
    string Nombre;
    string Descripcion;

    Generos_Musicales * sig;

    Canciones * cancion;

    Generos_Musicales(int id, string nombre, string descripcion){
        ID = id;
        Nombre = nombre;
        Descripcion = descripcion;

        sig = nullptr;
    }

}*primeroG;

//Lista simple Ins al inicio
struct Playlist {
    int ID;
    string Nombre;
    string Creador;
    string Fecha;

    Playlist * sig;

    Canciones * cancion;

}*primeroP;


//Lista doble y circular ins al final
struct Sellos_Discograficos {
    int ID;
    string Nombre;
    string Pais;
    int Anno_fundacion;

    Sellos_Discograficos * sig;
    Sellos_Discograficos * ant;

    Artistas * artist;

}*primeroSD;

//Funciones de Cancion
void insertarCancion(int id,string titulo,int duracion,int id_album,int id_artista){
    Canciones * nc = new Canciones (id, titulo, duracion, id_album, id_artista);
    nc -> sig = primeroC;
    primeroC = nc;
}


//Funciones de Album
void insertaralbum(Albumes*& cabeza, int id, string titulo, int anno) {
    Albumes* nueva = new Albumes(id, titulo, anno);

    if (!cabeza) {
        cabeza = nueva;
    } else {
        Albumes* actual = cabeza;
        while (actual->sig) {
            actual = actual->sig;
        }
        actual->sig = nueva;
    }
}

//Funciones de Artistas


//Funciones de Genero Musical
void insertarGeneroMusical (int id, string nombre, string descripcion){
    Generos_Musicales * ng = new Generos_Musicales(id,nombre,descripcion);

    if (primeroG == nullptr){
        primeroG = ng;
        ng -> sig = ng;
    }
    else{
        ng -> sig = primeroG;
        Generos_Musicales * temp = primeroG;
        while (temp -> sig != primeroG){
            temp = temp -> sig;
        }
        temp -> sig = ng;
    }
}

//Funciones de Playlists

//Funciones de Sellos Discograficos


