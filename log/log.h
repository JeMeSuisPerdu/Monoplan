// DUO : ANIS LAFRAD  && GABRIEL GASNIER

#ifndef LOG_H
#define LOG_H

#include <stdio.h>

// Activer ou désactiver les logs et les tests :)
#define LOG_ON 1
#define TEST_ON 1

#if LOG_ON
    //  Macro de log avec formatage pour prendre un msg de n'importe quel type + arguments optionnels
    #define LOG(msg, ...) printf("[LOG] " msg "\n", ##__VA_ARGS__)
#else      
    // Si les logs sont désactivés, la macro LOG ne fait rien (pas de printf)
    #define LOG(msg, ...)
#endif

#if TEST_ON
    //  Macro de test avec formatage (comme LOG_ON)
    #define TEST(msg, ...) printf("[TEST] " msg "\n", ##__VA_ARGS__)
#else      
    // Si tests = désactivés, la macro TEST_ON ne fait rien
    #define TEST(msg, ...)
#endif

#endif // du LOG_H