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
//intento de commit

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

void insertarCancion(int id,string t,int d,int id_al,int id_ar){
    Canciones * nc = new Canciones (id,t,d,id_al,id_ar);

    nc -> sig = primeroC;
    primeroC = nc;
}
void insertarcancionalbum(Canciones*& cabeza, int id, string titulo, int duracion, int id_album, int id_artista) {
    Canciones* nueva = new Canciones(id, titulo, duracion, id_album, id_artista);
    
    if (!cabeza) {
        cabeza = nueva;
    } else {
        Canciones* actual = cabeza;
        while (actual->sig) {
            actual = actual->sig;
        }
        actual->sig = nueva;
    }
}