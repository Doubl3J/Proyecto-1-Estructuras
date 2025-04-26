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

//Lista simple Ins al final
struct Albumes {
    int ID;
    string Titulo;
    int Anno;
    int N_canciones;

    Albumes * sig;

    Canciones * cancion;

    Albumes(int id, string titulo, int anno) {
        ID = id;
        Titulo = titulo;
        Anno = anno;
        N_canciones = 0;

        sig = nullptr;
        cancion = nullptr;
    }

}*primeroAlb;

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
    Canciones * canciones;

    Artistas(int id,string nombre_artistico, string nombre_real, string pais, string sello_discografico){
        ID = id;
        Nombre_Artistico = nombre_artistico;
        Nombre_Real = nombre_real;
        Pais = pais;
        Sello_Discografico = sello_discografico;

        sig = nullptr;
        ant = nullptr;

        album = nullptr;
        canciones = nullptr;
    }

}*primeroArt;



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
        cancion = nullptr;
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

    Playlist(int id, string nombre, string creador,string fecha){
        ID = id;
        Nombre = nombre;
        Creador = creador;
        Fecha = fecha;

        sig = nullptr;
        cancion = nullptr;
    }

}*primeroP;


//Lista doble y circular ins al final
struct Sellos_Discograficos {
    int ID;
    string Nombre;
    string Pais;
    int Anno_fundacion;

    Sellos_Discograficos* sig;
    Sellos_Discograficos* ant;

    Artistas* artist;

    Sellos_Discograficos(int _ID, string _Nombre, string _Pais, int _Anno_fundacion) {
        ID = _ID;
        Nombre = _Nombre;
        Pais = _Pais;
        Anno_fundacion = _Anno_fundacion;
        sig = ant = nullptr;
        artist = nullptr;
    }
} *primeroSD = nullptr;


//Funciones de Cancion
void insertarCancion(int id,string titulo,int duracion,int id_album,int id_artista){
    Canciones * nc = new Canciones (id, titulo, duracion, id_album, id_artista);
    nc -> sig = primeroC;
    primeroC = nc;
}


//Funciones de Album
void insertarAlbum(int id, string titulo, int anno) {
    Albumes* nueva = new Albumes(id, titulo, anno);

    if (primeroAlb==nullptr) {
        primeroAlb = nueva;
    } else {
        Albumes* actual = primeroAlb;
        while (actual->sig) {
            actual = actual->sig;
        }
        actual->sig = nueva;
    }
}

//Funciones de Artistas
void insertarArtistas (int id, string nombre_artistico, string nombre_real, string pais, string sello_discografico){
    Artistas * nuevoA = new Artistas (id, nombre_artistico, nombre_real, pais, sello_discografico);
    if (primeroArt == nullptr){
        primeroArt = nuevoA;
    }
    else{
        Artistas * temp = primeroArt;
        Artistas * tempAnt = nullptr;
        
        //mientras que nuevoA vaya siguiente alfabeticamente que temp
        while (temp != nullptr && nuevoA -> Nombre_Artistico > temp -> Nombre_Artistico ){
            tempAnt = temp;
            temp = temp -> sig;
        }
        //nuevoA va antes alfabeticamente que el primer nodo
        if (temp == primeroArt){
            temp -> ant = nuevoA;
            nuevoA -> sig = temp;
            primeroArt = nuevoA;
        }
        //nuevoA esta en el medio
        else if(tempAnt != nullptr && temp != nullptr){
            tempAnt -> sig = nuevoA;
            nuevoA -> ant = tempAnt;
            nuevoA -> sig = temp;
            temp -> ant = nuevoA;
        }
        //nuevoA esta en el final y por lo tanto temp es nullptr
        else{
            tempAnt -> sig = nuevoA;
            nuevoA -> ant = tempAnt;
        }
    }
}

void imprimirArtistas(){

    Artistas * temp = primeroArt;

    while (temp != nullptr){
        cout << "---------------------------------" << endl;
        cout << "Nombre Artistico: " << temp -> Nombre_Artistico << endl;
        cout << "Nombre Real: " << temp -> Nombre_Real << endl;
        cout << "Pais: " << temp -> Pais << endl;
        cout << "Sello Discografico: " <<temp -> Sello_Discografico << endl;

        temp = temp -> sig;
    }

}

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
void insertarPlaylist(int id, string nombre, string creador,string fecha){
    Playlist * np = new Playlist(id,nombre,creador,fecha);
    np -> sig = primeroP;
    primeroP = np;
}


//Funciones de Sellos Discograficos
void insertarsellosdiscograficos(int id, string nombre, string pais, int anno_de_fundacion) {
    Sellos_Discograficos* NSD = new Sellos_Discograficos(id, nombre, pais, anno_de_fundacion);

    if (primeroSD == nullptr) {
        primeroSD = NSD;
        primeroSD->sig = primeroSD;
        primeroSD->ant = primeroSD;
    } else {
        Sellos_Discograficos* ultimo = primeroSD->ant;
        ultimo->sig = NSD;
        NSD->ant = ultimo;
        NSD->sig = primeroSD;
        primeroSD->ant = NSD;
    }
}



int main (){


    //Test cases
    insertarArtistas(456,"Yoasobi","Lilas","Japan","SonyJP");
    insertarArtistas(123,"Clairo","Claire","USA","IDK");
    insertarArtistas(789,"Gunna","Sergio","USA","AtlanticRecords");
    insertarArtistas(303,"Men I Trust","Men I Trust","Canada","Independent");
    insertarArtistas(101,"Beabadoobee","Beatrice Kristi Laus","Philippines","DirtyHit");
    insertarArtistas(505,"J. Cole","Jermaine Cole","USA","DreamvilleRecords");
    insertarArtistas(808,"Future","Nayvadius DeMun Wilburn","USA","EpicRecords");

    imprimirArtistas();

    return 0;
}
