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


struct Sublista_Canciones{
    Canciones * cancion;
    Sublista_Canciones * sig;

    Sublista_Canciones(Canciones * c){
        cancion = c;
        sig = nullptr;
    }
};

//Lista simple Ins al final
struct Albumes {
    int ID;
    string Titulo;
    int Anno;
    int N_canciones;

    Albumes * sig;

    Sublista_Canciones * canciones;

    Albumes(int id, string titulo, int anno) {
        ID = id;
        Titulo = titulo;
        Anno = anno;
        N_canciones = 0;

        sig = nullptr;
        canciones = nullptr;
    }

}*primeroAlb;


struct Sublista_Albumes{
    Albumes * album;
    Sublista_Albumes * sig;

    Sublista_Albumes(Albumes * a){
        album = a;
        sig = nullptr;
    }
};


//Lista doble ordenada alfabeticamente
struct Artistas {
    int ID;
    string Nombre_Artistico;
    string Nombre_Real;
    string Pais;
    string Sello_Discografico;

    Artistas * sig;
    Artistas * ant;

    Sublista_Albumes * albumes;
    Sublista_Canciones * canciones;

    Artistas(int id,string nombre_artistico, string nombre_real, string pais, string sello_discografico){
        ID = id;
        Nombre_Artistico = nombre_artistico;
        Nombre_Real = nombre_real;
        Pais = pais;
        Sello_Discografico = sello_discografico;

        sig = nullptr;
        ant = nullptr;

        albumes = nullptr;
        canciones = nullptr;
    }

}*primeroArt;


struct Sublista_Artistas{
    Artistas * artista;
    Sublista_Artistas * sig;

    Sublista_Artistas(Artistas * a){
        artista = a;
        sig = nullptr;
    }
};

//Lista circular Ins al final
struct Generos_Musicales {
    int ID;
    string Nombre;
    string Descripcion;

    Generos_Musicales * sig;

    Sublista_Canciones * canciones;

    Generos_Musicales(int id, string nombre, string descripcion){
        ID = id;
        Nombre = nombre;
        Descripcion = descripcion;

        sig = nullptr;
        canciones = nullptr;
    }

}*primeroG;

//Lista simple Ins al inicio
struct Playlist {
    int ID;
    string Nombre;
    string Creador;
    string Fecha;

    Playlist * sig;

    Sublista_Canciones * canciones;

    Playlist(int id, string nombre, string creador,string fecha){
        ID = id;
        Nombre = nombre;
        Creador = creador;
        Fecha = fecha;

        sig = nullptr;
        canciones = nullptr;
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

    Sublista_Artistas * artistas;

    Sellos_Discograficos(int _ID, string _Nombre, string _Pais, int _Anno_fundacion) {
        ID = _ID;
        Nombre = _Nombre;
        Pais = _Pais;
        Anno_fundacion = _Anno_fundacion;
        sig = ant = nullptr;
        artistas = nullptr;
    }
} *primeroSD = nullptr;


//Funciones de Cancion
void insertarCancion(int id,string titulo,int duracion,int id_album,int id_artista){
    Canciones * nc = new Canciones (id, titulo, duracion, id_album, id_artista);
    nc -> sig = primeroC;
    primeroC = nc;
}

Canciones * buscarCancion(string titulo){
    Canciones * temp = primeroC;
    while (temp != nullptr){
        if (temp -> Titulo == titulo){
            return temp;
        }
        temp = temp -> sig;
    }
    return nullptr;
}

//Modificaciones
void modificarIDCancion(string titulo, int id){
    Canciones * cancion = buscarCancion(titulo);
    if (cancion == nullptr){
        cout << "Cancion no encontrada " << endl;
    }
    else{
        cout << "ID de Cancion modificado " << endl;
        cancion -> ID = id;
    }
}

void modificarTituloCancion(string tituloOG, string tituloNV){
    Canciones * cancion = buscarCancion(tituloOG);
    if (cancion == nullptr){
        cout << "Cancion no encontrada " << endl;
    }
    else{
        cout << "Titulo de Cancion modificado " << endl;
        cancion -> Titulo = tituloNV;
    }
}

void modificarDuracionCancion(string titulo, int duracion){
    Canciones * cancion = buscarCancion(titulo);
    if (cancion == nullptr){
        cout << "Cancion no encontrada " << endl;
    }
    else{
        cout << "Duracion de Cancion modificada " << endl;
        cancion -> Duracion = duracion;
    }
}

void modificarIDAlbumCancion(string titulo, int ID_Alb){
    Canciones * cancion = buscarCancion(titulo);
    if (cancion == nullptr){
        cout << "Cancion no encontrada " << endl;
    }
    else{
        cout << "ID de Album de Cancion modificado " << endl;
        cancion -> ID_Album = ID_Alb;
    }
}

void modificarIDArtistaCancion(string titulo, int ID_Art){
    Canciones * cancion = buscarCancion(titulo);
    if (cancion == nullptr){
        cout << "Cancion no encontrada " << endl;
    }
    else{
        cout << "ID de Artista de Cancion modificado " << endl;
        cancion -> ID_Artista = ID_Art;
    }
}

void eliminarCancion(string titulo){
    Canciones * temp = primeroC;
    Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> Titulo == titulo){
            tempAnt -> sig = temp -> sig;
            cout << "Cancion eliminada " << endl;
            delete temp;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Cancion no encontrada " << endl;
}


//Funciones de Album
void insertarAlbum(int id, string titulo, int anno) {
    Albumes* nueva = new Albumes(id, titulo, anno);

    if (primeroAlb == nullptr) {
        primeroAlb = nueva;
    } else {
        Albumes* actual = primeroAlb;
        while (actual->sig) {
            actual = actual->sig;
        }
        actual->sig = nueva;
    }
}


Albumes * buscarAlbum (string titulo){
    Albumes * temp = primeroAlb;
    while (temp != nullptr){
        if (temp -> Titulo == titulo){
            return temp;
        }
        temp = temp -> sig;
    }
    return nullptr;
}

//Modificaciones
void modificarIDAlbum(string titulo, int id){
    Albumes * album = buscarAlbum(titulo);
    if (album == nullptr){
        cout << "Album no encontrado " << endl;
    }
    else{
        cout << "ID de Album modificado " << endl;
        album -> ID = id;
    }
}

void modificarTituloAlbum(string tituloOG, string tituloNV){
    Albumes * album = buscarAlbum(tituloOG);
    if (album == nullptr){
        cout << "Album no encontrado " << endl;
    }
    else{
        cout << "Titulo de Album modificado " << endl;
        album -> Titulo = tituloNV;
    }
}

void modificarAnnoAlbum(string titulo, int anno){
    Albumes * album = buscarAlbum(titulo);
    if (album == nullptr){
        cout << "Album no encontrado " << endl;
    }
    else{
        cout << "Año de Album modificado " << endl;
        album -> Anno = anno;
    }
}

void modificarNCancionesAlbum(string titulo,int n){
    Albumes * album = buscarAlbum(titulo);
    if (album == nullptr){
        cout << "Album no encontrado " << endl;
    }
    else{
        cout << "Numero de canciones de Album modificado " << endl;
        album -> N_canciones = n;
    }
}

void eliminarAlbum(string titulo){
    Albumes * temp = primeroAlb;
    Albumes * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> Titulo == titulo){
            tempAnt -> sig = temp -> sig;
            cout << "Album eliminado " << endl;
            delete temp;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Album no encontrado " << endl;
}

//Considerar cambiar esto a que cuando se inserte sea por la duracion de la cancion de alto a menos para ahorrarnos trabajo a la hora de imprimir (Ver requisitos de reportes)
void insertarCancionAlbum(string tituloAlb, string tituloC){
    Albumes * album = buscarAlbum(tituloAlb);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || album == nullptr){
        cout << "Album o cancion no encontrada " << endl;
    } 
    else{
        Sublista_Canciones * nSub = new Sublista_Canciones(cancion);
        if (album -> canciones == nullptr){
            album -> canciones = nSub;
        }
        else{
            Sublista_Canciones * temp = album -> canciones;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }  
    }
}

void eliminarCancionAlbumAux(Albumes * album, Canciones * cancion){
    Sublista_Canciones * temp = album -> canciones;
    Sublista_Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> cancion == cancion){
            tempAnt -> sig = temp -> sig;
            cout << "Cancion eliminada de album" << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Cancion no existe o no esta en el Album seleccionado " << endl;
}

void eliminarCancionAlbum(string tituloAlb, string tituloC){
    Albumes * album = buscarAlbum(tituloAlb);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || album == nullptr){
        cout << "Album o cancion no encontrada " << endl;
    }
    else{
        if (album -> canciones -> cancion -> Titulo == tituloC){
            album -> canciones = album -> canciones -> sig;
            cout << "Cancion eliminada de album" << endl;
        }
        else{
            eliminarCancionAlbumAux(album,cancion);
        }
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

Artistas * buscarArtista (string nombre_artistico){
    Artistas * temp = primeroArt;
    while (temp != nullptr){
        if (temp -> Nombre_Artistico == nombre_artistico){
            return temp;
        }
        temp = temp -> sig;
    }
    return nullptr;
}

//Modificaciones
void modificarIDArtista(string nombre_artistico, int id){
    Artistas * artista = buscarArtista(nombre_artistico);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "ID de Artista modificado " << endl;
        artista -> ID = id;
    }
}

void modificarNArtisticoArtista(string nombre_artisticoOG, string nombre_artisticoNV){
    Artistas * artista = buscarArtista(nombre_artisticoOG);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "Nombre Artistico de Artista modificado " << endl;
        artista -> Nombre_Artistico = nombre_artisticoNV;
    }
}

void modificarNRealArtista(string nombre_artistico, string nombre_real){
    Artistas * artista = buscarArtista(nombre_artistico);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "Nombre Real de Artista modificado " << endl;
        artista -> Nombre_Real = nombre_real;
    }
}

void modificarPaisArtista(string nombre_artistico, string pais){
    Artistas * artista = buscarArtista(nombre_artistico);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "Pais de Artista modificado " << endl;
        artista -> Pais = pais;
    }
}

void modificarSDiscograficoArtista(string nombre_artistico, string sello_discografico){
    Artistas * artista = buscarArtista(nombre_artistico);
    if (artista == nullptr){
        cout << "Artista no encontrado " << endl;
    }
    else{
        cout << "Sello Discografico de Artista modificado " << endl;
        artista -> Sello_Discografico = sello_discografico;
    }
}

void insertarCancionArtista(string tituloArt, string tituloC){
    Artistas * artista = buscarArtista(tituloArt);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || artista == nullptr){
        cout << "Artista o album no encontrado " << endl;
    }
    else{
        Sublista_Canciones * nSub = new Sublista_Canciones(cancion);
        if (artista -> canciones == nullptr){
            artista -> canciones = nSub;
        }
        else{
            Sublista_Canciones * temp = artista -> canciones;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}

void eliminarArtistas(){
    
}

void eliminarCancionArtistaAux(Artistas * artista, Canciones * cancion){
    Sublista_Canciones * temp = artista -> canciones;
    Sublista_Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> cancion == cancion){
            tempAnt -> sig = temp -> sig;
            cout << "Cancion eliminada de artista " << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
}

void eliminarCancionArtista(string tituloArt, string tituloC){
    Artistas * artista = buscarArtista(tituloArt);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || artista == nullptr){
        cout << "Artista o album no encontrado " << endl;
    }
    else{
        if (artista -> canciones -> cancion -> Titulo == tituloC){
            artista -> canciones = artista -> canciones -> sig;
            cout << "Cancion eliminada de artista " << endl;
        }
        else{
            eliminarCancionArtistaAux(artista,cancion);
        }
    }
}

void insertarAlbumArtista(string tituloArt, string tituloAlb){

}

void eliminarAlbumArtista(string tituloArt, string tituloAlb){

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

Generos_Musicales * buscarGeneroMusical (string nombre){
    if (primeroG == nullptr){
        return nullptr;
    }
    Generos_Musicales * temp = primeroG;
    do {
        if (temp -> Nombre == nombre){
            return temp;
        }
        temp = temp -> sig;
    }
    while (temp != primeroG);
    return nullptr;
    
}

//Modificaciones
void modificarIDGeneroMusical(string nombre, int id){
    Generos_Musicales * genero_musical = buscarGeneroMusical(nombre);
    if (genero_musical == nullptr){
        cout << "Genero Musical no encontrado " << endl;
    }
    else{
        cout << "ID de Genero Musical modificado " << endl;
        genero_musical -> ID = id;
    }
}

void modificarIDGeneroMusical(string nombreOG, string nombreNV){
    Generos_Musicales * genero_musical = buscarGeneroMusical(nombreOG);
    if (genero_musical == nullptr){
        cout << "Genero Musical no encontrado " << endl;
    }
    else{
        cout << "Nombre de Genero Musical modificado " << endl;
        genero_musical -> Nombre = nombreNV;
    }
}

void modificarIDGeneroMusical(string nombre, string descripcion){
    Generos_Musicales * genero_musical = buscarGeneroMusical(nombre);
    if (genero_musical == nullptr){
        cout << "Genero Musical no encontrado " << endl;
    }
    else{
        cout << "ID de Genero Musical modificado " << endl;
        genero_musical -> Descripcion = descripcion;
    }
}

//Funciones de Playlists 
void insertarPlaylist(int id, string nombre, string creador,string fecha){
    Playlist * np = new Playlist(id,nombre,creador,fecha);
    np -> sig = primeroP;
    primeroP = np;
}

Playlist * buscarPlaylist (string nombre){
    Playlist * temp = primeroP;
    while (temp != nullptr){
        if (temp -> Nombre == nombre){
            return temp;
        }
        temp = temp -> sig;
    }
    return nullptr;
}

//Modificaciones
void modificarIDPlaylist(string nombre, int id){
    Playlist * playlist = buscarPlaylist(nombre);
    if (playlist == nullptr){
        cout << "Playlist no encontrado " << endl;
    }
    else{
        cout << "ID de Playlist modificado " << endl;
        playlist -> ID = id;
    }
}

void modificarNombrePlaylist(string nombreOG, string nombreNV){
    Playlist * playlist = buscarPlaylist(nombreOG);
    if (playlist == nullptr){
        cout << "Playlist no encontrado " << endl;
    }
    else{
        cout << "Nombre de Playlist modificado " << endl;
        playlist -> Nombre = nombreNV;
    }
}

void modificarCreadorPlaylist(string nombre, string creador){
    Playlist * playlist = buscarPlaylist(nombre);
    if (playlist == nullptr){
        cout << "Playlist no encontrado " << endl;
    }
    else{
        cout << "Creador de Playlist modificado " << endl;
        playlist -> Creador = creador;
    }
}

void modificarFechaPlaylist(string nombre, string fecha){
    Playlist * playlist = buscarPlaylist(nombre);
    if (playlist == nullptr){
        cout << "Playlist no encontrado " << endl;
    }
    else{
        cout << "Fecha de Playlist modificada " << endl;
        playlist -> Fecha = fecha;
    }
}


//Funciones de Sellos Discograficos
void insertarSellosDiscograficos(int id, string nombre, string pais, int anno_de_fundacion) {
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

Sellos_Discograficos * buscarSellosDiscograficos (string nombre){
    if (primeroSD == nullptr){
        return nullptr;
    }
    Sellos_Discograficos * temp = primeroSD;
    do {
        if (temp -> Nombre == nombre){
            return temp;
        }
        temp = temp -> sig;
    }
    while (temp != primeroSD);
    return nullptr;
}

//Modificaciones
void modificarIDSelloDiscografico (string nombre, int id){
    Sellos_Discograficos * sello_discografico = buscarSellosDiscograficos(nombre);
    if (sello_discografico == nullptr){
        cout << "Sello Discografico no encontrado " << endl;
    }
    else{
        cout << "ID de Sello Discografico modificado " << endl;
        sello_discografico -> ID = id;
    }
}

void modificarNombreSelloDiscografico (string nombreOG, string nombreNV){
    Sellos_Discograficos * sello_discografico = buscarSellosDiscograficos(nombreOG);
    if (sello_discografico == nullptr){
        cout << "Sello Discografico no encontrado " << endl;
    }
    else{
        cout << "Nombre de Sello Discografico modificado " << endl;
        sello_discografico -> Nombre = nombreNV;
    }
}

void modificarPaisSelloDiscografico (string nombre, string pais){
    Sellos_Discograficos * sello_discografico = buscarSellosDiscograficos(nombre);
    if (sello_discografico == nullptr){
        cout << "Sello Discografico no encontrado " << endl;
    }
    else{
        cout << "Pais de Sello Discografico modificado " << endl;
        sello_discografico -> Pais = pais;
    }
}

void modificarAnnoFundacionSelloDiscografico (string nombre, int anno_fundacion){
    Sellos_Discograficos * sello_discografico = buscarSellosDiscograficos(nombre);
    if (sello_discografico == nullptr){
        cout << "Sello Discografico no encontrado " << endl;
    }
    else{
        cout << "Año de fundacion de Sello Discografico modificado " << endl;
        sello_discografico -> Anno_fundacion = anno_fundacion;
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
