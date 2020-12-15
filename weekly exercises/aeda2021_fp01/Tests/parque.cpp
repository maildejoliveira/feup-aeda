#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot) ,numMaximoClientes(nMaxCli) {
    vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for (int i=0; i<clientes.size(); i++){
        if (clientes[i].nome==nome)
            return i;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if (clientes.size()==numMaximoClientes)
        return false;
    else {
        InfoCartao c;
        c.nome = nome;
        c.presente = false;
        clientes.push_back(c);
        return true;
    }
}

bool ParqueEstacionamento::entrar(const string &nome) {
    if (vagas==0)
        return false;
    for (int i=0; i<clientes.size(); i++) {
        if (clientes[i].nome==nome) {
            if (clientes[i].presente==true){
                return false;
            }
            else if (clientes[i].presente==false){
                clientes[i].presente=true;
                vagas--;
                return true;
            }
        }
    }
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    for (int i=0; i<clientes.size(); i++){
        if (clientes[i].nome==nome){
            if (clientes[i].presente==false){
                clientes.erase(clientes.begin()+i);
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

bool ParqueEstacionamento::sair(const string &nome) {
    for (int i=0; i<clientes.size(); i++){
        if (clientes[i].nome==nome){
            if (clientes[i].presente==true){
                vagas++;
                clientes[i].presente=false;
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao-vagas;
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}




