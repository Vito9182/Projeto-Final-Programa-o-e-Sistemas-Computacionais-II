#include <iostream>
#include "usuarios/usuarios.h"

int main() {
    ListaUsuarios lista;

    cadastrarUsuario(lista, 1, "Henrique", "henrique@email.com");

    listarUsuarios(lista);

    limparListaUsuarios(lista);

    return 0;
}