#ifndef dawg_h_included__
#define dawg_h_included__

#include "common.h"
#include "dawgnode.h"

typedef struct String {
	ssize_t	length;
	char*	chars;
} String;


typedef enum {
	EMPTY,
	ACTIVE,
	CLOSED
} DAWGState;


typedef struct DAWGStatistics {
	size_t	nodes_count;
	size_t	edges_count;
	size_t	words_count;
	size_t	longest_word;

	size_t	sizeof_node;
	size_t	graph_size;
} DAWGStatistics;


typedef struct DAWG {
	DAWGNode*	q0;				///< start state
	int			count;			///< number of distinct words
	int			longest_word;	///< length of the longest word (useful when iterating through words, cheap to keep up to date)
	DAWGState	state;			///< DAWG state

	size_t		n;				///< enteries in registry
	DAWGNode**	reg;			///< registry -- valid states
	String		prev_word;		///< previosuly added word
} DAWG;


/* init DAWG structure */
static int
DAWG_init(DAWG* dawg);


/* add new word, check if new word is larger then previosuly added */
static int
DAWG_add_word(DAWG* dawg, String word);


/* add new word, but do not check word order */
static int
DAWG_add_word_unchecked(DAWG* dawg, String word);


/* clear whole DAWG */
static int
DAWG_clear(DAWG* dawg);


/* minimize remaining states and do not allow to add new words */
static int
DAWG_close(DAWG* dawg);


typedef int (*DAWG_traverse_callback)(DAWGNode* node, const size_t depth, void* extra);


/* traverse in DFS order, nodes might be visited many times;
   callback is called before visiting children
 */
static int
DAWG_traverse_DFS(DAWG* dawg, DAWG_traverse_callback callback, void* extra);


/* traverse in DFS order, nodes are visited exactly one
   callback is called after visiting children
 */
static int
DAWG_traverse_DFS_once(DAWG* dawg, DAWG_traverse_callback callback, void* extra);


/* calculate some statistics */
static void
DAWG_get_stats(DAWG* dawg, DAWGStatistics* stats);


/* find word - returns longest prefix and last visited node */
static size_t PURE
DAWG_find(DAWG* dawg, const uint8_t* word, const size_t wordlen, DAWGNode** result);


/* checks if word exists in DAWG */
static bool PURE
DAWG_exists(DAWG* dawg, const uint8_t* word, const size_t wordlen);


/* returns longest prefix of word that exists in a DAWG */
static bool PURE
DAWG_longest_prefix(DAWG* dawg, const uint8_t* word, const size_t wordlen);


#endif
