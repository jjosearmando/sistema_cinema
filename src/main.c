#include "sistema.h"
#include "usuario.h"
#include "filme.h"
#include <stdlib.h>
#include <string.h>

int main() {
    Usuario *usuarios = NULL;
    int numUsuarios = 0;
    Filme *filmes = NULL;
    int numFilmes = 0;

    carregarUsuariosTxt(&usuarios, &numUsuarios);
    carregarFilmesTxt(&filmes, &numFilmes);

    int adminExiste = 0;
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].email, ADMIN_LOGIN) == 0) {
            adminExiste = 1;
            break;
        }
    }

    if (!adminExiste) {
        Usuario admin;
        strcpy(admin.email, ADMIN_LOGIN);
        strcpy(admin.senha, ADMIN_SENHA);
        strcpy(admin.nome, "Administrador");
        usuarios = realloc(usuarios, (numUsuarios + 1) * sizeof(Usuario));
        usuarios[numUsuarios] = admin;
        numUsuarios++;
    }

    menuPrincipal(&usuarios, &numUsuarios, &filmes, &numFilmes);

    salvarUsuariosTxt(usuarios, numUsuarios);
    salvarFilmesTxt(filmes, numFilmes);

    free(usuarios);
    free(filmes);

    return 0;
}
