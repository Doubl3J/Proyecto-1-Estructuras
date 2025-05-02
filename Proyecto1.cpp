#include <iostream>
using namespace std;

//Para validar que el usuario use inputs correctos(integer o string dependiendo de que se pide)
#include <limits>

//Lista simple Ins al inicio
struct Canciones {
    int ID;
    string Titulo;
    int Duracion;
    int ID_Album;
    int ID_Artista;

    Canciones * sig;

    Canciones(int id,string t,int d){
        ID = id;
        Titulo = t;
        Duracion = d;
        //Estos IDs se actualizan cuando se agreguen a un album o artista
        ID_Album = 0; 
        ID_Artista = 0;

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
        //Se actualiza mientras se agregan canciones
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

    //atributos agregador para consultas
    int albumes_publicados;

    Artistas(int id,string nombre_artistico, string nombre_real, string pais){
        ID = id;
        Nombre_Artistico = nombre_artistico;
        Nombre_Real = nombre_real;
        Pais = pais;
        //Se actualiza cuando un sello discografico lo agregue como artista
        Sello_Discografico = "Independiente";

        sig = nullptr;
        ant = nullptr;

        albumes = nullptr;
        canciones = nullptr;

        albumes_publicados = 0;
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

    //atributos agregador para consultas
    int numero_canciones;

    Generos_Musicales(int id, string nombre, string descripcion){
        ID = id;
        Nombre = nombre;
        Descripcion = descripcion;

        sig = nullptr;
        canciones = nullptr;

        numero_canciones = 0;
    }

}*primeroG;

//Lista simple Ins al inicio
struct Playlist {
    int ID;
    string Nombre;
    string Creador;
    int Fecha;

    Playlist * sig;

    Sublista_Canciones * canciones;

    //atributos agregador para consultas
    int numero_canciones;

    Playlist(int id, string nombre, string creador,int fecha){
        ID = id;
        Nombre = nombre;
        Creador = creador;
        Fecha = fecha;

        sig = nullptr;
        canciones = nullptr;

        numero_canciones = 0;
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

    //atributos agregador para consultas
    int numero_artistas;


    Sellos_Discograficos(int _ID, string _Nombre, string _Pais, int _Anno_fundacion) {
        ID = _ID;
        Nombre = _Nombre;
        Pais = _Pais;
        Anno_fundacion = _Anno_fundacion;
        sig = ant = nullptr;
        artistas = nullptr;

        numero_artistas = 0;
    }
} *primeroSD = nullptr;


//Insercion y actualizacion

//Funciones de Cancion
void insertarCancion(int id,string titulo,int duracion){
    Canciones * nc = new Canciones (id, titulo, duracion);
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

//Modificacion de sublistas


void insertarCancionAlbum(string tituloAlb, string tituloC){
    Albumes * album = buscarAlbum(tituloAlb);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || album == nullptr){
        cout << "Album o cancion no encontrada " << endl;
    } 
    else{
        cancion -> ID_Album = album -> ID;
        //Se ordena de mas duracion a menos duracion
        Sublista_Canciones * nSub = new Sublista_Canciones(cancion);
        if (album -> canciones == nullptr){
            album -> canciones = nSub;
        }
        else{
            Sublista_Canciones * temp = album -> canciones;
            //La nueva cancion tiene mas duracion que la primera cancion
            if (temp -> cancion -> Duracion < cancion -> Duracion){
                nSub -> sig = temp;
                album -> canciones = nSub;
            }
            //Si la nueva cancion es mas grande que la siguiente cancion evaluada se pone antes que esta
            while (temp -> sig != nullptr && temp -> sig -> cancion -> Duracion > cancion -> Duracion){
                temp = temp -> sig;
            }
            //Tambien se pone de siguiente si llegamos al final de la lista
            nSub -> sig = temp -> sig;
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
void insertarArtistas (int id, string nombre_artistico, string nombre_real, string pais){
    Artistas * nuevoA = new Artistas (id, nombre_artistico, nombre_real, pais);
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

void eliminarArtista(string tituloAlb){
    Artistas * temp = buscarArtista(tituloAlb);
    if (temp == nullptr){
        cout << "Artista no encontrado " << endl;
        return;
    }
    if (temp == primeroArt){
        primeroArt = temp -> sig;

        if (primeroArt != nullptr){
            primeroArt -> ant = nullptr;
        }

        delete temp;
    }
    else{
        if (temp -> ant != nullptr){
            temp -> ant -> sig = temp -> sig;
        }
        if (temp -> sig != nullptr){
            temp -> sig -> ant = temp -> ant;
        }
        delete temp;
    }
}

//Modificacion de sublistas

void insertarCancionArtista(string nombreArt, string tituloC){
    Artistas * artista = buscarArtista(nombreArt);
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
    cout << "Cancion no existe o no pertenece al Artista seleccionado " << endl;
}

void eliminarCancionArtista(string nombreArt, string tituloC){
    Artistas * artista = buscarArtista(nombreArt);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || artista == nullptr){
        cout << "Artista o cancion no encontrada " << endl;
    }
    else{
        cancion -> ID_Artista = artista -> ID;
        if (artista -> canciones -> cancion -> Titulo == tituloC){
            artista -> canciones = artista -> canciones -> sig;
            cout << "Cancion eliminada de artista " << endl;
        }
        else{
            eliminarCancionArtistaAux(artista,cancion);
        }
    }
}

void insertarAlbumArtista(string nombreArt, string tituloAlb){
    Artistas * artista = buscarArtista(nombreArt);
    Albumes * album = buscarAlbum(tituloAlb);
    if (artista == nullptr || album == nullptr){
        cout << "Artista o album no encontrado " << endl;
    }
    else{
        artista ->albumes_publicados++;
        Sublista_Albumes * nSub = new Sublista_Albumes(album);
        if (artista -> albumes == nullptr){
            artista -> albumes = nSub;
        }
        else{
            Sublista_Albumes * temp = artista -> albumes;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}

void eliminarAlbumArtistaAux(Artistas * artista, Albumes * album){
    Sublista_Albumes * temp = artista -> albumes;
    Sublista_Albumes * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> album == album){
            tempAnt -> sig = temp -> sig;
            cout << "Album eliminado de artista " << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Album no existe o no pertenece al Artista seleccionado " << endl;
}

void eliminarAlbumArtista(string tituloArt, string tituloAlb){
    Artistas * artista = buscarArtista(tituloArt);
    Albumes * album = buscarAlbum(tituloAlb);
    if (artista == nullptr || album == nullptr){
        cout << "Artista o album no encontrado " << endl;
    }
    else{
        if (artista -> albumes -> album -> Titulo == tituloAlb){
            artista -> albumes = artista -> albumes -> sig;
            cout << "Album eliminado de artista " << endl;
        }
        else{
            eliminarAlbumArtistaAux(artista,album);
        }
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

void modificarStringGeneroMusical(string nombre, string descripcion){
    Generos_Musicales * genero_musical = buscarGeneroMusical(nombre);
    if (genero_musical == nullptr){
        cout << "Genero Musical no encontrado " << endl;
    }
    else{
        cout << "ID de Genero Musical modificado " << endl;
        genero_musical -> Descripcion = descripcion;
    }
}

void eliminarGeneroMusical (string nombre){
    if (primeroG == nullptr){
        cout << "No hay generos musicales" << endl;
        return;
    }

    Generos_Musicales * temp = primeroG;
    Generos_Musicales * tempAnt = nullptr;

    do {
        if (temp -> Nombre == nombre){
            //eliminar cualquier otro nodo
            if (tempAnt != nullptr){

                tempAnt -> sig = temp -> sig;

                if (temp == primeroG){
                    primeroG = temp -> sig;
                }
            }
            else{
                //eliminar primer nodo
                primeroG = temp -> sig;

                if (primeroG == temp){
                    primeroG = nullptr;
                }
                else{
                    Generos_Musicales * ult = primeroG;

                    while (ult -> sig != temp){
                        ult = ult -> sig;
                    }
                    ult -> sig = primeroG;
                }
            }
            delete temp;
            return;
        }
    } while (temp != primeroG);
    cout << "El genero musical no se encuentra ingresado " << endl;
}

//Modificacion de sublistas

void insertarCancionGeneroMusical(string nombre, string tituloC){
    Generos_Musicales * gm = buscarGeneroMusical(nombre);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || gm == nullptr){
        cout << "Genero musical o cancion no encontrada " << endl;
    }
    else{
        gm -> numero_canciones ++;
        Sublista_Canciones * nSub = new Sublista_Canciones(cancion);
        if (gm -> canciones == nullptr){
            gm -> canciones = nSub;
        }
        else{
            Sublista_Canciones * temp = gm -> canciones;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}

void eliminarCancionGeneroMusicalAux(Generos_Musicales * gm, Canciones * cancion){
    Sublista_Canciones * temp = gm -> canciones;
    Sublista_Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> cancion == cancion){
            tempAnt -> sig = temp -> sig;
            cout << "Cancion eliminada de genero musical" << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Cancion no existe o no esta en el Genero Musical seleccionado " << endl;
}

void eliminarCancionGeneroMusical(string nombre, string tituloC){
    Generos_Musicales * gm = buscarGeneroMusical(nombre);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || gm == nullptr){
        cout << "Genero musical o cancion no encontrada " << endl;
    }
    else{
        if (gm -> canciones -> cancion -> Titulo == tituloC){
            gm -> canciones = gm -> canciones -> sig;
            cout << "Cancion elimnada de genero musical " << endl;
        }
        else{
            eliminarCancionGeneroMusicalAux(gm,cancion);
        }
    }
}

//Funciones de Playlists 
void insertarPlaylist(int id, string nombre, string creador,int fecha){
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

void modificarFechaPlaylist(string nombre, int fecha){
    Playlist * playlist = buscarPlaylist(nombre);
    if (playlist == nullptr){
        cout << "Playlist no encontrado " << endl;
    }
    else{
        cout << "Fecha de Playlist modificada " << endl;
        playlist -> Fecha = fecha;
    }
}

void eliminarPlaylist(string nombre){
    Playlist * temp = primeroP;
    Playlist * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> Nombre == nombre){
            tempAnt -> sig = temp -> sig;
            cout << "Playlist eliminada " << endl;
            delete temp;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Playlist no encontrada " << endl;
}

//Modificacion de sublistas
void insertarCancionPlaylist(string nombre, string tituloC){
    Playlist * playlist = buscarPlaylist(nombre);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || playlist == nullptr){
        cout << "Playlist o cancion no encontrada " << endl;
    }
    else{
        playlist -> numero_canciones ++;
        Sublista_Canciones * nSub = new Sublista_Canciones(cancion);
        if (playlist -> canciones == nullptr){
            playlist -> canciones = nSub;
        }
        else{
            Sublista_Canciones * temp = playlist -> canciones;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}

void eliminarCancionPlaylistAux(Playlist * playlist, Canciones * cancion){
    Sublista_Canciones * temp = playlist -> canciones;
    Sublista_Canciones * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> cancion == cancion){
            tempAnt -> sig = temp -> sig;
            cout << "Cancion eliminada de playlist" << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Cancion no existe o no esta en el Playlist seleccionado " << endl;
}

void eliminarCancionPlaylist(string nombre, string tituloC){
    Playlist * playlist = buscarPlaylist(nombre);
    Canciones * cancion = buscarCancion(tituloC);
    if (cancion == nullptr || playlist == nullptr){
        cout << "Playlist o cancion no encontrada " << endl;
    }
    else{
        if (playlist -> canciones -> cancion -> Titulo == tituloC){
            playlist -> canciones = playlist -> canciones -> sig;
            cout << "Cancion eliminada de playlist " << endl;
        }
        else{
            eliminarCancionPlaylistAux(playlist,cancion);
        }
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

void eliminarSelloDiscografico(string nombre){
    Sellos_Discograficos * temp = buscarSellosDiscograficos(nombre);
    if (temp == nullptr){
        cout << "Sello Discografico no encontrado " << endl;
        return;
    }
    if (temp == primeroSD){
        primeroSD = temp -> sig;

        if (primeroSD != nullptr){
            primeroSD -> ant = nullptr;
        }

        delete temp;
    }
    else{
        temp -> ant -> sig = temp -> sig;
        temp -> sig -> ant = temp -> ant;
        delete temp;
    }

}

//Modificacion de sublistas
void insertarArtistaSelloDiscografico(string nombre, string nombreArt){
    Sellos_Discograficos * sd = buscarSellosDiscograficos(nombre);
    Artistas * artista = buscarArtista(nombreArt);
    if (sd == nullptr || artista == nullptr){
        cout << "Sello Discografico o artista no encontrado " << endl;
    }
    else{
        artista->Sello_Discografico = sd -> Nombre;
        sd -> numero_artistas ++;
        Sublista_Artistas * nSub = new Sublista_Artistas (artista);
        if (sd -> artistas == nullptr){
            sd -> artistas = nSub;
        }
        else{
            Sublista_Artistas * temp = sd -> artistas;
            while (temp -> sig != nullptr){
                temp = temp -> sig;
            }
            temp -> sig = nSub;
        }
    }
}

void eliminarArtistaSelloDiscograficoAux(Sellos_Discograficos * sd, Artistas * artista){
    Sublista_Artistas * temp = sd -> artistas;
    Sublista_Artistas * tempAnt = temp;
    while (temp != nullptr){
        if (temp -> artista == artista){
            tempAnt -> sig = temp -> sig;
            cout << "Artista eliminado de Sello Discografico " << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Artista no existe o no pertenece al sello discografico seleccionado " << endl;
}

void eliminarArtistaSelloDiscografico(string nombre, string nombreArt){
    Sellos_Discograficos * sd = buscarSellosDiscograficos(nombre);
    Artistas * artista = buscarArtista(nombreArt);
    if (sd == nullptr || artista == nullptr){
        cout << "Sello Discografico o artista no encontrado " << endl;
    }
    else{
        if (sd -> artistas -> artista -> Nombre_Artistico == nombreArt){
            sd -> artistas = sd -> artistas -> sig;
            cout << "Artista eliminado de Sello Discografico " << endl;
        }
        else{
            eliminarArtistaSelloDiscograficoAux(sd,artista);
        }
    }
}

//Reportes

void imprimirCancion(Canciones * temp){
    cout << "---------------------------------" << endl;
    cout << "ID de Cancion: " << temp->ID << endl;
    cout << "Titulo de Cancion: " << temp->Titulo << endl;
    cout << "Duracion: " << temp->Duracion << endl;
    cout << "ID de Album: " << temp->ID_Album << endl;
    cout << "ID de Artista: " << temp->ID_Artista << endl;
}

void imprimirCanciones(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todas las canciones " << endl; 
    cout << "---------------------------------" << endl;
    Canciones * temp = primeroC;
    while(temp != nullptr){
        imprimirCancion(temp);
        temp = temp -> sig;
    }
}

void imprimirAlbum(Albumes * temp, bool printDetails){
    cout << "---------------------------------" << endl;
    cout << "ID de Album: " << temp->ID << endl;
    cout << "Titulo: " << temp->Titulo << endl;
    cout << "Año: " << temp->Anno << endl;
    cout << "Número de Canciones: " << temp->N_canciones << endl;
    cout << "---------------------------------" << endl;
    cout << "Canciones del Album: " << endl;
    if (printDetails){
        Sublista_Canciones * temp2 = temp->canciones;
        while(temp2 != nullptr){
            imprimirCancion(temp2->cancion);
            temp2 = temp2 -> sig;
        }
    }
    
}

void imprimirAlbumes(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todos los albumes " << endl; 
    cout << "---------------------------------" << endl;
    Albumes * temp = primeroAlb;
    while (temp != nullptr){
        imprimirAlbum(temp,true);
        temp = temp->sig;
    }
}


void imprimirArtista(Artistas * temp, bool printDetails){
    cout << "---------------------------------" << endl;
    cout << "Nombre Artistico: " << temp -> Nombre_Artistico << endl;
    cout << "Nombre Real: " << temp -> Nombre_Real << endl;
    cout << "Pais: " << temp -> Pais << endl;
    cout << "Sello Discografico: " <<temp -> Sello_Discografico << endl;
    cout << "---------------------------------" << endl;
    cout << "Canciones del Artista: " << endl;
    if (!printDetails){
        return;
    }
    Sublista_Canciones * temp2 = temp->canciones;
    while(temp2 != nullptr){
        imprimirCancion(temp2->cancion);
        temp2 = temp2 -> sig;
    }
    cout << "---------------------------------" << endl;
    cout << "Albumes del Artista: " << endl;
    Sublista_Albumes * temp3 = temp->albumes;
    while(temp3 != nullptr){
        imprimirAlbum(temp3->album,false);
        temp3 = temp3 -> sig;
    }
}

void imprimirArtistas(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todos los artistas " << endl; 
    cout << "---------------------------------" << endl;
    Artistas * temp = primeroArt;
    while (temp != nullptr){
        imprimirArtista(temp,true);
        temp = temp -> sig;
    }
}

void imprimirGenerosMusicales(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todos los generos musicales" << endl; 
    cout << "---------------------------------" << endl;
    Generos_Musicales * temp = primeroG;
    do{
        cout << "---------------------------------" << endl;
        cout << "ID de Genero Musical: " << temp->ID << endl;
        cout << "Nombre de Genero Musical: " << temp->Nombre << endl;
        cout << "Descripcion de Genero Musical: " << temp->Descripcion << endl;
        cout << "---------------------------------" << endl;
        cout << "Canciones del Genero Musical: " << endl;
        Sublista_Canciones * temp2 = temp->canciones;
        while(temp2 != nullptr){
            imprimirCancion(temp2->cancion);
            temp2 = temp2 -> sig;
        }
        temp = temp->sig;
    }
    while(temp != primeroG);
}

void imprimirPlaylists(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todas las playlists " << endl; 
    cout << "---------------------------------" << endl;
    Playlist * temp = primeroP;
    while (temp != nullptr){
        cout << "---------------------------------" << endl;
        cout << "ID de Playlist: " << temp -> ID << endl;
        cout << "Nombre de Playlist: " << temp -> Nombre << endl;
        cout << "Creador de Playlist: " << temp -> Creador << endl;
        cout << "Fecha de Playlist: " << temp->Fecha << endl;
        cout << "---------------------------------" << endl;
        cout << "Canciones de la Playlist: " << endl;
        Sublista_Canciones * temp2 = temp->canciones;
        while(temp2 != nullptr){
            imprimirCancion(temp2->cancion);
            temp2 = temp2 -> sig;
        }
        temp = temp->sig;
    }
}

void imprimirSellosDiscograficos(){
    cout << "---------------------------------" << endl;
    cout << "Imprimiendo todos los sellos discograficos " << endl; 
    cout << "---------------------------------" << endl;
    Sellos_Discograficos * temp = primeroSD;
    do{
        cout << "---------------------------------" << endl;
        cout << "ID de Sello Discografico: " << temp -> ID << endl;
        cout << "Nombre de Sello Discografico: " << temp->Nombre << endl;
        cout << "Pais de Sello Discografico: " << temp->Pais << endl;
        cout << "Año de Fundacion de Sello Discografico: " << temp->Anno_fundacion << endl;
        cout << "---------------------------------" << endl;
        Sublista_Artistas * temp2 = temp->artistas;
        while (temp2 != nullptr){
            imprimirArtista(temp2->artista,false);
            temp2 = temp2 -> sig;
        }
    }
    while (temp != primeroSD);
}

//Consultas

void generoPopular(){
    Generos_Musicales * temp = primeroG;
    Generos_Musicales * max = temp;
    do{
        if (temp -> numero_canciones > max -> numero_canciones){
            max = temp;
        }
        temp = temp->sig;
    }
    while(temp != primeroG);
    cout << "---------------------------------" << endl;
    cout << "Genero Musical con más canciones registradas: " << max ->Nombre << endl;
}

void artistaTrabajador(){
    Artistas * temp = primeroArt;
    Artistas * max = temp;
    while(temp != nullptr){
        if (temp->albumes_publicados > max -> albumes_publicados){
            max = temp;
        }
        temp = temp->sig;
    }
    cout << "---------------------------------" << endl;
    cout << "Artista con más albumes publicados: " << max -> Nombre_Artistico << endl;

}

void cancionLarga(){
    Canciones * temp = primeroC;
    Canciones * max = temp;
    while (temp != nullptr){
        if (temp -> Duracion > max -> Duracion){
            max = temp;
        }
        temp = temp -> sig;
    }
    cout << "---------------------------------" << endl;
    cout << "Canción más larga: " << max -> Titulo << endl;

}

void playlistLarga(){
    Playlist * temp = primeroP;
    Playlist * max = temp;
    while (temp != nullptr){
        if (temp -> numero_canciones > max -> numero_canciones){
            max = temp;
        }
        temp = temp -> sig;
    }
    cout << "---------------------------------" << endl;
    cout << "Playlist más larga: " << max -> Nombre << endl;
}

void albumesPorArtista(){
    Artistas * temp = primeroArt;
    cout << "---------------------------------" << endl;
    cout << "Albumes por Artista: " << endl;
    cout << "---------------------------------" << endl;
    while (temp != nullptr){
        cout << "Albumes publicados por " << temp->Nombre_Artistico << ": " << temp->albumes_publicados << endl;
        temp = temp->sig; 
    }
}

void selloDiscograficoPopular(){
    Sellos_Discograficos * temp = primeroSD;
    Sellos_Discograficos * max = temp;
    do{
        if (temp->numero_artistas > max -> numero_artistas){
            max = temp;
        }
        temp = temp -> sig;
    }
    while(temp != primeroSD);
    cout << "---------------------------------" << endl;
    cout << "Sello Discografico con más artistas publicados: " << max -> Nombre << endl;
}

void cancionesEnAnnoDetermindado (int a){
    Albumes * temp = primeroAlb;
    cout << "Albumes publicados en  " << a <<": "<< endl;
    while(temp != nullptr){
        if (temp -> Anno = a){
            imprimirAlbum(temp,true);
        }
        temp = temp -> sig;
    }
}

void albumesSuperiorNumero(int n){
    Albumes * temp = primeroAlb;
    cout << "---------------------------------" << endl;
    cout << "Albumes que superan " << n << " número de canciones: " << endl;
    while(temp != nullptr){
        if (temp -> N_canciones > n){
            cout << temp->Titulo << "con " << temp->N_canciones << " canciones" << endl;
        }
        temp = temp -> sig;
    }
}

//Validacion

int validInteger(){
    int num;

    // Si se le pone algo que no sea un integer, se quita el error y se elimina el input previo
    while (true){
        cin >> num;
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Input inválido, por favor escribir un número válido" << endl;
        }
        else{return num;}
    }
}

//Interfaz
void mantenimiento(){

}

void consultasAux(){
    cout << "\n" << "-------------------------------------------------" << endl;
    cout << "Menu de consultas" << endl;
    cout << "1 = Género con más canciones registradas" << endl;
    cout << "2 = Artista con más ablumes publicados " << endl;
    cout << "3 = Canción más larga de la base de datos" << endl;
    cout << "4 = Playlist con más canciones" << endl;
    cout << "5 = Cantidad de álbumes por artista" << endl;
    cout << "6 = Sello Discográfico con más artistas firmados" << endl;
    cout << "7 = Canciones publicadas en un año determinado" << endl;
    cout << "8 = Álbumes que superan un número determinado de canciones" << endl;
    cout << "9 = Volver al menu principal" << endl;
    cout << "Presione un número para seleccionar que hacer " << endl;
    
}

void consultas(){
    int n;
    while (true){
        consultasAux();
        n = validInteger();
        switch (n){
            case 1:
                generoPopular();
                break;
            case 2:
                artistaTrabajador();
                break;
            case 3:
                cancionLarga();
                break;
            case 4:
                playlistLarga();
            case 5:
                albumesPorArtista();
            case 6:
                selloDiscograficoPopular();
                break;
            case 7:
                int x = validInteger();
                cancionesEnAnnoDetermindado(x);
                break;
            case 8:
                int x = validInteger();
                albumesSuperiorNumero(x);
                break;
            case 9:
                interfaz();
                return;
        }
    }
}

void reportes(){

}

void interfazAux(){
    cout << "\n" << "-------------------------------------------------" << endl;
    cout << "Bienvenido a Musigest" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Menu de interacción" << endl;
    cout << "1 = Mantenimiento" << endl;
    cout << "2 = Consultas " << endl;
    cout << "3 = Reportes" << endl;
    cout << "4 = Salida" << endl;
    cout << "Presione un número para seleccionar que hacer " << endl;
}

void interfaz(){
    int n;
    while (true){
        interfazAux();
        n = validInteger();
        switch (n){
            case 1:
                mantenimiento();
                break;
            case 2:
                consultas();
                break;
            case 3:
                reportes();
                break;
            case 4:
                return;
        }
    }
}




int main (){


    //Test cases

    insertarCancion(111,"Show me how",5); //Men I Trust
    insertarCancion(213, "Halcyon", 4); // Men I Trust
    insertarCancion(789, "Forever", 3); // Clairo
    insertarCancion(345, "Glue Song", 3); // Beabadoobee
    insertarCancion(567, "The London", 4); // J. Cole, Future
    insertarCancion(910, "Yoru ni Kakeru", 4); // Yoasobi
    insertarCancion(678, "Pushin P", 2); // Gunna
    insertarCancion(432, "Numb", 3); // Men I Trust
    insertarCancion(156, "Sofia", 3); // Clairo
    insertarCancion(299, "See You Soon", 3); // Beabadoobee
    insertarCancion(701, "Wet Dreamz", 4); // J. Cole


    insertarAlbum(243,"Charm",2024);
    insertarAlbum(382, "THE BOOK 2", 2023); // Yoasobi
    insertarAlbum(715, "Immunity", 2019); // Clairo
    insertarAlbum(926, "DS4EVER", 2022); // Gunna
    insertarAlbum(564, "Forever Live Sessions", 2021); // Men I Trust
    insertarAlbum(837, "Beatopia", 2022); // Beabadoobee
    insertarAlbum(490, "2014 Forest Hills Drive", 2014); // J. Cole
    insertarAlbum(311, "High Off Life", 2020); // Future
    insertarAlbum(112, "The Book", 2021); // Yoasobi
    insertarAlbum(456, "Sling", 2021); // Clairo
    insertarAlbum(789, "Wunna", 2020); // Gunna
    insertarAlbum(234, "Oncle Jazz", 2019); // Men I Trust
    insertarAlbum(678, "Fake It Flowers", 2020); // Beabadoobee
    insertarAlbum(901, "KOD", 2018); // J. Cole
    insertarAlbum(345, "I Never Liked You", 2022); // Future

    insertarArtistas(456,"Yoasobi","Lilas","Japan");
    insertarArtistas(123,"Clairo","Claire","USA");
    insertarArtistas(789,"Gunna","Sergio","USA");
    insertarArtistas(303,"Men I Trust","Men I Trust","Canada");
    insertarArtistas(101,"Beabadoobee","Beatrice Kristi Laus","Philippines");
    insertarArtistas(505,"J. Cole","Jermaine Cole","USA");
    insertarArtistas(808,"Future","Nayvadius DeMun Wilburn","USA");


    insertarGeneroMusical(111,"Rap","You know what rap is");
    insertarGeneroMusical(222,"Indie","Idk if this is a real genre");
    insertarGeneroMusical(333,"Pop","Like taylor swift or something");
    insertarGeneroMusical(444,"Country","The one nobody likes");

    insertarPlaylist(231,"Best hits","Random Dude",2025);
    insertarPlaylist(324,"Running or idk","Runner",2077);
    insertarPlaylist(431,"Sleeping","Lazy guy",2024);

    insertarSellosDiscograficos(789, "Sony Music Japan", "Japan", 1968); // Yoasobi
    insertarSellosDiscograficos(456, "FADER Label", "USA", 2002); // Clairo
    insertarSellosDiscograficos(234, "YSL Records", "USA", 2016); // Gunna
    insertarSellosDiscograficos(567, "Independent", "Canada", 2015); // Men I Trust
    insertarSellosDiscograficos(901, "Dirty Hit", "UK", 2010); // Beabadoobee
    insertarSellosDiscograficos(678, "Dreamville Records", "USA", 2007); // J. Cole
    insertarSellosDiscograficos(345, "Epic Records", "USA", 1953); // Future

    imprimirCanciones();
    imprimirAlbumes();
    imprimirArtistas();
    imprimirPlaylists();
    imprimirGenerosMusicales();
    imprimirSellosDiscograficos();
    

    return 0;
}
