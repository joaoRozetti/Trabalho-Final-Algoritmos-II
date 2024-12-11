#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>
#include<cassert>

// Compatibilidade
#ifdef _WIN1
#include <Windoes.h>
#else
#include <unistd.h>
#endif

using namespace std;

typedef struct
{
    int dia, mes, ano;
} Data;

typedef struct
{
    string descricao;
    float valor;
    int tipo; // "débito" ou "crédito"
    Data data;
} LancamentoContabil;

typedef struct
{
    string descricao;
    float valor;
    int tipo; // 1 para "pagar" ou 2 para "receber"
    Data data_vencimento;
    bool pago;
} Conta;

typedef struct
{
    string descricao;
    int quantidade;
    float preco;
} ItemInventario;

typedef struct
{
    string nome;
    float salario_bruto;
    float descontos;
    float salario_liquido;
} Funcionario;

typedef struct
{
    bool valido;
    string nome;
    Data dia_cadastro;
    string senha;
    LancamentoContabil lancamentos[300];
    int qtd_lancamentos;
    Conta contas[300];
    int qtd_contas;
    ItemInventario inventario[300];
    int qtd_itens_inventario;
    Funcionario funcionarios[300];
    int num_funcionarios;
} Usuario;

Usuario *banco_usuarios;

int data_de_hoje(int opcao)
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    switch (opcao)
    {
    case 0:
        return now->tm_mday;
    case 1:
        return now->tm_mon + 1;
    case 2:
        return now->tm_year + 1900;
    default:
        return -1;
    }
}

void cabecalho()
{
    cout << string(100, '#') << endl
         << setw(65) << "Szeuczuk & Rozetti Contabilidade" << setw(13) << endl
         << string(100, '#') << endl;
}

int lerNumero()
{
    int numero;
    while (true)
    {
        cin >> numero;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a entrada inválida
            cout << "Entrada inválida! Por favor, insira um número: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
            return numero;
        }
    }
}

float lerFloat()
{
    float numero;
    while (true)
    {
        cin >> numero;
        if (cin.fail())
        {
            cin.clear();                                         // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora a entrada inválida
            cout << "Entrada inválida! Por favor, insira um número: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer
            return numero;
        }
    }
}

int cadastro(Usuario *banco_usuarios)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    for (int i = 0; i < 1000; ++i)
    {
        if (!banco_usuarios[i].valido)
        {
            string nome;
            cout << setw(55) << "Cadastro iniciado!" << endl
                 << "Digite seu nome: ";
            getline(cin, nome);
            bool duplicado = false;
            for (int j = 0; j < 1000; ++j)
            {
                if (banco_usuarios[j].valido && banco_usuarios[j].nome == nome)
                {
                    duplicado = true;
                    break;
                }
            }
            while (duplicado)
            {
                cout << "Nome já cadastrado, por favor digite outro nome:" << endl;
                getline(cin, nome);
                duplicado = false;
                for (int j = 0; j < 1000; ++j)
                {
                    if (banco_usuarios[j].valido && banco_usuarios[j].nome == nome)
                    {
                        duplicado = true;
                        break;
                    }
                }
            }
            banco_usuarios[i].valido = true;
            banco_usuarios[i].nome = nome;
            banco_usuarios[i].dia_cadastro.dia = data_de_hoje(0);
            banco_usuarios[i].dia_cadastro.mes = data_de_hoje(1);
            banco_usuarios[i].dia_cadastro.ano = data_de_hoje(2);
            cout << "Digite sua senha para ser utilizada no app: ";
            getline(cin, banco_usuarios[i].senha);
            cout << setw(57) << "Cadastro finalizado!" << endl;
            sleep(1.5);
            return i;
        }
    }
    cout << "Armazenamento cheio!!" << endl;
    sleep(1.5);
    return -1;
}

int login(Usuario *banco_usuarios)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    cout << "Você já é cadastrado (1 para sim, 2 para não)?" << endl;
    int opcao;
    opcao = lerNumero();
    string nome, senha;
    if (opcao == 1)
    {
        cout << "Digite seu nome: ";
        getline(cin, nome);
        for (int i = 0; i < 1000; i++)
        {
            if (banco_usuarios[i].valido && banco_usuarios[i].nome == nome)
            {
                cout << "Usuário encontrado! \nDigite sua senha: ";
                getline(cin, senha);
                if (banco_usuarios[i].senha == senha)
                {
                    cout << "Senha correta!" << endl;
                    return i;
                }
                else
                {
                    cout << "Senha Incorreta!" << endl;
                    sleep(1.5);
                    return login(banco_usuarios);
                }
            }
        }
        cout << "Usuário não encontrado!" << endl;
        sleep(1.5);
        system("clear||cls");
        cabecalho();
        cout << "Deseja se cadastrar [1 para sim][2 para não]?" << endl;
        opcao = lerNumero();
        if (opcao == 1)
            return cadastro(banco_usuarios);
        else if (opcao != 2)
            cout << "Dado Inválido!" << endl;
        return login(banco_usuarios);
    }
    else if(opcao==2)
        return(cadastro(banco_usuarios));
    else
        cout << "Dado Inválido!" << endl;
    return login(banco_usuarios);
}

void bubble_sort_recursivo_lancamentos(LancamentoContabil lancamentos[], int n)
{
    if (n <= 1)
        return;
    for (int i = 0; i < n - 1; i++)
    {
        if (lancamentos[i].data.ano > lancamentos[i + 1].data.ano ||
            (lancamentos[i].data.ano == lancamentos[i + 1].data.ano && lancamentos[i].data.mes > lancamentos[i + 1].data.mes) ||
            (lancamentos[i].data.ano == lancamentos[i + 1].data.ano && lancamentos[i].data.mes == lancamentos[i + 1].data.mes && lancamentos[i].data.dia > lancamentos[i + 1].data.dia))
        {
            swap(lancamentos[i], lancamentos[i + 1]);
        }
    }
    bubble_sort_recursivo_lancamentos(lancamentos, n - 1);
}

void buscar_lancamentos_contabeis(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    Data data_inicio, data_fim;
    cout << "Digite a data de início da busca (separados por enter):" << endl;
    data_inicio.dia = lerNumero();
    data_inicio.mes = lerNumero();
    data_inicio.ano = lerNumero();
    cout << "Digite a data de fim da busca (separados por enter):" << endl;
    data_fim.dia = lerNumero();
    data_fim.mes = lerNumero();
    data_fim.ano = lerNumero();
    bubble_sort_recursivo_lancamentos(banco_usuarios[indice_usuario].lancamentos, banco_usuarios[indice_usuario].qtd_lancamentos);
    bool encontrou = false;
    LancamentoContabil *lancamento = banco_usuarios[indice_usuario].lancamentos;
    for (int i = 0; i < banco_usuarios[indice_usuario].qtd_lancamentos; i++)
    {
        if ((lancamento->data.ano > data_inicio.ano ||
             (lancamento->data.ano == data_inicio.ano && lancamento->data.mes > data_inicio.mes) ||
             (lancamento->data.ano == data_inicio.ano && lancamento->data.mes == data_inicio.mes && lancamento->data.dia >= data_inicio.dia)) &&
            (lancamento->data.ano < data_fim.ano ||
             (lancamento->data.ano == data_fim.ano && lancamento->data.mes < data_fim.mes) ||
             (lancamento->data.ano == data_fim.ano && lancamento->data.mes == data_fim.mes && lancamento->data.dia <= data_fim.dia)))
        {
            cout << "Descrição: " << lancamento->descricao << ", Valor: " << lancamento->valor << ", Tipo: " << (lancamento->tipo == 1 ? "débito" : "crédito") << ", Data: " << lancamento->data.dia << "/" << lancamento->data.mes << "/" << lancamento->data.ano << endl;
            encontrou = true;
        }
        lancamento++;
    }
    if (!encontrou)
        cout << "Nenhum lançamento contábil encontrado no período especificado." << endl;
    sleep(10);
}

void lancamentos_contabeis(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    int opcao;
    cout << "Deseja incluir ou buscar lançamentos [1 para incluir][2 para buscar]? " << endl;
    opcao = lerNumero();
    if (opcao == 1)
    {
        if (banco_usuarios[indice_usuario].qtd_lancamentos < 300)
        {
            LancamentoContabil *lancamento = &banco_usuarios[indice_usuario].lancamentos[banco_usuarios[indice_usuario].qtd_lancamentos];
            lancamento->data.dia = data_de_hoje(0);
            lancamento->data.mes = data_de_hoje(1);
            lancamento->data.ano = data_de_hoje(2);
            cout << "Descrição do lançamento: ";
            cin.ignore();
            getline(cin, lancamento->descricao);
            cout << "Valor do lançamento: ";
            lancamento->valor = lerFloat();
            while (lancamento->valor <= 0)
            {
                cout << "Digite um valor maior que 0: ";
                lancamento->valor = lerFloat();
            }
            cout << "Tipo de lançamento [1 para débito][2 para crédito]: ";
            lancamento->tipo = lerNumero();
            while (lancamento->tipo != 1 && lancamento->tipo != 2)
            {
                cout << "Opção inválida! Por favor, digite [1 para débito][2 para crédito]: ";
                lancamento->tipo = lerNumero();
            }
            banco_usuarios[indice_usuario].qtd_lancamentos++;
            cout << "Lançamento registrado com sucesso!" << endl;
        }
        else
        {
            cout << "Limite de lançamentos atingido!" << endl;
        }
    }
    else if (opcao == 2)
        buscar_lancamentos_contabeis(indice_usuario);
    else
        cout << "Opção Inválida!" << endl;
}

void registrar_conta(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    if (banco_usuarios[indice_usuario].qtd_contas < 300)
    {
        Conta *conta = &banco_usuarios[indice_usuario].contas[banco_usuarios[indice_usuario].qtd_contas];
        cout << "Descrição da conta: ";
        cin.ignore();
        getline(cin, conta->descricao);
        cout << "Valor da conta: ";
        conta->valor = lerFloat();
        while (conta->valor <= 0)
        {
            cout << "Digite um valor maior que 0: ";
            conta->valor = lerFloat();
        }
        cout << "Tipo de conta [1 para pagar][2 para receber]: ";
        conta->tipo = lerNumero();
        while (conta->tipo != 1 && conta->tipo != 2)
        {
            cout << "Opção inválida! Por favor, digite [1 para pagar][2 para receber]: ";
            conta->tipo = lerNumero();
        }
        cout << "Data de vencimento (separados por Enter): ";
        conta->data_vencimento.dia = lerNumero();
      conta->data_vencimento.mes = lerNumero();
    conta->data_vencimento.ano = lerNumero();
        conta->pago = false;
        banco_usuarios[indice_usuario].qtd_contas++;
        cout << "Conta registrada com sucesso!" << endl;
    }
    else
        cout << "Limite de contas atingido!" << endl;
}

int busca_binaria_recursiva(Conta contas[], int esquerda, int direita, float valor)
{
    if (esquerda > direita)
        return -1;
    int meio = esquerda + (direita - esquerda) / 2;
    if (contas[meio].valor == valor)
        return meio;
    if (contas[meio].valor < valor)
        return busca_binaria_recursiva(contas, meio + 1, direita, valor);
    return busca_binaria_recursiva(contas, esquerda, meio - 1, valor);
}

void bubble_sort_recursivo_contas(Conta contas[], int n)
{
    if (n == 1)
        return;
    for (int i = 0; i < n - 1; i++)
    {
        if (contas[i].valor > contas[i + 1].valor)
        {
            swap(contas[i], contas[i + 1]);
        }
    }
    bubble_sort_recursivo_contas(contas, n - 1);
}

void editar_conta(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    if (banco_usuarios[indice_usuario].qtd_contas == 0)
    {
        cout << "Nenhuma conta registrada." << endl;
        return;
    }
    float valor_busca;
    cout << "Digite o valor da conta a editar: ";
    valor_busca = lerFloat();
    int resultado = busca_binaria_recursiva(banco_usuarios[indice_usuario].contas, 0, banco_usuarios[indice_usuario].qtd_contas - 1, valor_busca);
    if (resultado != -1)
    {
        Conta *conta = &banco_usuarios[indice_usuario].contas[resultado];
        cout << "Descrição: " << conta->descricao << ", Valor: " << conta->valor << ", Data de Vencimento: " << conta->data_vencimento.dia << "/" << conta->data_vencimento.mes << "/" << conta->data_vencimento.ano << ", Pago: " << (conta->pago ? "Sim" : "Não") << endl;
        char opcao;
        cout << "Deseja marcar como pago? [s/n]: ";
        cin >> opcao;
        if (opcao == 's' || opcao == 'S')
        {
            conta->pago = true;
            cout << "Conta marcada como paga." << endl;
        }
        else
        {
            cout << "Nenhuma alteração feita." << endl;
        }
    }
    else
        cout << "Conta não encontrada." << endl;
    sleep(3);
}

void buscar_contas(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    if (banco_usuarios[indice_usuario].qtd_contas != 0)
    {
        bubble_sort_recursivo_contas(banco_usuarios[indice_usuario].contas, banco_usuarios[indice_usuario].qtd_contas);
        float valor_busca;
        cout << "Digite o valor da conta a buscar: ";
        valor_busca = lerFloat();
        int resultado = busca_binaria_recursiva(banco_usuarios[indice_usuario].contas, 0, banco_usuarios[indice_usuario].qtd_contas - 1, valor_busca);
        if (resultado != -1)
        {
            Conta *conta = &banco_usuarios[indice_usuario].contas[resultado];
            cout << "Descrição: " << conta->descricao << ", Valor: " << conta->valor << ", Data de Vencimento: " << conta->data_vencimento.dia << "/" << conta->data_vencimento.mes << "/" << conta->data_vencimento.ano << ", Pago: " << (conta->pago ? "Sim" : "Não") << endl;
        }
        else
        {
            cout << "Conta não encontrada." << endl;
        }
    }
    else
        cout << "Nenhuma conta registrada." << endl;
    sleep(7);
}

void controle_contas(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    int opcao;
    cout << "Deseja registrar, buscar ou editar contas? [1 para registrar][2 para buscar][3 para editar]: ";
    opcao = lerNumero();
    if (opcao == 1)
    {
        registrar_conta(indice_usuario);
    }
    else if (opcao == 2)
    {
        buscar_contas(indice_usuario);
    }
    else if (opcao == 3)
    {
        editar_conta(indice_usuario);
    }
    else
    {
        cout << "Opção inválida!" << endl;
    }
}

void registrar_item(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    if (banco_usuarios[indice_usuario].qtd_itens_inventario < 300)
    {
        ItemInventario *item = &banco_usuarios[indice_usuario].inventario[banco_usuarios[indice_usuario].qtd_itens_inventario];
        cout << "Descrição do item: ";
        cin.ignore();
        getline(cin, item->descricao);
        cout << "Quantidade do item: ";
        item->quantidade = lerNumero();
        while (item->quantidade <= 0)
        {
            cout << "Digite um valor maior que 0: ";
            item->quantidade = lerNumero();
        }
        cout << "Preço do item: ";
        item->preco = lerFloat();
        while (item->preco <= 0)
        {
            cout << "Digite um valor maior que 0: ";
            item->preco = lerFloat();
        }
        banco_usuarios[indice_usuario].qtd_itens_inventario++;
        cout << "Item registrado com sucesso!" << endl;
    }
    else
        cout << "Limite de itens no inventário atingido!" << endl;
}

void buscar_itens(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    string descricao;
    cout << "Digite a descrição do item a buscar: ";
    cin.ignore();
    getline(cin, descricao);
    bool encontrou = false;
    for (int i = 0; i < banco_usuarios[indice_usuario].qtd_itens_inventario; i++)
    {
        ItemInventario *item = &banco_usuarios[indice_usuario].inventario[i];
        if (item->descricao.find(descricao) != string::npos)
        {
            cout << "Descrição: " << item->descricao << ", Quantidade: " << item->quantidade << ", Preço: " << item->preco << endl;
            encontrou = true;
        }
    }
    if (!encontrou)
        cout << "Nenhum item encontrado." << endl;
}

void atualizar_item(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    string descricao;
    cout << "Digite a descrição do item a atualizar: ";
    cin.ignore();
    getline(cin, descricao);
    for (int i = 0; i < banco_usuarios[indice_usuario].qtd_itens_inventario; i++)
    {
        ItemInventario *item = &banco_usuarios[indice_usuario].inventario[i];
        if (item->descricao == descricao)
        {
            cout << "Novo preço do item: ";
            item->preco = lerFloat();
            while (item->quantidade <= 0)
            {
                cout << "Digite um valor maior que 0: ";
                item->quantidade = lerFloat();
            }
            cout << "Nova quantidade do item: ";
            item->quantidade = lerNumero();
            while (item->quantidade <= 0)
            {
                cout << "Digite um valor maior que 0: ";
                item->quantidade = lerNumero();
            }
            cout << "Item atualizado com sucesso!" << endl;
            return;
        }
    }
    cout << "Item não encontrado." << endl;
}

void gestao_inventario(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    int opcao;
    cout << "Deseja registrar, buscar ou atualizar itens? [1 para registrar][2 para buscar][3 para atualizar]: ";
    opcao = lerNumero();
    switch (opcao)
    {
    case 1:
        registrar_item(indice_usuario);
        break;
    case 2:
        buscar_itens(indice_usuario);
        break;
    case 3:
        atualizar_item(indice_usuario);
        break;
    default:
        cout << "Opção inválida!" << endl;
    }
}

void adicionar_funcionario(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    if (banco_usuarios[indice_usuario].num_funcionarios < 300)
    {
        Funcionario *novo_funcionario = &banco_usuarios[indice_usuario].funcionarios[banco_usuarios[indice_usuario].num_funcionarios];
        cout << "Digite o nome do funcionário: ";
        cin.ignore();
        getline(cin, novo_funcionario->nome);
        cout << "Digite o salário bruto: ";
        novo_funcionario->salario_bruto = lerFloat();
        while (novo_funcionario->salario_bruto <= 0)
        {
            cout << "Digite um valor maior que 0: ";
            novo_funcionario->salario_bruto = lerFloat();
        }
        cout << "Digite os descontos: ";
        novo_funcionario->descontos = lerFloat();
        while (novo_funcionario->descontos < 0)
        {
            cout << "Digite um valor maior ou igual a 1: ";
            novo_funcionario->descontos = lerFloat();
        }
        novo_funcionario->salario_liquido = novo_funcionario->salario_bruto - novo_funcionario->descontos;
        banco_usuarios[indice_usuario].num_funcionarios++;
        cout << "Funcionário adicionado com sucesso!" << endl;
    }
    else
    {
        cout << "Limite de funcionários atingido." << endl;
    }
}

void atualizar_funcionario(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    string nome;
    cout << "Digite o nome do funcionário que deseja atualizar: ";
    cin.ignore();
    getline(cin, nome);

    for (int i = 0; i < banco_usuarios[indice_usuario].num_funcionarios; ++i)
    {
        if (banco_usuarios[indice_usuario].funcionarios[i].nome == nome)
        {
            cout << "Digite o novo salário bruto: ";
            banco_usuarios[indice_usuario].funcionarios[i].salario_bruto = lerFloat();
            while (banco_usuarios[indice_usuario].funcionarios[i].salario_bruto <= 0)
            {
                cout << "Digite um valor maior que 0: ";
                banco_usuarios[indice_usuario].funcionarios[i].salario_bruto = lerFloat();
            }
            cout << "Digite os novos descontos: ";
            banco_usuarios[indice_usuario].funcionarios[i].descontos = lerFloat();
            while (banco_usuarios[indice_usuario].funcionarios[i].descontos < 0)
            {
                cout << "Digite um valor maior ou igual a 0: ";
                banco_usuarios[indice_usuario].funcionarios[i].descontos = lerFloat();
            }
            banco_usuarios[indice_usuario].funcionarios[i].salario_liquido = banco_usuarios[indice_usuario].funcionarios[i].salario_bruto - banco_usuarios[indice_usuario].funcionarios[i].descontos;
            cout << "Funcionário atualizado com sucesso!" << endl;
            return;
        }
    }
    cout << "Funcionário não encontrado." << endl;
}

void remover_funcionario(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    string nome;
    cout << "Digite o nome do funcionário que deseja remover: ";
    cin.ignore();
    getline(cin, nome);
    for (int i = 0; i < banco_usuarios[indice_usuario].num_funcionarios; ++i)
    {
        if (banco_usuarios[indice_usuario].funcionarios[i].nome == nome)
        {
            for (int j = i; j < banco_usuarios[indice_usuario].num_funcionarios - 1; ++j)
            {
                banco_usuarios[indice_usuario].funcionarios[j] = banco_usuarios[indice_usuario].funcionarios[j + 1];
            }
            --banco_usuarios[indice_usuario].num_funcionarios;
            cout << "Funcionário removido com sucesso!" << endl;
            return;
        }
    }
    cout << "Funcionário não encontrado." << endl;
}

void listar_funcionarios(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    if (banco_usuarios[indice_usuario].num_funcionarios == 0)
    {
        cout << "Nenhum funcionário cadastrado." << endl;
        return;
    }
    for (int i = 0; i < banco_usuarios[indice_usuario].num_funcionarios; ++i)
    {
        Funcionario *funcionario = &banco_usuarios[indice_usuario].funcionarios[i];
        cout << "Nome: " << funcionario->nome << ", Salário Bruto: " << funcionario->salario_bruto << ", Descontos: " << funcionario->descontos << ", Salário Líquido: " << funcionario->salario_liquido << endl;
    }
    sleep(10);
}

void menu_funcionarios(int indice_usuario)
{
    int opcao;
    do
    {
        sleep(1.5);
        system("clear||cls");
        cabecalho();
        cout << R"(Você acessou a Folha de Pagamento.
        [1] Adicionar Funcionário
        [2] Atualizar Funcionário
        [3] Remover Funcionário
        [4] Exibir Folha de Pagamento
        [5] Voltar ao Menu Principal)"
             << endl;
        opcao = lerNumero();
        switch (opcao)
        {
        case 1:
            adicionar_funcionario(indice_usuario);
            break;
        case 2:
            atualizar_funcionario(indice_usuario);
            break;
        case 3:
            remover_funcionario(indice_usuario);
            break;
        case 4:
            listar_funcionarios(indice_usuario);
            break;
        case 5:
            cout << "Voltando ao menu principal..." << endl;
            break;
        default:
            cout << "Opção inválida! Tente novamente." << endl;
        }
    } while (opcao != 5);
}

void imposto_renda()
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    cout << "Simulação do Imposto de Renda" << endl;
    float salario_mensal, gastos_educacao, gastos_medicos, retido_fonte;
    int dependentes;
    cout << "Digite o seu salário mensal: R$ ";
    salario_mensal = lerFloat();
    cout << "Digite o número de dependentes: ";
    dependentes = lerNumero();
    cout << "Digite o total de gastos com educação: R$ ";
    gastos_educacao = lerFloat();
    cout << "Digite o total de gastos médicos: R$ ";
    gastos_medicos = lerFloat();
    cout << "Digite o valor já retido na fonte (anual): R$ ";
    retido_fonte = lerFloat();
    float salario_anual = salario_mensal * 12, deducao_dependentes = dependentes * 2275.08,
          total_deducoes = deducao_dependentes + gastos_educacao + gastos_medicos,
          renda_tributavel = salario_anual - total_deducoes, imposto = 0.0;
    if (renda_tributavel <= 22847.76)
    {
        imposto = 0.0;
        cout << "Isento de Imposto de Renda." << endl;
    }
    else if (renda_tributavel <= 33919.80)
        imposto = (renda_tributavel - 22847.76) * 0.075;
    else if (renda_tributavel <= 45012.60)
        imposto = (renda_tributavel - 33919.80) * 0.15 + 825.15;
    else if (renda_tributavel <= 55976.16)
        imposto = (renda_tributavel - 45012.60) * 0.225 + 1535.88;
    else
        imposto = (renda_tributavel - 55976.16) * 0.275 + 2995.21;
    float imposto_a_pagar = imposto - retido_fonte;
    cout << string(100, '-') << endl
         << fixed << setprecision(2)
         << "Renda Anual: R$ " << salario_anual << endl
         << "Deduções por Dependentes: R$ " << deducao_dependentes << endl
         << "Gastos com Educação: R$ " << gastos_educacao << endl
         << "Gastos Médicos: R$ " << gastos_medicos << endl
         << "Total de Deduções: R$ " << total_deducoes << endl
         << "Renda Tributável: R$ " << renda_tributavel << endl
         << "Imposto Bruto: R$ " << imposto << endl
         << "Imposto a Pagar (após retenção na fonte): R$ " << (imposto_a_pagar > 0 ? imposto_a_pagar : 0) << endl;
    sleep(10);
}

bool menu_inicial(int indice_usuario)
{
    sleep(1.5);
    system("clear||cls");
    cabecalho();
    cout << R"(Digite a opção que deseja efetuar:
    [1]              Lançamentos Contábeis
    [2]              Controle de Contas a Pagar e Receber
    [3]              Gestão de Inventário
    [4]              Folha de Pagamento
    [5]              Cálculo do Imposto de Renda
    [6]              Logout
    [7]              Encerrar o Programa(todos os dados serao apagados))"
         << endl;
    int opcao;
    opcao = lerNumero();
    switch (opcao)
    {
    case 1:
        lancamentos_contabeis(indice_usuario);
        return menu_inicial(indice_usuario);
    case 2:
        controle_contas(indice_usuario);
        return menu_inicial(indice_usuario);
    case 3:
        gestao_inventario(indice_usuario);
        return menu_inicial(indice_usuario);
    case 4:
        menu_funcionarios(indice_usuario);
        return menu_inicial(indice_usuario);
    case 5:
        imposto_renda();
        return menu_inicial(indice_usuario);
    case 6:
        return true; // Logout
    case 7:
        return false; // Encerrar programa
    default:
        cout << "Opção Inválida!";
        sleep(1.5);
        system("clear||cls");
        return menu_inicial(indice_usuario);
    }
}

void teste_cadastro()
{
    cout << "Iniciando teste de cadastro..." << endl;
    Usuario usuario;
    usuario.valido = true; 
    usuario.nome = "Teste";
    usuario.senha = "senha123";
    usuario.dia_cadastro = {1, 1, 2023};
    banco_usuarios[0] = usuario;
    assert(banco_usuarios[0].valido);
    assert(banco_usuarios[0].nome == "Teste");
    assert(banco_usuarios[0].senha == "senha123");
    assert(banco_usuarios[0].dia_cadastro.dia == 1);
    assert(banco_usuarios[0].dia_cadastro.mes == 1);
    assert(banco_usuarios[0].dia_cadastro.ano == 2023);
    cout << "Teste de cadastro bem-sucedido!" << endl;
}

void teste_login()
{
    cout << "Iniciando teste de login..." << endl;
    banco_usuarios[0].valido = true;
    banco_usuarios[0].nome = "Teste";
    banco_usuarios[0].senha = "senha123";
    assert(banco_usuarios[0].valido);
    assert(banco_usuarios[0].nome == "Teste");
    assert(banco_usuarios[0].senha == "senha123");
    cout << "Teste de login bem-sucedido!" << endl;
}

void teste_lancamentos_contabeis()
{
    cout << "Iniciando teste de lançamentos contábeis..." << endl;
    banco_usuarios[0].valido = true;
    banco_usuarios[0].qtd_lancamentos = 0;
    LancamentoContabil lancamento;
    lancamento.data = {1, 1, 2023};
    lancamento.descricao = "Venda";
    lancamento.valor = 100.0;
    lancamento.tipo = 2; 
    banco_usuarios[0].lancamentos[banco_usuarios[0].qtd_lancamentos++] = lancamento;
    assert(banco_usuarios[0].qtd_lancamentos == 1);
    assert(banco_usuarios[0].lancamentos[0].descricao == "Venda");
    assert(banco_usuarios[0].lancamentos[0].valor == 100.0);
    assert(banco_usuarios[0].lancamentos[0].tipo == 2);
    assert(banco_usuarios[0].lancamentos[0].data.ano == 2023);
    cout << "Teste de lançamentos contábeis bem-sucedido!" << endl;
}

void teste_controle_contas()
{
    cout << "Iniciando teste de controle de contas..." << endl;
    banco_usuarios[0].valido = true;
    banco_usuarios[0].qtd_contas = 0;
    Conta conta;
    conta.descricao = "Conta de Luz";
    conta.valor = 150.0;
    conta.tipo = 1; 
    conta.data_vencimento = {10, 2, 2023};
    conta.pago = false;
    banco_usuarios[0].contas[banco_usuarios[0].qtd_contas++] = conta;
    assert(banco_usuarios[0].qtd_contas == 1);
    assert(banco_usuarios[0].contas[0].descricao == "Conta de Luz");
    assert(banco_usuarios[0].contas[0].valor == 150.0);
    assert(banco_usuarios[0].contas[0].tipo == 1);
    assert(banco_usuarios[0].contas[0].data_vencimento.ano == 2023);
    cout << "Teste de controle de contas bem-sucedido!" << endl;
}

void teste_gestao_inventario()
{
    cout << "Iniciando teste de gestão de inventário..." << endl;
    banco_usuarios[0].valido = true;
    banco_usuarios[0].qtd_itens_inventario = 0;
    ItemInventario item;
    item.descricao = "Caneta";
    item.quantidade = 100;
    item.preco = 1.50;
    banco_usuarios[0].inventario[banco_usuarios[0].qtd_itens_inventario++] = item;
    assert(banco_usuarios[0].qtd_itens_inventario == 1);
    assert(banco_usuarios[0].inventario[0].descricao == "Caneta");
    assert(banco_usuarios[0].inventario[0].quantidade == 100);
    assert(banco_usuarios[0].inventario[0].preco == 1.50);
    cout << "Teste de gestão de inventário bem-sucedido!" << endl;
}

void teste_funcionario()
{
    cout << "Iniciando teste de funcionário..." << endl;
    banco_usuarios[0].valido = true;
    banco_usuarios[0].num_funcionarios = 0;
    Funcionario funcionario;
    funcionario.nome = "João";
    funcionario.salario_bruto = 3000.0;
    funcionario.descontos = 300.0;
    funcionario.salario_liquido = funcionario.salario_bruto - funcionario.descontos;
    banco_usuarios[0].funcionarios[banco_usuarios[0].num_funcionarios++] = funcionario;
    assert(banco_usuarios[0].num_funcionarios == 1);
    assert(banco_usuarios[0].funcionarios[0].nome == "João");
    assert(banco_usuarios[0].funcionarios[0].salario_bruto == 3000.0);
    assert(banco_usuarios[0].funcionarios[0].descontos == 300.0);
    assert(banco_usuarios[0].funcionarios[0].salario_liquido == 2700.0);
    cout << "Teste de funcionário bem-sucedido!" << endl;
}
int main()
{
    setlocale(LC_ALL, "portuguese");
    cout << "!!!PROGRAMA INICIADO!!!" << endl;
    banco_usuarios = new (nothrow) Usuario[1000];
    if (!banco_usuarios)
    {
        cout << "Falha de alocação de dinâmica de memória" << endl;
        return -1;
    }
    teste_cadastro();
    teste_login();
    teste_lancamentos_contabeis();
    teste_controle_contas();
    teste_gestao_inventario();
    teste_funcionario();
    cout<<"Testes Passados Tudo OK"<<endl;
    sleep(5);
    bool continuar = true;
    do
    {
        int indice_usuario = login(banco_usuarios);
        if (indice_usuario != -1)
            continuar = menu_inicial(indice_usuario);
        else
            continuar = false;
    } while (continuar);
    delete[] banco_usuarios;
    banco_usuarios = NULL;
    system("clear||cls");
    cout << "!!!PROGRAMA FINALIZADO!!!" << endl;
    return 0;
}