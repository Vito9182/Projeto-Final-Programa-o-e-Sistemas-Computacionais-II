# Projeto-Final-Programa-o-e-Sistemas-Computacionais-II

Sistema de biblioteca para cadastrar livros e usuários, controlar empréstimos e devoluções e guardar o histórico por usuário.

## Divisão de responsabilidades
| Vitor    | Cadastro de livros | `livros/` |
| Henrique | Cadastro de usuários | `--/` |
| Arthur   | Empréstimos e devoluções | `--/` |
| Elei     | Menu principal, integração e histórico | `--` |

---

## Cadastro de livros (`livros/`)

Esta parte guarda os livros da biblioteca e permite cadastrar, listar, buscar e remover.

### Arquivos
- `livros.h`: header com structs iniciais. struct Livro(nó) e struct Lista que guarda o primeiro livro.
- `livros.cpp`: código das funções

### Funções
| `cadastrar` | adiciona um livro (título, autor, código e quantidade) no fim da lista
| `listar` | mostra todos os livros cadastrados
