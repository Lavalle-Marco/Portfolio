// Inclusione delle librerie
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check = 1; // Variabile globale per controllare la validità dei dati

//prototipi delle funzioni
void toglispazi(char input[]);
void maiuscolo(char stringa[]);
int calcola_cognome(char cognome[], char codice_fiscale[]);
int calcola_nome(char nome[], char codice_fiscale[]);
int calcola_data(char giorno[], char mese[], char anno[], char sesso, char codice_fiscale[]);
int calcola_comune(char comune[], char codice_fiscale[]);
void calcola_controllo(char codice_fiscale[]);

int main() {
    char codice_fiscale[17] = {0};  // Inizializza il codice fiscale con tutti zeri (che poi verrà "compilato" da ogni funzione in modo graduale)
    char cognome[20], nome[20], comune[30], sesso;
    char data[11], giorno[3], mese[3], anno[5];

    // Chiede il cognome, toglie spazi e lo converte in maiuscolo
    do {
        printf("Inserisci cognome: ");
        scanf(" %[^\n]", cognome); //legge input fino al carattere di newline \n
        toglispazi(cognome);
        maiuscolo(cognome);
        check = calcola_cognome(cognome, codice_fiscale);
    } while (check == 0);

    // Chiede il nome, toglie spazi e lo converte in maiuscolo
    do {
        printf("Inserisci nome: ");
        scanf(" %[^\n]", nome);
        toglispazi(nome);
        maiuscolo(nome);
        check = calcola_nome(nome, codice_fiscale);
    } while (check == 0);

    
    // Chiede il sesso e verifica che sia Femmina o Maschio
    do {
        printf("Sesso (F-M): ");
        scanf(" %c", &sesso);
        if (sesso != 'F' && sesso != 'M') {
            printf("Carattere non valido. Inserire solo F o M.\n");
        }
    } while (sesso != 'F' && sesso != 'M');

    // Chiede la data di nascita e la divide in giorno, mese e anno
    do {
        printf("Inserire la data di nascita (gg/mm/aaaa): ");
        scanf("%10s", data); //10 caratteri per evitare overflow
        sscanf(data, "%2s/%2s/%4s", giorno, mese, anno); //scansiona data e la divide in giorno, mese e anno
        check = calcola_data(giorno, mese, anno, sesso, codice_fiscale);
    } while (check == 0);

     // Chiede il comune di nascita
    do {
        printf("Inserisci il nome del comune: ");
        scanf(" %[^\n]", comune);
        toglispazi(comune);
        maiuscolo(comune);
        check = calcola_comune(comune, codice_fiscale);
    } while (check == 0);

    // Calcola il carattere di controllo
    calcola_controllo(codice_fiscale);

    //stampa nel terminale il codice fiscale dell'utente 
    printf("Codice fiscale: %s\n", codice_fiscale);
}

//toglie gli spazi alle stringhe
void toglispazi(char input[]) {
    char *dest = input;
    for (char *src = input; *src; src++) {
        if (*src != ' ') { //se non è uno spazio copia il carattere nella destinzazione, altrimenti salta
            *dest++ = *src;
        }
    }
    *dest = '\0';
}

//converte ogni caratttere di una stringa in maiuscolo
void maiuscolo(char stringa[]) {
    for (int i = 0; stringa[i]; i++) {
        stringa[i] = toupper(stringa[i]);
    }
}

//funzione che calcola i caratteri dall'indice 0 al 2 carattere del CF, partendo dal cognome
int calcola_cognome(char cognome[], char codice_fiscale[]) {

    check = 1; // inizializza check a 1, per poter tornare 0 in caso di errore

    char cons[25] = {0}, vocal[25] = {0};
    int cont_cons = 0, cont_vocal = 0;

    //controlla se tutti caratteri sono nell'alfabeto (da 'a' a 'z' e da 'A' a 'Z')
    for (int i = 0; cognome[i]; i++) {
        if (isalpha(cognome[i])) {

            char tabella_vocali[6] = "AEIOU"; //tabella delle vocali

            if (strchr(tabella_vocali, cognome[i]) != NULL) { //compara i caratteri del cognome con la tabella delle vocali
                vocal[cont_vocal] = cognome[i]; //se è una vocale, lo salva nella stringa vocali
                cont_vocal++; //incrementa il contatore delle vocali
            } else {
                cons[cont_cons] = cognome[i]; //se non è una vocale, lo salva nella stringa consonanti
                cont_cons++; //incrementa il contatore delle consonanti
            }
        }
    }

    //in base alla quantità di vocali e consonanti, inserisce i caratteri del codice fiscale
    if (cont_cons >= 3) {
        codice_fiscale[0]= cons[0];
        codice_fiscale[1]= cons[1];
        codice_fiscale[2]= cons[2];
    }
    else if (cont_cons == 2) {
        codice_fiscale[0]= cons[0];
        codice_fiscale[1]= cons[1];
        codice_fiscale[2]= vocal[0];
    }
    else if (cont_cons == 1 && cont_vocal >= 2) {
        codice_fiscale[0]= cons[0];
        codice_fiscale[1]= vocal[0];
        codice_fiscale[2]= vocal[1];
        }
        else if (cont_cons == 1 && cont_vocal == 1) {
        codice_fiscale[0]= cons[0];
        codice_fiscale[1]= vocal[0];
        codice_fiscale[2]= 'X';
    }
    else if (cont_cons == 0 && cont_vocal >= 2) {
        codice_fiscale[0]= vocal[0];
        codice_fiscale[1]= vocal[1];
        codice_fiscale[2]= 'X';
    }
    else{   //se non sono soddisfatte le condizioni, stampa un messaggio di errore e imposta check a 0
        printf("cognome non valido.\n"); 
        check = 0; 
    }

    return check;
}

//funzione che calcola i caratteri dall'indice 3 al 5 carattere del CF, partendo dal nome
int calcola_nome(char nome[], char codice_fiscale[]) {
    check = 1; // inizializza check a 1, per poter tornare 0 in caso di errore

    char cons[25] = {0}, vocal[25] = {0};
    int cont_cons = 0, cont_vocal = 0;

    //controlla se tutti caratteri sono nell'alfabeto (da 'a' a 'z' e da 'A' a 'Z')
    for (int i = 0; nome[i]; i++) {
        if (isalpha(nome[i])) {

            
            char tabella_vocali[6] = "AEIOU"; //tabella dei vocali

            if (strchr(tabella_vocali, nome[i]) != NULL) { //compara i caratteri del nome con la tabella delle vocali
                vocal[cont_vocal] = nome[i]; //se è una vocale, lo salva nella stringa vocali
                cont_vocal++; //incrementa il contatore delle vocali
            } else {
                cons[cont_cons] = nome[i]; //se non è una vocale, lo salva nella stringa consonanti
                cont_cons++; //incrementa il contatore delle consonanti
            }
        }
    }

     //in base alla quantità di vocali e consonanti, inserisce i caratteri del codice fiscale
    if (cont_cons >= 4) {
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = cons[2];
        codice_fiscale[5] = cons[3];
    } 
    else if (cont_cons == 3) {
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = cons[1];
        codice_fiscale[5] = cons[2];
    } 
    else if (cont_cons == 2) {
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = cons[1];
        codice_fiscale[5] = vocal[0];
    } 
    else if (cont_cons == 1 && cont_vocal >= 2) {
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = vocal[0];
        codice_fiscale[5] = vocal[1];
    }
    else if (cont_cons == 1 && cont_vocal == 1) {
        codice_fiscale[3] = cons[0];
        codice_fiscale[4] = vocal[0];
        codice_fiscale[5] = 'X';
    }
    else if (cont_cons == 0 && cont_vocal >= 2) {
        codice_fiscale[3] = vocal[0];
        codice_fiscale[4] = vocal[1];
        codice_fiscale[5] = 'X';
    }
    else{
        printf("nome non valido.\n");
        check = 0;
    }

    return check;
}

//funzione che calcola i caratteri dall'indice 6 al 10 carattere del CF, partendo dalla data di nascita
int calcola_data(char giorno[], char mese[], char anno[], char sesso, char codice_fiscale[]) {
    check = 1; // inizializza check a 1, per poter tornare 0 in caso di errore

    //converte da ASCII a interi
    int g = atoi(giorno);
    int m = atoi(mese);
    int a = atoi(anno);
    char tabella_mese[13] = "ABCDEHLMPRST"; //tabella delle lettere da assegnare ai mesi

    //controllo della validità della data
    if (g <= 0 || m < 1 || m > 12 || a < 1920 || a > 2025 || //requsiti minimi
        (g > 30 && (m == 4 || m == 6 || m == 9 || m == 11)) || // Mesi con 30 giorni
        (g > 31) || // Nessun mese ha più di 31 giorni
        (m == 2 && ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) && g > 29) || // Anno bisestile
        (m == 2 && !((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) && g > 28)) { // Anno non bisestile
        return 0;
    }
    
    //inserisce caratteri nel CF
    codice_fiscale[6] = (a % 100) / 10 + '0';  //sposta la virgola a destra di 2 posizioni, e converte il resto in carattere con '0'
    codice_fiscale[7] = a % 10 + '0';  
    codice_fiscale[8] = tabella_mese[m - 1]; //prende dalla tabella_mese il valore con indice m-1 (perchè gli array partono da 0)
    codice_fiscale[9] = (g + (sesso == 'F' ? 40 : 0)) / 10 + '0'; //se il sesso è femminile, aggiunge 40 alla data di nascita
    codice_fiscale[10] = (g + (sesso == 'F' ? 40 : 0)) % 10 + '0'; 

    return 1;
}


//funzione che calcola i caratteri dall'indice 11 al 15 del CF, partendo dal comune di nascita
int calcola_comune(char comune[], char codice_fiscale[]) {
    check = 1; // inizializze check a 1, per poter tornare 0 in caso di errore
    
    char comune_file[30], codice_catastale[5]; 
    FILE *file = fopen("codice_cat.txt", "r"); //apre il file con i comuni e relativi codici catastali,in modalità lettura 

    //funzione che controlla che il file venga aperto correttamente
    if (file == NULL) {
        perror("Errore nell'aprire il file codice_cat.txt"); // stampa un messaggio di errore
        return 0;
    }


    while (fscanf(file, "%s %4s", comune_file, codice_catastale) == 2) { //se fscanf ritorna 2 valori (comune_file, codice_catastale) allore procede
        if (strcmp(comune, comune_file) == 0) { //compara le due stringhe di comuni
            strncpy(codice_fiscale + 11, codice_catastale, 4); //in caso positivo, inserisce i 4 caratteri del codice catastale nel CF
            fclose(file); //chiude file
            return 1;
        }
    }

    fclose(file); //chiude il file in caso fscanf non ritorni 2 valori
    printf("Comune non trovato.\n");
    return 0;
}

//funzione che calcola il caratteri dell'indice 16 del CF, partendo da tutte le altre lettere fino ad ora inserite nel codice_fiscale
void calcola_controllo(char codice_fiscale[]){
    check = 1; // inizializza check a 1, per poter tornare 0 in caso di errore

    int somma = 0;
    int resto = 0;

    char tabella_controllo[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  // Tabella per il carattere di controllo


    //converte lettere e numeri in valori precisi e calcola la somma degli indici dispari
    for (int i = 0; i < 15; i += 2) {
        switch (codice_fiscale[i]) {
            case 'A': case '0': somma += 1; break;
            case 'B': case '1': somma += 0; break;
            case 'C': case '2': somma += 5; break;
            case 'D': case '3': somma += 7; break;
            case 'E': case '4': somma += 9; break;
            case 'F': case '5': somma += 13; break;
            case 'G': case '6': somma += 15; break;
            case 'H': case '7': somma += 17; break;
            case 'I': case '8': somma += 19; break;
            case 'J': case '9': somma += 21; break;
            case 'K': somma += 2; break;
            case 'L': somma += 4; break;
            case 'M': somma += 18; break;
            case 'N': somma += 20; break;
            case 'O': somma += 11; break;
            case 'P': somma += 3; break;
            case 'Q': somma += 6; break;
            case 'R': somma += 8; break;
            case 'S': somma += 12; break;
            case 'T': somma += 14; break;
            case 'U': somma += 16; break;
            case 'V': somma += 10; break;
            case 'W': somma += 22; break;
            case 'X': somma += 25; break;
            case 'Y': somma += 24; break;
            case 'Z': somma += 23; break;
        }
    }


    //converte lettere e numeri in valori precisi e calcola la somma degli indici pari
    for (int i = 1; i < 15; i += 2) {
        switch (codice_fiscale[i]) {
            case 'A': case '0': somma += 0; break;
            case 'B': case '1': somma += 1; break;
            case 'C': case '2': somma += 2; break;
            case 'D': case '3': somma += 3; break;
            case 'E': case '4': somma += 4; break;
            case 'F': case '5': somma += 5; break;
            case 'G': case '6': somma += 6; break;
            case 'H': case '7': somma += 7; break;
            case 'I': case '8': somma += 8; break;
            case 'J': case '9': somma += 9; break;
            case 'K': somma += 10; break;
            case 'L': somma += 11; break;
            case 'M': somma += 12; break;
            case 'N': somma += 13; break;
            case 'O': somma += 14; break;
            case 'P': somma += 15; break;
            case 'Q': somma += 16; break;
            case 'R': somma += 17; break;
            case 'S': somma += 18; break;
            case 'T': somma += 19; break;
            case 'U': somma += 20; break;
            case 'V': somma += 21; break;
            case 'W': somma += 22; break;
            case 'X': somma += 23; break;
            case 'Y': somma += 24; break;
            case 'Z': somma += 25; break;
        }
    }

    resto = somma % 26; //calcola resto della somma divisa per 26
    codice_fiscale[15] = tabella_controllo[resto]; //utilizza il resto come indice nella tabella_controllo per stabilire il carattere di controllo del CF
   
}