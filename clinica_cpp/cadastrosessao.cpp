#include "cadastrosessao.h"
#include "ui_cadastrosessao.h"

cadastroSessao::cadastroSessao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cadastroSessao)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes");

    if (query.exec()){
        setTabelaPacSes(query);
    } else {
        qDebug() << "Erro ao carregar a tabela de pacientes na janela de cadastro de sessões";
    }

}

cadastroSessao::~cadastroSessao()
{
    delete ui;
}

// DEFINIÇÃO DO METODO CADASTRAR SESSÃO

void cadastroSessao::on_btnCadastrarSes_clicked()
{
    // Recupera os dados dos campos da interface do usuário                                                         // OBTÉM OS DADOS DOS CAMPOS DA SESSÃO

    QString data = ui->dataAgenda->date().toString("dd/MM/yyyy");

    QString paciente = ui->pesquisarPacAg->text();

    QString hora = ui->horaAgenda->time().toString("hh:mm");




    // Conecta o sinal pacienteCadastrado ao slot correspondente                                                   // CONECTA O SINAL PACIENTE CADASTRADO AO SLOT CORRESPONDENTE
    // connect(&paciente, &Paciente::pacienteCadastrado, this, &cadastroPacientes::pacienteCadastrado);

    QSqlQuery query;
    query.prepare("SELECT * ");


    // Salva o objeto Paciente no banco de dados                                                                   // SALVA O OBJETO PACIENTE NO BANCO DE DADOS
    if (query.exec()) {
        QMessageBox::information(this, "", "Nova sessão cadastrada");
        this->close();
    } else {
        QMessageBox::information(this, " ", "Erro ao cadastrar sessão");
    }
}

// FIM


// DEFINIÇÃO DO METODO CANCELAR CADASTRO

void cadastroSessao::on_btnCancelarSes_clicked()
{
    this->close();
}

// FIM

void cadastroSessao::redimensionarTable(QTableWidget* table)
{

    table->resizeColumnsToContents();  // Ajusta as colunas ao conteúdo

    // Agora, fazemos as colunas se expandirem para preencher a largura total da tabela
    for (int i = 0; i < table->columnCount(); ++i) {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // Após redimensionar as colunas, fazemos o ajuste de layout
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Adicionando Tooltips para mostrar o conteúdo completo ao passar o mouse sobre a célula
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem* item = table->item(row, col);
            if (item) {
                // Define o conteúdo completo da célula como o Tooltip
                item->setToolTip(item->text());
                // Alinha os itens das tabelas no centro das colunas
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void cadastroSessao::setTabelaPacSes(QSqlQuery &query)
{
    int tb_linha = 0;

    // Limpa os dados antigos da tabela
    ui->tw_paciente_ses->clearContents();
    ui->tw_paciente_ses->setRowCount(0);  // Reseta as linhas

    ui->tw_paciente_ses->setColumnCount(9);                                                                        // SETA A TABLE EM 9 COLUNAS
    while(query.next()){

        ui->tw_paciente_ses->insertRow(tb_linha);

        for(int i = 0; i <= 8; i++){
            ui->tw_paciente_ses->setItem(tb_linha,i,new QTableWidgetItem(query.value(i).toString()));              // LOOP QUE PREENCHE A TABLE COM OS DADOS DO BANCO
        }
        ui->tw_paciente_ses->setRowHeight(tb_linha,20);

        tb_linha++;
    }

    QStringList cabecalho = {"ID", "Nome", "Idade", "CPF", "Diagnóstico", "NºCelular", "E-mail", "Convêvio/Plano", "Nascimento"};
    ui->tw_paciente_ses->setHorizontalHeaderLabels(cabecalho);
    ui->tw_paciente_ses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_paciente_ses->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_paciente_ses->verticalHeader()->setVisible(false);
    ui->tw_paciente_ses->setStyleSheet("QTableWidget::item:selected {background-color: blue}");

    redimensionarTable(ui->tw_paciente_ses);                                                                       // REDIMENSIONANDO A TABELA
}

void cadastroSessao::on_pesquisarPacAg_textChanged(const QString &arg1)
{
    QString nome = ui->pesquisarPacAg->text(); // Pegando o texto do linePesquisaPac                               // MÉTODO SLOT DO QT PARA RECONHCER O QUE ESTÁ SENDO DIGITADO NA LINHA EM TEMPO REAL

    QSqlQuery query;
    query.prepare("SELECT * FROM tb_pacientes WHERE nome LIKE :nome");                                              // FAZENDO A QUERY DE SELECT PELO NOME
    query.bindValue(":nome", nome + "%");

    if(query.exec()){
        setTabelaPacSes(query);                                                                                  // SETANDO A TABLE EM TEMPO REAL
    }else{
        QMessageBox::warning(this, " ", "Não foi possível acessar os pacientes no banco de dados");
    }
}

