#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <locale.h>

using namespace std;

void gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

struct Profissional {
    int id;
    string matricula;
    string cpf;
    string nome;
    string tipo_profissal;
    string data_nascimento;
    string email;
    string telefone;
    string numero_registro;

     Profissional(int id, const std::string& nome) : id(id), nome(nome) {
        // Construtor da classe Usuario
    }
};

struct Cliente {
    int id;
    int codigo;
    string nome;
    string data_nascimento;
    int idade;
    string email;
    string celular;
    string endereco;
    string cep;

    Cliente(int id, const std::string& nome) : id(id), nome(nome) {
        // Construtor da classe Usuario
    }
};

typedef struct {
    string data_atendimento;
    string descricao_atendimento;
} Atendimento;


void cadastrarProfissional(vector<Profissional*>& profissionais){
    static int proximoId = 0;  // Variável estática para armazenar o próximo ID disponível
    string nome;

    Profissional* profissional = new Profissional(proximoId, nome);
    cout << "Digite o nome do profissional: ";
    cin >> profissional->nome;
    cout << "Digite o CPF: ";
    cin >> profissional->cpf;
    cout << "Digite o Matrícula: ";
    cin >> profissional->matricula;
    cout << "Digite a especialidade médica: ";
    cin >> profissional->tipo_profissal;
    cout << "Digite o e-mail: ";
    cin >> profissional->email;
    cout << "Digite o telefone: ";
    cin >> profissional->telefone;
    cout << "Digite o número de registro: ";
    cin >> profissional->numero_registro;
    cout << "Digite a data de nascimento (DD-MM-AAAA): ";
    cin >> profissional->data_nascimento;

    //abrindo o arquivo com tipo de abertura w
    ofstream arquivoPro("dados_profissionais.txt", ios::app);

    //testando se o arquivo foi realmente criado
     if(!arquivoPro){
        cout << "Erro na abertura do arquivo" << endl; 
        return;
    }

    arquivoPro  << profissional->id << "    "   << profissional->nome << "      " << profissional->cpf << "      " << profissional->matricula << "          " << profissional->tipo_profissal << "    " << 
    profissional->data_nascimento << "    " << profissional->email << "    " << profissional->telefone << "    " << profissional->numero_registro << endl;
    arquivoPro.close();

    cout << "Dados gravados com sucesso" << endl;

    profissionais.push_back(profissional);
    proximoId++;
}

void atualizarArquivoProfissionais(const vector<Profissional*>& profissionais) {
    ofstream arquivoPro("dados_profissionais.txt", ios::trunc);  // Abre o arquivo para escrita, truncando o conteúdo antigo

    if (!arquivoPro) {
        cout << "Erro na abertura do arquivo" << endl;
        return;
    }

    for (const auto& profissional : profissionais) {
        arquivoPro  << profissional->id << "    "   << profissional->nome << "      " << profissional->cpf << "      " << profissional->matricula << "          " << profissional->tipo_profissal << "    " << 
        profissional->data_nascimento << "    " << profissional->email << "    " << profissional->telefone << "    " << profissional->numero_registro << endl;
    }

    arquivoPro.close();
}

void editarProfissionais(vector<Profissional*>& profissionais, int id){
    string nome;
    string cpf;
    string matricula;
    string tipo_profissal;
    string data_nascimento;
    string email;
    string telefone;
    string numero_registro;

    for(Profissional* profissional : profissionais) {
        if(profissional->id) {
            cout << "Digite o novo nome do profissional: " << endl;
            cin >> nome;
            cout << "Digite o novo CPF do profissional: " << endl;
            cin >> cpf;
            cout << "Digite a nova matricula do profissional: " << endl;
            cin >> matricula;
            cout << "Digite a nova especialidade do profissional: " << endl;
            cin >> tipo_profissal;
            cout << "Digite o nova data de nascimento do  profissional: " << endl;
            cin >> data_nascimento;
            cout << "Digite o novo email do profissional: " << endl;
            cin >> email;
            cout << "Digite o novo telefone do profissional: " << endl;
            cin >> telefone;
            cout << "Digite o novo numero do registro do profissional: " << endl;
            cin >> numero_registro;

            profissional->nome = nome;
            profissional->cpf = cpf;
            profissional->matricula = matricula;
            profissional->tipo_profissal = tipo_profissal;
            profissional->data_nascimento = data_nascimento;
            profissional->email = email;
            profissional->telefone = telefone;
            profissional->numero_registro = numero_registro;

            cout << "Dados do profissional atualizados com sucesso!" << endl;

            // Após editar, o arquivo será atualizado
            atualizarArquivoProfissionais(profissionais);
            return ;
        }
    }
    cout << "Profissional com ID " << id << "não encontrado" << endl;
}

void excluirProfissional(vector<Profissional*>& profissionais) {
    int id;
    cout << "Digite o ID do profissional que deseja excluir: ";
    cin >> id;

    for (auto it = profissionais.begin(); it != profissionais.end(); ++it) {
        if ((*it)->id == id) {
            delete *it;
            profissionais.erase(it);
            cout << "Profissional removido com sucesso!" << endl;

            atualizarArquivoProfissionais(profissionais);
            return;
        }
    }
    cout << "Profissional com o ID " << id << " não encontrado." << endl;

        // Abrir o arquivo original em modo de leitura e escrita
    fstream arquivoPro("dados_profissionais.txt", ios::in | ios::out);
    if (!arquivoPro) {
        cout << "Erro na abertura do arquivo" << endl;
        return;
    }

    // Criar um novo arquivo temporário
    ofstream arquivoTemp("dados_profissionais_temp.txt");
    if (!arquivoTemp) {
        cout << "Erro na criação do arquivo temporário" << endl;
        arquivoPro.close();
        return;
    }

    string linha;
    bool encontrado = false;

    // Percorrer o arquivo original linha por linha
    while (getline(arquivoPro, linha)) {
        // Extrair o ID da linha atual
        int idLinha = stoi(linha.substr(0, linha.find(" ")));

        // Verificar se o ID corresponde ao ID do profissional que será excluído
        if (idLinha == id) {
            encontrado = true;
            continue; // Não copiar essa linha para o arquivo temporário
        }

        // Copiar a linha para o arquivo temporário
        arquivoTemp << linha << endl;
    }

    // Fechar os arquivos
    arquivoPro.close();
    arquivoTemp.close();

    if (encontrado) {
        // Excluir o arquivo original
        remove("dados_profissionais.txt");

        // Renomear o arquivo temporário com o nome do arquivo original
        rename("dados_profissionais_temp.txt", "dados_profissionais.txt");

        cout << "Profissional removido do arquivo com sucesso!" << endl;
    } else {
        // Excluir o arquivo temporário
        remove("dados_profissionais_temp.txt");

        cout << "Profissional com o ID " << id << " não encontrado no arquivo." << endl;
    }
}

// void listarProfissionaisCadastrados() {
//     ifstream arquivoPro("dados_profissionais.txt");
//     string linha;

//     cout << "*************************************************  PROFISSIONAIS CADASTRADOS ***************************************************" << endl;
//     cout << "Nome         CPF               Matrícula      Especialidade     D. Nascimento    E-mail               Telefone      Registro" << endl;

//     if (!arquivoPro) {
//         cout << "Erro na abertura do arquivo" << endl;
//         return;
//     }

//     cout << "Dados cadastrados:" << endl;
//     while (getline(arquivoPro, linha)) {
//         cout << linha << endl;
//     }

//     arquivoPro.close();
// }

void telaCadastrar();

void exibirProfissionais(vector<Profissional*>& profissionais){
    int linha = 9; // Inicia a partir da linha 9
    char opcaoProfissional; 
    ifstream arquivoPro("dados_profissionais.txt");
    string linhaArq;

    gotoxy(1,5);
    cout << "*************************************************  PROFISSIONAIS CADASTRADOS ***************************************************";
    gotoxy(2,7);
    cout << "id   Nome         CPF            Matrícula      Especialidade     D. Nascimento    E-mail               Telefone      Registro";
    for (const auto& profissional : profissionais) {
        gotoxy(2,linha);
        cout << profissional->id << endl;
        gotoxy(7,linha);
        cout << profissional->nome << endl;
        gotoxy(20,linha);
        cout << profissional->cpf << endl;
        gotoxy(35,linha);
        cout << profissional->matricula << endl;
        gotoxy(50,linha);
        cout << profissional->tipo_profissal << endl;
        gotoxy(68,linha);
        cout << profissional->data_nascimento << endl;
        gotoxy(85,linha);
        cout << profissional->email << endl;
        gotoxy(106,linha);
        cout << profissional->telefone << endl;
        gotoxy(132,linha);
        cout << profissional->numero_registro << endl;

        linha++; // Incrementa a linha para a próxima exibição
        cout << endl;
    }

   if (!arquivoPro) {
    cout << "Erro na abertura do arquivo" << endl;
    return;
    }

    cout << endl;
    while (getline(arquivoPro, linhaArq)) {
        cout << linhaArq << endl;
    }
    arquivoPro.close();

        cout << endl;
        cout << "Escolha uma opcao: " << endl;
        cout << "1. Cadastrar mais um profissional" << endl;
        cout << "2. Editar um profissional" << endl;
        cout << "3. Excluir um profissional" << endl;
        cout << "4. Voltar ao menu" << endl;
        cout << "Digite o numero da opcao desejada: ";
        cin >> opcaoProfissional;

        switch (opcaoProfissional) {
            case '1':
                        //continuar cadastrando profissionais
                break;
            case '2':
                        //editar um profissional cadastrado
                int id;
                cout << "Digite o ID do profissional que deseja editar: ";
                cin >> id;
                editarProfissionais(profissionais, id);
                system("cls");
                exibirProfissionais(profissionais);
            break;
             case '3':
                excluirProfissional(profissionais);
                system("cls");
                exibirProfissionais(profissionais);
            break;
             case '4':
                system("cls");
                return telaCadastrar();
            break;
        default:
            cout << "Opcao invalida. Tente novamente." <<endl;
            break;
        }
}

void cadastrarCliente(vector<Cliente*>& clientes){
    static int proximoId = 1;
    string nome;

    Cliente* cliente = new Cliente(proximoId, nome);
    cout << "Digite o nome do cliente: ";
    cin >> cliente->nome;
    cout << "Digite o codigo do cliente: ";
    cin >> cliente->codigo;

    ofstream arquivoCli("dados_clientes.txt", ios::app);

    if(!arquivoCli){
        cout << "Erro na abertura do arquivo" << endl;
        return;
    }

    arquivoCli << cliente->nome << ", " << cliente->codigo << endl;
    arquivoCli.close();
    
    clientes.push_back(cliente);
    proximoId++;
}

void exibirClientes(const vector<Cliente*>& clientes){
    int linha = 9; // Inicia a partir da linha 9

    gotoxy(1,5);
    cout << "***************************  CLIENTES CADASTRADOS *****************************";
    gotoxy(2,7);
    cout << "id   Nome           Código";
    for (const auto& cliente : clientes) {
        gotoxy(2,linha);
        cout << cliente->id << endl;
        gotoxy(7,linha);
        cout << cliente->nome << endl;
        gotoxy(22,linha);
        cout << cliente->codigo << endl;

        linha++; // Incrementa a linha para a próxima exibição
        cout << endl;

    }

}

void telaCadastrar(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    vector<Profissional*> profissionais;
    vector<Cliente*> clientes;
    char opcaoMenu; 
    char opcaoProfissional; 
    char opcaoCliente;

    cout << endl;
    cout << "╔═══════════════════════════ BEM-VINDO AO SISTEMA DE SAÚDE! ═══════════════════════════╗" << endl;
    cout << "║ Escolha uma opcao:                                                                   ║" << endl;
    cout << "║ 1. Cadastrar Profissional                                                            ║" << endl;
    cout << "║ 2. Listar Profissionais Cadastrados                                                  ║" << endl;
    cout << "║ 3. Cadastrar Cliente                                                                 ║" << endl;
    cout << "║ 4. Listar Clientes Cadastrados                                                       ║" << endl;
    cout << "║ Digite o numero da opcao desejada:                                                   ║" << endl;
    cout << "════════════════════════════════════════════════════════════════════════════════════════" << endl;
    
    cin >> opcaoMenu; 

    switch (opcaoMenu) {
        case '1':
             do{
                cadastrarProfissional(profissionais);
                system("cls");
                exibirProfissionais(profissionais);
             }
            while (opcaoProfissional != 3);
            // Liberar a memória alocada para os usuários
            for (const auto& usuario : profissionais) {
                delete usuario;
                /* code */
            }
            break;

        case '2':
            system("cls");
            exibirProfissionais(profissionais);
            break;
        
        case '3':
            do{
                cadastrarCliente(clientes);
                system("cls");
                exibirClientes(clientes);

                cout << "Escolha uma opcao: " << endl;
                cout << "1. Cadastrar mais um cliente" << endl;
                cout << "2. Editar um cliente" << endl;
                cout << "3. Editar um cliente" << endl;
                cout << "4. Sair" << endl;
                cout << "Digite o numero da opcao desejada: ";
                cin >> opcaoCliente;

                switch (opcaoCliente) {
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
            while (opcaoCliente != 3);
            // Liberar a memória alocada para os usuários
            for (const auto& usuario : clientes) {
                delete usuario;
                /* code */
            }
            break;

    default:
        cout << "Opção inválida!";
        break;
    }
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    vector<Profissional*> profissionais;
    vector<Cliente*> clientes;
    char opcaoProfissional; 
    char opcaoMenu; 
    
telaCadastrar();

   
    return 0;
}
