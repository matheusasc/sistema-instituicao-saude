#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <locale.h>
#include <sstream>

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
    string codigo;
    string nome;
    string data_nascimento;
    string idade;
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
    cout << "Digite o codigo do cliente: ";
    cin >> cliente->codigo;
    cout << "Digite o nome do cliente: ";
    cin >> cliente->nome;
    cout << "Digite a data de nascimento do cliente: ";
    cin >> cliente->data_nascimento;
    cout << "Digite a idade do cliente: ";
    cin >> cliente->idade;
    cout << "Digite o email do cliente: ";
    cin >> cliente->email;
    cout << "Digite o celular do cliente: ";
    cin >> cliente->celular;
    cout << "Digite o cep do cliente: ";
    cin >> cliente->cep;
    cout << "Digite o endereco do cliente: ";
    cin >> cliente->endereco;

    ofstream arquivoCli("dados_clientes.txt", ios::app);

    if(!arquivoCli){
        cout << "Erro na abertura do arquivo" << endl;
        return;
    }

    arquivoCli << cliente->id << "   " << cliente->codigo << "      "  << cliente->nome << "     " << cliente->data_nascimento << "     " << cliente->idade << "      "  << 
    cliente->email << "      "  << cliente->celular << "      "  << cliente->cep << "      "  << cliente->endereco << "      "  << endl;
    arquivoCli.close();
    
    clientes.push_back(cliente);
    proximoId++;
}

void atualizarArquivoClientes(const vector<Cliente*>& clientes) {
    ofstream arquivoPro("dados_clientes.txt", ios::trunc);  // Abre o arquivo para escrita, truncando o conteúdo antigo

    if (!arquivoPro) {
        cout << "Erro na abertura do arquivo" << endl;
        return;
    }

    for (const auto& cliente : clientes) {
        arquivoPro  << cliente->id << "    " << cliente->codigo << "      "  << cliente->nome << "      " << cliente->data_nascimento << "    " << 
        cliente->idade << "    " << cliente->email << "    " << cliente->celular << "    " << cliente->cep <<  "    " << cliente->endereco << "    " << endl;
    }

    arquivoPro.close();
}

void editarClientes(vector<Cliente*>& clientes, int id){
    string codigo;
    string nome;
    string data_nascimento;
    string idade;
    string email;
    string celular;
    string endereco;
    string cep;

    for(Cliente* cliente : clientes) {
        if(cliente->id) {
            cout << "Digite o novo codigo do cliente: " << endl;
            cin >> codigo;
            cout << "Digite o novo nome do cliente: " << endl;
            cin >> nome;
            cout << "Digite a nova data de nascimento do  cliente: " << endl;
            cin >> data_nascimento;
            cout << "Digite a nova idade do cliente: " << endl;
            cin >> idade;
            cout << "Digite o novo email do cliente: " << endl;
            cin >> email;
            cout << "Digite o novo celular do cliente: " << endl;
            cin >> celular;
            cout << "Digite o novo cep do cliente: " << endl;
            cin >> cep;
            cout << "Digite o novo endereco do cliente: " << endl;
            cin >> endereco;

            cliente->codigo = codigo;
            cliente->nome = nome;
            cliente->data_nascimento = data_nascimento;
            cliente->idade = idade;
            cliente->email = email;
            cliente->celular = celular;
            cliente->cep = cep;
            cliente->endereco = endereco;

            cout << "Dados do cliente atualizados com sucesso!" << endl;

            // Após editar, o arquivo será atualizado
            atualizarArquivoClientes(clientes);
            return ;
        }
    }
    cout << "Cliente com ID " << id << "não encontrado" << endl;
}

void excluirClientes(vector<Cliente*>& clientes) {
    int id;
    cout << "Digite o ID do profissional que deseja excluir: ";
    cin >> id;

    for (auto it = clientes.begin(); it != clientes.end(); ++it) {
        if ((*it)->id == id) {
            delete *it;
            clientes.erase(it);
            cout << "Profissional removido com sucesso!" << endl;

            atualizarArquivoClientes(clientes);
            return;
        }
    }
    cout << "Cliente com o ID " << id << " não encontrado." << endl;

        // Abrir o arquivo original em modo de leitura e escrita
    fstream arquivoCli("dados_clientes.txt", ios::in | ios::out);
    if (!arquivoCli) {
        cout << "Erro na abertura do arquivo" << endl;
        return;
    }

    // Criar um novo arquivo temporário
    ofstream arquivoTemp("dados_clientes_temp.txt");
    if (!arquivoTemp) {
        cout << "Erro na criação do arquivo temporário" << endl;
        arquivoCli.close();
        return;
    }

    string linha;
    bool encontrado = false;

    // Percorrer o arquivo original linha por linha
    while (getline(arquivoCli, linha)) {
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
    arquivoCli.close();
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

void exibirClientes(vector<Cliente*>& clientes){
    int linha = 9; // Inicia a partir da linha 9
    char opcaoCliente; 
    ifstream arquivoCli("dados_clientes.txt");
    string linhaArq;

    gotoxy(1,5);
    cout << "***************************  CLIENTES CADASTRADOS *****************************";
    gotoxy(2,7);
    cout << "id  Código      Nome         D. Nascimento       Idade      E-mail        Celular      CEP         Endereco";
    for (const auto& cliente : clientes) {
        gotoxy(2,linha);
        cout << cliente->id << endl;
        gotoxy(7,linha);
        cout << cliente->codigo << endl;
        gotoxy(22,linha);
        cout << cliente->nome << endl;
        gotoxy(35,linha);
        cout << cliente->data_nascimento << endl;
        gotoxy(50,linha);
        cout << cliente->idade << endl;
        gotoxy(68,linha);
        cout << cliente->email << endl;
        gotoxy(85,linha);
        cout << cliente->celular << endl;
        gotoxy(106,linha);
        cout << cliente->cep << endl;
        gotoxy(132,linha);
        cout << cliente->endereco << endl;

        linha++; // Incrementa a linha para a próxima exibição
        cout << endl;

    }

    if (!arquivoCli) {
    cout << "Erro na abertura do arquivo" << endl;
    return;
    }

    cout << endl;
    while (getline(arquivoCli, linhaArq)) {
        cout << linhaArq << endl;
    }
    arquivoCli.close();

        cout << endl;
        cout << "Escolha uma opcao: " << endl;
        cout << "1. Cadastrar mais um cliente" << endl;
        cout << "2. Editar um cliente" << endl;
        cout << "3. Excluir um cliente" << endl;
        cout << "4. Voltar ao menu" << endl;
        cout << "Digite o numero da opcao desejada: ";
        cin >> opcaoCliente;

        switch (opcaoCliente) {
            case '1':
                        //continuar cadastrando profissionais
                break;
            case '2':
                        //editar um profissional cadastrado
                int id;
                cout << "Digite o ID do cliente que deseja editar: ";
                cin >> id;
                editarClientes(clientes, id);
                system("cls");
                exibirClientes(clientes);
            break;
             case '3':
                excluirClientes(clientes);
                system("cls");
                exibirClientes(clientes);
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



void lerDadosClientes(vector<Cliente*>& clientes) {
     ifstream arquivoCli("dados_clientes.txt");

    if (!arquivoCli) {
        cout << "Erro na abertura do arquivo" << endl;
        return;
    }

    string linha;
    while (getline(arquivoCli, linha)) {
        stringstream ss(linha);
        int id;
        string codigo, nome, data_nascimento, idade, email, celular, endereco, cep;

        ss >> id >> codigo >> nome >> data_nascimento >> idade >> email >> celular >> endereco >> cep;

        // Adicione os outros dados do cliente conforme necessário
        // Exemplo: ss >> codigo >> nome >> data_nascimento >> idade >> email >> celular >> cep >> endereco;

        // Crie um novo objeto Cliente e adicione-o ao vetor clientes
        Cliente* cliente = new Cliente(id, nome);
        clientes.push_back(cliente);
    }

    arquivoCli.close();
}

void lerDadosProfissionais(vector<Profissional*>& profissionais) {
    ifstream arquivoPro("dados_profissionais.txt");

    if (!arquivoPro) {
        cout << "Erro na abertura do arquivo" << endl;
        return;
    }

    string linha;
    while (getline(arquivoPro, linha)) {
        stringstream ss(linha);
        int id;
        string nome, cpf, matricula, tipo_profissional, data_nascimento, email, telefone, numero_registro;

        ss >> id >> nome >> cpf >> matricula >> tipo_profissional >> data_nascimento >> email >> telefone >> numero_registro;

        // Adicione os outros dados do cliente conforme necessário
        // Exemplo: ss >> codigo >> nome >> data_nascimento >> idade >> email >> celular >> cep >> endereco;

        // Crie um novo objeto Cliente e adicione-o ao vetor clientes
        Profissional* profissional = new Profissional(id, nome);
        profissionais.push_back(profissional);
    }

    arquivoPro.close();
}




void criarConsulta(vector<Cliente*>& clientes, vector<Profissional*>& profissionais) {
    int idCliente, idProfissional;

      // Chamar as funções para ler os dados dos clientes e dos profissionais
    lerDadosClientes(clientes);
    lerDadosProfissionais(profissionais);

    cout << "Digite o ID do cliente: ";
    cin >> idCliente;
    cout << "Digite o ID do profissional: ";
    cin >> idProfissional;

    // Verificar se o ID do cliente existe
    bool clienteEncontrado = false;
    Cliente* clienteSelecionado = nullptr;
    for (const auto& cliente : clientes) {
        if (cliente->id == idCliente) {
            clienteEncontrado = true;
            clienteSelecionado = cliente;
            break;
        }
    }

    // Verificar se o ID do profissional existe
    bool profissionalEncontrado = false;
    Profissional* profissionalSelecionado = nullptr;
    for (const auto& profissional : profissionais) {
        if (profissional->id == idProfissional) {
            profissionalEncontrado = true;
            profissionalSelecionado = profissional;
            break;
        }
    }

    // Criar a consulta se ambos os IDs existirem
    if (clienteEncontrado && profissionalEncontrado) {

         // Abrir o arquivo de consultas em modo de escrita (ios::app para adicionar ao final do arquivo)
        ofstream arquivoConsulta("consultas.txt", ios::app);

        if (!arquivoConsulta) {
            cout << "Erro na abertura do arquivo" << endl;
            return;
        }

        // Escrever a consulta no arquivo
        arquivoConsulta << "Consulta marcada: Cliente: " << clienteSelecionado->nome << ", Profissional: " << profissionalSelecionado->nome << endl;

        // Fechar o arquivo
        arquivoConsulta.close();

        cout << "Consulta médica criada com sucesso!" << endl;
    } else {
        cout << "Cliente ou profissional não encontrado. Verifique os IDs digitados." << endl;
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
    cout << "║ 1. Criar Consulta                                                                    ║" << endl;
    cout << "║ 2. Cadastrar Profissional                                                            ║" << endl;
    cout << "║ 3. Listar Profissionais Cadastrados                                                  ║" << endl;
    cout << "║ 4. Cadastrar Cliente                                                                 ║" << endl;
    cout << "║ 5. Listar Clientes Cadastrados                                                       ║" << endl;
    cout << "║ Digite o numero da opcao desejada:                                                   ║" << endl;
    cout << "════════════════════════════════════════════════════════════════════════════════════════" << endl;
    
    cin >> opcaoMenu; 

    switch (opcaoMenu) {
        case '1':
            system("cls");
            criarConsulta(clientes, profissionais);
        break;

        case '2':
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

        case '3':
            system("cls");
            exibirProfissionais(profissionais);
            break;
        
        case '4':
            do{
                cadastrarCliente(clientes);
                system("cls");
                exibirClientes(clientes);

            break;
                
            } 
            while (opcaoCliente != 3);
            // Liberar a memória alocada para os usuários
            for (const auto& usuario : clientes) {
                delete usuario;
                /* code */
            }
            break;
        
        case '5':
            system("cls");
            exibirClientes(clientes);
            break;

    default:
        cout << "Opção inválida!";
        break;
    }
}

void listarProfissionaisCadastrados() {
    ifstream arquivoPro("dados_profissionais.txt");
    string linha;

    cout << "*************************************************  PROFISSIONAIS CADASTRADOS ***************************************************" << endl;
    cout << "Nome         CPF               Matrícula      Especialidade     D. Nascimento    E-mail               Telefone      Registro" << endl;

    if (!arquivoPro) {
        cout << "Erro na abertura do arquivo" << endl;
        return;
    }

    cout << "Dados cadastrados:" << endl;
    while (getline(arquivoPro, linha)) {
        cout << linha << endl;
    }

    arquivoPro.close();
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
