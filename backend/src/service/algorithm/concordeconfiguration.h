#include <string>
#include <vector>
#include <optional>

struct ConcordeConfig {
    // File e input/output
    std::string PROBLEM_FILE;                    // file TSP (obbligatorio)
    std::optional<std::string> OUTPUT_TOUR_FILE; // -o output file tour
    std::optional<std::string> INITIAL_TOUR_FILE; // -t tour iniziale
    std::optional<std::string> RESTART_FILE;     // -R file di restart

    // Modalità di esecuzione
    std::optional<bool> BRANCHING;               // se fare branching (default true)
    std::optional<bool> DFS_BRANCHING;           // -d o -y: usa DFS anziché BFS nel branching
    std::optional<bool> BOSS_MODE;                // -h esegui come boss
    std::optional<std::string> GRUNT_HOST;        // -g <host> esegui come grunt worker

    // Edge sets
    std::optional<std::string> EDGEGEN_FILE;      // -D edgegen file
    std::optional<std::string> INITIAL_EDGE_FILE; // -e file con archi iniziali
    std::optional<std::string> FULL_EDGE_FILE;    // -E file con insieme completo di archi

    // Cut settings
    std::optional<std::string> EXTRA_CUT_FILE;    // -F file con cut extra
    std::optional<std::string> CUTPOOL_FILE;      // -P cutpool file

    // Algoritmo e ottimizzazione
    std::optional<int> MAX_CHUNK_SIZE;            // -C dimensione max chunk local cuts (default 16)
    std::optional<int> BRANCH_ATTEMPTS;            // -J numero di rami tentativi
    std::optional<bool> SKIP_CUTS_AT_ROOT;         // -q non tagliare alla radice
    std::optional<bool> NO_BRANCH_ON_SUBTOUR;      // -U disabilita branching su subtour inequalities
    std::optional<bool> ONLY_BLOSSOM_POLYHEDRON;   // -i risolvi solo blossom polyhedron
    std::optional<bool> ONLY_SUBTOUR_POLYHEDRON;   // -I risolvi solo subtour polyhedron
    std::optional<bool> MULTI_PASS_CUTS;            // -m usa più passaggi di cutting

    // Randomizzazione e semina
    std::optional<int> SEED;                        // -s seme random
    std::optional<int> RANDOM_GRID_SIZE;            // -r problema random NxN grid

    // Verbosità e logging
    std::optional<bool> VERBOSE;                     // -v verbose
    std::optional<bool> FAST_CUTS_ONLY;              // -V usa solo fast cuts
    std::optional<int> WRITE_MIN_REDUCED_COST_ARCS; // -z numero archi a costo ridotto minimo scritti su file

    // Formato distanza
    std::optional<int> DISTANCE_NORM;                // -N norma distanza (default Euclidea 2)

    // Output e pulizia
    std::optional<bool> DELETE_TEMP_FILES;            // -x cancella file temporanei .sav .pul .mas

    // Altri parametri meno comuni
    std::optional<std::string> PROBLEM_NAME;          // -n identificatore problema
    std::optional<bool> SAVE_TOUR_AS_EDGE_FILE;       // -f salva tour come file edge
};

