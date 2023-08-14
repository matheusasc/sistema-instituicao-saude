#include <iostream>
#include <vector>

using namespace std;

void gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

struct Profissional {
    int id;
    string cpf;
    string nome;
    string tipo_profissal;
    string data_nascimento;
    string email;
    string telefone;
    string matricula;
    string numero_registro;

     Profissional(int id, const std::string& nome) : id(id), nome(nome) {
        // Construtor da classe Usuario
    }
};

struct Cliente {
    int codigo;
    string nome;
    string data_nascimento;
    int idade;
    string email;
    string celular;
    string endereco;
    string cep;
};

typedef struct {
    string data_atendimento;
    string descricao_atendimento;
} Atendimento;

void cadastrarProfissional(vector<Profissional*>& profissionais){
    static int proximoId = 1;  // Variável estática para armazenar o próximo ID disponível
    string nome;

    Profissional* profissional = new Profissional(proximoId, nome);
    cout << "Digite o nome do profissional: ";
    cin >> profissional->nome;
    cout << "Digite o CPF: ";
    cin >> profissional->cpf;

    profissionais.push_back(profissional);
}

void exibirProfissionais(const vector<Profissional*>& profissionais){
    int linha = 9; // Inicia a partir da linha 9

    gotoxy(1,5);
    cout << "***************************  PROFISSIONAIS CADASTRADOS *****************************";
    gotoxy(2,7);
    cout << "id   Nome           CPF";
    for (const auto& profissional : profissionais) {
        gotoxy(2,linha);
        cout << profissional->id << endl;
        gotoxy(7,linha);
        cout << profissional->nome << endl;
        gotoxy(22,linha);
        cout << profissional->cpf << endl;

        linha++; // Incrementa a linha para a próxima exibição
        cout << endl;
    }
}

void cadastrarCliente(vector<Cliente*>& clientes){
    Cliente* cliente = new Cliente();
    cout << "Digite o nome do cliente: ";
    cin >> cliente->nome;
    cout << "Digite o codigo do cliente: ";
    cin >> cliente->codigo;
    
    clientes.push_back(cliente);
}

int main() {
    vector<Profissional*> profissionais;
    char opcao; 

    do{
        cadastrarProfissional(profissionais);
        system("cls");
        exibirProfissionais(profissionais);

        cout << "Escolha uma opcao: " << endl;
        cout << "1. Cadastrar mais um profissional" << endl;
        cout << "2. Editar um profissional" << endl;
        cout << "4. Sair" << endl;
        cout << "Digite o numero da opcao desejada: ";
        cin >> opcao;

        switch (opcao) {
            case '1':
                //continuar cadastrando profissionais
                break;
            case '2':
                int id;
                cout << "Digite o ID do profissional que deseja editar: ";
                //editar um profissional cadastrado
        default:
            cout << "Opcao invalida. Tente novamente." <<endl;
            break;
        }
    } 
    while (opcao != 3);
    // Liberar a memória alocada para os usuários
    for (const auto& usuario : profissionais) {
        delete usuario;
        /* code */
    }
    return 0;
}
