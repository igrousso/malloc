# malloc

Réimplémentation de `malloc`, `free` et `realloc` en C, utilisant `mmap` comme allocateur bas niveau. Projet réalisé dans le cadre du cursus 42.

---

## Compilation

```bash
make
```

Génère `libft_malloc_<HOSTTYPE>.so` (ex: `libft_malloc_x86_64_Linux.so`).

```bash
make clean   # supprime les objets
make fclean  # supprime les objets et la lib
make re      # recompile tout
```

---

## Utilisation

### Avec un programme de test

```bash
cc main.c libft_malloc_x86_64_Linux.so
LD_LIBRARY_PATH=. ./a.out
```

Ou avec le Makefile :

```bash
make exec MAIN=main.c
```

---

## Architecture

### Catégories d'allocation

| Catégorie | Taille de l'allocation | Taille d'un chunk | Chunks par zone | Taille d'une zone |
|-----------|------------------------|-------------------|-----------------|-------------------|
| **TINY**  | 1 – 64 octets          | 64 octets         | 128             | 3 pages (12 Ko)   |
| **SMALL** | 65 – 1024 octets       | 1024 octets       | 128             | 33 pages (~132 Ko)|
| **LARGE** | > 1024 octets          | —                 | —               | 1 `mmap` par appel|

### Fonctionnement

- Les zones TINY et SMALL sont des blocs `mmap` réutilisés entre plusieurs allocations. Chaque zone contient un header avec une bitmap de 128 bits pour tracker les chunks libres/occupés.
- Les zones LARGE font l'objet d'un appel `mmap` dédié à chaque `malloc` et d'un `munmap` à chaque `free`.
- Les zones sont chaînées en liste chaînée par catégorie. Une zone vide est libérée via `munmap`, sauf la dernière de chaque catégorie qui est conservée pour éviter un `mmap` inutile.

### Thread safety

L'allocateur est thread-safe via 4 mutex : un par catégorie (TINY, SMALL, LARGE) et un dédié aux affichages verbose.

---

## Fonctions exposées

```c
void *malloc(size_t size);
void  free(void *ptr);
void *realloc(void *ptr, size_t size);
void  show_alloc_mem(void);
void  show_alloc_mem_ex(void);
```

`show_alloc_mem` affiche l'état des zones allouées avec les adresses et tailles.  
`show_alloc_mem_ex` affiche en plus un dump hexadécimal du contenu de chaque chunk alloué.

---

## Variables d'environnement

| Variable | Description |
|----------|-------------|
| `MALLOC_CHECK_` | Active des vérifications supplémentaires sur les pointeurs passés à `free` : double free, invalid free, pointeur mal aligné. Les erreurs sont affichées sur `stderr`. |
| `MALLOC_PERTURB_` | Remplit les chunks alloués avec `~valeur` et les chunks libérés avec `valeur` (0–255). Permet de détecter les lectures non initialisées et les accès après `free`. |
| `MALLOC_PAGE_MAX_` | Limite le nombre total de pages mmap simultanées. Si la limite est atteinte, `malloc` retourne `NULL` et un message est affiché sur `stderr`. |
| `MALLOC_VERBOSE` | Affiche sur `stderr` chaque opération `malloc`, `free` et `realloc` avec les adresses et tailles. |

### Exemples

```bash
# Vérifications sur les free invalides
MALLOC_CHECK_=1 LD_LIBRARY_PATH=. ./a.out

# Remplir la mémoire allouée avec 0xAB et libérée avec 0x54
MALLOC_PERTURB_=171 LD_LIBRARY_PATH=. ./a.out

# Limiter à 100 pages mmap simultanées
MALLOC_PAGE_MAX_=100 LD_LIBRARY_PATH=. ./a.out

# Afficher chaque malloc/free en temps réel
MALLOC_VERBOSE=1 LD_LIBRARY_PATH=. ./a.out
```