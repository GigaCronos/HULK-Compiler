#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Object Object;

// Estructura de nodo para la lista enlazada
typedef struct Node {
    char *key;
    Object *value;
    struct Node *next;
} Node;

// Estructura del mapa
typedef struct Map {
    Node *head;
} Map;

// Función para crear un nuevo nodo
Node *createNode(char *key, Object *value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: no se pudo asignar memoria para el Nodo");
        exit(1);
    }
    newNode->key = strdup(key); // Copiar la clave
    newNode->value = value; // Copiar la referencia
    newNode->next = NULL;
    return newNode;
}

// Función para crear un mapa vacío
Map *createMap() {
    Map *newMap = (Map *)malloc(sizeof(Map));
    if (newMap == NULL) {
        printf("Error: no se pudo asignar memoria para el Mapa");
        exit(1);
    }
    newMap->head = NULL;
    return newMap;
}

// Función para insertar un par clave-valor en el mapa
void insert(Map *map, char *key, Object *value) {
    Node *newNode = createNode(key, value);
    newNode->next = map->head;
    map->head = newNode;
}

// Función para buscar un valor por clave
Object *get(Map *map, char *key) {
    Node *current = map->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // Clave no encontrada
}

// Función para eliminar un par clave-valor del mapa
void removeKey(Map *map, char *key) {
    Node *current = map->head;
    Node *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (previous == NULL) {
                map->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Función para liberar la memoria del mapa
void destroyMap(Map *map) {
    Node *current = map->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    free(map);
}





// Nodo de la lista enlazada
typedef struct SetNode {
    char *data;
    struct SetNode *next;
} SetNode;

// Estructura del set
typedef struct StringSet {
    SetNode *head;
} StringSet;

// Función para crear un nuevo nodo
SetNode *createSetNode(char *data) {
    SetNode *newNode = (SetNode *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: no se pudo asignar memoria para el nodo.n");
        exit(1);
    }
    newNode->data = strdup(data);
    newNode->next = NULL;
    return newNode;
}

// Función para crear un set vacío
StringSet *createStringSet() {
    StringSet *newSet = (StringSet *)malloc(sizeof(StringSet));
    if (newSet == NULL) {
        printf("Error: no se pudo asignar memoria para el set.n");
        exit(1);
    }
    newSet->head = NULL;
    return newSet;
}

// Función para verificar si un elemento está presente en el set
int contains(StringSet *set, char *data) {
    SetNode *current = set->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Función para insertar un elemento en el set
void Set_insert(StringSet *set, char *data) {
    // Si el elemento ya existe, no se hace nada
    if (contains(set, data)) {
        return;
    }

    SetNode *newNode = createSetNode(data);
    newNode->next = set->head;
    set->head = newNode;
}

// Función para eliminar un elemento del set
void removeElement(StringSet *set, char *data) {
    SetNode *current = set->head;
    SetNode *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (previous == NULL) {
                set->head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->data);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Función para liberar la memoria del set
void destroyStringSet(StringSet *set) {
    SetNode *current = set->head;
    while (current != NULL) {
        SetNode *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(set);
}




typedef struct Class{
    struct Class *Parent;
    StringSet functions;
} Class;





struct Object{
    char* real_type;
    char* current_type;
    Map attributes;
    int value;
    float rvalue;
    char* string_value;
};

Object* bool_object(int a){
    Object *new_object = (Object* )malloc(sizeof(Object));
    new_object->value=a;
    new_object->real_type="bool";
    new_object->current_type="bool";
}

Object* string_object(char* a){
    Object *new_object = (Object* )malloc(sizeof(Object));
    new_object->string_value=a;
    new_object->real_type="string";
    new_object->current_type="string";
}

Object* number_object(float a){
    Object *new_object = (Object* )malloc(sizeof(Object));
    new_object->rvalue=a;
    new_object->real_type="number";
    new_object->current_type="number";
}

int get_bool(Object* a){
    return a->value;
}

float get_number(Object* a){
    return a->rvalue;
}


char* get_string(Object *a){
    
    if(a->real_type=="string"){
        return a->string_value;
    }
    if(a->real_type=="number"){
        char* cadena=(char*)malloc(20);
        snprintf(cadena,sizeof(cadena),"%f",a->rvalue);
        return cadena;
    }
    if(a->real_type=="bool"){
        if(a->value==0){
            return "false";
        }else{
            return "true";
        }
    }
    char* f="instance of ";
    int d=strlen(a->current_type);
    char* ans=(char*)malloc(d+50);
    snprintf(ans,d+50, "%s%s",f,ans);
    return ans;
}

Object *concatenate(Object* a,Object* b){
    char *sa=get_string(a);
    char *sb=get_string(b);
    int len=strlen(sa)+strlen(sb)+3;
    char* ans=(char*)malloc(len);
    snprintf(ans,len,"%s%s",sa,sb);
    return string_object(ans);
}

int equals(Object *a,Object *b){
    if(a->real_type != b->real_type)return 0;
    if(a->rvalue != b->rvalue)return 0;
    if(a->value != b->value)return 0;
    if(!strcmp(a->string_value,b->string_value))return 0;
    Node* cura=a->attributes.head;
    Node* curb=b->attributes.head;
    while(1){
        if(cura==NULL && curb==NULL)break;
        if(cura==NULL || curb==NULL)return 0;
        if(!equals(cura->value,curb->value))return 0;
        cura=cura->next;
        curb=curb->next;
    }
    return 1;
}


Object* function_print(Object *a){
    printf(get_string(a));
    return a;
}

Object* function_sqrt(Object *a){
    return number_object(sqrtf(get_number(a)));
}

Object* function_sin(Object *a){
    return number_object(sin(get_number(a)));
}

Object* function_cos(Object *a){
    return number_object(cos(get_number(a)));
}

Object* function_exp(Object *a){
    return number_object(exp(get_number(a)));
}

Object* function_log(Object *bas,Object* arg){
    return number_object(log(get_number(arg))/log(get_number(bas)));
}

Object* function_rand(Object *a){
    return number_object((double)rand() / (double)RAND_MAX);
}



Object * function_operate(Object * Var_x, Object * Var_y){
Object * Nod_1;
Nod_1 = Var_x;
Object * Nod_2;
Nod_2 = Var_y;
Object * Nod_3;
Nod_3 = number_object(( get_number(Nod_1) + get_number(Nod_2) ));
Object * Nod_4;
Nod_4 = string_object("");
Object * Nod_5;
Nod_5 = string_object("\n");
Object * Nod_6;
Nod_6 = concatenate(Nod_3, concatenate(Nod_4, Nod_5));
Object * Nod_7;
Nod_7 = function_print(Nod_6);
Object * Nod_8;
Nod_8 = Var_x;
Object * Nod_9;
Nod_9 = Var_y;
Object * Nod_10;
Nod_10 = number_object(( get_number(Nod_8) - get_number(Nod_9) ));
Object * Nod_11;
Nod_11 = string_object("");
Object * Nod_12;
Nod_12 = string_object("\n");
Object * Nod_13;
Nod_13 = concatenate(Nod_10, concatenate(Nod_11, Nod_12));
Object * Nod_14;
Nod_14 = function_print(Nod_13);
Object * Nod_15;
Nod_15 = Var_x;
Object * Nod_16;
Nod_16 = Var_y;
Object * Nod_17;
Nod_17 = number_object(( get_number(Nod_15) * get_number(Nod_16) ));
Object * Nod_18;
Nod_18 = string_object("");
Object * Nod_19;
Nod_19 = string_object("\n");
Object * Nod_20;
Nod_20 = concatenate(Nod_17, concatenate(Nod_18, Nod_19));
Object * Nod_21;
Nod_21 = function_print(Nod_20);
Object * Nod_22;
Nod_22 = Var_x;
Object * Nod_23;
Nod_23 = Var_y;
Object * Nod_24;
Nod_24 = number_object(( get_number(Nod_22) / get_number(Nod_23) ));
Object * Nod_25;
Nod_25 = string_object("");
Object * Nod_26;
Nod_26 = string_object("\n");
Object * Nod_27;
Nod_27 = concatenate(Nod_24, concatenate(Nod_25, Nod_26));
Object * Nod_28;
Nod_28 = function_print(Nod_27);
Object * Nod_29;
Nod_29 = Nod_28;
return Nod_29;
}
int main(){
Object * Nod_51;
{
 Object * Nod_31;
Nod_31 = number_object(0);
Object * Var_a;
Object * Nod_32;
Nod_32 = Nod_31;
Var_a = Nod_31;
Object * Nod_33;
Nod_33 = string_object("Jorge");
Object * Nod_34;
Nod_34 = string_object(" ");
Object * Nod_35;
Nod_35 = string_object("Pichardo");
Object * Nod_36;
Nod_36 = concatenate(Nod_33, concatenate(Nod_34, Nod_35));
Object * Nod_37;
Nod_37 = function_print(Nod_36);
Object * Nod_38;
Nod_38 = string_object("\n");
Object * Nod_39;
Nod_39 = function_print(Nod_38);
Object * Nod_40;
Nod_40 = number_object(10);
Object * Nod_41;
Nod_41 = number_object(2);
Object * Nod_42;
Nod_42 = function_operate(Nod_40, Nod_41);
Object * Nod_43;
Nod_43 = Var_a;
Object * Nod_44;
Nod_44 = number_object(2);
*Nod_43 = *Nod_44;
Object * Nod_45;
Nod_45 = Nod_43;
Object * Nod_46;
Nod_46 = Var_a;
Object * Nod_47;
Nod_47 = number_object(4);
Object * Nod_48;
Nod_48 = number_object(pow(get_number(Nod_46), get_number(Nod_47)));
Object * Nod_49;
Nod_49 = function_print(Nod_48);
Object * Nod_50;
Nod_50 = Nod_49;
Nod_51 = Nod_32;
}
return 0;
}
