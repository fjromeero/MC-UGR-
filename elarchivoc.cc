#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <string>

static size_t Convertir_a_texto(void *cont,size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)cont, size *nmemb);
    return size * nmemb;
}

using namespace std;

int main(){
    CURL *curl;
    CURLcode res;
    std::string leer;
    fstream archivo;

    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL,"https://git-scm.com/download/linux");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,Convertir_a_texto);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,&leer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    archivo.open("/home/fjromeero/Documentos/GitHub/MC-UGR-/http.txt");
    if(!archivo.is_open()){
        cout<<"NO SE ABRE EL ARCHIVO";
    }
    archivo << leer;
}
