#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define size_max 250
//structure pour la relation
typedef struct relation
{
    int taille;//taille de la relation
    int max;// nombre des attributs
    char nom[size_max];
    char R[size_max];//POUR LES ATTRIBUTS DE LA RELATION
} rlt;
//structure pour les dependances fonctionnelles de la relation
typedef struct DFs
{
    int num_df;
    char DFg[size_max];
    char DFd[size_max];
    char DFg_aff[size_max];
    char DFd_aff[size_max];
} dfs;
//structure pour les cles de la relation
typedef struct keys
{
    char tmp_keys[size_max];
    char keys[size_max];
    char mini_keys[size_max];
    int nbr_keys;
    int nbr_mini_keys;
} keys;
/**DECLARATIONS POUR LES FONCTIONS UTILISEES**/
/////////////////////////////////////////////////////////////////////////////////
//FONCTIONS PRINCIPALES
void fermeture(char *Att,char *closure,dfs *D);
int valid_keys(char *Att,dfs *D,int taille);
void recherche_cles(rlt *A,dfs *D,keys *K);
//FONCTIONS ADJOINTES
keys *minimal_keys(keys *K);
void ajout_att(char *closure,char *att);
void choix_attribut(char *key,char *att);
void supprime_inutile(char *T,dfs *D,int andice);
void supprime_vergule(char *A);
void separer_partie_DFs(char *T,dfs *D,int andice);
keys *supprime_cle_double(keys*K,char *tmp);
keys *ajout_espace(keys *K,rlt *R);
bool existe_dans_fermeture(const char *closure,const char *A);
//FONCTIONS POUR LES INPUTS
dfs *input_Dfs(dfs*D);
rlt *input_relation(rlt*A);
//FONCTIONS POUR LES OUTPUTS
void affiche_keys(keys *K,rlt *R);
void affiche_relation(rlt*A);
void affiche_DF(dfs *D);
//FONCTION POUR LA SUPPRESSION ET LA REINITIALISATION
void struct_relation_init(rlt *R);
void struct_DFs_init(dfs *D);
void struct_Keys_init(keys *K);
//FONCTION POUR UNE PETITE REMARQUE
void remarque();
////////////////////////////////////////////////////////////////////////////////
//pour calculer la fermeture
void fermeture(char *Att,char *closure,dfs *D)
{
    //pour ajouter un attribut pour appliquer la fermeture
    ajout_att(closure,Att);
    int etat=1,tous_presents,i;
    while(etat)
    {
        etat=0;
        for(i=0; i<D->num_df; i++)
        {
            tous_presents=1;
            //si l'attribut ne se trouve pas dans la partie gauche des DFs
            if(existe_dans_fermeture(closure,D[i].DFg)==false)
                tous_presents=0;
            //si l'attribut se trouve dans la partie gauche et ne se trouve pas dans la partie droite des DFs
            if(tous_presents && existe_dans_fermeture(closure,D[i].DFd)==false)
            {
                ajout_att(closure,D[i].DFd); // pour ajouter l'attribut de la partie droite des DFs
                etat=1;
            }
        }
    }
}
//pour verifier si un attribut se trouve dans la partie gauche des DFs
bool existe_dans_fermeture(const char *closure,const char *A)
{
    int i=0;
    while(A[i]!='\0')
    {
        //si un attribut ne se trouve pas dans la partie gauche des DFs returne faux
        if(!strchr(closure,A[i])) return false;
        i++;
    }
    //si l'attribut se trouve dans la partie gauche des DFs return vrai
    return true;
}
//pour ajouter des attributs
void ajout_att(char *closure,char *att)
{
    int j=0;
    while(att[j]!='\0')
    {
        closure[strlen(closure)]=att[j];
        j++;
    }
    closure[strlen(closure)]='\0';
}
//pour verifier si l'ensemble choisis est une cle
int valid_keys(char *Att,dfs *D,int taille)
{
    char closure[size_max]="";
    fermeture(Att,closure,D);
// si on trouve tous les attributs apres la fermeture
    if(strlen(closure)!=taille)
        return 0; // si non
    return 1;// si oui
}
//pour verifier toutes les possibilites pour trouver une ou plusieurs cles
void recherche_cles(rlt *A,dfs *D,keys *K)
{
    int i,j;
    K->nbr_keys=0;
    // pour verifier les ((2^n)-1) possibilites
    for(i=0; i< (1 << A->max) ; i++)
    {
        char possibilite[size_max]="";
        for(j=0; j<A->max; j++)
        {
            //pour verifier si la possibilite est definie dans i (representee par i)
            if(i & (1 << j))
            {
                choix_attribut(possibilite,A[j].R);
                //pour verifier si la possibilite determine tous les attributs apres la fermeture
                if(valid_keys(possibilite,D,A->taille))
                    //pour stocker les cles trouvees dans un tableau et eviter la repetition dans le tableau
                    K=supprime_cle_double(K,possibilite);
            }
        }
    }
}
//pour choisir un attribut comme cle(possibilite)
void choix_attribut(char *key,char *att)
{
    int j=0;
    while(att[j]!='\0')
    {
        key[strlen(key)]=att[j];
        j++;
    }
    key[strlen(key)]='\0';
}
//pour stocker les cles trouvees dans un tableau et eviter la repetition dans le tableau
keys *supprime_cle_double(keys*K,char *tmp)
{
    int i,doublement=1;
    for(i=0; i<K->nbr_keys; i++)
        if(strcmp(K[i].tmp_keys,tmp)== 0)
        {
            doublement =0;
            break;
        }
    if(doublement)
    {
        ajout_att(K[K->nbr_keys].tmp_keys,tmp);
        K->nbr_keys++;
    }
    return K;
}
//pour choisir les cles minimales
keys *minimal_keys(keys *K)
{
    int i,j,k=0,mini_key;
    for(i=0; i<K->nbr_keys; i++)
    {
        mini_key=1;
        for(j=0; j<K->nbr_keys; j++)
            if( i != j && strlen(K[i].tmp_keys) > strlen(K[j].tmp_keys))
            {
                mini_key=0;
                break;
            }
        if(mini_key)
        {
            ajout_att(K[k].keys,K[i].tmp_keys);
            k++;
        }
    }
    K->nbr_mini_keys=k;
    return K;
}
//pour entrer les les DFs
dfs *input_Dfs(dfs*D)
{
    int i,k,j,m,n;
    char A[size_max];
    printf("\n\t\t\t\t\tEntrez le nombre des DFs:");
    scanf("%d",&D->num_df);
    printf("\n\t\t\t\t\tEntrez les DFs sous forme (a,..,->b,..):\n\n");
    for(i=0; i<D->num_df; i++)
    {
        printf("\t\t\t\t\tDF[%d]:",i+1);
        scanf("%s",A);
        //pour supprimer les espaces.....
        supprime_inutile(A,D,i);
        //pour separer les DFs par partie
        separer_partie_DFs(A,D,i);
    }
    return D;
}
void supprime_inutile(char *T,dfs *D,int andice)
{
    int j,n,m,k;
    j=m=n=k=0;
    while(T[j]!='\0')
    {
        if(T[j]!=',' && T[j]!=' ' && T[j]!='.' && T[j]!=';')
        {
            if(T[j]!='-' && k== 0)
            {
                D[andice].DFg[n]=T[j];
            }
            else k=1;
            if(k==1 && T[j]!= '-' && T[j]!='>')
            {
                D[andice].DFd[m]=T[j];
                m++;
            }
            n++;
        }
        j++;
    }
}
//pour l'affichage de DFs
void separer_partie_DFs(char *T,dfs *D,int andice)
{
    int j,n,m,k;
    j=m=n=k=0;
    while(T[j]!='\0')
    {

        if(T[j]!='-' && k== 0)
        {
            D[andice].DFg_aff[n]=T[j];
        }
        else k=1;
        if(k==1 && T[j]!= '-' && T[j]!='>')
        {
            D[andice].DFd_aff[m]=T[j];
            m++;
        }
        n++;
        j++;
    }
}
//pour entrer les attributs de la relation
rlt *input_relation(rlt*A)
{
    int i;
    A->taille=0;
    printf("\t\t\t///////////////////////////////////////////////////////////////////////////\n\n");
    printf("\n\t\t\t\t\tEntrez le nom de la relation:");
    scanf("%s",A->nom);
    printf("\n\t\t\t\tEntrez le nombre des attributs de cette relation:");
    scanf("%d",&A->max);
    printf("\n\n");
    for(i=0; i<A->max; i++)
    {
        printf("\t\t\t\t\tAtt[%d]:",i+1);
        scanf("%s",A[i].R);
        A->taille+=strlen(A[i].R);
    }
    printf("\n\n\t\t\t////////////////////////////////////////////////////////////////////////\n\n");
    return A;
}
//pour separer les elements des ensembles de cles trouvees par les espaces
keys *ajout_espace(keys *K,rlt *R)
{
    int i,j;
    K=minimal_keys(K);
    for(i=0; i<K->nbr_mini_keys; i++)
    {
        K[i].mini_keys[strlen(K[i].mini_keys)]=' ';
        for(j=0; j<R->max; j++)
            if(existe_dans_fermeture(K[i].keys,R[j].R)==true)
            {
                ajout_att(K[i].mini_keys,R[j].R);
                K[i].mini_keys[strlen(K[i].mini_keys)]=' ';
            }
        K[i].mini_keys[strlen(K[i].mini_keys)]='\0';
    }
    return K;
}
//pour l'affichage des clees
void affiche_keys(keys *K,rlt *R)
{
    int i;
    K=ajout_espace(K,R);
    printf("\n\t\t\t\t\tKey(s) : ");
    for(i=0; i<K->nbr_mini_keys; i++)
    {
        printf(" {%s}",K[i].mini_keys);
    }
    printf("\n\n\t\t\t/////////////////////////////////////////////////////////////////////////\n\n");
}
//pour l'affichage de la relation
void affiche_relation(rlt*A)
{
    int i;
    printf("\n\t\t\t\t\tLa relation est: %s(%s",A->nom,A->R);
    for(i=1; i<A->max; i++)
        printf(",%s",A[i].R);
    printf(")\n\n");
    printf("\t\t\t/////////////////////////////////////////////////////////////////////////\n\n");
}
//pour l'affichage des DFs
void affiche_DF(dfs *D)
{
    int i;
    printf("\n\n\t\t\t/////////////////////////////////////////////////////////////////////////\n\n");
    printf("\n\n\t\t\t\t\tDependances foctionnelles :\n\n");
    for(i=0; i<D->num_df; i++)
        printf("\t\t\t\t\t%s --> %s \n",D[i].DFg_aff,D[i].DFd_aff);
    printf("\n\n\t\t\t//////////////////////////////////////////////////////////////////////////\n\n");
}
void remarque()
{
    int i;
    for(i=0; i<25; i++)
        printf("\n");
    printf("\tNB:VOUS DEVEZ PRENDRE EN COMPTE LES REMARQUES AU SEIN DU PROGRMME POUR QU'IL FONCTIONNE BIEN AVEC VOUS!!");
    for(i=0; i<15; i++)
        printf("\n");
    printf("\t\t\t\t\t\t\twaiting...");
    sleep(5);
}
//suppression de tous les elements de la relation pour la reinitialisation
void struct_relation_init(rlt *R)
{
    int i;
    memset(R->nom,0,sizeof(R->nom));
    for(i=0; i<R->max; i++)
        memset(R[i].R,0,sizeof(R[i].R));
}
//suppression de tous les elements de dependances fonctionnelles pour la reinitialisation
void struct_DFs_init(dfs *D)
{
    int i;
    for(i=0; i<D->num_df; i++)
    {
        memset(D[i].DFg,0,sizeof(D[i].DFg));// remplacer tous les caracteres par '\0'
        memset(D[i].DFd,0,sizeof(D[i].DFd));
        memset(D[i].DFg_aff,0,sizeof(D[i].DFg_aff));
        memset(D[i].DFd_aff,0,sizeof(D[i].DFd_aff));
    }
}
//suppression de tous les elements des  cles pour la reinitialisation
void struct_Keys_init(keys *K)
{
    int i;
    for(i=0; i<K->nbr_keys; i++)
        memset(K[i].tmp_keys,0,sizeof(K[i].tmp_keys));
    for(i=0; i<K->nbr_mini_keys; i++)
    {
        memset(K[i].keys,0,sizeof(K[i].keys));
        memset(K[i].mini_keys,0,sizeof(K[i].mini_keys));
    }
}
//pour supprimer les vergules
void supprime_vergule(char *A)
{
    int i=0,j;
    while(A[i])
    {
        if(A[i]==',')
        {
            for(j=i; A[j]!='\0'; j++)
            {
                A[j]=A[j+1];
            }
            i--;
        }
        else i++;
    }
    A[strlen(A)]='\0';
}
int main()
{
    char a;
    int n,v,i;
    keys K[size_max];
    rlt T[size_max];
    dfs D[size_max];
    remarque();
    do
    {
        struct_relation_init(T);
        struct_DFs_init(D);
        struct_Keys_init(K);
        system("cls");
        printf("\t\t\t//////////////////////////////////////////////////////////////////////////\n\n");
        printf("\n\t\t\t\t\tTROUVER LES CLES D'UNE RELATION [1]:\n");
        printf("\n\t\t\t\t\tVALIDER LES CLES D'UNE RELATION [2]:\n");
        printf("\n\t\t\t\t\tARRETER LE PROGRAMME [3]:\n");
        printf("\n\n ENTREZ VOTRE CHOIX [1/2/3]:");
        scanf("%d",&n);
        system("cls");
        switch (n)
        {
        case 1:
        {
            input_relation(T);
            affiche_relation(T);
            input_Dfs(D);
            affiche_DF(D);
            recherche_cles(T,D,K);
            affiche_keys(K,T);
            break;
        }
        case 2:
        {
            input_relation(T);
            affiche_relation(T);
            input_Dfs(D);
            affiche_DF(D);
            printf("\n\n ENTREZ LE NOMBRE DES CLES QUI SERONT VALIDEES:");
            scanf("%d",&v);
            for(i=0; i<v; i++)
            {
                char cle1[size_max]="";
                char cle2[size_max]="";
                printf("\n\n ENTREZ LA CLE(%d) QUI SERA VALIDEE SOUS FORME(A,B,..): ",i+1);
                scanf("%s",&cle1);
                strcpy(cle2,cle1);
                supprime_vergule(cle1);
                if(valid_keys(cle1,D,T->taille))
                    printf("\n\n\t\t{ %s } est une cle\n",cle2);
                else printf("\n\n\t\t{ %s } n'est pas une cle\n",cle2);
            }
            break;
        }
        case 3:
        {
            system("cls");
            printf("\n\n\n\n\n\n\n\t\t\t\t\t MERCI POUR VOTRE VISITE \n\n\n\n\n\n\n");
            return 0;
        }
        default :
            printf("\n\n\tVotre choix n'existe pas\n\n");
        }
        printf("\n Pour repeter l'operation pour une autre relation entrez [y] pour arreter le programme entrez autre:\n");
        scanf("%s",&a);
    }
    while(a=='y'||a=='Y');
    system("cls");
    printf("\n\n\n\n\n\n\n\t\t\t\t\t MERCI POUR VOTRE VISITE \n\n\n\n\n\n\n");
    return (0);
}
