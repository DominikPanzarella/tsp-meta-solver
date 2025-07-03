#include <string>
#include <vector>
#include <optional>

struct LKH3Config {
    // Mandatory
    std::string PROBLEM_FILE; // Nome file problema (obbligatorio)

    // Candidate edges & sets
    std::optional<int> ASCENT_CANDIDATES; // default 50
    std::optional<int> BACKBONE_TRIALS;  // default 0
    std::optional<bool> BACKTRACKING;     // YES/NO, default NO
    std::vector<std::string> CANDIDATE_FILE; // più files possibili
    std::optional<std::tuple<int,int,std::optional<int>>> BWTSP; // B Q L (default 0 0 1)
    std::optional<std::string> CANDIDATE_SET_TYPE; // ALPHA, DELAUNAY [PURE], NEAREST-NEIGHBOR, QUADRANT (default ALPHA)
    std::optional<int> EXCESS;              // real, default 1.0/DIMENSION
    std::optional<int> EXTRA_CANDIDATES;    // integer [SYMMETRIC], default 0
    std::optional<std::string> EXTRA_CANDIDATE_SET_TYPE; // NEAREST-NEIGHBOR, QUADRANT (default QUADRANT)

    // Gain / heuristics
    std::optional<bool> GAIN23;             // YES/NO default YES
    std::optional<bool> GAIN_CRITERION;     // YES/NO default YES
    std::optional<bool> SUBGRADIENT;        // YES/NO default YES

    // Initial tour and ascent parameters
    std::optional<int> INITIAL_PERIOD;      // default DIMENSION/2 (>=100)
    std::optional<int> INITIAL_STEP_SIZE;   // default 1
    std::optional<std::string> INITIAL_TOUR_ALGORITHM; // BORUVKA, CVRP, GREEDY, MOORE, MTSP, NEAREST-NEIGHBOR, QUICK-BORUVKA, SIERPINSKI, WALK (default WALK)
    std::optional<std::string> INITIAL_TOUR_FILE;
    std::optional<double> INITIAL_TOUR_FRACTION; // [0;1] default 1.0

    // Tours controlling search
    std::optional<std::string> INPUT_TOUR_FILE;    // file contenente tour di limitazione
    std::optional<std::string> MERGE_TOUR_FILE;    // può essere multiplo

    // Kicks and moves
    std::optional<int> KICKS;           // default 1
    std::optional<int> KICK_TYPE;       // default 0
    std::optional<bool> MAKESPAN;       // YES/NO default NO
    std::optional<int> MAX_BREADTH;     // default INT_MAX
    std::optional<int> MAX_CANDIDATES;  // integer [SYMMETRIC] default 5
    std::optional<int> MAX_SWAPS;       // default DIMENSION
    std::optional<int> MAX_TRIALS;      // default number of nodes (DIMENSION)
    std::optional<int> MOVE_TYPE;       // k-opt >=2 [SPECIAL], default 5
    std::optional<int> NONSEQUENTIAL_MOVE_TYPE; // >=4 default MOVE_TYPE + PATCHING_A + PATCHING_B -1
    std::optional<int> PATCHING_A;      // integer [RESTRICTED|EXTENDED], default 1
    std::optional<int> PATCHING_C;      // integer [RESTRICTED|EXTENDED], default 0
    std::optional<int> SUBSEQUENT_MOVE_TYPE; // integer >=2 [SPECIAL], default 0
    std::optional<bool> SUBSEQUENT_PATCHING; // YES/NO default YES

    // Optimization / stopping
    std::optional<int> OPTIMUM;         // default -LLONG_MIN
    std::optional<bool> STOP_AT_OPTIMUM; // YES/NO default YES
    std::optional<double> TIME_LIMIT;    // secondi real default DBL_MAX

    // Problem characteristics
    std::optional<int> DEPOT;           // default 1
    std::optional<std::string> COMMENT; // commenti liberi, opzionale

    // Output
    std::string OUTPUT_TOUR_FILE;
    std::optional<std::string> TOUR_FILE;        // nome file best tour scritto ogni miglioramento
    std::optional<int> TRACE_LEVEL;       // default 1

    // Misc
    std::optional<int> POPULATION_SIZE;  // default 0
    std::optional<int> PRECISION;        // default 100
    std::optional<bool> RESTRICTED_SEARCH; // YES/NO default YES
    std::optional<int> RUNS;              // default 10
    std::optional<int> SEED;              // default 1
    std::optional<int> SALESMEN;          // default 1
    std::optional<int> SCALE;             // default 1
    std::optional<std::string> SINTEF_SOLUTION_FILE; // opzionale file soluzione MTSP/VRP
    std::optional<std::string> PI_FILE;   // file Pi-values

    // Subproblem
    std::optional<int> SUBPROBLEM_SIZE; // int + (DELAUNAY|KARP|K-CENTER|K-MEANS|MOORE|SIERPINSKI) + [BORDERS] + [COMPRESSED]
    std::optional<std::string> SUBPROBLEM_TOUR_FILE;

    // MTSP / VRP parameters
    std::optional<int> MTSP_MIN_SIZE;  // default 0
    std::optional<int> MTSP_MAX_SIZE;  // default DIMENSION-1
    std::optional<std::string> MTSP_OBJECTIVE; // MINMAX, MINMAX_SIZE, MINSUM
    std::optional<std::string> MTSP_SOLUTION_FILE;
    std::optional<int> VEHICLES; // alias di SALESMEN

    // Flags for special mode
    std::optional<bool> SPECIAL; // equivale a set di parametri predefiniti

    // Altri parametri eventualmente utili da aggiungere in base a necessità
};
