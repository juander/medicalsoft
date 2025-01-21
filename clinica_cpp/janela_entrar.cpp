#include "janela_entrar.h"
#include "ui_janela_entrar.h"
#include <QMessageBox>

#include "mainwindow.h"

janela_entrar::janela_entrar(QWidget *parent, Conexao *conexao)
    : QDialog(parent)
    , ui(new Ui::janela_entrar)
    , conexao(conexao)
{
    ui->setupUi(this);
    logado = false;
}

janela_entrar::~janela_entrar()
{
    delete ui;
}

void janela_entrar::on_btnEnt_clicked()
{
    if(!conexao->abrir()){
        qDebug() << "Erro ao abrir o banco de dados:";                           // CONFERINDO SE O BANCO FOI CONECTADO
    } else {
        qDebug() << "Banco de dados conectado com sucesso!";
        QString nome, senha;
        nome = ui->txtnome->text();
        senha = ui->txtsenha->text();
        QSqlQuery query;
        query.prepare("SELECT * FROM tb_usuarios WHERE nome = :nome");
        query.bindValue(":nome", nome);
        if(query.exec()){
            if(query.first()){
                if(query.value(2).toString() == senha){
                    MainWindow::logado = true;
                    MainWindow::id = query.value(0).toInt();
                    MainWindow::nome_usuario = query.value(1).toString();
                    MainWindow::clinica = query.value(3).toString();
                    MainWindow::cargo = query.value(4).toString();
                    close();
                } else {
                    QMessageBox::warning(this, " ", "Senha incorreta");
                }
            } else {
                QMessageBox::warning(this, " ", "Usuário não encontrado");
            }
        } else {
            QMessageBox::warning(this, " ", "Falha no Login");
        }
    }
    conexao->fechar();
}

void janela_entrar::on_btnCancelar_clicked()
{
    logado = false;
    close();
}

void janela_entrar::on_btnMostrar_clicked()
{
    if(ui->txtsenha->echoMode() == QLineEdit::Password){
        ui->txtsenha->setEchoMode(QLineEdit::Normal);
        ui->btnMostrar->setIcon(QIcon(":/icons/Eye.png")); // Ícone de olho aberto
    } else {
        ui->txtsenha->setEchoMode(QLineEdit::Password);
        ui->btnMostrar->setIcon(QIcon(":/icons/Hide.png")); // Ícone de olho com risco
    }
}
