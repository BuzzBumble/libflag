#include "libflags.h"

static struct sf_str *sf_buildStrFlag(char *name, char *dval, char *desc);
static struct sf_int *sf_buildIntFlag(char *name, int dval, char *desc);
static struct sf_bool *sf_buildBoolFlag(char *name, bool dval, char *desc);

static void sf_header(char *buf);

static int sf_sftos(char *buf, const struct sf_str *strflag);
static int sf_iftos(char *buf, const struct sf_int *intflag);
static int sf_bftos(char *buf, const struct sf_bool *boolflag);
static int sf_ftos(char *buf, const struct sf_flag *flag);

struct sf_flags* sf_newFlags(int cap) {
	struct sf_flags* ret = malloc(sizeof(struct sf_flags));
	ret->flags = malloc(sizeof(struct sf_flag*) * cap);
	ret->count = 0;
	ret->cap = cap;
	return ret;
}

int sf_addBoolFlag(struct sf_flags *fs, char *name, bool dval, char *desc) {
	if (fs->count + 1 >= fs->cap) {
		fs->flags = realloc(fs->flags, sizeof(struct sf_flag*) * SF_FLAGSINC);
		fs->cap = fs->cap + SF_FLAGSINC;
	}

	struct sf_bool *f = sf_buildBoolFlag(name, dval, desc);
	fs->flags[fs->count++] = (struct sf_flag *)f;

	return 0;
}

int sf_addStrFlag(struct sf_flags *fs, char *name, char *dval, char *desc) {
	if (fs->count + 1 >= fs->cap) {
		fs->flags = realloc(fs->flags, sizeof(struct sf_flag*) * SF_FLAGSINC);
		fs->cap = fs->cap + SF_FLAGSINC;
	}

	struct sf_str *f = sf_buildStrFlag(name, dval, desc);
	fs->flags[fs->count++] = (struct sf_flag *)f;

	return 0;
}

int sf_addIntFlag(struct sf_flags *fs, char *name, int dval, char *desc) {
	if (fs->count + 1 > fs->cap) {
		fs->flags = realloc(fs->flags, sizeof(struct sf_flag*) * SF_FLAGSINC);
		fs->cap = fs->cap + SF_FLAGSINC;
	}

	struct sf_int *f = sf_buildIntFlag(name, dval, desc);
	fs->flags[fs->count++] = (struct sf_flag *)f;

	return 0;
}

static struct sf_str *sf_buildStrFlag(char *name, char *dval, char *desc) {
	struct sf_str *strflag = malloc(sizeof(struct sf_str));
	strcpy(strflag->name, name);
	strcpy(strflag->dval, dval);
	strflag->ftype = SF_STRTYPE;
	strcpy(strflag->desc, desc);

	return strflag;
}

static struct sf_int *sf_buildIntFlag(char *name, int dval, char *desc) {
	struct sf_int *intflag = malloc(sizeof(struct sf_int));
	strcpy(intflag->name, name);
	intflag->dval = dval;
	strcpy(intflag->desc, desc);
	intflag->ftype = SF_INTTYPE;

	return intflag;
}

static struct sf_bool *sf_buildBoolFlag(char *name, bool dval, char *desc) {
	struct sf_bool *boolflag = malloc(sizeof(struct sf_bool));
	strcpy(boolflag->name, name);
	boolflag->dval = dval;
	strcpy(boolflag->desc, desc);
	boolflag->ftype = SF_BOOLTYPE;

	return boolflag;
}

void sf_printFlags(const struct sf_flags *fs) {
	char *buf = malloc(sizeof(char) * SF_LINESIZE);
	sf_header(buf);
	printf("%s\n", buf);
	bzero(buf, SF_LINESIZE);
	for (size_t i = 0; i < fs->count; i++) {
		if ((sf_ftos(buf, fs->flags[i])) != -1) {
			printf("%s\n", 	buf);
			bzero(buf, SF_LINESIZE);
		}
	}
}

static int sf_sftos(char *buf, const struct sf_str *strflag) {
	return sprintf(buf, "%-*s%-*s%s",
			SF_FIRSTPAD,
			strflag->name,
			SF_SECPAD,
			strflag->dval,
			strflag->desc);
}

static int sf_iftos(char *buf, const struct sf_int *intflag) {
	return sprintf(buf, "%-*s%-*d%s",
			SF_FIRSTPAD,
			intflag->name,
			SF_SECPAD,
			intflag->dval,
			intflag->desc);
}

static int sf_bftos(char *buf, const struct sf_bool *boolflag) {
	return sprintf(buf, "%-*s%-*s%s",
			SF_FIRSTPAD,
			boolflag->name,
			SF_SECPAD,
			boolflag->dval ? "true" : "false",
			boolflag->desc);
}

static int sf_ftos(char *buf, const struct sf_flag *flag) {
	switch(flag->ftype) {
		case SF_STRTYPE:
			return sf_sftos(buf, (struct sf_str *)flag);
			break;
		case SF_INTTYPE:
			return sf_iftos(buf, (struct sf_int *)flag);
			break;
		case SF_BOOLTYPE:
			return sf_bftos(buf, (struct sf_bool *)flag);
			break;
		default:
			return -1;
	}
}

static void sf_header(char* buf) {
	sprintf(buf, "%-*s%-*s%s",
			SF_FIRSTPAD,
			"NAME",
			SF_SECPAD,
			"DEFAULT",
			"DESCRIPTION");
}

void sf_destroyFlags(struct sf_flags *fs) {
	for (int i = 0; i < fs->count; i++) {
		free(fs->flags[i]);
	}
	free(fs->flags);
	free(fs);
}
