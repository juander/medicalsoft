#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsDropShadowEffect>
#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QCommandLinkButton>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

#include "cadastropacientes.h"
#include "cadastrocolaboradores.h"

#include "edicaopaciente.h"
#include "edicaocolaboradores.h"

#include "pessoa.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // MÉTODOS DA TROCA DE PÁGINAS

    void on_btnAgenda_clicked();

    void on_btnAtendimento_clicked();

    void on_btnPacientes_clicked();

    void on_btnColaboradores_clicked();

    void on_btnFornecedores_clicked();

    void on_btnRelatorios_clicked();

    //////////////////////////////////////////////

    // Método para configurar a tabela de pacientes
    void setTabelaPacientes(QSqlQuery &query);

    // Método para adicionar um paciente na tabela
    void adicionarPacienteNaTabela(int id = 0);

    // Método para cadastrar um novo paciente               // MÉTODOS DO PACIENTE
    void on_btnCadastroPac_clicked();

    // Método para apagar um paciente selecionado
    void on_btnApagarPac_clicked();

    // Método para editar um paciente selecionado
    void on_btnEditarPac_clicked();

    // Método para pesquisar pacientes pelo nome
    void on_linePesquisaPac_textChanged(const QString &arg1);

    ///////////////////////////////////////////////

    // Método para configurar a tabela de colaboradores
    void setTabelaColaboradores(QSqlQuery &query);

    // Método para adicionar um paciente na tabela
    void adicionarColaboradorNaTabela(int id = 0);          // MÉTODOS DO COLABORADOR

    // Método para cadastrar um novo colaborador
    void on_btnCadastroCol_clicked();

    // Método para apagar um colaborador
    void on_btnApagarCol_clicked();

    // Método para editar um colaborador
    void on_btnEditarCol_clicked();

    //////////////////////////////////////////////

    void on_linePesquisaCol_textChanged(const QString &arg1);

    void on_btnInicio_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase bancoDeDados; // Objeto para conexão com o banco de dados

    void resetButtonStyles();                               // MÉTODO PARA RESETAR OS ESTILOS DOS BOTÕES
};

#endif // MAINWINDOW_H
