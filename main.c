#include <stdio.h>
#include <string.h>

#define MAX 30

// ---------------------------
// STRUCTURE PRINCIPALE
// ---------------------------
typedef struct {
    char immatriculation[20];
    char marque[20];     // BMW 320, Dacia Logan...
    char categorie[20];  // Economique, Standard, Luxe
    char client[50];
    int jours;

    float tarif;         // prix/jour
    float assurance;     // taux assurance (0.05, 0.08, 0.12)
    float total;         // coût total calculé
} Location;

// ---------------------------
// FONCTION CALCUL DU COUT
// ---------------------------
float calculerTotal(Location *l) {
    // Formule : (Jours * Tarif) + (Jours * Tarif * Taux Assurance)
    return (l->jours * l->tarif) * (1 + l->assurance);
}

// ---------------------------
// DEFINIR TARIF + ASSURANCE
// ---------------------------
void definirTarif(Location *l) {
    if (strcmp(l->categorie, "Economique") == 0) {
        l->tarif = 200;
        l->assurance = 0.05;
    } else if (strcmp(l->categorie, "Standard") == 0) {
        l->tarif = 350;
        l->assurance = 0.08;
    } else if (strcmp(l->categorie, "Luxe") == 0) {
        l->tarif = 600;
        l->assurance = 0.12;
    }
}

// ---------------------------
// ENREGISTRER UNE LOCATION
// ---------------------------
void enregistrer(Location tab[], int *n) {
    if (*n >= MAX) {
        printf("Tableau plein !\n");
        return;
    }

    Location *l = &tab[*n]; // pointe vers la prochaine case vide

    printf("Immatriculation: ");
    scanf("%s", l->immatriculation);

    printf("Marque (Dacia, BMW, Clio...): ");
    scanf(" %[^\n]", l->marque); // Lit aussi les espaces (ex: BMW 320)

    do {
            printf("Categorie (Economique / Standard / Luxe): ");
            scanf("%s", l->categorie);

    if (strcmp(l->categorie, "Economique") != 0 &&
            strcmp(l->categorie, "Standard") != 0 &&
            strcmp(l->categorie, "Luxe") != 0) {

            printf("Categorie invalide ! Reessayez.\n");
        }

    } while (strcmp(l->categorie, "Economique") != 0 &&
             strcmp(l->categorie, "Standard") != 0 &&
             strcmp(l->categorie, "Luxe") != 0);


    printf("Nom du client: ");
    scanf(" %[^\n]", l->client); // Lit aussi les espaces (ex: Alami Sara)

    do {
            printf("Nombre de jours: ");
            scanf("%d", &l->jours);

    if (l->jours <= 0) {
            printf("Le nombre de jours doit etre positif !\n");
        }

    } while (l->jours <= 0);

    definirTarif(l);
    l->total = calculerTotal(l);

    printf(">>> Prix total de la location: %.2f MAD\n", l->total);
    (*n)++; //on passe à la case suivante
}

// ---------------------------
// TRI PAR COUT DECROISSANT
// ---------------------------
void trierParTotal(Location tab[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tab[i].total < tab[j].total) {
                Location temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}

// ---------------------------
// RAPPORT DE RENTABILITE
// ---------------------------
void rapport(Location tab[], int n) {
    trierParTotal(tab, n);
    float chiffreTotal = 0;

    printf("\n==========================================================================\n");
    printf("--- RAPPORT DE RENTABILITE ---\n");
    printf("==========================================================================\n");
    printf("Rang | Client | Vehicule | Cat | Jours | Tarif | Assurance | Total\n");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        // CORRECTION : Calcul des montants cumulés pour l'affichage
        float tarifCumule = tab[i].tarif * tab[i].jours;
        float montantAssurance = tarifCumule * tab[i].assurance;

        printf("%d | %s | %s | %s | %dj | %.0f | %.0f | %.2f MAD\n",
               i + 1,
               tab[i].client,
               tab[i].marque,
               tab[i].categorie,
               tab[i].jours,
               tarifCumule,      // Affiche 3000 au lieu de 600
               montantAssurance, // Affiche 360 au lieu de 0.12
               tab[i].total);

        chiffreTotal += tab[i].total;
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Chiffre d'affaires total : %.2f MAD | Vehicules loues: %d\n", chiffreTotal, n);
    printf("==========================================================================\n");
}

// ---------------------------
// AUTRES FONCTIONS (Tri Nom, Recherche, Modif)
// ---------------------------
void trierParNom(Location tab[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(tab[i].client, tab[j].client) > 0) {
                Location temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}

void listeAlphabetique(Location tab[], int n) {
    trierParNom(tab, n);
    printf("\n--- LISTE PAR CLIENT ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s - %s - %.2f MAD\n", tab[i].client, tab[i].marque, tab[i].total);
    }
}

void rechercher(Location tab[], int n) {
    char nom[50];
    printf("Nom du client: ");
    scanf(" %[^\n]s", nom);
    for (int i = 0; i < n; i++) {
        if (strcmp(tab[i].client, nom) == 0) {
            printf("Trouve: %s - %s - %.2f MAD\n", tab[i].client, tab[i].marque, tab[i].total);
            return;
        }
    }
    printf("Client non trouve.\n");
}

void modifier(Location tab[], int n) {
    char imm[20];
    printf("Immatriculation: ");
    scanf("%s", imm);
    for (int i = 0; i < n; i++) {
        if (strcmp(tab[i].immatriculation, imm) == 0) {
            do {
                    printf("Nouvelle duree (jours): ");
                    scanf("%d", &tab[i].jours);

            if (tab[i].jours <= 0) {
                    printf("La duree doit etre positive !\n");
                }

            } while (tab[i].jours <= 0);

            tab[i].total = calculerTotal(&tab[i]);
            printf("Nouveau total mis a jour: %.2f MAD\n", tab[i].total);
            return;
        }
    }
    printf("Location non trouvee.\n");
}

int main() {
    Location tab[MAX];
    int n = 0, choix;
    do {
        printf("\n====== LOCATION DES VOITURES ======\n");
        printf("1. Enregistrer une location\n2. Rapport de rentabilite\n3. Liste alphabetique\n4. Rechercher\n5. Modifier duree\n6. Quitter\n");
        do{
                printf("Votre choix: ");
                scanf("%d", &choix);

        if (choix < 1 || choix > 6) {
                printf("Choix invalide ! Reessayez.\n");
            }

        } while (choix < 1 || choix > 6);


        switch (choix) {
            case 1: enregistrer(tab, &n); break;
            case 2: if(n>0) rapport(tab, n); else printf("Aucune donnée.\n"); break;
            case 3: listeAlphabetique(tab, n); break;
            case 4: rechercher(tab, n); break;
            case 5: modifier(tab, n); break;
            case 6: printf("Au revoir !\n"); break;

            default: printf("Choix invalide.\n");
        }
    } while (choix != 6);
    return 0;
}
