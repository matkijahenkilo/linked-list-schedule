#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

struct agenda {
    string nome;
    int idade;
    string telefone;
};
typedef struct agenda Agenda;

struct lista {
    Agenda *pItemAgenda;
    struct lista* prox;
};
typedef struct lista Lista;

Lista* inicializa (void)
{
    return NULL;
}

void bubbleSort(Lista* *l) {
    Lista* list = *l;
    agenda* aux;
    while (list->prox != NULL) {
        if (list->pItemAgenda->nome[0] > list->prox->pItemAgenda->nome[0]) {
            aux = list->pItemAgenda;
            list->pItemAgenda = list->prox->pItemAgenda;
            list->prox->pItemAgenda = aux;
        }
        list = list->prox;
    }
}

Lista* insere (Lista* l, string nomeRef, int idadeRef, string telRef)
{
    Agenda *ag = new Agenda;
    Lista* novo = new Lista;
    novo -> pItemAgenda = ag;
    novo->pItemAgenda->nome = nomeRef;
    novo->pItemAgenda->idade = idadeRef;
    novo->pItemAgenda->telefone = telRef;
    novo->prox = l;
    bubbleSort(&novo);
    return novo;
}

/* função imprime: imprime valores dos elementos */
void imprime (Lista* l)
{
    Lista* p;
    for (p = l; p != NULL; p = p->prox)
        cout <<"Registro = " << p->pItemAgenda->nome << " - " << p->pItemAgenda->idade << " - " << p->pItemAgenda->telefone << " " << endl;
}

void mostrarOpcoes() {
    cout << "\n\n1. Cadastrar contato\n2. Buscar Contato\n3. Excluir Contato\n4. Mostrar Contatos\n5. Sair" << endl;
}

Lista* cadastrarContato(Lista* l) {
    string r1 = "b";
    int r2;
    string r3;

    while (r1[0] < 65 || r1[0] > 90) {
        cout << "Insira o nome do contato com a inicial em maiuscula: ";
        cin >> r1;
    }

    cout << "Insira a idade do contato: ";
    cin >> r2;

    cout << "Insira o numero do contato: ";
    cin >> r3;

    l = insere(l, r1, r2, r3);
    return l;
}

void buscarContato(Lista* l) {
    string name;
    cout << "Insira o nome do contato para fazer a busca: ";
    cin >> name;

    Lista* p;
    for (p = l; p != NULL; p = p->prox) {
        if (name == p->pItemAgenda->nome) {
            cout << "Contato '" << name << "' foi encontrado!" << endl;
            return;
        }
    }
    cout << "Contato não foi encontrado!" << endl;
}

Lista* excluirContato(Lista* l) {
    string name;
    cout << "Insira o nome do contato para deletar: ";
    cin >> name;

    bool confirmation = false;
    Lista* list = l;
    agenda* aux;
    while (list->prox != NULL) {
        if (list->pItemAgenda->nome == name) {
            aux = list->pItemAgenda;
            list->pItemAgenda = list->prox->pItemAgenda;
            list->prox->pItemAgenda = aux;
            confirmation = true;
        }
        list = list->prox;
    }

    if (confirmation) {
        list = l;
        while (true) {
            if (list->prox->pItemAgenda->nome == name) {
                list->prox = NULL;
                cout << "Contato excluido." << endl;
                return l;
            }
            list = list->prox;
        }
    } else {
        cout << "Contato nao encontrado." << endl;
    }
    return l;
}

void receberResposta(int *x) {
    cout << "Escolha a opcao: ";
    cin >> *x;
}

Lista* runTime(Lista* l) {
    mostrarOpcoes();
    int resposta;
    receberResposta(&resposta);

    while (resposta != 5) {
        switch (resposta) {
        case 1:
            l = cadastrarContato(l);
            break;
        case 2:
            buscarContato(l);
            break;
        case 3:
            l = excluirContato(l);
            break;
        case 4:
            imprime(l);
            break;
        default:
            mostrarOpcoes();
            receberResposta(&resposta);
            break;
        }
        mostrarOpcoes();
        receberResposta(&resposta);
    }

    return l;
}

int main()
{
    Lista* l;
    l = inicializa();
    //l = insere(l, "Alexandre", 21, "9988-9999");
    //l = insere(l, "Joao", 21, "9988-9999");
    //system("pause");

    l = runTime(l);

    delete l;

    return 0;
}
