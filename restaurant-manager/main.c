#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define size_max 250
char login[40];
char password[40];
typedef struct
{
    int nbvisite;
    int codeID;
    char prenom[15];
    char nom[15];
    char sexe;
    struct consomation
    {
        float Aperitifs;
        float PlatPrincipal;
        float Boissons ;
        float Dessert;
    } consomation;
    float Total;
} client;
typedef struct cellule
{
    client E;
    int table;
    char comment[size_max];
    struct cellule *next;
} cellule;
/////////////////////////////////////////////////////////////
cellule *insertion_debut(cellule *A,client B);
cellule *insertion_fin(cellule *A,client B);
void aff_liste(cellule *A);
client Ajouter_cellule(client B,cellule *A);
cellule *suppression(cellule *A,int nb);
cellule *Update_client(cellule *A,client B,int nb);
cellule *Chercher_client(cellule *A,int nb);
int vrf_liste_triee(cellule *A);
cellule *insertion_milieu(cellule *A,client B);
cellule *trier_liste(cellule *A);
cellule *Trouver_max(cellule *A);
cellule *Trouver_min(cellule *A);
void afficher_client(cellule *A);
cellule *trier_alphabie(cellule *A);
int calcul_nb_client(cellule *A);
float calcul_Total(cellule *A);
void etat_client(cellule *A);
int vrf_liste_alph(cellule *A);
int strComp(char s[], char t[]);
void strAdd(char *A,char *B);
cellule *insert_mil_alph(cellule *A,client B);
void reserver_table(cellule *L,int *T,client *B);
void demande_plat(client *B);
int *mise_a_jour_table( int *T);
int *trier_table(int *T);
void affiche_menu();
cellule *commentaire(cellule *C,char *A);
void affiche_comment(cellule *C);
void affiche_tables_disponibles(cellule *L);
cellule *insertionFin_table(cellule *L,int n);
int recherche_table(cellule *L,int n);
void affiche_addition(client *C);
client mode_client_ajout(client B,cellule *A);
cellule *read_database(cellule *L,client C);
void delete_from_database(int id);
void insert_to_data(char *newClient);
void save_newData(client *C,char *newData);
void remplacing_database_for_update();
void remplacing_database_for_deleting();
void update_database(char *newdata,int id);
cellule *contenu_corbeille(cellule *L,client C);
void recuperation(cellule *A,cellule *B);
void modifier_client(cellule *C);
void vider_corbeille();
void ouvrir_corbeille();
//////////////////////////////////////////////////////////////////////
int main()
{
    int n,i,D[20],choix,m,ID,mode,serveur,mode2,access,a;
    char Ch[size_max],c,newData[size_max];
    cellule *L,*S,*C,*Table,*data,*Cm,*contenu;
    client T,M;
    L=NULL;
    Table=NULL;
    C=NULL;
    data=NULL;
    Cm=NULL;
    contenu=NULL;

    ouvrir_corbeille();
    L=read_database(L,M);

    do
    {
        system("cls");
        printf("\n\n\n\t\t\033[94m\******  *** ****** ***     *** ***           *** ****** ***     *** ***    ***\n");
        printf("\t\t*     *  *  *       **      *   *             *  *       **      *   *      *\n");
        printf("\t\t*     *  *  *       * *     *    *           *   *       * *     *   *      *\n");
        printf("\t\t*     *  *  *       *  *    *     *         *    *       *  *    *   *      *\n");
        printf("\t\t* * *    *  ******  *   *   *      *       *     ******  *   *   *   *      *\n");
        printf("\t\t*     *  *  *       *    *  *       *     *      *       *    *  *   *      *\n");
        printf("\t\t*     *  *  *       *     * *        *   *       *       *     * *   *      *\n");
        printf("\t\t*     *  *  *       *      **         * *        *       *      **   *      *\n");
        printf("\t\t******  *** ****** ***     ***        ***        ****** ***     ***  ********\033[0m\n\n");
        printf("\t\t\033[92m\///////////////////////////\033[95m\RESTAURANT EL_MOUBTAHIJ\033[92m\////////////////////////////\033[0m\n");
        printf("\n\033[96m\ LES MODES DE PROGRAMME :\033[0m\n\n");
        printf("\t\t\t\t\033[33m\MODE CLIENT [1]\n");
        printf("\n\t\t\t\tMODE CHEF [2]\n");
        printf("\n\t\t\t\tARRITER LE PROGRAMME [3]\033[0m\n");
        printf("\n CHOISISSEZ POUR CONTINUE:");
        scanf("%d",&ID);
        mode=1;
        c='n';
        memset(newData,0,sizeof(newData));
        switch(ID)
        {
        case 1:
        {
            system("CLS");
            printf("\033[35m\////////////////////\033[92m\BIENVENU AU MODE CLIENT\033[35m\////////////////////\033[0m\n\n");
            printf("\n\033[36m\ ENTREZ VOTRE INFORMATIONS:\033[0m\n");
            T=mode_client_ajout(T,L);
            reserver_table(Table,D,&T);
            save_newData(&T,newData);
            insert_to_data(newData);
            L=insertion_fin(L,T);
            system("cls");
            if(T.sexe=='H' || T.sexe=='h')
                printf("\n\n\n\n\n\t\t\t\t\t\033[92m\ BON APPETIT !!! Monsieur\033[95m\ %s %s\033[0m\n\n\n\n\n\n\n"
                       ,T.nom,T.prenom);
            else
                printf("\n\n\n\n\n\t\t\t\t\t\033[92m\ BON APPETIT !!! Madame\033[95m\ %s %s\033[0m\n\n\n\n\n\n\n"
                       ,T.nom,T.prenom);
            system("pause");
            do
            {
                mode2=1;
                system("CLS");
                printf("\n\033[96m\ LISTES DE CHOIX :\n\033[31m\ remarque pour sortir il faut payer votre consomation!!\033[0m\n");
                printf("\n\t\t\t\t\033[33m\DEMANDER AUTRE CHOSE [1]\n");
                printf("\n\t\t\t\tDEMANDER L'ADDITION [2]\n");
                printf("\n\t\t\t\tLAISSER UN COMMENTAIRE [3]\033[0m\n");
                printf("\n CHOISISSEZ POUR CONTINUE:");
                scanf("%d",&serveur);
                switch(serveur)
                {
                case 1:
                {
                    affiche_menu();
                    demande_plat(&T);
                    system("cls");
                    if(T.sexe=='h' || T.sexe=='H')
                        printf("\n\n\n\n\n\t\t\t\t\t\033[92m\ BON APPETIT !!! Monsieur\033[95m\ %s %s\033[0m\n\n\n\n\n\n\n"
                               ,T.nom,T.prenom);
                    else
                        printf("\n\n\n\n\n\t\t\t\t\t\033[92m\ BON APPETIT !!! Madame\033[95m\ %s %s\033[0m\n\n\n\n\n\n\n"
                               ,T.nom,T.prenom);
                    system("pause");
                    break;
                }
                case 2:
                {
                    affiche_addition(&T);
                    system("pause");
                    system("cls");
                    printf("\n\033[32m\ Si vous voullez aller au mode Chef tapez [Y/y] sinon tapez [N/n]:\033[0m");
                    scanf("%s",&c);
                    mode2=0;
                    save_newData(&T,newData);
                    update_database(newData,T.codeID);
                    L=Update_client(L,T,T.codeID);
                    break;
                }
                case 3:
                {
                    memset(Ch,0,sizeof(Ch));
                    strAdd(Ch,T.nom);
                    strAdd(Ch," ");
                    strAdd(Ch,T.prenom);
                    strAdd(Ch,":");
                    C=commentaire(C,Ch);
                    memset(Ch,0,sizeof(Ch));
                    printf("\n Entrez votre commentaire:");
                    fflush(stdin);
                    gets(Ch);
                    C=commentaire(C,Ch);
                    printf("\n\t\033[32m\ commentaire est bien  enregistre\033[0m\n\n");
                    system("pause");
                    break;
                }
                default :
                {
                    system("cls");
                    printf("\n\033[31m\ VOTRE CHOIX N'EXISTE PAS :\033[0m\n");
                    system("\npause");
                }
                }
            }
            while(mode2);
            break;
        }
        case 2:
        {
            mode=0;
            break ;
        }
        case 3:
        {
            system("cls");
            printf("\n\t\033[31m\ Fin de traitement ! Merci beaucoup.\033[0m");
            return 0;
        }
        default :
        {
            system("cls");
            printf("\n\033[31m\ VOTRE CHOIX N'EXISTE PAS :\033[0m\n");
            system("\npause");
        }
        }
    }
    while( mode==1 && (c=='n' || c=='N'));
    system("cls");
    printf("\033[35m\////////////////////\033[92m\BIENVENU AU MODE CHEF\033[35m\////////////////////\033[0m\n\n");
    /*  le LOGINE ET MOT DE PASSE  */
    access=1;
    printf( "\n\033[96m\ Please, enter your login: \033[0m" );
    scanf( "%s", login );
    while(strComp( login, "El_Moubtahij")!=0 && access<=2 )
    {
        printf( "\n\033[31m\ Les informations inccorectes\n\n\033[96m\ Please, enter your login: \033[0m" );
        scanf( "%s", login );
        access++;
    }
    if(access<=2)
    {
        printf( "\n\033[96m\ Enter your password: \033[0m" );
        scanf( "%s", password );
        access=1;
        while(strComp( password, "ESTA2024" )!=0&& access<=2)
        {
            printf( "\n\033[31m\ Les informations inccorectes\n\n\033[96m\ Enter your password: \033[0m" );
            scanf( "%s", password );
            access++;
        }
    }
    if(access<=2)
    {
        system("CLS");
        printf("\n\n\n\t\t\t\033[36m\  ||=====================================||");
        printf("\n\t\t\t |||\033[33m\                                     \033[36m\|||");
        printf("\n\t\t\t||||\033[33m\   Bienvenu au votre espace (^_^)    \033[36m\||||");
        printf("\n\t\t\t |||\033[33m\                                     \033[36m\|||");
        printf("\n\t\t\t  ||=====================================||\033[0m\n\n");
        printf("\n\n");
        system("pause");

        do
        {
            menu();
            memset(newData,0,sizeof(newData));
            printf("\n\n\t choisissez une fontion parmi ces fonctions : ");
            scanf("%d",&choix);
            switch(choix)
            {
            case 0 :
            {
                system("CLS");
                printf("\n\033[104m\//////////\033[105m\ la liste des clients \033[104m\///////////\033[0m\n\n");
                aff_liste(L);
                printf("\n\n");
                system("pause");
                break;
            }
            case 1 :
            {
                system("cls");
                printf("\n\n\t Veuillez saisir le nombre des clients que vous voulez inscrire : ");
                scanf("%d",&n);
                for(i=0; i<n; i++)
                {
                    printf("\n\t\033[96m\ Les informations de client(e) %d : \033[0m\n",i+1);
                    T=Ajouter_cellule(T,L);
                    save_newData(&T,newData);
                    insert_to_data(newData);
                    L=insertion_fin(L,T);
                }
                if(n>=1)
                    printf("\n\033[32m\ Insertion bien effectuee!!\033[0m\n\n");
                else
                    printf("\n\033[31m\ Aucune insertion \033[0m\n\n");
                printf("\n\n");
                system("pause");
                break;
            }
            case 2 :
            {
                system("cls");
                T=Ajouter_cellule(T,L);
                save_newData(&T,newData);
                insert_to_data(newData);
                L=insertion_fin(L,T);
                system("cls");
                printf("\n\033[104m\//////////\033[105m\ la nouvelle liste des clients \033[104m\///////////\033[0m\n\n");
                aff_liste(L);
                printf("\n\n");
                system("pause");
            }
            break;
            case 3 :
            {
                system("cls");
                T=Ajouter_cellule(T,L);
                save_newData(&T,newData);
                insert_to_data(newData);
                L=insertion_debut(L,T);
                system("cls");
                printf("\n\033[104m\//////////\033[105m\ la nouvelle liste des clients \033[104m\///////////\033[0m\n\n");
                aff_liste(L);
                printf("\n\n");
                system("pause");
            }
            break;
            case 4 :
            {
                system("cls");
                do
                {
                    printf("\n\t Tapez le codeID de client que vous voulez supprimer : ");
                    scanf("%d",&m);
                }
                while(Chercher_client(L,m) == NULL);
                L=suppression(L,m);
                delete_from_database(m);
                system("CLS");
                printf("\n\033[104m\//////////\033[105m\ la nouvelle liste des clients \033[104m\///////////\033[0m\n\n");
                aff_liste(L);
                printf("\n\n");
                system("pause");
            }
            break;
            case 5 :
            {
                system("cls");
                printf("\n\t Tapez le codeID de client(e) que vous voulez modifier ses informationts : ");
                scanf("%d",&m);
                Cm=Chercher_client(L,m);

                if(Cm==NULL)
                    printf("\n\t\033[31m\ le client que vous cherchez de modifier n'existe pas dans la liste !\033[0m\n");
                else
                {
                    modifier_client(Cm);
                    save_newData(&Cm->E,newData);
                    update_database(newData,m);
                    L=Update_client(L,Cm->E,m);
                    system("CLS");
                    printf("\n\033[104m\//////////\033[105m\ Client modifie \033[104m\///////////\033[0m\n\n");
                    afficher_client(&Cm->E);
                }
                printf("\n\n");
                system("pause");
            }
            break;
            case 6 :
            {
                system("cls");
                printf("\n\t Tapez le codeID de client que vous voulez chercher : ");
                scanf("%d",&m);
                S=Chercher_client(L,m);
                if(S==NULL)
                {
                    printf("\n\t\033[31m\ le client que vous cherchez n'existe pas dans la liste !\033[0m");
                    printf("\n\n");
                    system("pause");
                }
                else
                {
                    printf("\n\033[36m\ Voici les informations de client que vous cherchez : \033[0m\n");
                    afficher_client(S);
                    printf("\n\n");
                    system("pause");
                }
            }
            break;
            case 7 :
            {
                system("cls");
                m=vrf_liste_triee(L);
                if(m==0)
                {
                    printf("\n\t\033[31m\ La liste est vide !!\033[0m");
                    printf("\n\n");
                    system("pause");
                }
                if(m==-1)
                {
                    printf("\n\t\033[31m\ La liste n'est pas triee selon la consomation ! Donc vous ne pouvez pas inserer aucun clients.\033[0m");
                    printf("\n\n");
                    system("pause");
                }
                else
                {
                    printf("\n\t Tapez les informations de client que vous voulez inserer : ");
                    T=Ajouter_cellule(T,L);
                    save_newData(&T,newData);
                    insert_to_data(newData);
                    L=insertion_milieu(L,T);
                    system("cls");
                    printf("\n\033[104m\//////////\033[105m\ la nouvelle liste des clients \033[104m\///////////\033[0m\n\n");
                    aff_liste(L);
                    printf("\n\n");
                    system("pause");
                }
            }
            break;
            case 8 :
            {
                system("cls");
                printf("\n\033[32m\ La liste est triee selon la consomation par ordre decroissant : \033[0m\n");
                L=trier_liste(L);
                aff_liste(L);
                printf("\n\n");
                system("pause");
            }
            break;
            case 9 :
            {
                system("cls");
                S=Trouver_max(L);
                printf("\n\033[36m\ Voici les informations de client(e) qui a la plus grande consomation (le Meilleur client): \033[0m\n");
                afficher_client(S);
                printf("\n\n");
                system("pause");
            }
            break;
            case 10 :
            {
                system("cls");
                S=Trouver_min(L);
                printf("\n\033[36m\ Voici les informations de client qui a la plus petite consomation (): \033[0m\n");
                afficher_client(S);
                printf("\n\n");
                system("pause");
            }
            break;
            case 11 :
            {
                system("cls");
                printf("\n\033[92m\ La liste est triee selon les noms des clients par ordre alphabetique : \033[0m\n");
                L=trier_alphabie(L);
                aff_liste(L);
                printf("\n\n");
                system("pause");
            }
            break;
            case 12 :
            {
                system("cls");
                printf("\n le nombre des clients enregistres dans la liste est : \033[31m\%d\033[0m",calcul_nb_client(L));
                printf("\n\n");
                system("pause");
            }
            break;
            case 13 :
            {
                system("cls");
                printf("\n Revenu mensuel du restaurant : \033[31m\%2.f$\033[0m",calcul_Total(L));
                printf("\n\n");
                system("pause");
            }
            break;
            case 14 :
            {
                system("cls");
                printf("\n Voici l'etat de chaque client(e) de votre liste : \n\n");
                etat_client(L);
                printf("\n\n");
                system("pause");
            }
            break;
            case 15 :
            {
                system("cls");
                m=vrf_liste_alph(L);
                if(m==1)
                {
                    printf("\n\t Tapez les informations de client que vous voulez inserer : ");
                    T=Ajouter_cellule(T,L);
                    save_newData(&T,newData);
                    insert_to_data(newData);
                    L=insert_mil_alph(L,T);
                    system("cls");
                    printf("\n\033[104m\//////////\033[105m\ la nouvelle liste des clients \033[104m\///////////\033[0m\n\n");
                    aff_liste(L);
                    printf("\n\n");
                    system("pause");
                }
                else
                {
                    printf("\n\033[31m\ La liste n'est pas triee ! Donc vous ne pouvez pas inserer aucun client(e).\033[0m");
                    printf("\n\n");
                    system("pause");
                }
            }
            break;
            case 16:
            {
                system("cls");
                printf("\n\033[105m\ Voici la liste de commentaires:\033[0m\n\n");
                affiche_comment(C);
                printf("\n\n");
                system("pause");
            }
            break;
            case 17 :
            {
                system("cls");
                contenu=contenu_corbeille(contenu,T);
                if(contenu==NULL)
                {
                    printf("\n\t\033[31m\ La corbeille est vide !! aucun client deja supprime \033[0m \n");
                    printf("\n\n");
                    system("pause");
                }
                else
                {
                    printf("\n\033[104m\ Voici le contenu de la corbeille\033[0m\n\n");
                    aff_liste(contenu);
                    printf("\n\t\t\t\033[36m\  ||=====================================||");
                    printf("\n\t\t\t |||\033[33m\ 1->Recuperer les elements suppremes \033[36m\|||");
                    printf("\n\t\t\t||||\033[33m\ 2->Vider la corbeilles              \033[36m\||||");
                    printf("\n\t\t\t |||\033[33m\ 3->Sortir                           \033[36m\|||");
                    printf("\n\t\t\t  ||=====================================||\033[0m");
                    printf("\n\n Entrez votre choix:");
                    scanf("%d",&a);
                    while(a< 1 || a >3)
                    {
                        printf("\033[31m\ Choix n'existe pas !!\033[0m\n\n");
                        printf(" Entrez votre choix:");
                        scanf("%d",&a);
                    }
                    if(a==1)
                    {
                        recuperation(contenu,L);
                        vider_corbeille();
                        system("CLS");
                        printf("\n\033[104m\ La nouvelle liste des clients : \033[0m\n");
                        aff_liste(L);
                        printf("\n\n");
                        system("pause");
                    }
                    if(a==2)
                    {
                        vider_corbeille();
                        printf("\n\t\033[32m\ La corbeille est videe\033[0m\n");
                        printf("\n\n");
                        system("pause");
                    }
                }
            }
            break;
            case 18 :
            {
                system("cls");
                printf("\n\t\033[32m\ Fin de traitement ! Merci beaucoup.\033[0m");
            }
            break;
            default :
                system("cls");
                printf("\n\t\033[31m\ Choix non valide\033[0m");
                printf("\n\n");
                system("pause");
                break;
            }
        }
        while(choix!=18);
    }
    else
        printf( "\n\033[31m\ Login failed. Retry later.\033[0m\n" );
    return 0;
}
void ouvrir_corbeille()
{
    FILE *corbeille=fopen("corbeille.txt","r");
    char buffer[size_max];
    if(corbeille==NULL)
    {
        vider_corbeille();
    }
}
cellule *contenu_corbeille(cellule *L,client C)
{
    FILE *data;
    int i,k,j;
    char buffer[size_max];
    char tmp[size_max];
    data=fopen("corbeille.txt","r");
    if(data==NULL)
    {
        return NULL;
    }
    while(fgets(buffer,sizeof(buffer),data))
    {
        i=k=j=0;
        C.Total=0;
        while(buffer[i]!='\0')
        {
            if(buffer[i]!=',')
            {
                tmp[j]=buffer[i];
                j++;
            }
            else k++;
            if(k==1 && buffer[i]==',')
            {
                C.codeID=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==2 && buffer[i]==',')
            {
                C.nbvisite=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==3 && buffer[i]==',')
            {
                strcpy(C.prenom,tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==4 && buffer[i]==',')
            {
                strcpy(C.nom,tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==5 && buffer[i]==',')
            {
                C.sexe=tmp[0];
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==6 && buffer[i]==',')
            {
                C.consomation.PlatPrincipal=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==7 && buffer[i]==',')
            {
                C.consomation.Aperitifs=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==8 && buffer[i]==',')
            {
                C.consomation.Dessert=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==9 && buffer[i]==',')
            {
                C.consomation.Boissons=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            i++;
        }
        C.Total+=C.consomation.Aperitifs+C.consomation.PlatPrincipal+C.consomation.Boissons+C.consomation.Dessert;
        L=insertion_fin(L,C);
    }
    return L;
}
void vider_corbeille()
{
    FILE *data=fopen("corbeille.txt","w");
    if(data==NULL)
        printf("\n La corbeille ne sera pas videe");
    fclose(data);
}
void recuperation(cellule *A,cellule *B)
{
    char newData[size_max];
    cellule *tmp =A;
    while(tmp)
    {
        save_newData(&tmp->E,newData);
        insert_to_data(newData);
        B=insertion_fin(B,tmp->E);
        tmp=tmp->next;
    }
    vider_corbeille();
}
void modifier_client(cellule *C)
{
    int choix;
    do
    {
        system("cls");
        printf("\t\033[35m\/////////////////\033[31m\***\033[34m\MODIFICATIONS\033[31m\***\033[35m\////////////////////\033[0m");
        printf("\n\n\t\033[33m\ 1- Modifier les informations personnelles ");
        printf("\n\t 2- Modifier les consomations ");
        printf("\n\t 3- Sortir\033[0m");
        printf("\n\n Entrez votre choix:");
        scanf("%d",&choix);
        while(choix< 1 || choix >3)
        {
            printf("\033[31m\ Choix n'existe pas !!\033[0m\n\n");
            printf(" Entrez votre choix:");
            scanf("%d",&choix);
        }
        switch (choix)
        {
        case 1:
        {
            do
            {
                system("cls");
                printf("\t\033[35m\/////////////////\033[31m\***\033[34m\LES INFORMATIONS PERSONNELLES\033[31m\***\033[35m\////////////////////\033[0m");
                printf("\n\n\t\033[33m\ 1- Modifier le code ID \n");
                printf("\t 2- Modifier le nom  \n");
                printf("\t 3- Modifier le prenom \n");
                printf("\t 4- Modifier le sexe \n");
                printf("\t 5-Retour \033[0m\n\n");
                printf(" Entrez votre choix:");
                scanf("%d",&choix);
                while(choix< 1 || choix >5)
                {
                    printf("\033[31m\ Choix n'existe pas !!\033[0m\n\n");
                    printf(" Entrez votre choix:");
                    scanf("%d",&choix);
                }
                if(choix==1)
                {
                    printf("\n\t CodeID (3chifres): ");
                    scanf("%d",&C->E.codeID);
                }
                if(choix==2)
                {
                    printf("\n\t Nom: ");
                    fflush(stdin);
                    gets(C->E.nom);
                }
                if(choix==3)
                {
                    printf("\n\t Prenom: ");
                    fflush(stdin);
                    gets(C->E.prenom);
                }
                if(choix==4)
                {
                    printf("\n\t Homme[H/h],Femme[F/f] :");
                    scanf("%c",&C->E.sexe);
                }
                if(choix!=5)
                {
                    printf("\n\n\033[32m\ modification reussie\033[0m\n\n");
                    system("pause");
                }
            }
            while(choix!=5);
            choix=1;
            break;
        }
        case 2:
        {
            do
            {
                system("cls");
                printf("\t\033[35m\/////////////////\033[31m\***\033[34m\LES CONSOMATIONS\033[31m\***\033[35m\////////////////////\033[0m");
                printf("\n\n\t\033[33m\ 1- Modifier le nombre de visite  \n");
                printf("\t 2- Modifier les consomations du plat principal \n");
                printf("\t 3- Modifier les consomations d'apertitif \n");
                printf("\t 4- Modifier les consomations du dessert \n");
                printf("\t 5- Modifier les consomations du boissons \n");
                printf("\t 6-Retour \033[0m\n\n");
                printf(" Entrez votre choix:");
                scanf("%d",&choix);
                while(choix< 1 || choix >6)
                {
                    printf("\033[31m\ Choix n'existe pas !!\033[0m\n\n");
                    printf(" Entrez votre choix:");
                    scanf("%d",&choix);
                }
                if(choix==1)
                {
                    do
                    {
                        printf("\n\t Nombre de visite : ");
                        scanf("%d",&C->E.nbvisite);
                        if(C->E.nbvisite<=0)
                            printf(" \033[31m\S'il vous plait (nombre de visite <= 0) n'a pas un sens ,Entrez 1 ou plus \033[0m \n\n");
                    }
                    while(C->E.nbvisite<=0);
                }
                if(choix==2)
                {
                    C->E.Total-=C->E.consomation.PlatPrincipal;
                    do
                    {
                        printf("\n\t Plat principal : ");
                        scanf("%f",&C->E.consomation.PlatPrincipal);
                        if (C->E.consomation.PlatPrincipal < 0 )
                            printf("\n\t\033[31m\ Veuillez entrer un nombre superieur a 0\033[0m");
                    }
                    while(C->E.consomation.PlatPrincipal < 0 );
                    C->E.Total+=C->E.consomation.PlatPrincipal;
                }
                if(choix==3)
                {
                    C->E.Total-=C->E.consomation.Aperitifs;
                    do
                    {
                        printf("\n\t Apertitifs : ");
                        scanf("%f$",&C->E.consomation.Aperitifs);
                        if (C->E.consomation.Aperitifs < 0 )
                            printf("\n\t\033[31m\ Veuillez entrer un nombre superieur a 0\033[0m");
                    }
                    while(C->E.consomation.Aperitifs < 0 );
                    C->E.Total+=C->E.consomation.Aperitifs;
                }
                if(choix==4)
                {
                    C->E.Total-=C->E.consomation.Dessert;
                    do
                    {
                        printf("\t Dessert: ");
                        scanf("%f",&C->E.consomation.Dessert);
                        if (C->E.consomation.Dessert < 0 )
                            printf("\n\t\033[31m\ Veuillez entrer un nombre superieur a 0.\033[0m\n");
                    }
                    while(C->E.consomation.Dessert < 0 );
                    C->E.Total+=C->E.consomation.Dessert;
                }
                if(choix==5)
                {
                    C->E.Total-=C->E.consomation.Boissons;
                    do
                    {
                        printf("\t Boissons : ");
                        scanf("%f",&C->E.consomation.Boissons);
                        if (C->E.consomation.Boissons < 0)
                            printf("\n\t\033[31m\ Veuillez entrer un nombre superieur a 0\033[0m");
                    }
                    while(C->E.consomation.Boissons < 0);
                    C->E.Total+=C->E.consomation.Boissons;
                }
                if(choix!=6)
                {
                    printf("\n\n\033[32m\ modification rieussite\033[0m\n\n");
                    system("pause");
                }
            }
            while(choix!=6);
            choix=2;
            break;
        }
        }
    }
    while(choix!=3);
}
void insert_to_data(char *newClient)
{
    FILE *data;
    data=fopen("database.txt","r+");
    if(data==NULL)
    {
        printf("Erreur");
    }
    else
    {
        fseek(data,0,SEEK_END);
        fprintf(data,newClient);
    }
    fclose(data);
}
void save_newData(client *C,char *newData)
{
    char tmp[20];
    sprintf(newData,"%d",C->codeID);
    strAdd(newData,",");
    sprintf(tmp,"%d",C->nbvisite);
    strAdd(newData,tmp);
    strAdd(newData,",");
    strAdd(newData,C->prenom);
    strAdd(newData,",");
    strAdd(newData,C->nom);
    strAdd(newData,",");

    memset(tmp,0,sizeof(tmp));
    tmp[0]=C->sexe;
    strAdd(newData,tmp);
    strAdd(newData,",");

    memset(tmp,0,sizeof(tmp));
    sprintf(tmp,"%2.f",C->consomation.PlatPrincipal);
    strAdd(newData,tmp);
    strAdd(newData,",");

    memset(tmp,0,sizeof(tmp));
    sprintf(tmp,"%2.f",C->consomation.Aperitifs);
    strAdd(newData,tmp);
    strAdd(newData,",");

    memset(tmp,0,sizeof(tmp));
    sprintf(tmp,"%2.f",C->consomation.Dessert);
    strAdd(newData,tmp);
    strAdd(newData,",");

    memset(tmp,0,sizeof(tmp));
    sprintf(tmp,"%2.f",C->consomation.Boissons);
    strAdd(newData,tmp);
    strAdd(newData,",\n");
}
void remplacing_database_for_update()
{
    FILE *DB=fopen("database.txt","w");
    FILE *newDB=fopen("datamodifiee.txt","r");
    char buffer[size_max];
    if(DB==NULL || newDB==NULL)
    {
        printf("\nErreur #34#\n");
        return;
    }
    while(fgets(buffer,sizeof(buffer),newDB))
    {
        fputs(buffer,DB);
    }
    fclose(newDB);
    fclose(DB);
}
void update_database(char *newdata,int id)
{
    FILE *data=fopen("database.txt","r");
    FILE *Ndata=fopen("datamodifiee.txt","w");
    char buffer[size_max];
    char tmp[4]="";
    sprintf(tmp,"%d",id);
    if(data==NULL || Ndata==NULL)
    {
        printf("\nErreur #33#\n");
        return;
    }
    if(data==NULL)
    {
        printf("\nErreur #32#\n");
        return;
    }

    while(fgets(buffer,sizeof(buffer),data))
    {
        if(strstr(buffer,tmp))
            fputs(newdata,Ndata);
        else
            fputs(buffer,Ndata);
    }

    fclose(data);
    fclose(Ndata);
    remplacing_database_for_update();
}
void remplacing_database_for_deleting()
{
    FILE *DB=fopen("database.txt","w");
    FILE *newDB=fopen("newdata.txt","r");
    char buffer[size_max];
    if(DB==NULL || newDB==NULL)
    {
        printf("\nErreur #36#\n");
        return;
    }
    while(fgets(buffer,sizeof(buffer),newDB))
    {
        fputs(buffer,DB);
    }
    fclose(newDB);
    fclose(DB);
}
void delete_from_database(int id)
{
    FILE *data=fopen("database.txt","r");
    FILE *Ndata=fopen("newdata.txt","w");
    FILE *Db_deleted=fopen("corbeille.txt","r+");
    char buffer[size_max];
    char tmp[4]="";
    sprintf(tmp,"%d",id);
    if(data==NULL || Ndata==NULL || Db_deleted==NULL)
    {
        printf("\nErreur #31#\n");
        return;
    }
    fseek(Db_deleted,0,SEEK_END);
    while(fgets(buffer,sizeof(buffer),data))
    {
        if(strstr(buffer,tmp)==NULL)
            fputs(buffer,Ndata);
        else fputs(buffer,Db_deleted);
    }

    fclose(data);
    fclose(Ndata);
    fclose(Db_deleted);

    remplacing_database_for_deleting();
}
cellule *read_database(cellule *L,client C)
{
    FILE *data;
    int i,k,j;
    char buffer[size_max];
    char tmp[size_max];
    data=fopen("database.txt","r");
    if(data==NULL)
    {
        return NULL;
    }
    while(fgets(buffer,sizeof(buffer),data))
    {
        i=k=j=0;
        C.Total=0;
        while(buffer[i]!='\0')
        {
            if(buffer[i]!=',')
            {
                tmp[j]=buffer[i];
                j++;
            }
            else k++;
            if(k==1 && buffer[i]==',')
            {
                C.codeID=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==2 && buffer[i]==',')
            {
                C.nbvisite=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==3 && buffer[i]==',')
            {
                strcpy(C.prenom,tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==4 && buffer[i]==',')
            {
                strcpy(C.nom,tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==5 && buffer[i]==',')
            {
                C.sexe=tmp[0];
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==6 && buffer[i]==',')
            {
                C.consomation.PlatPrincipal=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==7 && buffer[i]==',')
            {
                C.consomation.Aperitifs=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==8 && buffer[i]==',')
            {
                C.consomation.Dessert=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            if(k==9 && buffer[i]==',')
            {
                C.consomation.Boissons=atoi(tmp);
                memset(tmp,0,sizeof(tmp));
                j=0;
            }
            i++;
        }
        C.Total+=C.consomation.Aperitifs+C.consomation.PlatPrincipal+C.consomation.Boissons+C.consomation.Dessert;
        L=insertion_fin(L,C);
    }
    return L;
}
client mode_client_ajout(client B,cellule *A)
{
    printf("\n CodeID (3chiffers): ");
    scanf("%d",&B.codeID);
    while(Chercher_client(A,B.codeID))
    {
        printf("\033[31m\ Ce code deja insere!!\033[32m\ Entrez autre\033[0m");
        printf("\n CodeID (3chiffers): ");
        scanf("%d",&B.codeID);
    }
    do
    {
        printf("\n Nombre de visite : ");
        scanf("%d",&B.nbvisite);
        if(B.nbvisite<=0)
            printf(" \033[31m\S'il vous plait (nombre de visite <= 0) n'a pas un sens ,Entrez 1 ou plus \033[0m \n\n");
    }
    while(B.nbvisite<=0);
    printf("\n Votre prenom :");
    fflush(stdin);
    gets(B.prenom);
    printf("\n Votre nom :");
    fflush(stdin);
    gets(B.nom);
    do
    {
        printf("\n Homme[H/h],Femme[F/f] :");
        fflush(stdin);
        scanf("%c",&B.sexe);
        if(B.sexe!='h' && B.sexe!='H' && B.sexe!='F' && B.sexe!='f')
            printf("\n\t\033[31m\ Etat invalide !! \033[0m\n");
    }
    while(B.sexe!='h' && B.sexe!='H' && B.sexe!='F' && B.sexe!='f');
    return B;
}
void affiche_menu()
{
    char buffer[size_max];
    FILE *menuT;
    int i=1;
    menuT=fopen("menu.txt","r");
    if(menuT==NULL)
    {
        printf("erreur file");
        exit(0);
    }
    system("cls");
    printf("\n\t\033[36m\ VOICI LE MENU:\033[0m");
    while(fgets(buffer,sizeof(buffer),menuT))
    {
        if(i<6)
            printf("\t\t\t\033[94m\%s",buffer);
        else
            printf("\t\t\t\033[33m\%s",buffer);
        i++;
    }
    printf("\033[0m\n");
    fclose(menuT);
    printf("\n\t\t\t\033[31m\   {Remarque:si vous ne voulez pas une chose,Entrez 0}\033[0m\n");
}
void demande_plat(client *B)
{
    int n;
    int Plat[7]= {0,75,80,40,30,45,50};
    int Desrt[7]= {0,50,55,60,10,70,40};
    int Aper[7]= {0,20,5,30,40,30,20};
    int Boiss[7]= {0,5,15,10,2,20,18};
    printf("\n Choisissez le numero d'un plat principal preferable:");
    scanf("%d",&n);
    while(n<0 || n>6)
    {
        printf("\n\033[31m\ S'il vous plait!!\033[0m\n Entrez un numero d'un plat principal preferable a partir du MENU:");
        scanf("%d",&n);
    }
    printf("\033[32m\  Parfait (^_^)\033[0m");
    B->Total-=B->consomation.PlatPrincipal;
    B->consomation.PlatPrincipal+=Plat[n];
    printf("\n Choisissez le numero d'un apertitif preferable:");
    scanf("%d",&n);
    while(n<0 || n>6)
    {
        printf("\n\033[31m\ S'il vous plait!!\033[0m\n Entrez un numero d'un apertitif preferable a partir du MENU:");
        scanf("%d",&n);
    }
    printf("\033[32m\  Parfait (^_^)\033[0m");
    B->Total-=B->consomation.Aperitifs;
    B->consomation.Aperitifs+=Aper[n];
    printf("\n Choisissez le numero d'un dessert preferable:");
    scanf("%d",&n);
    while(n<0 || n>6)
    {
        printf("\n\033[31m\ S'il vous plait!!\033[0m\n Entrez un numero d'un dessert preferable a partir du MENU:");
        scanf("%d",&n);
    }
    printf("\033[32m\  Parfait (^_^)\033[0m");
    B->Total-=B->consomation.Dessert;
    B->consomation.Dessert+=Desrt[n];
    printf("\n Choisissez le numero d'un boissons preferable:");
    scanf("%d",&n);
    while(n<0 || n>6)
    {
        printf("\n\033[31m\ S'il vous plait!!\033[0m\n Entrez un numero d'un boissons preferable a partir du MENU:");
        scanf("%d",&n);
    }
    printf("\033[32m\  Parfait (^_^)\033[0m");
    B->Total-=B->consomation.Boissons;
    B->consomation.Boissons+=Boiss[n];
    B->Total+=B->consomation.Aperitifs+B->consomation.PlatPrincipal+B->consomation.Boissons+B->consomation.Dessert;
}
void affiche_tables_disponibles(cellule *L)
{
    cellule *tmp=L;
    while(tmp!=NULL)
    {
        printf("\033[95m\ Table[\033[31m\%d\033[95m\]\033[0m ",tmp->table);
        tmp=tmp->next;
    }
}
cellule *insertionFin_table(cellule *L,int n)
{
    cellule *nouv=malloc(sizeof(cellule));
    nouv->table=n;
    nouv->next=NULL;
    cellule *tmp=L;
    if(L==NULL)
    {
        nouv->next=L;
        L=nouv;
        return L;
    }
    while(tmp->next!=NULL)
        tmp=tmp->next;
    tmp->next=nouv;
    return L;
}
int recherche_table(cellule *L,int n)
{
    cellule *tmp=L;
    if(L==NULL) return -1;
    while(tmp!=NULL)
    {
        if(tmp->table==n) return 1;
        tmp=tmp->next;
    }
    return 0;
}
int *mise_a_jour_table( int *T)
{
    int i,table_disponible,j;
    srand(time(NULL));
    for(i=0; i<10; i++)
    {
        do
        {
            table_disponible=(int)rand()%20;
            for(j=0; j<=i; j++)
                if(T[j]==table_disponible)
                {
                    table_disponible=-1;
                    break;
                }
        }
        while(table_disponible==-1);
        T[i]=table_disponible;
    }
    return T;
}
int *trier_table(int *T)
{
    int i,j=0,etat,tmp;
    T=mise_a_jour_table(T);
    do
    {
        etat =0;
        for(i=0; i<10-j; i++)
            if(T[i]>T[i+1])
            {
                tmp=T[i];
                T[i]=T[i+1];
                T[i+1]=tmp;
                etat=1;
            }
        j++;
    }
    while(etat);
    return T;
}
void reserver_table( cellule *L,int *T,client *B)
{
    int i,n;
    T=trier_table(T);
    for(i=0; i<10; i++)
        L=insertionFin_table(L,T[i]+1);
    system("CLS");
    printf("\n\033[36m\ LES CATEGORIES DISPONIBLES DANS LE RESTAURANT:\033[0m\n");
    printf("\n\t\033[33m\ TABLES SUR LA TERRASSE[1,2..5]{\033[31m\+15$\033[0m\033[33m\}");
    printf("\n\t TABLES INDIVIDUELLES[6,7...10]{\033[31m\+10$\033[0m\033[33m\}");
    printf("\n\t TABLES FAMILLIALES[11,12...15]{\033[31m\+00$\033[0m\033[33m\}");
    printf("\n\t\ TABLES BINOMIALLES[16,17...20]{\033[31m\+20$\033[0m\033[33m\}\033[0m\n");
    printf("\n Entrez le numero de votre choix parmi les categories au-dessus pour reserver une table:");
    scanf("%d",&n);
    while( n<1 || n>20 )
    {
        printf("\n\033[31m\ Erreur au niveau de votre choix !!\033[0m\n\n S'il vous plait Entrez un numero d'une table a partir des categories precedentes:");
        scanf("%d",&n);
    }
    if(recherche_table(L,n))
    {
        printf("\n\n\033[92m\ La table est bien reservee\033[0m\n\n");
        system("\npause");
    }
    else
    {
        if(B->sexe=='H' || B->sexe=='h')
            printf("\n\033[31m\ Desole Monsieur %s %s votre choix est deja reserve par un autre Client \033[0m\n\n033[36m\ Voici les tables disponibles:\033[0m\n\n"
                   ,B->nom,B->prenom);
        else
            printf("\n\033[31m\ Desole Madame %s %s votre choix est deja reserve par un autre Client \033[0m\n\n\033[36m\ Voici les tables disponibles:\033[0m\n\n"
                   ,B->nom,B->prenom);
        affiche_tables_disponibles(L);

        printf("\n\n Choisissez le numero de la table que vous voullez reservee:");
        scanf("%d",&n);

        while(!recherche_table(L,n))
        {
            printf("\n\033[31m\ Erreur au niveau de votre choix !!\033[0m\n\n S'il vous plait Entrez un numero d'une table disponible:");
            scanf("%d",&n);
        }
        printf("\n\n\033[32m\ La table est bien reservee\033[0m\n\n");
        system("\npause");
    }
    affiche_menu();
    if(n>15&&n<=20)
    {
        B->Total=20;
        demande_plat(B);
    }
    if(n>10&&n<=15)
    {
        B->Total=0;
        demande_plat(B);
    }
    if(n>5&&n<=10)
    {
        B->Total=10;
        demande_plat(B);
    }
    if(n>0&&n<=5)
    {
        B->Total=15;
        demande_plat(B);
    }
}
void affiche_addition(client *C)
{
    float paiement,tmp,k;
    if(C->Total<=20) C->Total+=2;
    tmp=C->Total;
    k=1;
    printf("\n VOICI VOTRE CONSOMMATION: \033[31m\TOTAL=%.2f$\033[0m\n\n",C->Total);
    do
    {
        printf(" Payez ici s'il vous plait:");
        scanf("%f",&paiement);
    }
    while(paiement<=0);
    if(tmp>paiement)
    {
        tmp=tmp-paiement;
        do
        {
            printf("\n\033[31m\ S'il vous plait il reste a payer  %.2f$ :\033[0m",tmp);
            scanf("%f",&paiement);
            tmp=tmp-paiement;
        }
        while(tmp >0);
        if(tmp!=0) k=0;
    }
    if(tmp<paiement && tmp!=0)
    {
        printf("\n\033[35m\ Le reste du paiement est \033[31m\%.2f$\033[0m\ Veuillez attendre pour le recevoir... ",k*paiement-tmp);
        sleep(6);
        system("cls");
        printf("\n\n\n \t\t\t\t\033[32m\MERCI !! POUR VOTRE VISITE \033[0m\n\n");
    }
    else
    {
        system("cls");
        printf("\n\n\n \t\t\t\t\033[32m\MERCI !! POUR VOTRE VISITE \033[0m\n\n");
    }

}
cellule *commentaire(cellule *C,char *A)
{
    cellule *nouv=malloc(sizeof(cellule));
    cellule *tmp=C;
    strcpy(nouv->comment,A);
    nouv->next=NULL;
    if(C==NULL)
        return nouv;
    while(tmp->next!=NULL)
        tmp=tmp->next;
    tmp->next=nouv;
    return C;
}
void affiche_comment(cellule *C)
{
    cellule *tmp=C;
    if(C==NULL) printf("\n\t\033[31m\ AUCUN COMMENTAIRE\033[0m\n\n");
    while(tmp!=NULL)
    {
        printf("\t\033[32m\ %s \033[0m\n",tmp->comment);
        tmp=tmp->next;
    }
}
cellule *insertion_debut(cellule *A,client B)
{
    cellule *nouv;
    nouv=(cellule*)malloc(sizeof(cellule));
    nouv->E=B;
    nouv->next=NULL;
    if(A==NULL)  return nouv;
    nouv->next=A;
    A=nouv;
    return A;
}
cellule *insertion_fin(cellule *A,client B)
{
    cellule *nouv,*tmp;
    nouv=(cellule*)malloc(sizeof(cellule));
    nouv->E=B;
    nouv->next=NULL;
    if(A==NULL)  return nouv;
    tmp=A;
    while(tmp->next!=NULL)
    {
        tmp=tmp->next;
    }
    tmp->next=nouv;
    return A;
}
void aff_liste(cellule *A)
{
    cellule *tmp;
    tmp=A;
    int i=1;
    while(tmp!=NULL)
    {
        printf("\033[105m\ Client(e) numero %d :\033[0m \n\t\t\033[36m\==============================================================================\033[0m\n",i);
        printf("\n\t\t\t codeID :\033[32m\%d\t\t\t",tmp->E.codeID);
        printf("\033[0m Nom complet :\033[32m\ %s  %s",tmp->E.prenom,tmp->E.nom);
        printf("\n\n\t\t\033[36m\============================Les prix de consomations:=========================\033[0m\n");
        printf("\n\t\t\t plat principale :\033[31m\ %.2f$\033[0m\t\t Aperitifs :\033[31m\ %.2f$\n"
               ,tmp->E.consomation.PlatPrincipal,tmp->E.consomation.Aperitifs);
        printf("\n\t\t\t\033[0m Desserts :\033[31m\ %.2f$\t\t\t\033[0m Boissons :\033[31m\ %.2f$\n"
               ,tmp->E.consomation.Dessert,tmp->E.consomation.Boissons);
        printf("\n\t\t\t\033[0m Nombre de visite :\033[31m\%d\t\t\t",tmp->E.nbvisite);
        printf("\033[0m Le total =\033[31m\ %.2f $\033[0m",tmp->E.Total);
        printf("\n\t\t\033[36m\==============================================================================\033[0m\n");
        tmp=tmp->next;
        i++;
    }
}
client Ajouter_cellule(client B,cellule *A)
{
    float s=0;
    printf("\n\t\033[104m\//////////\033[105m\ Informations personnelles \033[104m\///////////\033[0m\n");
    printf("\n\t CodeID (3chiffers): ");
    scanf("%d",&B.codeID);
    while(Chercher_client(A,B.codeID))
    {
        printf("\033[31m\ Ce code deja insere!!\033[32m\ Entrez autre\033[0m");
        printf("\n\t CodeID (3chiffers): ");
        scanf("%d",&B.codeID);
    }
    printf("\t le prenom :");
    fflush(stdin);
    gets(B.prenom);
    printf("\t le nom :");
    fflush(stdin);
    gets(B.nom);
    do
    {
        printf("\t Homme[H/h],Femme[F/f] :");
        scanf("%c",&B.sexe);
        if(B.sexe!='h' && B.sexe!='H' && B.sexe!='F' && B.sexe!='f')
            printf("\n\t\033[31m\ Etat invalide !! \033[0m\n");
    }
    while(B.sexe!='h' && B.sexe!='H' && B.sexe!='F' && B.sexe!='f');
    printf("\n\t\033[104m\//////////\033[105m\ les consomations en $ \033[104m\///////////\033[0m\n");
    do
    {
        printf("\n\t Nombre de visite : ");
        scanf("%d",&B.nbvisite);
        if(B.nbvisite<=0)
            printf(" \033[31m\S'il vous plait (nombre de visite <= 0) n'a pas un sens ,Entrez 1 ou plus \033[0m \n\n");
    }
    while(B.nbvisite<=0);
    do
    {
        printf("\n\t Apertitifs : ");
        scanf("%f",&B.consomation.Aperitifs);
        if (B.consomation.Aperitifs < 0 )
            printf("\n\t\033[31m\ Veuillez entrer un nombre superieur a 0\033[0m");
    }
    while(B.consomation.Aperitifs < 0 );
    do
    {
        printf("\t Plat principal : ");
        scanf("%f",&B.consomation.PlatPrincipal);
        if (B.consomation.PlatPrincipal < 0 )
            printf("\n\t\033[31m\ Veuillez entrer un nombre superieur a 0\033[0m");
    }
    while(B.consomation.PlatPrincipal < 0 );
    do
    {
        printf("\t Boissons : ");
        scanf("%f",&B.consomation.Boissons);
        if (B.consomation.Boissons < 0)
            printf("\n\t\033[31m\ Veuillez entrer un nombre superieur a 0\033[0m");
    }
    while(B.consomation.Boissons < 0);
    do
    {
        printf("\t Dessert: ");
        scanf("%f",&B.consomation.Dessert);
        if (B.consomation.Dessert < 0 )
            printf("\n\t\033[31m\ Veuillez entrer un nombre superieur a 0.\033[0m\n");
    }
    while(B.consomation.Dessert < 0 );
    s=B.consomation.Aperitifs+B.consomation.PlatPrincipal+B.consomation.Boissons+B.consomation.Dessert;
    B.Total=s;
    return B;
}
cellule *suppression(cellule *A,int nb)
{
    cellule *tmp,*p;
    tmp=A;
    if(A==NULL) return NULL;

    if(A->E.codeID==nb)
    {
        A=A->next;
        free(tmp);
        return A;
    }
    while(tmp->next!=NULL && tmp->next->E.codeID!=nb)
        tmp=tmp->next;

    if(tmp->next->E.codeID==nb)
    {
        p=tmp->next;
        tmp->next=p->next;
        free(p);
        return A;
    }
    return A;
}
cellule* Update_client(cellule *L, client T, int codeID)
{
    cellule *p = Chercher_client(L, codeID);
    if (p != NULL)
    {
        p->E = T;
        printf("\n\t\033[32m\ Modification reussie.\033[0m\n");
    }
    else
    {
        printf("\n\t\033[31m\ Client(e) ne se trouve pas dans la liste.\033[0m\n");
    }
    return L;
}
cellule *Chercher_client(cellule *A,int nb)
{
    cellule *tmp;
    tmp=A;
    while(tmp!=NULL && tmp->E.codeID!=nb)
    {
        tmp=tmp->next;
    }
    if(tmp==NULL)
        return NULL;
    return tmp;
}
int vrf_liste_triee(cellule *A)
{
    cellule *tmp=A,*p;
    if(tmp==NULL)
        return 0;
    p=tmp->next;

    while(p!=NULL)
    {
        if(tmp->E.Total < p->E.Total)
            return -1;
        tmp=tmp->next;
        p=p->next;
    }
    return 1;
}
cellule *insertion_milieu(cellule *A,client B)
{
    cellule *nouveau,*tmp,*p;
    nouveau = (cellule*)malloc(sizeof(cellule));
    nouveau->E=B;
    nouveau->next=NULL;
    if(A==NULL)      return nouveau;
    tmp=A;
    p=A;
    while(tmp!=NULL)
    {
        if(A->E.Total < B.Total)
        {
            nouveau->next=tmp;
            A=nouveau;
            return A;
        }
        else if(tmp->E.Total < B.Total)
        {
            nouveau->next=tmp;
            p->next=nouveau;
            return A;
        }
        p=tmp;
        tmp=tmp->next;
    }
    nouveau=insertion_fin(A,B);
    return A;
}
cellule *trier_liste(cellule *A)
{
    cellule *tmp,*p;
    client C;
    for(tmp=A; tmp!=NULL; tmp=tmp->next)
    {
        for(p=tmp->next; p!=NULL; p=p->next)
        {
            if(tmp->E.Total < p->E.Total)
            {
                C=p->E;
                p->E=tmp->E;
                tmp->E=C;
            }
        }
    }
    return A;
}
cellule *Trouver_max(cellule *A)
{
    cellule *tmp,*p;
    tmp=A;
    p=tmp;
    float max;
    max=tmp->E.Total;
    while(tmp!=NULL)
    {
        if(tmp->E.Total > max)
        {
            max=tmp->E.Total;
            p=tmp;
        }
        tmp=tmp->next;
    }
    return p;
}
cellule *Trouver_min(cellule *A)
{
    cellule *tmp,*p;
    tmp=A;
    p=tmp;
    float min;
    min=tmp->E.Total;
    while(tmp!=NULL)
    {
        if(tmp->E.Total < min)
        {
            min=tmp->E.Total;
            p=tmp;
        }
        tmp=tmp->next;
    }
    return p;
}
void afficher_client(cellule *A)
{
    printf("\033[36m\================================================================================\033[0m\n");
    printf("\t codeID :\033[32m\%d\t\t\t",A->E.codeID);
    printf("\033[0m Nom complet :\033[32m\ %s  %s",A->E.prenom,A->E.nom);
    printf("\n\n\033[36m\============================Les prix de consomations:===========================\033[0m\n");
    printf("\n\t plat principale :\033[31m\ %.2f$\033[0m\t\t Aperitifs :\033[31m\ %.2f$\n"
           ,A->E.consomation.PlatPrincipal,A->E.consomation.Aperitifs);
    printf("\n\t\033[0m Desserts :\033[31m\ %.2f$\t\t\t\033[0m Boissons :\033[31m\ %.2f$\n\n"
           ,A->E.consomation.Dessert,A->E.consomation.Boissons);
    printf("\t\033[0m Nombre de visite :\033[31m\%d\t\t",A->E.nbvisite);
    printf("\033[0m Le total =\033[31m\ %.2f $\033[0m",A->E.Total);
    printf("\n\033[36m\===============================================================================\033[0m\n");

}
cellule *trier_alphabie(cellule *A)
{
    cellule *tmp,*p;
    client C;
    for(tmp=A; tmp!=NULL; tmp=tmp->next)
    {
        for(p=tmp->next; p!=NULL; p=p->next)
        {
            if(strcmp(tmp->E.nom,p->E.nom)==1)
            {
                C=p->E;
                p->E=tmp->E;
                tmp->E=C;
            }
        }
    }
    return A;
}
int calcul_nb_client(cellule *A)
{
    cellule *tmp=A;
    int i=0;
    while(tmp!=NULL)
    {
        i++;
        tmp=tmp->next;
    }
    return i;
}
float calcul_Total(cellule *A)
{
    cellule *tmp=A;
    int i=0;
    float s=0,m;
    while(tmp!=NULL)
    {
        s=s+tmp->E.Total;
        i++;
        tmp=tmp->next;
    }
    m=s;
    return m;
}
void etat_client(cellule *A)
{
    cellule *tmp=A;
    while(tmp!=NULL)
    {
        if(tmp->E.nbvisite>=4)
        {
            if(tmp->E.sexe=='H' || tmp->E.sexe=='h')
                printf("\n\t %s %s est\033[94m\ un client fidele \033[0m",tmp->E.prenom,tmp->E.nom);
            else
                printf("\n\t %s %s est\033[94m\ une cliente fidele \033[0m",tmp->E.prenom,tmp->E.nom);
        }
        else if(tmp->E.nbvisite=1)
        {
            if(tmp->E.sexe=='H' || tmp->E.sexe=='h')
                printf("\n\t %s %s est\033[94m\ un nouveau client\033[0m",tmp->E.prenom,tmp->E.nom);
            else
                printf("\n\t %s %s est\033[94m\ une nouvelle cliente\033[0m",tmp->E.prenom,tmp->E.nom);
        }
        tmp=tmp->next;
    }
}
int vrf_liste_alph(cellule *A)
{
    cellule *tmp=A,*p;
    p=tmp->next;
    while(p!=NULL)
    {
        if(strcmp(tmp->E.nom,p->E.nom)==1)
            return 0;
        tmp=tmp->next;
        p=p->next;
    }
    return 1;
}
cellule *insert_mil_alph(cellule *A,client B)
{
    cellule *nouveau,*tmp,*p;
    nouveau = (cellule*)malloc(sizeof(cellule));
    nouveau->E=B;
    nouveau->next=NULL;
    if(A==NULL)      return nouveau;

    if(strcmp(B.nom,A->E.nom)== -1)
    {
        nouveau->next=A;
        A=nouveau;
        return A;
    }
    p=A;
    tmp=A->next;
    while(tmp!=NULL)
    {
        if(strcmp(tmp->E.nom,B.nom)==1)
        {
            nouveau->next=tmp;
            p->next=nouveau;
            return A;
        }
        p=tmp;
        tmp=tmp->next;
    }
    nouveau=insertion_fin(A,B);
    return A;
}
int strComp(char s[], char t[])
{
    int i;
    for (i = 0; s[i] == t[i] && s[i] != '\0'; i++);
    if (s[i] == t[i])        return 0;
    else if (s[i] < t[i])    return -1;
    return 1;
}
void strAdd(char *A,char *B)
{
    int i,j;
    i=0;
    j=strlen(A);
    while(B[i]!='\0')
    {
        A[j]=B[i];
        j++;
        i++;
    }
    A[j]='\0';
}
void menu()
{
    system("CLS");
    printf("\n\t\t\t\033[35m\ /////////////////\033[34m\***\033[92m\MENU\033[34m\***\033[35m\/////////////////// \033[0m ");
    printf("\n\033[34m\==========================================================================================================\033[0m");
    printf("\n\t\033[33m\ 0->Afficher la liste des clients ");
    printf("\n\t 1->Ajouter plusieurs clients a la fois ");
    printf("\n\t 2->Ajouter un client(e) a la fin d'une liste ");
    printf("\n\t 3->Ajouter un client e) au debut d'une liste ");
    printf("\n\t 4->Supprimer un client(e) ");
    printf("\n\t 5->Modifier les informationts d'un client(e) ");
    printf("\n\t 6->Chercher un client(e) s'il existe ");
    printf("\n\t 7->insertion dans une liste deja triee (selon leur consomation) ");
    printf("\n\t 8->Trier la liste des clients selon leur consomation ");
    printf("\n\t 9->Afficher les informations de client(e) qui a la plus grande consomation(le Meilleur client) ");
    printf("\n\t 10->Afficher les informations client(e) qui a la plus petite consomation (^_^) ");
    printf("\n\t 11->Trier la liste des clients selon l'ordre alphabetique des noms des clients ");
    printf("\n\t 12->Calculer le nombre des client enregistres dans la liste ");
    printf("\n\t 13->Calculer Revenu mensuel du restaurant ");
    printf("\n\t 14->Afficher l'etat de chaque Clients (^_^) ");
    printf("\n\t 15->insertion dans une liste deja triee (selon l'ordre alphabetique des noms des client)");
    printf("\n\t 16->Afficher les commentaires des clients");
    printf("\n\t 17->Corbeille");
    printf("\n\t 18->Fin du traitement");
    printf("\n\033[34m\===========================================================================================================\033[0m");
}
