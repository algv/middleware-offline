# Projeto Open Source do Middleware do Cartão de Cidadão Português
## Introdução
### Objectivos

O objectivo deste projecto é disponibilizar uma nova versão de middleware que facilite e potencie a utilização do cartão de cidadão. 

## SDK

Está disponível um SDK, com o objetivo de disponibilizar a integração com outras aplicações, das funcionalidades desenvolvidas no âmbito deste projeto.
Existem SDK's para as linguagens C, JAVA e .NET C#.

## Compilar o Middleware do Cartão de Cidadão

### Linux

1 - Instalação das dependências
As dependências para a compilação do Middleware em Linux (nomes de pacotes para a distribuição Ubuntu), são as seguintes:

libpcsclite-dev default-jdk qtbase5-dev qt5-qmake qt5-default libssl-dev libxerces-c-dev swig libcurl4-openssl-dev libpoppler-qt5-dev libxml-security-c-dev

2 - Compilar o projecto na directoria eidmw

cd eidmw
./configure
make

3 - Caso pretenda instalar a aplicação

make install

A aplicação utilitária será instalada em: /usr/local/bin/pteidgui

### Windows

Instruções para build em Windows (Visual Studio 2013)

É importante assegurar que as dependências são compiladas com a mesma versão de Visual Studio que será usada para compilar o Middleware.
Será assim necessário compilar as seguintes bibliotecas:

- openSSL 1.0.2 -  https://www.openssl.org/source/openssl-1.0.2n.tar.gz
- xerces-c -  https://xerces.apache.org/xerces-c/build-3.html#Windows
- xml-security-c -  https://santuario.apache.org/download.html
- libcurl -  https://curl.haxx.se/download.html
- poppler-qt5 0.52 -  https://poppler.freedesktop.org/poppler-0.52.0.tar.xz

Para o caso do Qt 5.6 estão disponíveis binários pré-compilados, poderá ser utilizado o instalador disponível em:  https://download.qt.io/archive/online_installers/2.0/qt-unified-windows-x86-2.0.3-online.exe
Ferramentas adicionais a instalar: - 7-zip
- Java JDK
- Swigwin 2.0.12 - disponível em  https://sourceforge.net/projects/swig/files/swigwin/swigwin-2.0.12/
- Windows Platform SDK

Após configurado o ambiente conforme acima descrito,efetuar os seguintes passos:
1- Checkout do código fonte: https://svn.gov.pt/projects/ccidadao/repository/middleware-offline/trunk/
2- Configurar os caminhos para as dependências (x86 e x64) e ferramentas no ficheiro windows\ezbuild\vc9\set_path_vc9.bat
3- Abrir a Solução de VS2013 através do script windows\ezbuild\vc9\ezbuild_sln_vc9.bat
4- Seleccionar a configuração "Release | Win32" ou "Release | x64"
5- Compilar o projecto através do menu "Build solution" 
