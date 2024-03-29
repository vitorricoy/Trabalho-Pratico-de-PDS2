#include <iostream>
#include <vector>
#include <algorithm>
#include "documento.h"
#include "busca.h"
#include "indexador.h"
#include "leitor.h"

std::string lerDiretorio() {
    std::cout << "Deseja ler os documentos do diretório default (D) ou de um diretorio personalizado (P)?" << std::endl;
    char resp;
    std::cin >> resp;
    if(resp == 'D' || resp == 'd') {
        return "dados";
    } else {
        std::cout << "Digite o diretorio a ser lido e pressione enter: " << std::endl;
        std::string dir;
        std::cin.ignore();
        std::getline(std::cin, dir);
        return dir;
    }
}

int main() {
    std::string dir = lerDiretorio();

    //Cria sistema de busca
    Leitor leitor(dir);
    IndiceInvertido indiceInvertido = leitor.obterIndiceInvertido();
    Indexador indexador(indiceInvertido);
    std::vector<Documento> documentos = leitor.obterDocumentosLidos();
    Busca busca(indiceInvertido, indexador, documentos);

    //Realiza a busca
    int numeroDocumentosMostrados;
    std::cout << "Digite quantos documentos serao retornados por query: ";
    std::cin >> numeroDocumentosMostrados;
    std::string query;
    char continuar;

    do {
        system("cls||clear");
        std::cout << "Digite a query de busca e pressione enter: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, query);
        std::vector<Documento> resposta = busca.obterRelevanciaQuery(query);
        std::cout << "Resultados: " << std::endl << std::endl;
        for(int I=0; I<std::min(numeroDocumentosMostrados, (int)resposta.size()); I++) {
            std::cout << resposta[I].obterNomeDocumento() << std::endl;
        }
        std::cout << "Deseja realizar outra query(S/N)? ";
        std:: cin >> continuar;
    } while(continuar == 'S' || continuar == 's');

    return 0;
}