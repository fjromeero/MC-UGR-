#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <string>

static size_t Convertir_a_texto(void *cont,size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)cont, size *nmemb);
    return size * nmemb;
}

using namespace std;

int main(int argc,char *argv[]){

    CURL *curl;
    CURLcode res;
    std::string leer;
    fstream archivo;

    if(argc!=2){
        cout<< "Recuerde introducir la url"<<endl;
        exit(-1);
    }

    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL,argv[1]);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,Convertir_a_texto);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,&leer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    archivo.open("../MC-UGR-/http.txt");
    if(!archivo.is_open()){
        cout<<"NO SE ABRE EL ARCHIVO";
    }
    archivo << leer;
}
