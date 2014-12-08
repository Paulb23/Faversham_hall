/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Inifile.h
   @author  P. Batty
   @brief   Implements a Ini file parser

   This module implements a ini file parser, a structure containing a
   dictionary object that can write and read to file.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Inifile.h"
#include "../ect/dictionary.h"
#include "../ect/iniparser.h"
#include "../misc/SSL_Logger.h"
#include <string.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static char *combine_cat_key(char *cat, char *key) {
	char combined[strlen(cat) + strlen(key) + 2];
	memset(combined, 0, strlen(cat) + strlen(key) + 2);
	strcat(combined, cat);
	strcat(combined, ":");
	strcat(combined, key);
	char *p = combined;
	return p;
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Inifile object.
  @return Pointer to a SSL_Inifile object on successful creation otherwise -1.

  Creates a new SSL_Inifile object with allocated memory destroy with
  SSL_Inifile_Destroy.

  If it cannot create the object it will return -1.

\-----------------------------------------------------------------------------*/
SSL_IniFile *SSL_IniFIle_Create() {
	SSL_IniFile *ini = malloc(sizeof(SSL_IniFile));

	if (!ini) {
		SSL_Log_Write("Error: Unable to allocate memory for INI file!");
		free(ini);
		return (void *)-1;
	}

	return ini;
}


/*!--------------------------------------------------------------------------
  @brief    Loads a ini file from the path
  @param    inifile       The inifile object to store the file into
  @param    path       	  The path to the file.
  @return void

  Loads the ini file from the path into the object.

\-----------------------------------------------------------------------------*/
void SSL_IniFile_Load(SSL_IniFile *inifile, char *path) {
	inifile->dictionary = iniparser_load(path);
}


/*!--------------------------------------------------------------------------
  @brief    Gets the number of sections inside the ini file
  @param    inifile       The inifile object to examine
  @return Number of sections inside the ini file else -1

  Number of sections inside the ini file return -1 on an error

\-----------------------------------------------------------------------------*/
int SSL_IniFile_GetSection_Count(SSL_IniFile *inifile) {
	return iniparser_getnsec(inifile->dictionary);
}


/*!--------------------------------------------------------------------------
  @brief    Gets the name of section inside the ini file
  @param    inifile       The inifile object to examine
  @param	n			  Section number to get the name of
  @return Section name at n else NULL

  Number of sections inside the ini file and location n, return null on error

\-----------------------------------------------------------------------------*/
char *SSL_Inifile_GetSection_Name(SSL_IniFile *inifile, int n) {
	return iniparser_getsecname(inifile->dictionary, n);
}


/*!--------------------------------------------------------------------------
  @brief    Saves the ini file in the file handler
  @param    inifile       The inifile object to save
  @param	file		   The file handler to save to.
  @return void

  Saves the ini file into the file handler passed in.

\-----------------------------------------------------------------------------*/
void SSL_Inifile_Dump(SSL_IniFile *inifile, FILE *file) {
	iniparser_dump_ini(inifile->dictionary, file);
}


/*!--------------------------------------------------------------------------
  @brief    Saves a section of the ini file in the file handler
  @param    inifile       The inifile object to save
  @param	section		   The section name to save.
  @param	file		  The file handler to save to.
  @return void

  Saves a section of the ini file into the file handler passed in.

\-----------------------------------------------------------------------------*/
void SSL_Inifile_DumpSection(SSL_IniFile *inifile, char *section, FILE *file) {
	iniparser_dumpsection_ini(inifile->dictionary, section, file);
}


/*!--------------------------------------------------------------------------
  @brief    Gets the number of keys within a given section
  @param    inifile       The inifile object to examine
  @param	section		   The section name to inspect.
  @return Number of keys in a section.

  Gets the total number of keys within a given section

\-----------------------------------------------------------------------------*/
int SSL_IniFile_GetSection_KeyCount(SSL_IniFile *inifile, char *section) {
	return iniparser_getsecnkeys(inifile->dictionary, section);
}


/*!--------------------------------------------------------------------------
  @brief    Gets the value associated with the key
  @param    inifile       The inifile object to search
  @param	catogory	  catogory that the key is in.
  @param	key			  The key to look for
  @param	notFound	  What to return if it can't find the key-value
  @return Value associated with the key as a string

  Gets the value associated with the key as a string if not found
  will return the notFound argument.

\-----------------------------------------------------------------------------*/
char *SSL_IniFile_GetString(SSL_IniFile *inifile, char *catogory, char *key, char *notFound) {
	return iniparser_getstring(inifile->dictionary, combine_cat_key(catogory, key), notFound);
}


/*!--------------------------------------------------------------------------
  @brief    Gets the value associated with the key
  @param    inifile       The inifile object to search
  @param	catogory	  catogory that the key is in.
  @param	key			  The key to look for
  @param	notFound	  What to return if it can't find the key-value
  @return Value associated with the key as a int

  Gets the value associated with the key as a int if not found
  will return the notFound argument.

\-----------------------------------------------------------------------------*/
int SSL_IniFile_GetInt(SSL_IniFile *inifile, char *catogory, char *key, int notFound) {
	return iniparser_getint(inifile->dictionary, combine_cat_key(catogory, key), notFound);
}


/*!--------------------------------------------------------------------------
  @brief    Gets the value associated with the key
  @param    inifile       The inifile object to search
  @param	catogory	  catogory that the key is in.
  @param	key			  The key to look for
  @param	notFound	  What to return if it can't find the key-value
  @return Value associated with the key as a double

  Gets the value associated with the key as a double if not found
  will return the notFound argument.

\-----------------------------------------------------------------------------*/
int SSL_IniFile_Getdouble(SSL_IniFile *inifile, char *catogory, char *key, double notFound) {
	return iniparser_getdouble(inifile->dictionary, combine_cat_key(catogory, key), notFound);
}


/*!--------------------------------------------------------------------------
  @brief    Gets the value associated with the key
  @param    inifile       The inifile object to search
  @param	catogory	  catogory that the key is in.
  @param	key			  The key to look for
  @param	notFound	  What to return if it can't find the key-value
  @return Value associated with the key as a boolean 1/0

  Gets the value associated with the key as a boolean 1/0 if not found
  will return the notFound argument.

\-----------------------------------------------------------------------------*/
int SSL_IniFile_Getboolean(SSL_IniFile *inifile, char *catogory, char *key, int notFound) {
	return iniparser_getboolean(inifile->dictionary, combine_cat_key(catogory, key), notFound);
}


/*!--------------------------------------------------------------------------
  @brief    Sets the value in the ini file
  @param    inifile       The inifile object to add the value to
  @param	catogory	  catogory to put the key in
  @param	key			  The key
  @param	value		  The value
  @return 0 on success -1 on error

  Sets a key-value at the given location, if it already exits it will modify
  the value else it will create a new entry NOT SAVED TO FILE!

\-----------------------------------------------------------------------------*/
int SSL_IniFile_Set(SSL_IniFile *inifile, char *catogory, char *key, char *value) {
	return iniparser_set(inifile->dictionary, combine_cat_key(catogory, key), value);
}


/*!--------------------------------------------------------------------------
  @brief    Removes the value in the ini file
  @param    inifile       The inifile object to remove the value from
  @param	catogory	  catogory to remove the key from
  @param	key			  The key
  @return void

  Removes a key-value at the given location NOT SAVED TO FILE!

\-----------------------------------------------------------------------------*/
void SSL_IniFile_Unset(SSL_IniFile *inifile, char *catogory, char *key) {
	iniparser_unset(inifile->dictionary, combine_cat_key(catogory, key));
}


/*!--------------------------------------------------------------------------
  @brief    Finds the value in the ini file
  @param    inifile       The inifile object examine
  @param	catogory	  catogory to search
  @param	key			  The key to search for
  @return 1 if it exists else 0

  Searches the ini file for the key, and return 1 if it exists else 0

\-----------------------------------------------------------------------------*/
int SSL_IniFile_Find(SSL_IniFile *inifile, char *catogory, char *key) {
	return iniparser_find_entry(inifile->dictionary, combine_cat_key(catogory, key));
}


/*!--------------------------------------------------------------------------
  @brief    Destroys the ini file
  @param    inifile       The inifile object to destroy
  @return 1 if it exists else 0

  Destroys the ini file.

\-----------------------------------------------------------------------------*/
void SSL_IniFile_Destroy(SSL_IniFile *inifile) {
	iniparser_freedict(inifile->dictionary);
	free(inifile);
}
