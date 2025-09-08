#ifndef HIST_H
    #define HIST_H

    #include <stdbool.h>

    typedef struct historico_ HIST;

    HIST* hist_criar(char proc[]);
    bool hist_apagar(HIST **hist);
    void hist_imprimir(HIST *hist);
    char *hist_get(HIST *hist);
	bool hist_set(HIST *hist, char proc[]);

#endif