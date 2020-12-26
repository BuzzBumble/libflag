#ifndef SK_FLAGS_H
#define SK_FLAGS_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @defgroup flag_attrs
 */
#define SF_LINESIZE 1024 /**< Size of one flag line */
#define SF_FIRSTPAD 15 /**< Padding after flag name */
#define SF_SECPAD 15 /**< Padding after flag default */
/**
 * @def sf_namesize
 * Default max size of name field.
 */
#define SF_NAMESIZE 32
/**
 * @def sf_descsize
 * Default max size of the description field.
 */
#define SF_DESCSIZE 512
/**
 * @def sf_flagsinc
 * Default size to increase a flags array by when cap is reached
 */
#define SF_FLAGSINC 5

/**
 * @defgroup flagtypes
 * @brief Possible types for flags.
 */
#define SF_STRTYPE 0 /**< String type */
#define SF_INTTYPE 1 /**< Integer type */
#define SF_BOOLTYPE 2 /**< Boolean type */

/**
 * @struct sf_flag
 * @brief Generic flag struct.
 * @var name Name of flag
 * @var desc Description of flag
 * @var ftype Type described by int value
 * @see flagtypes
 */
struct sf_flag {
	char name[SF_NAMESIZE];
	char desc[SF_DESCSIZE];
	int ftype;
};

/**
 * @struct sf_flags
 * @brief Flag array representation
 * @var flags Array of flag pointers to be casted
 * @var count Number of stored flags
 * @var cap Current capacity before realloc'ing
 */
struct sf_flags {
	struct sf_flag **flags;
	int count;
	int cap;
};

/**
 * @struct sf_str
 * @see sf_flag
 * @var dval Default value (char array)
 */
struct sf_str {
	char name[SF_NAMESIZE]; // Name of flag
	char dval[SF_NAMESIZE]; // Default value
	char desc[SF_DESCSIZE]; // Short description
	int ftype;
};

/**
 * @struct sf_int
 * @see sf_flag
 * @var dval Default value (int)
 */
struct sf_int {
	char name[SF_NAMESIZE]; // Name of flag
	int dval;				// Default value
	char desc[SF_DESCSIZE]; // Short description
	int ftype;
};

/**
 * @struct sf_bool
 * @see sf_flag
 * @var dval Default value (bool)
 */
struct sf_bool {
	char name[SF_NAMESIZE]; // Name of flag
	bool dval;				// Default value
	char desc[SF_DESCSIZE]; // Short description
	int ftype;
};

/**
 * @brief Prints flags stored in fs
 *
 * @param fs struct sf_flags containing flags to be printed
 */
void sf_printFlags(const struct sf_flags *fs);

/**
 * @brief Constructor for struct sf_flags
 *
 * @param cap initial capacity of flag array
 *
 * @return new struct sf_flags
 * @note USE sf_destroyFlags TO CLEAR MEMORY
 */
struct sf_flags *sf_newFlags(int cap);

/**
 * @brief struct sf_flags destructor
 *
 * @param fs struct sf_flags to be destroyed
 */
void sf_destroyFlags(struct sf_flags *fs);

/**
 * @brief Add string flag to struct sf_flags.
 *
 * @param fs struct sf_flags to add flag to
 * @param name name of flag
 * @param dval default value of flag
 * @param desc description of flag
 *
 * @return 0 on success, -1 on failure
 */
int sf_addStrFlag(struct sf_flags *fs, char *name, char *dval, char *desc);
/**
 * @brief Add int flag to struct sf_flags.
 *
 * @param fs struct sf_flags to add flag to
 * @param name name of flag
 * @param dval default value of flag
 * @param desc description of flag
 *
 * @return 0 on success, -1 on failure
 */
int sf_addIntFlag(struct sf_flags *fs, char *name, int dval, char *desc);
/**
 * @brief Add bool flag to struct sf_flags.
 *
 * @param fs struct sf_flags to add flag to
 * @param name name of flag
 * @param dval default value of flag
 * @param desc description of flag
 *
 * @return 0 on success, -1 on failure
 */
int sf_addBoolFlag(struct sf_flags *fs, char *name, bool dval, char *desc);

#endif
